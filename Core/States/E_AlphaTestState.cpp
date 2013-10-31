/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_AlphaTestState.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include "../../ELibMinSG.h"

#include <E_Rendering/E_ParameterStructs.h>

namespace E_MinSG {

EScript::Type * E_AlphaTestState::getTypeObject() {
	// E_AlphaTestState ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

void E_AlphaTestState::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<MinSG::AlphaTestState,E_AlphaTestState>();

	using namespace MinSG;

	//! [ESF] AlphaTestState new AlphaTestState
	ES_CONSTRUCTOR(typeObject, 0, 1, {
		if(parameter.count() == 1) {
			return EScript::create(new MinSG::AlphaTestState(parameter[0].to<const Rendering::AlphaTestParameters&>(rt)));
		} else {
			return EScript::create(new MinSG::AlphaTestState);
		}
	})

	//! [ESMF] Rendering.AlphaTestParameters AlphaTestState.getParameters()
	ES_MFUN(typeObject, const AlphaTestState, "getParameters", 0,  0,
				 EScript::create(thisObj->getParameters()))

	//! [ESMF] thisEObj AlphaTestState.setParameters(Rendering.AlphaTestParameters)
	ES_MFUN(typeObject, AlphaTestState, "setParameters", 1, 1,
				 (thisObj->setParameters(parameter[0].to<const Rendering::AlphaTestParameters&>(rt)), thisEObj))
}

}
