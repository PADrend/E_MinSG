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

#include "E_VisibilityEvaluator.h"
#include <MinSG/Ext/Evaluator/VisibilityEvaluator.h>

#include <EScript/EScript.h>

using namespace MinSG::Evaluators;
using namespace EScript;

namespace E_MinSG {

Type* E_VisibilityEvaluator::typeObject=nullptr;

//! initMembers
void E_VisibilityEvaluator::init(EScript::Namespace & lib) {
	// E_VisibilityEvaluator ----|> E_Evaluator ----|> Object
	typeObject = new EScript::Type(E_Evaluator::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	
	//! [ESMF] new MinSG.VisibilityEvaluator( [direction] )	
	ES_CTOR(typeObject,0,1,new E_VisibilityEvaluator(
					static_cast<Evaluator::DirectionMode>(parameter[0].to<int32_t>(rt,static_cast<int32_t>(Evaluator::SINGLE_VALUE)))))
	
	//! [ESMF] Bool VisibilityEvaluator.doesCountPolygons() 
	ES_MFUN(typeObject, const VisibilityEvaluator,"doesCountPolygons",0,0,thisObj->doesCountPolygons() )

	//! [ESMF] self VisibilityEvaluator.setCountPolygons(Bool) 
	ES_MFUN(typeObject, VisibilityEvaluator,"setCountPolygons",1,1,(thisObj->setCountPolygons(parameter[0].toBool()),thisEObj))
}

//---

//! [ctor]
E_VisibilityEvaluator::E_VisibilityEvaluator(Evaluator::DirectionMode mode):E_Evaluator(new VisibilityEvaluator(mode),typeObject){
}

const MinSG::Evaluators::VisibilityEvaluator * E_VisibilityEvaluator::operator*()const		{	return static_cast<const MinSG::Evaluators::VisibilityEvaluator*>(ref().get());	}
MinSG::Evaluators::VisibilityEvaluator * E_VisibilityEvaluator::operator*()					{	return static_cast<MinSG::Evaluators::VisibilityEvaluator*>(ref().get());	}


}

#endif /* MINSG_EXT_EVALUATORS */
