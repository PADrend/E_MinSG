/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2012-2013 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_MULTIALGORENDERING

#include "E_SurfelRenderer.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_MinSG {
namespace E_MAR {
	
	using MinSG::MAR::SurfelRenderer;

//! (static)
EScript::Type * E_SurfelRenderer::getTypeObject() {
	// E_SurfelRenderer ---|> [E_NodeRendererState] ---|> [E_State] ---|> [ReferenceObject]
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_SurfelRenderer::init(EScript::Namespace & lib) {
	
	declareConstant(&lib, E_SurfelRenderer::getClassName(), getTypeObject());
	
	addFactory<SurfelRenderer,E_SurfelRenderer>();

	// SurfelRenderer(Util::StringIdentifier newChannel = MinSG::FrameContext::DEFAULT_CHANNEL)
	//! [ESF] new SurfelRenderer(p0[,p1])
	ES_CONSTRUCTOR(getTypeObject(), 0,1, {
		if(parameter.count()==0)
			return EScript::create(new SurfelRenderer);
		else
			return EScript::create(new SurfelRenderer((parameter[1].to<std::string>(rt))));
	})
	
	ES_MFUN(getTypeObject(), const SurfelRenderer, "getSurfelSizeFactor", 0, 0, thisObj->getSurfelSizeFactor())
	ES_MFUN(getTypeObject(), SurfelRenderer, "setSurfelSizeFactor", 1, 1, (thisObj->setSurfelSizeFactor(parameter[0].to<float>(rt)), EScript::create(nullptr)))

	ES_MFUN(getTypeObject(), const SurfelRenderer, "getSurfelCountFactor", 0, 0, thisObj->getSurfelCountFactor())
	ES_MFUN(getTypeObject(), SurfelRenderer, "setSurfelCountFactor", 1, 1, (thisObj->setSurfelCountFactor(parameter[0].to<float>(rt)), EScript::create(nullptr)))

	ES_MFUN(getTypeObject(), const SurfelRenderer, "getMaxAutoSurfelSize", 0, 0, thisObj->getMaxAutoSurfelSize())
	ES_MFUN(getTypeObject(), SurfelRenderer, "setMaxAutoSurfelSize", 1, 1, (thisObj->setMaxAutoSurfelSize(parameter[0].to<float>(rt)), EScript::create(nullptr)))

	ES_MFUN(getTypeObject(), const SurfelRenderer, "getForceSurfels", 0, 0, thisObj->getForceSurfels())
	ES_MFUN(getTypeObject(), SurfelRenderer, "setForceSurfels", 1, 1, (thisObj->setForceSurfels(parameter[0].to<bool>(rt)), EScript::create(nullptr)))
}
}

}
#endif // MINSG_EXT_MULTIALGORENDERING

