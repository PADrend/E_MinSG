/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_SceneManager.h"
#include "E_ImportContext.h"


#include "../Core/Nodes/E_GroupNode.h"
#include "../Core/States/E_State.h"
#include "../ELibMinSG.h"
#include "../Core/Behaviours/E_AbstractBehaviour.h"
#include "../Core/Behaviours/E_BehaviourManager.h"

#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <E_Util/E_Utils.h>
#include <MinSG/SceneManagement/ExportFunctions.h>
#include <MinSG/SceneManagement/ImportFunctions.h>
#include <MinSG/SceneManagement/SceneManager.h>
#include <MinSG/SceneManagement/Exporter/WriterDAE.h>

#include <Util/IO/FileName.h>

using namespace MinSG;
using namespace MinSG::SceneManagement;

namespace E_MinSG {

//! (static)
EScript::Type * E_SceneManager::getTypeObject() {
	// MinSG.SceneManager ----|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_SceneManager::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] new MinSG.SceneManager( )
	ES_CTOR(typeObject,0,0,new E_SceneManager)

	//! [ESMF] ImportContext MinSG.SceneManager.createImportContext( options = 0)
	ES_MFUNCTION(typeObject,SceneManager,"createImportContext",0,1,{
		importOption_t options=static_cast<importOption_t>(parameter[0].toInt(0));
		return new E_ImportContext(createImportContext(*thisObj,options));
	})

	//! [ESMF] node MinSG.SceneManager.createInstance(String id)
	ES_MFUNCTION(typeObject,SceneManager,"createInstance",1,1,{
		Node * n=thisObj->createInstance(parameter[0].toString());
		if(!n) return EScript::create(nullptr);
		return EScript::create(n);
	})

	//! [ESMF] void MinSG.SceneManager.getBehaviourManager()
	ES_MFUNCTION(typeObject,SceneManager,"getBehaviourManager",0,0,{
		return new E_BehaviourManager(thisObj->getBehaviourManager());
	})


	//! [ESMF] string|bool MinSG.SceneManager.getNameOfRegisteredNode(Node node)
	ES_MFUNCTION(typeObject,SceneManager,"getNameOfRegisteredNode",1,1,{
		Node * n=parameter[0].to<MinSG::Node*>(rt);
		std::string name=thisObj->getNameOfRegisteredNode(n);
		if(name.empty())
			return false;
		else
			return name;
	})

	//! [ESMF] string|bool MinSG.SceneManager.getNameOfRegisteredState(State state)
	ES_MFUNCTION(typeObject,SceneManager,"getNameOfRegisteredState",1,1,{
		State * s = parameter[0].to<MinSG::State*>(rt);
		std::string name=thisObj->getNameOfRegisteredState(s);
		if(name.empty())
			return false;
		else
			return name;
	})

	//! [ESMF] Array MinSG.SceneManager.getNamesOfRegisteredStates()
	ES_MFUNCTION(typeObject,SceneManager,"getNamesOfRegisteredStates",0,0,{
		std::vector<std::string> names;
		thisObj->getNamesOfRegisteredStates(names);
		return EScript::Array::create(names);
	})

	//! [ESMF] Array MinSG.SceneManager.getNamesOfRegisteredNodes()
	ES_MFUNCTION(typeObject,SceneManager,"getNamesOfRegisteredNodes",0,0,{
		std::vector<std::string> names;
		thisObj->getNamesOfRegisteredNodes(names);
		return EScript::Array::create(names);
	})
		//! [ESMF] node MinSG.SceneManager.getRegisteredNode(String id)
	ES_MFUN(typeObject,SceneManager,"getRegisteredNode",1,1,EScript::create( (thisObj->
			getRegisteredNode( parameter[0].toString() ))))


	//! [ESMF] state MinSG.SceneManager.getRegisteredState(String id)
	ES_MFUN(typeObject,SceneManager,"getRegisteredState",1,1,EScript::create( (thisObj->
			getRegisteredState(parameter[0].toString() ))))



	//! [ESMF] GroupNode MinSG.SceneManager.loadCOLLADA( importContext,filename || filename, [importOptions])
	ES_MFUNCTION(typeObject,SceneManager,"loadCOLLADA",1,2,{
		E_ImportContext * eImportContext = parameter[0].toType<E_ImportContext>();
		if(eImportContext){
			assertParamCount(rt,parameter,2,2);
			return EScript::create(loadCOLLADA( eImportContext->ref(), Util::FileName(parameter[1].toString())));
		}else{
			importOption_t options=static_cast<importOption_t>(parameter[1].toInt(0));
			return EScript::create(loadCOLLADA(*thisObj,Util::FileName(parameter[0].toString()),options ));
		}
	})

	//! [ESMF] Array|false MinSG.SceneManager.loadMinSGFile( importContext,filename || filename[,importOptions=0])
	ES_MFUNCTION(typeObject,SceneManager,"loadMinSGFile",1,2,{
		std::vector<Util::Reference<Node>> nodes;
		E_ImportContext * eImportContext = parameter[0].toType<E_ImportContext>();
		if(eImportContext){
			assertParamCount(rt,parameter,2,2);
			nodes = loadMinSGFile(eImportContext->ref(), Util::FileName(parameter[1].toString()));
			if(nodes.empty()) {
				return false;
			}
		}else{
			importOption_t options=static_cast<importOption_t>(parameter[1].toInt(0));
			nodes = loadMinSGFile(*thisObj,Util::FileName(parameter[0].toString()), options);
			if(nodes.empty()) {
				return false;
			}
		}
		return EScript::Array::create(nodes);
	})

	//! [ESMF] Array|false MinSG.SceneManager.loadMinSGString(ImportContext, String)
	ES_FUNCTION(typeObject,  "loadMinSGString", 2, 2, {
		auto & importContext = **EScript::assertType<E_ImportContext>(rt, parameter[0]);
		std::stringstream stream(parameter[1].toString());
		auto nodes = loadMinSGStream(importContext, stream);
		if(nodes.empty()) 
			return false;
		return EScript::Array::create(nodes);
	})

	//! [ESMF] self MinSG.SceneManager.registerGeometryNodes(rootNode)
	ES_MFUN(typeObject,SceneManager,"registerGeometryNodes",1,1,(thisObj->
			registerGeometryNodes( parameter[0].to<MinSG::Node*>(rt) ),thisEObj))


	//! [ESMF] self MinSG.SceneManager.registerNode([String id,] node)
	ES_MFUNCTION(typeObject,SceneManager,"registerNode",1,2,{
		if(parameter.count()==1){
			Node * n =parameter[0].to<MinSG::Node*>(rt);
			thisObj->registerNode(n);
		}else if(parameter.count()==2){
			Node * n =parameter[1].to<MinSG::Node*>(rt);
			thisObj->registerNode(parameter[0].toString(),n);
		}
		return thisEObj;
	})

	//! [ESMF] self MinSG.SceneManager.registerState([String id,] state)
	ES_MFUNCTION(typeObject,SceneManager,"registerState",1,2,{
		if(parameter.count()==1){
			State * s  = parameter[0].to<MinSG::State*>(rt);
			thisObj->registerState(s);
		}else if(parameter.count()==2){
			State * s  = parameter[1].to<MinSG::State*>(rt);
			thisObj->registerState(parameter[0].toString(),s);
		}
		return thisEObj;
	})

	//! [ESF] bool MinSG.SceneManager.saveCOLLADA(filename, root)
	ES_FUNCTION2(typeObject,"saveCOLLADA",2,2,{
		Util::FileName file(parameter[0].toString());
		Node * root = parameter[1].to<MinSG::Node*>(rt);
		bool result = MinSG::SceneManagement::WriterDAE::saveFile(file, root);
		return result;
	})

	//! [ESMF] void MinSG.SceneManager.saveMeshesInSubtreeAsPLY(rootNode, dirName [,saveRegisteredNodes=false])  \deprecated
	ES_FUNCTION(typeObject,"saveMeshesInSubtreeAsPLY",2,3,{
		saveMeshesInSubtreeAsPLY(parameter[0].to<MinSG::Node*>(rt), parameter[1].toString(), parameter[2].toBool(false));
		return nullptr;
	})

	//! [ESMF] void MinSG.SceneManager.saveMeshesInSubtreeAsMMF(rootNode, dirName [,saveRegisteredNodes=false])  \deprecated
	ES_FUNCTION(typeObject,"saveMeshesInSubtreeAsMMF",2,3,{
		saveMeshesInSubtreeAsMMF(parameter[0].to<MinSG::Node*>(rt), parameter[1].toString(), parameter[2].toBool(false));
		return nullptr;
	})

	//! [ESF] void MinSG.SceneManager.saveMinSGFile(filename, Array nodes)  \deprecated
	ES_MFUNCTION(typeObject,SceneManager,"saveMinSGFile",2,2,{
		std::deque<Node *> nodes;
		EScript::Array * array = parameter[1].to<EScript::Array*>(rt);
		for(auto & element : *array)
			nodes.push_back(element.to<MinSG::Node*>(rt));
		saveMinSGFile(*thisObj,Util::FileName(parameter[0].toString()), nodes);
		return nullptr;
	})

	//! [ESF] String|false MinSG.SceneManager.saveMinSGString(Array nodes)  \deprecated
	ES_MFUNCTION(typeObject, SceneManager,"saveMinSGString", 1, 1, { // 
		std::deque<Node *> nodes;
		EScript::Array * array = parameter[0].to<EScript::Array*>(rt);
		for(auto & element : *array)
			nodes.push_back(element.to<MinSG::Node*>(rt));
		std::stringstream stream;
		saveMinSGStream(*thisObj,stream, nodes);
		return stream.str();
	})

	//! [ESMF] self MinSG.SceneManager.unregisterNode(String id)
	ES_MFUN(typeObject,SceneManager,"unregisterNode",1,1,(thisObj->
			unregisterNode( parameter[0].toString() ),thisEObj))

	//! [ESMF] self MinSG.SceneManager.unregisterState(state)
	ES_MFUN(typeObject,SceneManager,"unregisterState",1,1,(thisObj->
			unregisterState( parameter[0].toString() ),thisEObj))


	// consts
	declareConstant(typeObject,"IMPORT_OPTION_NONE",					static_cast<uint32_t>(IMPORT_OPTION_NONE));
	declareConstant(typeObject,"IMPORT_OPTION_REUSE_EXISTING_STATES",	static_cast<uint32_t>(IMPORT_OPTION_REUSE_EXISTING_STATES));
	declareConstant(typeObject,"IMPORT_OPTION_DAE_INVERT_TRANSPARENCY",	static_cast<uint32_t>(IMPORT_OPTION_DAE_INVERT_TRANSPARENCY));
	declareConstant(typeObject,"IMPORT_OPTION_USE_TEXTURE_REGISTRY",	static_cast<uint32_t>(IMPORT_OPTION_USE_TEXTURE_REGISTRY));
	declareConstant(typeObject,"IMPORT_OPTION_USE_MESH_HASHING_REGISTRY",static_cast<uint32_t>(IMPORT_OPTION_USE_MESH_HASHING_REGISTRY));
	declareConstant(typeObject,"IMPORT_OPTION_USE_MESH_REGISTRY",		static_cast<uint32_t>(IMPORT_OPTION_USE_MESH_REGISTRY));
}

E_SceneManager::E_SceneManager(EScript::Type * type) : 
	ExtReferenceObject_t(type ? type : getTypeObject(), new MinSG::SceneManagement::SceneManager) {
}

E_SceneManager::~E_SceneManager() = default;

}
