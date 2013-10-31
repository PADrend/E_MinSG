/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_VISIBILITY_SUBDIVISION

#include "E_CostEvaluator.h"
#include "../../SceneManagement/E_SceneManager.h"
#include <EScript/EScript.h>
#include <MinSG/Ext/VisibilitySubdivision/CostEvaluator.h>

using namespace EScript;
using namespace MinSG::VisibilitySubdivision;

namespace E_MinSG {

Type* E_CostEvaluator::typeObject=nullptr;

void E_CostEvaluator::init(EScript::Namespace & lib) {
	// E_CostEvaluator ----|> E_Evaluator ----|> Object
	typeObject = new EScript::Type(E_Evaluator::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] CostEvaluator new CostEvaluator(Number)
	ES_CTOR(typeObject, 1, 1, new E_CostEvaluator(new CostEvaluator(static_cast<MinSG::Evaluators::Evaluator::DirectionMode>(parameter[0].toUInt()))))
}

//---

E_CostEvaluator::E_CostEvaluator(CostEvaluator * evaluator) :
		E_Evaluator(evaluator, typeObject) {
}

E_CostEvaluator::~E_CostEvaluator() {
}


}

#endif // MINSG_EXT_VISIBILITY_SUBDIVISION
