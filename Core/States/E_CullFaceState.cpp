/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_CullFaceState.h"

#include "../../ELibMinSG.h"
#include <EScript/EScript.h>

using namespace MinSG;

namespace E_MinSG {

EScript::Type* E_CullFaceState::typeObject = nullptr;

// -----

//! (static)
void E_CullFaceState::init(EScript::Namespace & lib) {
	// MinSG.CullFaceState ---|> MinSG.State ---|> [Object]
	typeObject = new EScript::Type(E_State::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::CullFaceState,E_CullFaceState>();

	//! [ESMF] CullFaceState new MinSG.CullFaceState( )
	ES_CTOR(typeObject, 0, 0, EScript::create(new CullFaceState))

	//! [ESMF] thisEObj CullFaceState.getCullingEnabled()
	ES_MFUN(typeObject, const CullFaceState, "getCullingEnabled", 0,  0,
				thisObj->getParameters().isEnabled())

	//! [ESMF] thisEObj CullFaceState.setCullingEnabled(Bool)
	ES_MFUNCTION(typeObject, CullFaceState, "setCullingEnabled", 1,  1, {
		if(parameter[0].toBool()) {
			thisObj->changeParameters().enable();
		} else {
			thisObj->changeParameters().disable();
		}
		return thisEObj;
	})

	//! [ESMF] number CullFaceState.getCullMode()
	ES_MFUN(typeObject, const CullFaceState, "getCullMode", 0, 0, 
				 static_cast<uint32_t>(thisObj->getParameters().getMode()))

	//! [ESMF] thisEObj CullFaceState.setCullMode(Number)
	ES_MFUN(typeObject, CullFaceState, "setCullMode", 1,  1,
				 (thisObj->changeParameters().setMode(static_cast<Rendering::CullFaceParameters::cullFaceMode_t>(parameter[0].toUInt())), thisEObj))

}
// ------------------------------------------------------------
// ------------------------------------------------------------

//! (ctor)
E_CullFaceState::E_CullFaceState(CullFaceState * c, EScript::Type * type) :
	E_State(c, type ? type : typeObject) {
}

}
