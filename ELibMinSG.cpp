/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2013 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "ELibMinSG.h"

#include "Ext/ELibMinSGExt.h"

// --

#include "Core/Behaviours/E_AbstractBehaviour.h"
#include "Core/Behaviours/E_Behavior.h"
#include "Core/Behaviours/E_BehaviorStatus.h"
#include "Core/Behaviours/E_BehaviourManager.h"
#include "Core/Behaviours/E_ScriptedBehavior.h"
#include "Core/E_FrameContext.h"
#include "Core/E_RenderParam.h"
#include "Core/E_Statistics.h"
#include "Core/Nodes/E_Node.h"
#include "Core/Nodes/E_GroupNode.h"
#include "Core/Nodes/E_LightNode.h"
#include "Core/Nodes/E_ListNode.h"
#include "Core/Nodes/E_GeometryNode.h"
#include "Core/Nodes/E_AbstractCameraNode.h"
#include "Core/Nodes/E_CameraNode.h"
#include "Core/Nodes/E_CameraNodeOrtho.h"
#include "Core/States/E_AlphaTestState.h"
#include "Core/States/E_BlendingState.h"
#include "Core/States/E_CullFaceState.h"
#include "Core/States/E_GroupState.h"
#include "Core/States/E_LightingState.h"
#include "Core/States/E_MaterialState.h"
#include "Core/States/E_NodeRendererState.h"
#include "Core/States/E_PointParameterState.h"
#include "Core/States/E_PolygonModeState.h"
#include "Core/States/E_ShaderState.h"
#include "Core/States/E_ShaderUniformState.h"
#include "Core/States/E_State.h"
#include "Core/States/E_TextureState.h"
#include "Core/States/E_TransparencyRenderer.h"

#include "SceneManagement/E_SceneManagement.h"
#include "Helper/E_GraphVizOutput.h"
#include "Helper/E_StdNodeVisitors.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <E_Geometry/E_Matrix4x4.h>

// --
#include <MinSG/MinSG.h>
#include <MinSG/Helper/Helper.h>

#include <Rendering/Serialization/Serialization.h>
#include <Rendering/Texture/TextureUtils.h>
#include <Rendering/Texture/Texture.h>
#include <Rendering/MeshUtils/MeshUtils.h>

#include <E_Rendering/Texture/E_Texture.h>
#include <E_Rendering/Mesh/E_Mesh.h>
#include <E_Rendering/E_RenderingContext.h>

#include <E_Geometry/E_Box.h>

#include <E_Util/IO/E_FileLocator.h>
#include <Util/IO/FileName.h>
#include <Util/Macros.h>

#include <map>

namespace E_MinSG {

//! init classes and Members
void init(EScript::Namespace * globals) {
	
	using namespace EScript;
	
	Namespace * lib=new Namespace();
	declareConstant(globals,"MinSG",lib);

	// ----------
	// ---- Core
	E_RenderParam::init(*lib);
	E_Node::init(*lib);
	E_GroupNode::init(*lib);
	E_ListNode::init(*lib);
	E_GeometryNode::init(*lib);
	E_FrameContext::init(*lib);
	E_Behavior::init(*lib);
	E_AbstractBehaviour::init(*lib);
	E_AbstractCameraNode::init(*lib);
	E_BehaviourManager::init(*lib);
	E_BehaviorStatus::init(*lib);
	E_CameraNode::init(*lib);
	E_CameraNodeOrtho::init(*lib);
	E_State::init(*lib);
	E_LightingState::init(*lib);
	E_LightNode::init(*lib);
	E_ShaderState::init(*lib);
	E_ShaderUniformState::init(*lib);
	E_TextureState::init(*lib);
	E_BlendingState::init(*lib);
	E_CullFaceState::init(*lib);
	E_GroupState::init(*lib);
	E_AlphaTestState::init(*lib);
	E_PointParameterState::init(*lib);
	E_PolygonModeState::init(*lib);
	E_MaterialState::init(*lib);
	E_NodeRendererState::init(*lib);
	E_ScriptedBehavior::init(*lib);
	E_Statistics::init(*lib);
	E_TransparencyRenderer::init(*lib);
	// ----------
	// ---- SceneManagement
	E_SceneManagement::init(*lib);

	// ----------
	// ---- Helper

	//! [ESF] void MinSG.changeParentKeepTransformation(Node child, GroupNode newParent)
	ES_FUNCTION(lib,"changeParentKeepTransformation",2,2, {
		auto ep = parameter[1].toType<E_GroupNode>();
		MinSG::changeParentKeepTransformation(parameter[0].to<MinSG::Node*>(rt), ep ? **ep : nullptr);
		return nullptr;
	})

	//! [ESF] Box MinSG.combineNodesWorldBBs(Array nodes)
	ES_FUNCTION(lib,"combineNodesWorldBBs",1,1, {
		std::vector<MinSG::Node*> nodes;
		for(const auto & eNode : *assertType<EScript::Array>(rt,parameter[0]))
			nodes.push_back( **EScript::assertType<E_Node>(rt,eNode));
		return EScript::create( combineNodesWorldBBs(nodes) );
	})


	//! [ESF] void MinSG.destroy(Node)
	ES_FUNCTION(lib,"destroy",1,1, {
		MinSG::Node * n=parameter[0].to<MinSG::Node*>(rt);
		MinSG::destroy(n);
		return nullptr;
	})

	//! [ESF] void MinSG.initShaderState(ShaderState, Array vsFiles, Array gsFiles, Array fsFiles, [Shader::flag_t _usage], _Util::FileLocator )
	ES_FUNCTION(lib,"initShaderState",4,6, {
		MinSG::ShaderState * s=**EScript::assertType<E_ShaderState>(rt,parameter[0]);

		EScript::Collection * c;

		c = EScript::assertType<EScript::Collection>(rt,parameter[1]);
		std::vector<std::string> vsFiles;
		for(ERef<Iterator> iRef=c->getIterator(); !iRef->end() ;iRef->next()){
			ObjRef value=iRef->value();
			vsFiles.push_back(value.toString());
		}
		c = EScript::assertType<EScript::Collection>(rt,parameter[2]);
		std::vector<std::string> gsFiles;
		for(ERef<Iterator> iRef=c->getIterator(); !iRef->end() ;iRef->next()){
			ObjRef value=iRef->value();
			gsFiles.push_back(value.toString());
		}
		c = EScript::assertType<EScript::Collection>(rt,parameter[3]);
		std::vector<std::string> fsFiles;
		for(ERef<Iterator> iRef=c->getIterator(); !iRef->end() ;iRef->next()){
			ObjRef value=iRef->value();
			fsFiles.push_back(value.toString());
		}
				
		;
		if(parameter.count()>5){
			const Util::FileLocator searchPaths = parameter[5].to<const Util::FileLocator&>(rt);
			MinSG::initShaderState(s,vsFiles,gsFiles,fsFiles, parameter[4].toUInt(Rendering::Shader::USE_UNIFORMS | Rendering::Shader::USE_GL),searchPaths);
		}else{
			MinSG::initShaderState(s,vsFiles,gsFiles,fsFiles, parameter[4].toUInt(Rendering::Shader::USE_UNIFORMS | Rendering::Shader::USE_GL), Util::FileLocator());
		}
		
		return nullptr;
	})

	//! [ESF] MinSG.Node MinSG.loadModel(filename[,flags[,TransMat]])
	ES_FUNCTION(lib,"loadModel",1,3, {
		E_Geometry::E_Matrix4x4 *em=parameter[2].toType<E_Geometry::E_Matrix4x4>();
		Util::FileName file(parameter[0].toString());
		MinSG::Node * n=MinSG::loadModel(
			file,
			parameter[1].toUInt(0),
			em!=nullptr?&em->ref():nullptr
			);
		return EScript::create(n);
	})
	
	// ---------------------------------------------------------)

	// ----------
	// ---- Constants:
	declareConstant(lib,"VERSION",String::create(MINSG_VERSION));

	declareConstant(lib,"BOUNDING_BOXES",Number::create(MinSG::BOUNDING_BOXES));
	declareConstant(lib,"NO_GEOMETRY",Number::create(MinSG::NO_GEOMETRY));
	declareConstant(lib,"FRUSTUM_CULLING",Number::create(MinSG::FRUSTUM_CULLING));
	declareConstant(lib,"SHOW_META_OBJECTS",Number::create(MinSG::SHOW_META_OBJECTS));
	declareConstant(lib,"SHOW_COORD_SYSTEM",Number::create(MinSG::SHOW_COORD_SYSTEM));
	declareConstant(lib,"USE_WORLD_MATRIX",Number::create(MinSG::USE_WORLD_MATRIX));
	declareConstant(lib,"NO_STATES",Number::create(MinSG::NO_STATES));
	declareConstant(lib,"SKIP_RENDERER",Number::create(MinSG::SKIP_RENDERER));

	declareConstant(lib,"MESH_AUTO_CENTER",Number::create(MinSG::MESH_AUTO_CENTER));
	declareConstant(lib,"MESH_AUTO_CENTER_BOTTOM",Number::create(MinSG::MESH_AUTO_CENTER_BOTTOM));
	declareConstant(lib,"MESH_AUTO_SCALE",Number::create(MinSG::MESH_AUTO_SCALE));

	// Helper
	init_stdNodeVisitors(lib);
	GraphVizOutput::init(lib);

	// init extensions
	init_ext(globals,lib);
}

}
