/*
	This file is part of the E_MinSG library extension SphericalSampling.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SPHERICALSAMPLING

#include "E_BudgetRenderer.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <MinSG/Ext/SphericalSampling/BudgetRenderer.h>
#include <cstdint>

namespace E_MinSG {
namespace SphericalSampling {

EScript::Type * E_BudgetRenderer::getTypeObject() {
	// E_BudgetRenderer ---|> E_NodeRendererState ---|> E_State
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	return typeObject.get();
}

void E_BudgetRenderer::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_BudgetRenderer::getTypeObject();
	declareConstant(&lib, "BudgetRenderer", typeObject);
	addFactory<MinSG::SphericalSampling::BudgetRenderer, E_BudgetRenderer>();

	//! [ESF] new MinSG.SphericalSampling.BudgetRenderer()
	ES_CTOR(typeObject, 0, 0, EScript::create(new MinSG::SphericalSampling::BudgetRenderer))

	//! [ESMF] Number BudgetRenderer.getBudget()
	ES_MFUN(typeObject, const MinSG::SphericalSampling::BudgetRenderer, "getBudget", 0, 0, 
				 EScript::Number::create(thisObj->getBudget()))

	//! [ESMF] self BudgetRenderer.setBudget(Number)
	ES_MFUN(typeObject, MinSG::SphericalSampling::BudgetRenderer, "setBudget", 1, 1,
				 (thisObj->setBudget(parameter[0].to<uint32_t>(rt)), thisEObj))
}

E_BudgetRenderer::E_BudgetRenderer(MinSG::SphericalSampling::BudgetRenderer * renderer) :
		E_NodeRendererState(renderer, E_BudgetRenderer::getTypeObject()) {
}

E_BudgetRenderer::~E_BudgetRenderer() = default;

}
}

#endif /* MINSG_EXT_SPHERICALSAMPLING */
