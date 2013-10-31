/*
	This file is part of the E_MinSG library extension Evaluator.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_EVALUATORS

#include "E_OverdrawFactorEvaluator.h"
#include <MinSG/Ext/Evaluator/OverdrawFactorEvaluator.h>
#include <EScript/Basics.h>
#include <stdexcept>

namespace E_MinSG {

EScript::Type * E_OverdrawFactorEvaluator::getTypeObject() {
	// E_OverdrawFactorEvaluator ---|> E_Evaluator ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_Evaluator::getTypeObject());
	return typeObject.get();
}

void E_OverdrawFactorEvaluator::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);


	using namespace MinSG::Evaluators;
	
	//! [ESF] Evaluator new OverdrawFactorEvaluator([mode=SINGLE_VALUE])
	ES_CTOR(typeObject, 0, 1,
		new E_OverdrawFactorEvaluator(parameter.count() > 0 ? static_cast<MinSG::Evaluators::Evaluator::DirectionMode>(parameter[0].toInt()) : MinSG::Evaluators::Evaluator::SINGLE_VALUE))

	//! [ESMF] Number OverdrawFactorEvaluator.getResultQuantile()
	ES_MFUN(typeObject, const OverdrawFactorEvaluator, "getResultQuantile", 0, 0,	thisObj->getResultQuantile())

	//! [ESMF] self OverdrawFactorEvaluator.setResultQuantile(Number)
	ES_MFUN(typeObject, OverdrawFactorEvaluator, "setResultQuantile", 1, 1, 		(thisObj->setResultQuantile(parameter[0].toDouble()), thisEObj))

	//! [ESMF] Bool OverdrawFactorEvaluator.areZeroValuesIgnored()
	ES_MFUN(typeObject, const OverdrawFactorEvaluator, "areZeroValuesIgnored", 0, 0,thisObj->areZeroValuesIgnored())

	//! [ESMF] self OverdrawFactorEvaluator.ignoreZeroValues()
	ES_MFUN(typeObject, OverdrawFactorEvaluator, "ignoreZeroValues", 0, 0, 			(thisObj->ignoreZeroValues(), thisEObj))

	//! [ESMF] self OverdrawFactorEvaluator.keepZeroValues()
	ES_MFUN(typeObject, OverdrawFactorEvaluator, "keepZeroValues", 0, 0, 			(thisObj->keepZeroValues(), thisEObj))
}

E_OverdrawFactorEvaluator::E_OverdrawFactorEvaluator(MinSG::Evaluators::Evaluator::DirectionMode mode) :
		E_Evaluator(new MinSG::Evaluators::OverdrawFactorEvaluator(mode), getTypeObject()) {
}

E_OverdrawFactorEvaluator::~E_OverdrawFactorEvaluator() = default;


const MinSG::Evaluators::OverdrawFactorEvaluator * E_OverdrawFactorEvaluator::operator*()const		{	return static_cast<const MinSG::Evaluators::OverdrawFactorEvaluator*>(ref().get());	}
MinSG::Evaluators::OverdrawFactorEvaluator * E_OverdrawFactorEvaluator::operator*()					{	return static_cast<MinSG::Evaluators::OverdrawFactorEvaluator*>(ref().get());	}

}

#endif /* MINSG_EXT_EVALUATORS */
