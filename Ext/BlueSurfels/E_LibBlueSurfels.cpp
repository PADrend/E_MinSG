/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2014 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2017 Sascha Brandt <myeti@mail.uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_LibBlueSurfels.h"

#include "E_SurfelRenderer.h"

#include "Strategies/E_AbstractSurfelStrategy.h"
#include "Strategies/E_AdaptiveStrategy.h"
#include "Strategies/E_CommonStrategies.h"
#include "Strategies/E_FoveatedStrategy.h"
#include "Strategies/E_ShaderStrategy.h"

#include "Samplers/E_AbstractSurfelSampler.h"
#include "Samplers/E_GreedyCluster.h"
#include "Samplers/E_ProgressiveSampler.h"
#include "Samplers/E_RandomSampler.h"

#include "../../Core/E_FrameContext.h"
#include "../../Core/Nodes/E_Node.h"
#include "../../Core/Nodes/E_AbstractCameraNode.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <MinSG/Ext/BlueSurfels/SurfelAnalysis.h>
#include <E_Rendering/Mesh/E_Mesh.h>

namespace E_MinSG{

void BlueSurfels::init(EScript::Namespace & lib) {
	EScript::Namespace * nsBlueSurfels = new EScript::Namespace;
	declareConstant(&lib,"BlueSurfels",nsBlueSurfels);
	
	BlueSurfels::E_SurfelRenderer::init(lib); // namespace MinSG
	BlueSurfels::E_AbstractSurfelStrategy::init(*nsBlueSurfels);
	BlueSurfels::E_AdaptiveStrategy::init(*nsBlueSurfels);
	BlueSurfels::E_CommonStrategies::init(*nsBlueSurfels);
	BlueSurfels::E_FoveatedStrategy::init(*nsBlueSurfels);
	BlueSurfels::E_ShaderStrategy::init(*nsBlueSurfels);
	
	BlueSurfels::E_AbstractSurfelSampler::init(*nsBlueSurfels);
	BlueSurfels::E_GreedyCluster::init(*nsBlueSurfels);
	BlueSurfels::E_ProgressiveSampler::init(*nsBlueSurfels);
	BlueSurfels::E_RandomSampler::init(*nsBlueSurfels);
	
	//! [Number*] MinSG.BlueSurfels.getProgressiveMinimalMinimalVertexDistances(Rendering.Mesh)
	ES_FUN(nsBlueSurfels,"getProgressiveMinimalMinimalVertexDistances",1,1,
			EScript::Array::create(MinSG::BlueSurfels::getProgressiveMinimalMinimalVertexDistances(*parameter[0].to<Rendering::Mesh*>(rt))))

	//! [Number*] MinSG.BlueSurfels.getMinimalVertexDistances(Rendering.Mesh,int)
	ES_FUN(nsBlueSurfels,"getMinimalVertexDistances",2,2,
			EScript::Array::create(MinSG::BlueSurfels::getMinimalVertexDistances(*parameter[0].to<Rendering::Mesh*>(rt),parameter[1].to<uint32_t>(rt))))
	
	//! [ESMF] Number MinSG.BlueSurfels.getMedianOfNthClosestNeighbours(Rendering::Mesh& mesh, size_t prefixLength, size_t nThNeighbour)
	ES_FUN(nsBlueSurfels,"getMedianOfNthClosestNeighbours",3,3,		
			MinSG::BlueSurfels::getMedianOfNthClosestNeighbours(*parameter[0].to<Rendering::Mesh*>(rt),parameter[1].to<size_t>(rt),parameter[2].to<size_t>(rt)))
				
	//! [ESMF] Number MinSG.BlueSurfels.getPrefixForRadius(float radius, float medianDist, uint32_t medianCount, uint32_t maxCount)
	ES_FUN(nsBlueSurfels,"getPrefixForRadius",4,4,		
			MinSG::BlueSurfels::getPrefixForRadius(parameter[0].toFloat(),parameter[1].toFloat(),parameter[2].toUInt(),parameter[3].toUInt()))
			
	//! [ESMF] Number MinSG.BlueSurfels.getRadiusForPrefix(uint32_t prefixLength, float medianDist, uint32_t medianCount)
	ES_FUN(nsBlueSurfels,"getRadiusForPrefix",3,3,		
			MinSG::BlueSurfels::getRadiusForPrefix(parameter[0].toUInt(),parameter[1].toFloat(),parameter[2].toUInt()))
			
	//! [ESMF] Number MinSG.BlueSurfels.getMeterPerPixel(MinSG::FrameContext & context, MinSG::Node * node)
	ES_FUN(nsBlueSurfels,"getMeterPerPixel",2,2,		
		MinSG::BlueSurfels::getMeterPerPixel(parameter[0].to<MinSG::AbstractCameraNode*>(rt),parameter[1].to<MinSG::Node*>(rt)))
		
	//! [ESMF] Number MinSG.BlueSurfels.radiusToSize(float radius, float mpp)
	ES_FUN(nsBlueSurfels,"radiusToSize",2,2,		
			MinSG::BlueSurfels::radiusToSize(parameter[0].toFloat(),parameter[1].toFloat()))
			
	//! [ESMF] Number MinSG.BlueSurfels.sizeToRadius(float size, float mpp)
	ES_FUN(nsBlueSurfels,"sizeToRadius",2,2,		
			MinSG::BlueSurfels::sizeToRadius(parameter[0].toFloat(),parameter[1].toFloat()))
}

}
#endif // MINSG_EXT_BLUE_SURFELS

