/*
	This file is part of the E_MinSG library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_BudgetAnnotationState.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <MinSG/Ext/States/BudgetAnnotationState.h>

namespace E_MinSG {

EScript::Type * E_BudgetAnnotationState::getTypeObject() {
	// E_BudgetAnnotationState ---|> E_State
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

void E_BudgetAnnotationState::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_BudgetAnnotationState::getTypeObject();
	declareConstant(&lib, E_BudgetAnnotationState::getClassName(), typeObject);
	addFactory<MinSG::BudgetAnnotationState, E_BudgetAnnotationState>();

	using namespace MinSG;

	declareConstant(typeObject, "DISTRIBUTE_EVEN", EScript::Number::create(MinSG::BudgetAnnotationState::DISTRIBUTE_EVEN));
	declareConstant(typeObject, "DISTRIBUTE_PROJECTED_SIZE", EScript::Number::create(MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE));
	declareConstant(typeObject, "DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT", EScript::Number::create(MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT));
#ifdef MINSG_EXT_THESISJONAS
	declareConstant(typeObject, "DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT_ITERATIVE", EScript::Number::create(MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT_ITERATIVE));
#endif
	declareConstant(typeObject, "DISTRIBUTE_DELETE", EScript::Number::create(MinSG::BudgetAnnotationState::DISTRIBUTE_DELETE));

	//! [ESF] new BudgetAnnotationState()
	ES_CTOR(typeObject, 0, 0, EScript::create(new MinSG::BudgetAnnotationState))

	//! [ESMF] String BudgetAnnotationState.getAnnotationAttribute()
	ES_MFUN(typeObject, const BudgetAnnotationState, "getAnnotationAttribute", 0, 0, thisObj->getAnnotationAttribute().toString())

	//! [ESMF] self BudgetAnnotationState.setAnnotationAttribute(String)
	ES_MFUN(typeObject,BudgetAnnotationState, "setAnnotationAttribute", 1, 1,
				 (thisObj->setAnnotationAttribute(EScript::assertType<EScript::String>(rt, parameter[0])->toString()), thisEObj))

	//! [ESMF] Number BudgetAnnotationState.getBudget()
	ES_MFUN(typeObject, const BudgetAnnotationState, "getBudget", 0, 0, 
				 EScript::Number::create(thisObj->getBudget()))

	//! [ESMF] self BudgetAnnotationState.setBudget(Number)
	ES_MFUN(typeObject,BudgetAnnotationState, "setBudget", 1, 1,
				 (thisObj->setBudget(parameter[0].to<double>(rt)), thisEObj))

	//! [ESMF] Number BudgetAnnotationState.getDistributionType()
	ES_MFUN(typeObject, const BudgetAnnotationState, "getDistributionType", 0, 0, 
				 EScript::Number::create(thisObj->getDistributionType()))

	//! [ESMF] self BudgetAnnotationState.setDistributionType(Number)
#ifdef MINSG_EXT_THESISJONAS
	ES_MFUNCTION(typeObject,BudgetAnnotationState, "setDistributionType", 1, 1, {
		switch(parameter[0].to<uint32_t>(rt)) {
			case MinSG::BudgetAnnotationState::DISTRIBUTE_EVEN:
				thisObj->setDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_EVEN);
				break;
			case MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE:
				thisObj->setDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE);
				break;
			case MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT:
				thisObj->setDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT);
				break;
			case MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT_ITERATIVE:
				thisObj->setDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT_ITERATIVE);
				break;
			case MinSG::BudgetAnnotationState::DISTRIBUTE_DELETE:
			default:
				thisObj->setDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_DELETE);
				break;
		}
		return thisEObj;
	})
#else
	ES_MFUNCTION(typeObject,BudgetAnnotationState, "setDistributionType", 1, 1, {
		switch(parameter[0].to<uint32_t>(rt)) {
			case MinSG::BudgetAnnotationState::DISTRIBUTE_EVEN:
				thisObj->setDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_EVEN);
				break;
			case MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE:
				thisObj->setDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE);
				break;
			case MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT:
				thisObj->setDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT);
				break;
			case MinSG::BudgetAnnotationState::DISTRIBUTE_DELETE:
			default:
				thisObj->setDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_DELETE);
				break;
		}
		return thisEObj;
	})
#endif
}

E_BudgetAnnotationState::E_BudgetAnnotationState(MinSG::BudgetAnnotationState * state) :
	E_State(state, E_BudgetAnnotationState::getTypeObject()) {
}

E_BudgetAnnotationState::~E_BudgetAnnotationState() = default;

const MinSG::BudgetAnnotationState * E_BudgetAnnotationState::operator*() const {
	return static_cast<const MinSG::BudgetAnnotationState *>(ref().get());
}
MinSG::BudgetAnnotationState * E_BudgetAnnotationState::operator*() {
	return static_cast<MinSG::BudgetAnnotationState *>(ref().get());
}

}
