/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_MULTIALGORENDERING


#include "ELib_MAR.h"
#include "E_MultiAlgoGroupNode.h"
#include "E_AlgoSelector.h"
#include "E_Region.h"
#include "E_RegionEvaluator.h"
#include "E_SampleContext.h"
#include "E_SampleStorage.h"
#include "E_SampleRegion.h"
#include "E_SurfelRenderer.h"

#include <E_Rendering/Mesh/E_Mesh.h>

#include <E_Rendering/Texture/E_Texture.h>
#include <Rendering/Texture/Texture.h>
#include <Util/Graphics/PixelAccessor.h>
#include <Util/Serialization/Serialization.h>

#include <EScript/EScript.h>


using namespace Rendering;
using namespace MinSG;
using namespace MinSG::MAR;
using namespace Util;

using namespace EScript;

namespace E_MinSG {
namespace E_MAR {

void init(EScript::Namespace * minsg) {

	Namespace * lib = new Namespace();
	declareConstant(minsg, "MAR", lib);

	E_MultiAlgoGroupNode::init(*lib);
	E_AlgoSelector::init(*lib);
	E_Region::init(*lib);
	E_RegionEvaluator::init(*lib);
	E_SampleContext::init(*lib);
	E_SampleStorage::init(*lib);
	E_SampleRegion::init(*lib);
	E_SampleResult::init(*lib);
    E_SurfelRenderer::init(*lib);

    typedef std::map<uint32_t, uint32_t> result_t;
    ES_FUNCTION(lib, "getPixelPerAlgo", 1, 1, {
                    result_t result;
                     Util::Reference<Util::Bitmap> bitmap = Util::Serialization::loadBitmap(Util::FileName(parameter[0].to<std::string>(rt)));
                    uint32_t size = bitmap->getWidth() * bitmap->getHeight();
                    uint32_t * data = reinterpret_cast<uint32_t*>(bitmap->data());
                    for(uint32_t i=0;i<size;++i){
                        result[*data]++;
                        data++;
                    }
                    auto map = EScript::Map::create();
                    map->setValue(
                    EScript::create("Sum"),
                        EScript::create(size));
                    map->setValue(
                    EScript::create("Back"),
                        EScript::create(result[Util::Color4ub(255,255,255,0).getAsUInt()]));
                    map->setValue(
                        EScript::create(MinSG::MAR::MultiAlgoGroupNode::BruteForce),
                        EScript::create(result[Util::Color4ub(222, 222, 222).getAsUInt()]));
                    map->setValue(
                        EScript::create(MinSG::MAR::MultiAlgoGroupNode::CHCpp),
                        EScript::create(result[Util::Color4ub(255, 255, 51).getAsUInt()]));
                    map->setValue(
                        EScript::create(MinSG::MAR::MultiAlgoGroupNode::CHCppAggressive),
                        EScript::create(result[Util::ColorLibrary::BLACK.getAsUInt()]));
                    map->setValue(
                        EScript::create(MinSG::MAR::MultiAlgoGroupNode::ColorCubes),
                        EScript::create(result[Util::Color4ub(255, 127, 0).getAsUInt()]));
                    map->setValue(
                        EScript::create(MinSG::MAR::MultiAlgoGroupNode::BlueSurfels),
                        EScript::create(result[Util::Color4ub(128, 177, 211).getAsUInt()]));
                    map->setValue(
                        EScript::create(MinSG::MAR::MultiAlgoGroupNode::ForceSurfels),
                        EScript::create(result[Util::ColorLibrary::BLUE.getAsUInt()]));
                    map->setValue(
                        EScript::create(MinSG::MAR::MultiAlgoGroupNode::SphericalSampling),
                        EScript::create(result[Util::Color4ub(77, 175, 74).getAsUInt()]));
                    map->setValue(
                        EScript::create(MinSG::MAR::MultiAlgoGroupNode::ClassicLOD),
                        EScript::create(result[Util::Color4ub(152, 78, 163).getAsUInt()]));
                    return map;
    });
}

}
}

#endif // MINSG_EXT_MULTIALGORENDERING
