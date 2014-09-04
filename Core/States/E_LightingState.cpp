/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_LightingState.h"
#include "../Nodes/E_LightNode.h"
#include "../../ELibMinSG.h"
#include <EScript/EScript.h>

namespace E_MinSG {
//! (static)
EScript::Type * E_LightingState::getTypeObject() {
	//  E_LightingState ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}


//! (static)
void E_LightingState::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::LightingState,E_LightingState>();

	using namespace MinSG;

	//!	[ESMF] new MinSG.LightingNode([LightNode])
	ES_CONSTRUCTOR(typeObject, 0, 1,{
		MinSG::LightingState * light = new MinSG::LightingState;
		if(parameter.count() == 1) {
			MinSG::LightNode * node = **EScript::assertType<E_LightNode>(rt, parameter[0]);
			light->setLight(node);
		}
		return EScript::create(light);
	})

	//! [ESMF] MinSG.LightNode MinSG.LightingState.getEnableLight()
	ES_MFUN(typeObject, const LightingState, "getEnableLight", 0, 0, thisObj->getEnableLight())

	//! [ESMF] MinSG.LightNode MinSG.LightingState.getLight()
	ES_MFUN(typeObject, const LightingState, "getLight", 0, 0,EScript::create(thisObj->getLight()))

	//! [ESMF] thisEObj MinSG.LightingState.setEnableLight(Bool)
	ES_MFUN(typeObject, LightingState, "setEnableLight", 1, 1, (thisObj->setEnableLight( parameter[0].toBool()),thisEObj))
			
	//! [ESMF] thisEObj MinSG.LightingState.setLight(MinSG.LightNode)
	ES_MFUN(typeObject, LightingState, "setLight", 1, 1, (thisObj->setLight( parameter[0].to<LightNode*>(rt)),thisEObj))
}


}
