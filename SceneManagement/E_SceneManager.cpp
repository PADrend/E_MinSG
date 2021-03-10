/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2014 Claudius Jähn <claudius@uni-paderborn.de>
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


#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <E_Util/E_Utils.h>
#include <MinSG/SceneManagement/SceneManager.h>


#include <Util/IO/FileName.h>

using namespace MinSG;
using namespace MinSG::SceneManagement;

namespace E_MinSG {

//! (static)
EScript::Type * E_SceneManager::getTypeObject() {
	// MinSG.SceneManagement.SceneManager ----|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_SceneManager::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] new MinSG.SceneManagement.SceneManager
	ES_CTOR(typeObject,0,0,new E_SceneManager)

	//! [ESMF] node sceneManager.createInstance(String id)
	ES_MFUNCTION(typeObject,SceneManager,"createInstance",1,1,{
		Node * n=thisObj->createInstance(parameter[0].toString());
		if(!n) return EScript::create(nullptr);
		return EScript::create(n);
	})

	//! [ESMF] void sceneManager.getBehaviourManager()
	ES_MFUNCTION(typeObject,SceneManager,"getBehaviourManager",0,0,{
		return new E_BehaviourManager(thisObj->getBehaviourManager());
	})


	//! [ESMF] string|bool sceneManager.getNameOfRegisteredNode(Node node)
	ES_MFUNCTION(typeObject,SceneManager,"getNameOfRegisteredNode",1,1,{
		Node * n=parameter[0].to<MinSG::Node*>(rt);
		std::string name=thisObj->getNameOfRegisteredNode(n);
		if(name.empty())
			return false;
		else
			return name;
	})

	//! [ESMF] string|bool sceneManager.getNameOfRegisteredState(State state)
	ES_MFUNCTION(typeObject,SceneManager,"getNameOfRegisteredState",1,1,{
		State * s = parameter[0].to<MinSG::State*>(rt);
		std::string name=thisObj->getNameOfRegisteredState(s);
		if(name.empty())
			return false;
		else
			return name;
	})

	//! [ESMF] Array sceneManager.getNamesOfRegisteredStates()
	ES_MFUNCTION(typeObject,SceneManager,"getNamesOfRegisteredStates",0,0,{
		std::vector<std::string> names;
		for(const auto & id : thisObj->getStateIds() )
			names.emplace_back(id.toString());
		return EScript::Array::create(names);
	})

	//! [ESMF] Array sceneManager.getNamesOfRegisteredNodes()
	ES_MFUNCTION(typeObject,SceneManager,"getNamesOfRegisteredNodes",0,0,{
		std::vector<std::string> names;
		for(const auto & id : thisObj->getNodeIds() )
			names.emplace_back(id.toString());
		return EScript::Array::create(names);
	})
		//! [ESMF] node sceneManager.getRegisteredNode(String id)
	ES_MFUN(typeObject,SceneManager,"getRegisteredNode",1,1,EScript::create( (thisObj->
			getRegisteredNode( parameter[0].toString() ))))


	//! [ESMF] state sceneManager.getRegisteredState(String id)
	ES_MFUN(typeObject,SceneManager,"getRegisteredState",1,1,EScript::create( (thisObj->
			getRegisteredState(parameter[0].toString() ))))




	//! [ESMF] self sceneManager.registerGeometryNodes(rootNode)
	ES_MFUN(typeObject,SceneManager,"registerGeometryNodes",1,1,(thisObj->
			registerGeometryNodes( parameter[0].to<MinSG::Node*>(rt) ),thisEObj))


	//! [ESMF] self sceneManager.registerNode([String id,] node)
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

	//! [ESMF] self sceneManager.registerState([String id,] state)
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


	//! [ESMF] self sceneManager.unregisterNode(String id)
	ES_MFUN(typeObject,SceneManager,"unregisterNode",1,1,(thisObj->
			unregisterNode( parameter[0].toString() ),thisEObj))

	//! [ESMF] self sceneManager.unregisterState(state)
	ES_MFUN(typeObject,SceneManager,"unregisterState",1,1,(thisObj->
			unregisterState( parameter[0].toString() ),thisEObj))

	// ------------------------------------------------------------
	
}

E_SceneManager::E_SceneManager(EScript::Type * type) : 
	ExtReferenceObject_t(type ? type : getTypeObject(), new MinSG::SceneManagement::SceneManager) {
}

E_SceneManager::~E_SceneManager() = default;

}
