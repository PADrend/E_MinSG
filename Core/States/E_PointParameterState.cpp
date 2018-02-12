/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	Copyright (C) 2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_PointParameterState.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include "../../ELibMinSG.h"

#include <E_Rendering/E_ParameterStructs.h>

namespace E_MinSG {

EScript::Type * E_PointParameterState::getTypeObject() {
	// E_PointParameterState ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

void E_PointParameterState::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<MinSG::PointParameterState,E_PointParameterState>();

	using namespace MinSG;

	//! [ESF] PointParameterState new PointParameterState()
	ES_CTOR(typeObject, 0, 0, EScript::create(new MinSG::PointParameterState))

	//! [ESMF] Rendering.PointParameters PointParameterState.getParameters()
	ES_MFUN(typeObject, const PointParameterState, "getParameters", 0, 0,
		EScript::create(thisObj->getParameters()))

	//! [ESMF] thisEObj PointParameterState.setParameters(Rendering.PointParameters)
	ES_MFUN(typeObject, PointParameterState, "setParameters", 1, 1,
		(thisObj->setParameters(parameter[0].to<const Rendering::PointParameters&>(rt)), thisEObj))

	//! [ESMF] Number PointParameterState.getPointSize()
	ES_MFUN(getTypeObject(), const PointParameterState,"getSize",0,0,
		EScript::Number::create(thisObj->getParameters().getSize())
	)

	//! [ESMF] thisEObj PointParameterState.setSize(Number)
	ES_MFUN(getTypeObject(), PointParameterState,"setSize",1,1,
		(thisObj->changeParameters().setSize(parameter[0].toFloat()), thisEObj)
	)
	
	//! [ESMF] Bool PointParameterState.isPointSmoothingEnabled()
	ES_MFUN(getTypeObject(), const PointParameterState,"isPointSmoothingEnabled",0,0,
		EScript::Bool::create(thisObj->getParameters().isPointSmoothingEnabled())
	)

	//! [ESMF] thisEObj PointParameterState.setPointSmoothingEnabled(Bool)
	ES_MFUN(getTypeObject(), PointParameterState,"setPointSmoothingEnabled",1,1,
		(parameter[0].toBool() ? thisObj->changeParameters().enablePointSmoothing() : thisObj->changeParameters().disablePointSmoothing(), thisEObj)
	)
}

}
