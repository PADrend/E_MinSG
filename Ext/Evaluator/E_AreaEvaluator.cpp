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

#include "E_AreaEvaluator.h"
#include <MinSG/Ext/Evaluator/AreaEvaluator.h>

#include <EScript/EScript.h>

using namespace EScript;

namespace E_MinSG {

Type* E_AreaEvaluator::typeObject=nullptr;
//! initMembers
void E_AreaEvaluator::init(EScript::Namespace & lib) {
	// E_AreaEvaluator ----|> E_Evaluator ----|> Object
	typeObject = new EScript::Type(E_Evaluator::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] new MinSG.AreaEvaluator( [mode=SINGLE_VALUE] )	
	ES_CTOR(typeObject,0,1,new E_AreaEvaluator(
					static_cast<MinSG::Evaluators::Evaluator::DirectionMode>(parameter[0].to<int32_t>(rt,static_cast<int32_t>(MinSG::Evaluators::Evaluator::SINGLE_VALUE)))))
}

E_AreaEvaluator::E_AreaEvaluator(MinSG::Evaluators::Evaluator::DirectionMode mode):E_Evaluator(new MinSG::Evaluators::AreaEvaluator(mode),typeObject){
}

E_AreaEvaluator::~E_AreaEvaluator() = default;

}

#endif /* MINSG_EXT_EVALUATORS */
