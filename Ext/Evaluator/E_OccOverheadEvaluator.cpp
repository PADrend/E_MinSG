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

#include "E_OccOverheadEvaluator.h"
#include <MinSG/Ext/Evaluator/OccOverheadEvaluator.h>

#include <EScript/EScript.h>

using namespace EScript;

namespace E_MinSG {

Type* E_OccOverheadEvaluator::typeObject=nullptr;

//! initMembers
void E_OccOverheadEvaluator::init(EScript::Namespace & lib) {
	// E_OccOverheadEvaluator ----|> E_Evaluator ----|>Object
	typeObject = new EScript::Type(E_Evaluator::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] new MinSG.OccOverheadEvaluator( [direction] )	
	ES_CTOR(typeObject,0,1,new E_OccOverheadEvaluator(
		static_cast<MinSG::Evaluators::Evaluator::DirectionMode>(parameter[0].to<int32_t>(rt,static_cast<int32_t>(MinSG::Evaluators::Evaluator::SINGLE_VALUE)))))

}

E_OccOverheadEvaluator::E_OccOverheadEvaluator(MinSG::Evaluators::Evaluator::DirectionMode mode):E_Evaluator(new MinSG::Evaluators::OccOverheadEvaluator(mode),typeObject){
}

E_OccOverheadEvaluator::~E_OccOverheadEvaluator() = default;

}

#endif /* MINSG_EXT_EVALUATORS */
