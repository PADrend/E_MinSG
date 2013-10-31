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

#include "E_Evaluator.h"
#include "../../Core/Nodes/E_Node.h"
#include "../../Core/E_FrameContext.h"
#include <MinSG/Ext/Evaluator/Evaluator.h>
#include <EScript/EScript.h>
#include <E_Geometry/E_Rect.h>
#include <E_Util/E_Utils.h>

namespace E_MinSG {

EScript::Type * E_Evaluator::getTypeObject() {
	// E_Evaluator ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(Object::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_Evaluator::init(EScript::Namespace & lib) {
	auto * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace MinSG::Evaluators;

	declareConstant(typeObject,"SINGLE_VALUE", EScript::Number::create(Evaluator::SINGLE_VALUE));
	declareConstant(typeObject,"DIRECTION_VALUES", EScript::Number::create(Evaluator::DIRECTION_VALUES));
	
	//! [ESMF] self Evaluator.beginMeasure()
	ES_MFUN(typeObject, Evaluator,"beginMeasure",0,0,(thisObj->beginMeasure() ,thisEObj))

	//! [ESMF] self Evaluator.endMeasure(FrameContext) 
	ES_MFUN(typeObject, Evaluator,"endMeasure",1,1,(thisObj->endMeasure(parameter[0].to<MinSG::FrameContext&>(rt)) ,thisEObj))

	//! [ESMF] Array Evaluator.getResults() 
	ES_MFUN(typeObject, Evaluator,"getResults",0,0,E_Util::E_Utils::convertGenericAttributeToEScriptObject(thisObj->getResults()))

	//! [ESMF] number Evaluator.getMaxValue()   
	ES_MFUN(typeObject, const Evaluator,"getMaxValue",0,0,E_Util::E_Utils::convertGenericAttributeToEScriptObject(thisObj->getMaxValue()))

	//! [ESMF] number Evaluator.getMode()   
	ES_MFUN(typeObject, const Evaluator,"getMode",0,0,EScript::Number::create(thisObj->getMode()))

	//! [ESMF] self Evaluator.measure(FrameContext,Node,Rect) 
	ES_MFUN(typeObject, Evaluator,"measure",3,3,(thisObj->
					measure(parameter[0].to<MinSG::FrameContext&>(rt),
							*parameter[1].to<MinSG::Node*>(rt),
							parameter[2].to<const Geometry::Rect&>(rt)) ,thisEObj))
							
	//! [ESMF] self Evaluator.setMode(SINGLE_VALUE|DIRECTION_VALUES)
	ES_MFUN(typeObject, Evaluator,"setMode",1,1,(thisObj->setMode(static_cast<Evaluator::DirectionMode>(parameter[0].toInt())) ,thisEObj))
}

E_Evaluator::E_Evaluator(MinSG::Evaluators::Evaluator * _obj, EScript::Type * type) : 
	ExtReferenceObject_t(type ? type : getTypeObject(), _obj) {
}

E_Evaluator::~E_Evaluator() = default;

}

#endif /* MINSG_EXT_EVALUATORS */
