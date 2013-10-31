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

#include "E_TrianglesEvaluator.h"
#include <MinSG/Ext/Evaluator/TrianglesEvaluator.h>

#include <EScript/EScript.h>

using namespace MinSG::Evaluators;
using namespace EScript;

namespace E_MinSG {

Type * E_TrianglesEvaluator::typeObject = nullptr;

void E_TrianglesEvaluator::init(EScript::Namespace & lib) {
	// E_TrianglesEvaluator ----|> E_Evaluator ----|> Object
	typeObject = new EScript::Type(E_Evaluator::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	
	ES_CTOR(typeObject, 0, 0, new E_TrianglesEvaluator)
}

E_TrianglesEvaluator::E_TrianglesEvaluator() :
	E_Evaluator(new TrianglesEvaluator, typeObject) {
}

E_TrianglesEvaluator::~E_TrianglesEvaluator() = default;

}

#endif /* MINSG_EXT_EVALUATORS */
