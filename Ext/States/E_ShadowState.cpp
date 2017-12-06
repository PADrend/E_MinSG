/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_ShadowState.h"
#include "../../Core/Nodes/E_LightNode.h"
#include "../../ELibMinSG.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <MinSG/Core/Nodes/LightNode.h>
#include <MinSG/Ext/States/ShadowState.h>

namespace E_MinSG {

EScript::Type * E_ShadowState::getTypeObject() {
	// E_ShadowState ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

void E_ShadowState::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<MinSG::ShadowState,E_ShadowState>();

	using namespace MinSG;

	//! [ESMF] ShadowState new ShadowState(Number textureSize)
	ES_CTOR(typeObject, 1, 1, EScript::create(new ShadowState(parameter[0].toUInt())));

	//! [ESMF] LightNode ShadowState.getLight()
	ES_MFUN(typeObject,ShadowState, "getLight", 0, 0, EScript::create(thisObj->getLight()))

	//! [ESMF] self ShadowState.setLight(LightNode)
	ES_MFUN(typeObject,ShadowState, "setLight", 1, 1, (thisObj->setLight( parameter[0].to<LightNode*>(rt) ), thisEObj))
	
	//! [ESMF] Bool ShadowState.isStatic()
	ES_MFUN(typeObject,ShadowState, "isStatic", 0, 0, EScript::create(thisObj->isStatic()))

	//! [ESMF] self ShadowState.setStatic(Bool)
	ES_MFUN(typeObject,ShadowState, "setStatic", 1, 1, (thisObj->setStatic( parameter[0].toBool() ), thisEObj))
	
	//! [ESMF] self ShadowState.update()
	ES_MFUN(typeObject,ShadowState, "update", 0, 0, (thisObj->update(), thisEObj))

}

}
