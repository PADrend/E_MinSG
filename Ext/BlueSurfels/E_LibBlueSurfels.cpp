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
#include "Samplers/E_ScriptedSampler.h"

#include <E_Util/Graphics/E_Bitmap.h>

#include "../../Core/E_FrameContext.h"
#include "../../Core/Nodes/E_Node.h"
#include "../../Core/Nodes/E_AbstractCameraNode.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <MinSG/Ext/BlueSurfels/SurfelAnalysis.h>
#include <E_Rendering/Mesh/E_Mesh.h>

namespace E_MinSG{
using namespace MinSG::BlueSurfels;

void BlueSurfels::init(EScript::Namespace & lib) {
	EScript::Namespace * nsBlueSurfels = new EScript::Namespace;
	declareConstant(&lib,"BlueSurfels",nsBlueSurfels);
	
	//! @ingroup ext
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
	BlueSurfels::E_ScriptedSampler::init(*nsBlueSurfels);
	
	declareConstant(nsBlueSurfels,"CENTER_BB",ReferencePoint::CENTER_BB);
	declareConstant(nsBlueSurfels,"CLOSEST_BB",ReferencePoint::CLOSEST_BB);
	declareConstant(nsBlueSurfels,"CLOSEST_SURFEL",ReferencePoint::CLOSEST_SURFEL);
	declareConstant(nsBlueSurfels,"FARTHEST_BB",ReferencePoint::FARTHEST_BB);
	
	//! [Number*] MinSG.BlueSurfels.getProgressiveMinimalMinimalVertexDistances(Rendering.Mesh)
	ES_FUN(nsBlueSurfels,"getProgressiveMinimalMinimalVertexDistances",1,1,
			EScript::Array::create(MinSG::BlueSurfels::getProgressiveMinimalMinimalVertexDistances(*parameter[0].to<Rendering::Mesh*>(rt))))

	//! [Number*] MinSG.BlueSurfels.getMinimalVertexDistances(Rendering.Mesh,Number,[Bool])
	ES_FUN(nsBlueSurfels,"getMinimalVertexDistances",2,3,
			EScript::Array::create(MinSG::BlueSurfels::getMinimalVertexDistances(*parameter[0].to<Rendering::Mesh*>(rt),parameter[1].to<uint32_t>(rt), parameter[2].toBool(false))))
	
	//! [ESMF] Number MinSG.BlueSurfels.getMedianOfNthClosestNeighbours(Rendering::Mesh& mesh, size_t prefixLength, size_t nThNeighbour)
	ES_FUN(nsBlueSurfels,"getMedianOfNthClosestNeighbours",3,3,		
			MinSG::BlueSurfels::getMedianOfNthClosestNeighbours(*parameter[0].to<Rendering::Mesh*>(rt),parameter[1].to<size_t>(rt),parameter[2].to<size_t>(rt)))


	//! [ESF] Bitmap Experiments.differentialDomainAnalysis(Mesh, Number diff_max, [Number resolution, [Number count, [Bool geodetic, [Bool adaptive]]]])
	ES_FUN(nsBlueSurfels, "differentialDomainAnalysis", 2, 6, 
		EScript::create(MinSG::BlueSurfels::differentialDomainAnalysis(
			parameter[0].to<Rendering::Mesh*>(rt), parameter[1].toFloat(), 
			parameter[2].toUInt(256), parameter[3].toUInt(0), parameter[4].toBool(true), parameter[5].toBool(false))))
	
	//! [Number*] MinSG.BlueSurfels.getRadialMeanVariance(Util.Bitmap dda)
	ES_FUNCTION(nsBlueSurfels,"getRadialMeanVariance",1,1, {
		auto* a = EScript::Array::create();
		for(auto& rad : MinSG::BlueSurfels::getRadialMeanVariance(parameter[0].to<Util::Reference<Util::Bitmap>>(rt))) {
			auto obj = new EScript::ExtObject;
			obj->setAttribute("mean", EScript::Number::create(rad.mean));
			obj->setAttribute("variance", EScript::Number::create(rad.variance));
			obj->setAttribute("count", EScript::Number::create(rad.count));
			a->pushBack(obj);
		}
		return a;
	})
	
	//! [ESMF] Number MinSG.BlueSurfels.getPrefixForRadius(float radius, float packing)
	ES_FUN(nsBlueSurfels,"getPrefixForRadius",2,2,		
			MinSG::BlueSurfels::getPrefixForRadius(parameter[0].toFloat(),parameter[1].toFloat()))
			
	//! [ESMF] Number MinSG.BlueSurfels.getRadiusForPrefix(uint32_t prefix, float packing)
	ES_FUN(nsBlueSurfels,"getRadiusForPrefix",2,2,		
			MinSG::BlueSurfels::getRadiusForPrefix(parameter[0].toUInt(),parameter[1].toFloat()))
			
	//! [ESMF] Number MinSG.BlueSurfels.computeSurfelPacking(Rendering.Mesh)
	ES_FUN(nsBlueSurfels,"computeSurfelPacking",1,1,
			MinSG::BlueSurfels::computeSurfelPacking(parameter[0].to<Rendering::Mesh*>(rt)))
			
	//! [ESMF] Number MinSG.BlueSurfels.computeRelPixelSize(MinSG::FrameContext & context, MinSG::Node * node)
	ES_FUN(nsBlueSurfels,"computeRelPixelSize",2,3,
		MinSG::BlueSurfels::computeRelPixelSize(
			parameter[0].to<MinSG::AbstractCameraNode*>(rt),
			parameter[1].to<MinSG::Node*>(rt),
			static_cast<ReferencePoint>(parameter[2].toUInt(ReferencePoint::CLOSEST_SURFEL))))
		
	//! [ESMF] Number MinSG.BlueSurfels.radiusToSize(float radius, float relPixelSize)
	ES_FUN(nsBlueSurfels,"radiusToSize",2,2,
			MinSG::BlueSurfels::radiusToSize(parameter[0].toFloat(),parameter[1].toFloat()))
			
	//! [ESMF] Number MinSG.BlueSurfels.sizeToRadius(float size, float relPixelSize)
	ES_FUN(nsBlueSurfels,"sizeToRadius",2,2,
			MinSG::BlueSurfels::sizeToRadius(parameter[0].toFloat(),parameter[1].toFloat()))
}

}
#endif // MINSG_EXT_BLUE_SURFELS

