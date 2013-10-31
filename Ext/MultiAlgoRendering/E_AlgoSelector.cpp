/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/


#ifdef MINSG_EXT_MULTIALGORENDERING

#include "E_AlgoSelector.h"

#include "../../ELibMinSG.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include "E_SampleContext.h"
#include "E_MultiAlgoGroupNode.h"
#include <E_Rendering/Texture/E_Texture.h>

using namespace MinSG::MAR;

namespace E_MinSG {
namespace E_MAR {
	

EScript::Type * E_AlgoSelector::getTypeObject() {
	// E_MAR::E_AlgoSelector ---|> E_State ---|> [ReferenceObject<Util::Reference<MinSG::State>>
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

void E_AlgoSelector::init(EScript::Namespace & lib) {

	declareConstant(&lib,getClassName(),getTypeObject());
	
	addFactory<AlgoSelector,E_AlgoSelector>();
	
	declareConstant(getTypeObject(),"NEAREST",EScript::create(AlgoSelector::NEAREST));
	declareConstant(getTypeObject(),"MAX4",EScript::create(AlgoSelector::MAX4));
	declareConstant(getTypeObject(),"BARY",EScript::create(AlgoSelector::BARY));

    declareConstant(getTypeObject(),"ABS",EScript::create(AlgoSelector::ABS));
    declareConstant(getTypeObject(),"REL",EScript::create(AlgoSelector::REL));
    declareConstant(getTypeObject(),"CYCLE",EScript::create(AlgoSelector::CYCLE));

	ES_CTOR(getTypeObject(), 0, 0, EScript::create(new AlgoSelector()))
	
	ES_MFUN(getTypeObject(), AlgoSelector, "setInterpolationMode", 1, 1, (thisObj->setInterpolationMode(parameter[0].to<AlgoSelector::INTERPOLATION_MODE>(rt)), EScript::create(nullptr)))
	ES_MFUN(getTypeObject(), const AlgoSelector, "getInterpolationMode", 0, 0, EScript::create(thisObj->getInterpolationMode()))

    ES_MFUN(getTypeObject(), AlgoSelector, "setRegulationMode", 1, 1, (thisObj->setRegulationMode(parameter[0].to<AlgoSelector::REGULATION_MODE>(rt)), EScript::create(nullptr)))
    ES_MFUN(getTypeObject(), const AlgoSelector, "getRegulationMode", 0, 0, EScript::create(thisObj->getRegulationMode()))
	
	ES_MFUN(getTypeObject(), AlgoSelector, "setSampleContext", 1, 1, (thisObj->setSampleContext(parameter[0].to<SampleContext*>(rt)), EScript::create(nullptr)))
	ES_MFUN(getTypeObject(), const AlgoSelector, "getSampleContext", 0, 0, EScript::create(thisObj->getSampleContext()))
	
    ES_MFUN(getTypeObject(), AlgoSelector, "setRenderMode", 1, 1, (thisObj->setRenderMode(parameter[0].to<MinSG::MAR::MultiAlgoGroupNode::AlgoId>(rt)), EScript::create(nullptr)))
    ES_MFUN(getTypeObject(), const AlgoSelector, "getRenderMode", 0, 0, EScript::create(thisObj->getRenderMode()))
	
	ES_MFUN(getTypeObject(), AlgoSelector, "setTargetTime", 1, 1, (thisObj->setTargetTime(parameter[0].to<float>(rt)), EScript::create(nullptr)))
	ES_MFUN(getTypeObject(), const AlgoSelector, "getTargetTime", 0, 0, thisObj->getTargetTime())

    //! eval functions
    ES_MFUN(getTypeObject(), const AlgoSelector, "countMAGNsInFrustum", 0, 0, thisObj->countMAGNsInFrustum())
    ES_MFUN(getTypeObject(), const AlgoSelector, "getTimReal", 0, 0, thisObj->getTimReal())
    ES_MFUN(getTypeObject(), const AlgoSelector, "getTimCalc", 0, 0, thisObj->getTimCalc())
    ES_MFUN(getTypeObject(), const AlgoSelector, "getTimMini", 0, 0, thisObj->getTimMini())
    ES_MFUN(getTypeObject(), const AlgoSelector, "getTimMaxi", 0, 0, thisObj->getTimMaxi())
    ES_MFUN(getTypeObject(), const AlgoSelector, "getTimLPIn", 0, 0, thisObj->getTimLPIn())
    ES_MFUN(getTypeObject(), const AlgoSelector, "getTimUser", 0, 0, thisObj->getTimUser())
    ES_MFUN(getTypeObject(), const AlgoSelector, "getErrCalc", 0, 0, thisObj->getErrCalc())
            ES_MFUN(getTypeObject(), const AlgoSelector, "getAlgoUsage", 1, 1, thisObj->getAlgoUsage(parameter[0].to<MultiAlgoGroupNode::AlgoId>(rt)))
            ES_MFUN(getTypeObject(), AlgoSelector, "keepSamples", 1, 1, (thisObj->keepSamples(parameter[0].to<uint32_t>(rt)), EScript::create(nullptr)))
}

}
}
namespace EScript{
Object * create(AlgoSelector::INTERPOLATION_MODE obj) {
        return EScript::create(static_cast<AlgoSelector::INTERPOLATION_MODE_t>(obj));
}
Object * create(AlgoSelector::REGULATION_MODE obj) {
        return EScript::create(static_cast<AlgoSelector::REGULATION_MODE_t>(obj));
}
}

#endif // MINSG_EXT_MULTIALGORENDERING
