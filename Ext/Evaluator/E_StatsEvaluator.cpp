/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_EVALUATORS

#include "E_StatsEvaluator.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <MinSG/Ext/Evaluator/Evaluator.h>
#include <MinSG/Ext/Evaluator/StatsEvaluator.h>

namespace EScript {
class Namespace;
}
namespace E_MinSG {

EScript::Type * E_StatsEvaluator::getTypeObject() {
	// E_StatsEvaluator ---|> E_Evaluator ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_Evaluator::getTypeObject());
	return typeObject.get();
}

void E_StatsEvaluator::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	
	using namespace MinSG::Evaluators;

	//! [ESF] StatsEvaluator new StatsEvaluator([mode = SINGLE_VALUE])
	ES_CTOR(typeObject, 0, 1, 
		new E_StatsEvaluator(
			parameter.count() > 0 
			? static_cast<MinSG::Evaluators::Evaluator::DirectionMode>(parameter[0].toInt())
			: MinSG::Evaluators::Evaluator::SINGLE_VALUE
		)
	)

	//! [ESMF] Number StatsEvaluator.getNumberOfIterations()
	ES_MFUN(typeObject, const StatsEvaluator, "getNumberOfIterations", 0, 0, thisObj->getNumberOfIterations())
	//! [ESMF] Void StatsEvaluator.setNumberOfIterations(Number)
	ES_MFUN(typeObject, StatsEvaluator, "setNumberOfIterations", 1, 1, (thisObj->setNumberOfIterations(parameter[0].toInt()), thisEObj));

	//! [ESMF] Number StatsEvaluator.getStatIndex()
	ES_MFUN(typeObject, const StatsEvaluator, "getStatIndex", 0, 0, thisObj->getStatIndex())
	//! [ESMF] Void StatsEvaluator.setStatIndex(Number)
	ES_MFUN(typeObject, StatsEvaluator, "setStatIndex", 1, 1, (thisObj->setStatIndex(parameter[0].toInt()), thisEObj));

	//! [ESMF] Bool StatsEvaluator.getCallGlFinish()
	ES_MFUN(typeObject, const StatsEvaluator, "getCallGlFinish", 0, 0, thisObj->getCallGlFinish())
	//! [ESMF] Void StatsEvaluator.setCallGlFinish(Bool)
	ES_MFUN(typeObject, StatsEvaluator, "setCallGlFinish", 1, 1, (thisObj->setCallGlFinish(parameter[0].toBool()), thisEObj))
}

E_StatsEvaluator::E_StatsEvaluator(MinSG::Evaluators::Evaluator::DirectionMode mode, EScript::Type * type) 
	: E_Evaluator(new MinSG::Evaluators::StatsEvaluator(mode), type != nullptr ? type : getTypeObject()) {
}

const MinSG::Evaluators::StatsEvaluator * E_StatsEvaluator::operator*()const		{	return static_cast<const MinSG::Evaluators::StatsEvaluator*>(ref().get());	}
MinSG::Evaluators::StatsEvaluator * E_StatsEvaluator::operator*()					{	return static_cast<MinSG::Evaluators::StatsEvaluator*>(ref().get());	}


}

#endif /* MINSG_EXT_EVALUATORS */
