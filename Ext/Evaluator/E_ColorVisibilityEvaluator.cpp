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

#include "E_ColorVisibilityEvaluator.h"

#include <EScript/EScript.h>

namespace E_MinSG {

EScript::Type * E_ColorVisibilityEvaluator::typeObject = nullptr;

void E_ColorVisibilityEvaluator::init(EScript::Namespace & lib) {
	// E_VisibilityEvaluator ----|> E_Evaluator ----|> Object
	typeObject = new EScript::Type(E_Evaluator::getTypeObject());
	declareConstant(&lib, getClassName(), typeObject);


	//! [ESMF] ColorVisibilityEvaluator new ColorVisibilityEvaluator([mode = SINGLE_VALUE])
	ES_CTOR(typeObject, 0, 1, new E_ColorVisibilityEvaluator(
			parameter.count() > 0 ? static_cast<MinSG::Evaluators::Evaluator::DirectionMode>(parameter[0].toInt()) : MinSG::Evaluators::Evaluator::SINGLE_VALUE));
}

E_ColorVisibilityEvaluator::E_ColorVisibilityEvaluator(MinSG::Evaluators::Evaluator::DirectionMode mode) :
		E_Evaluator(new MinSG::Evaluators::ColorVisibilityEvaluator(mode), typeObject) {
}

E_ColorVisibilityEvaluator::~E_ColorVisibilityEvaluator() = default;

}

#endif /* MINSG_EXT_EVALUATORS */
