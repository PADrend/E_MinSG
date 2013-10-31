/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_PolygonModeState.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include "../../ELibMinSG.h"

#include <E_Rendering/E_ParameterStructs.h>

namespace E_MinSG {

EScript::Type * E_PolygonModeState::getTypeObject() {
	// E_PolygonModeState ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

void E_PolygonModeState::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<MinSG::PolygonModeState,E_PolygonModeState>();

	using namespace MinSG;

	//! [ESF] PolygonModeState new PolygonModeState()
	ES_CTOR(typeObject, 0, 0, EScript::create(new MinSG::PolygonModeState))

	//! [ESMF] Rendering.PolygonModeParameters PolygonModeState.getParameters()
	ES_MFUN(typeObject, const PolygonModeState, "getParameters", 0,  0,
				EScript::create(thisObj->getParameters()))

	//! [ESMF] thisEObj PolygonModeState.setParameters(Rendering.PolygonModeParameters)
	ES_MFUN(typeObject, PolygonModeState, "setParameters", 1,  1,
				 (thisObj->setParameters(parameter[0].to<const Rendering::PolygonModeParameters&>(rt)), thisEObj))

	//! [ESMF] Number PolygonModeState.getMode()
	ES_MFUN(getTypeObject(), const PolygonModeState,"getMode",0,0,
				static_cast<uint32_t>(thisObj->getParameters().getMode())
	)

	//! [ESMF] thisEObj PolygonModeState.setMode(Number)
	ES_MFUN(getTypeObject(), PolygonModeState,"setMode",1,1,
				(thisObj->changeParameters().setMode(static_cast<Rendering::PolygonModeParameters::polygonModeMode_t>(parameter[0].toUInt())), thisEObj)
	)
}

}
