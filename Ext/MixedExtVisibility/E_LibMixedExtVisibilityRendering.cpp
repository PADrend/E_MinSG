/*
	This file is part of the MinSG library extension MixedExtVisibility.
	Copyright (C) 2015 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_MIXED_EXTERN_VISIBILITY

#include "E_LibMixedExtVisibilityRendering.h"
//#include <E_Rendering/Mesh/E_Mesh.h>
#include "../../Core/Nodes/E_Node.h"
#include "../../Core/Nodes/E_AbstractCameraNode.h"
#include "../../Core/E_FrameContext.h"
#include <MinSG/Ext/MixedExtVisibility/Preprocessor.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_MinSG{

void MixedExtVisibility::init(EScript::Namespace & lib) {
	EScript::Namespace * ns = new EScript::Namespace;
	declareConstant(&lib,"MixedExtVisibility",ns);
	
	ES_FUNCTION(ns,"filterAndSortNodesByExtVisibility",4,4,{
		std::vector<Util::Reference<MinSG::Node>> nodes;
		for(auto& eNode: *parameter[1].to<EScript::Array*>(rt))
			nodes.push_back( eNode.to<MinSG::Node*>(rt) );

		std::vector<Util::Reference<MinSG::AbstractCameraNode>> cameras;
		for(auto& eCam: *parameter[2].to<EScript::Array*>(rt))
			cameras.push_back( eCam.to<MinSG::AbstractCameraNode*>(rt) );
		EScript::ERef<EScript::Array> result( EScript::Array::create() );
		
		for(auto& node : MinSG::MixedExtVisibility::filterAndSortNodesByExtVisibility(
															parameter[0].to<MinSG::FrameContext&>(rt),
															nodes,
															cameras,
															parameter[3].to<size_t>(rt)))
			result->pushBack(EScript::create(node));
		return result.detachAndDecrease();
	})

}

}
#endif // MINSG_EXT_MIXED_EXTERN_VISIBILITY

