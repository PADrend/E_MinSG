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

#include "E_BoxQualityEvaluator.h"
#include <MinSG/Ext/Evaluator/BoxQualityEvaluator.h>

#include <EScript/EScript.h>

using namespace MinSG::Evaluators;
using namespace EScript;

namespace E_MinSG {

Type* E_BoxQualityEvaluator::typeObject=nullptr;

//! initMembers
void E_BoxQualityEvaluator::init(EScript::Namespace & lib) {
	// E_BoxQualityEvaluator ----|> E_Evaluator ----|> Object
	typeObject = new EScript::Type(E_Evaluator::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);

	declareConstant(typeObject,"OBJECTS_CLASSIFIED_AS_VISIBLE",Number::create(BoxQualityEvaluator::OBJECTS_CLASSIFIED_AS_VISIBLE));
	declareConstant(typeObject,"OBJECTS_VISIBLE",Number::create(BoxQualityEvaluator::OBJECTS_VISIBLE));
	declareConstant(typeObject,"TRIANGLES_IN_VISIBLE_BOXES",Number::create(BoxQualityEvaluator::TRIANGLES_IN_VISIBLE_BOXES));
	declareConstant(typeObject,"TRIANGLES_IN_VISIBLE_OBJECTS",Number::create(BoxQualityEvaluator::TRIANGLES_IN_VISIBLE_OBJECTS));

	ES_CTOR(typeObject,0,0,new E_BoxQualityEvaluator)

}

E_BoxQualityEvaluator::E_BoxQualityEvaluator():E_Evaluator(new BoxQualityEvaluator(),typeObject){
}

E_BoxQualityEvaluator::~E_BoxQualityEvaluator() = default;

}

#endif /* MINSG_EXT_EVALUATORS */
