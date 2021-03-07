/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2014 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_SceneManagement.h"
#include "E_ImportContext.h"
#include "E_SceneManager.h"


#include "../Core/Nodes/E_GroupNode.h"
//#include "../Core/States/E_State.h"
//#include "../ELibMinSG.h"
//#include "../Core/Behaviours/E_AbstractBehaviour.h"
//#include "../Core/Behaviours/E_BehaviourManager.h"
//

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
//#include <E_Util/E_Utils.h>
#include <MinSG/SceneManagement/ExportFunctions.h>
#include <MinSG/SceneManagement/ImportFunctions.h>
//#include <MinSG/SceneManagement/SceneManager.h>
#include <MinSG/SceneManagement/Exporter/WriterDAE.h>
//
//#include <Util/IO/FileName.h>

#include <MinSG/Ext/LoaderGLTF/LoaderGLTF.h>

using namespace MinSG;
using namespace MinSG::SceneManagement;

namespace E_MinSG {
namespace E_SceneManagement {

void init(EScript::Namespace & lib){
	EScript::Namespace * ns = new EScript::Namespace;
	declareConstant(&lib,"SceneManagement",ns);
	
	E_ImportContext::init(*ns);
	E_SceneManager::init(*ns);

	
	// consts
	declareConstant(ns,"IMPORT_OPTION_NONE",						static_cast<uint32_t>(IMPORT_OPTION_NONE));
	declareConstant(ns,"IMPORT_OPTION_REUSE_EXISTING_STATES",		static_cast<uint32_t>(IMPORT_OPTION_REUSE_EXISTING_STATES));
	declareConstant(ns,"IMPORT_OPTION_DAE_INVERT_TRANSPARENCY",		static_cast<uint32_t>(IMPORT_OPTION_DAE_INVERT_TRANSPARENCY));
	declareConstant(ns,"IMPORT_OPTION_USE_TEXTURE_REGISTRY",		static_cast<uint32_t>(IMPORT_OPTION_USE_TEXTURE_REGISTRY));
	declareConstant(ns,"IMPORT_OPTION_USE_MESH_HASHING_REGISTRY",	static_cast<uint32_t>(IMPORT_OPTION_USE_MESH_HASHING_REGISTRY));
	declareConstant(ns,"IMPORT_OPTION_USE_MESH_REGISTRY",			static_cast<uint32_t>(IMPORT_OPTION_USE_MESH_REGISTRY));

	//! [ESMF] ImportContext MinSG.SceneManagement.createImportContext( SceneManager, options = 0)
	ES_FUN(ns,"createImportContext",1,2,
		new E_ImportContext(createImportContext(parameter[0].to<SceneManager&>(rt), static_cast<importOption_t>(parameter[1].toInt(0)))))
		
			
	//! [ESMF] GroupNode sceneManager.loadCOLLADA( importContext,filename || SceneManager, filename, [importOptions])
	ES_FUNCTION(ns,"loadCOLLADA",2,3,{
		if(parameter[0].toType<E_ImportContext>()){
			assertParamCount(rt,parameter,2,2);
			return EScript::create(loadCOLLADA( parameter[0].to<ImportContext&>(rt), Util::FileName(parameter[1].toString())));
		}else{
			return EScript::create(loadCOLLADA(parameter[0].to<SceneManager&>(rt),
												Util::FileName(parameter[1].toString()),
												static_cast<importOption_t>(parameter[2].toInt(0) )));
		}
	})

	//! [ESMF] Array|false MinSG.SceneManagement.loadMinSGFile( importContext,filename || SceneManager,filename, [importOptions] )
	ES_FUNCTION(ns,"loadMinSGFile",2,3,{
		std::vector<Util::Reference<Node>> nodes;
		if(parameter[0].toType<E_ImportContext>()){
			assertParamCount(rt,parameter,2,2);
			nodes = loadMinSGFile(parameter[0].to<ImportContext&>(rt), Util::FileName(parameter[1].toString()));
		}else{
			nodes = loadMinSGFile(parameter[0].to<SceneManager&>(rt), Util::FileName(parameter[1].toString()),static_cast<importOption_t>(parameter[2].toInt(0)));
		}
		if(nodes.empty())
			return false;
		return EScript::Array::create(nodes);
	})

	//! [ESMF] Array|false MinSG.SceneManagement.loadMinSGString(ImportContext, String)
    ES_FUNCTION(ns,"loadMinSGString", 2, 2, {
		std::stringstream stream(parameter[1].toString());
		auto nodes = loadMinSGStream(parameter[0].to<ImportContext&>(rt), stream);
		if(nodes.empty()) 
			return false;
		return EScript::Array::create(nodes);
	})
		
	//! [ESF] bool sceneManager.saveCOLLADA(filename, root)
	ES_FUNCTION(ns,"saveCOLLADA",2,2,{
		Util::FileName file(parameter[0].toString());
		return MinSG::SceneManagement::WriterDAE::saveFile(file, parameter[1].to<MinSG::Node*>(rt));
	})
	
	//! [ESMF] void MinSG.SceneManagement.saveMeshesInSubtreeAsPLY(rootNode, dirName [,saveRegisteredNodes=false])
    ES_FUNCTION(ns,"saveMeshesInSubtreeAsPLY",2,3,{
		saveMeshesInSubtreeAsPLY(parameter[0].to<MinSG::Node*>(rt), parameter[1].toString(), parameter[2].toBool(false));
		return nullptr;
	})

	//! [ESMF] void MinSG.SceneManagement.saveMeshesInSubtreeAsMMF(rootNode, dirName [,saveRegisteredNodes=false])
    ES_FUNCTION(ns,"saveMeshesInSubtreeAsMMF",2,3,{
		saveMeshesInSubtreeAsMMF(parameter[0].to<MinSG::Node*>(rt), parameter[1].toString(), parameter[2].toBool(false));
		return nullptr;
	})
	
	//! [ESF] void MinSG.SceneManagement.saveMinSGFile(sceneManager, filename, Array nodes) 
	ES_FUNCTION(ns,"saveMinSGFile",3,3,{
		std::deque<Node *> nodes;
		for(auto & element : *parameter[2].to<EScript::Array*>(rt))
			nodes.push_back(element.to<MinSG::Node*>(rt));
		saveMinSGFile(parameter[0].to<SceneManager&>(rt),Util::FileName(parameter[1].toString()), nodes);
		return nullptr;
	})
	
	//! [ESF] String|false MinSG.SceneManagement.saveMinSGString(sceneManager,Array nodes) 
	ES_FUNCTION(ns,"saveMinSGString", 2, 2, { 
		std::deque<Node *> nodes;
		for(auto & element : *parameter[1].to<EScript::Array*>(rt))
			nodes.push_back(element.to<MinSG::Node*>(rt));
		std::stringstream stream;
		saveMinSGStream(parameter[0].to<SceneManager&>(rt),stream, nodes);
		return stream.str();
	})
	
	//! [ESMF] Array|false sceneManager.loadGLTF( importContext,filename || SceneManager,filename, [importOptions])
	ES_FUNCTION(ns,"loadGLTF",2,3,{
		std::vector<Util::Reference<Node>> nodes;
		if(parameter[0].toType<E_ImportContext>()){
			assertParamCount(rt,parameter,2,2);
			nodes = LoaderGLTF::loadGLTFScene(parameter[0].to<ImportContext&>(rt), Util::FileName(parameter[1].toString()));
		}else{
			nodes = LoaderGLTF::loadGLTFScene(parameter[0].to<SceneManager&>(rt), Util::FileName(parameter[1].toString()),static_cast<importOption_t>(parameter[2].toInt(0)));
		}
		if(nodes.empty())
			return false;
		return EScript::Array::create(nodes);
	})

}
}
}
