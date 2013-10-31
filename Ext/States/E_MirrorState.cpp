/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_MirrorState.h"
#include "../../Core/Nodes/E_GroupNode.h"
#include "../../ELibMinSG.h"
#include <EScript/Basics.h>
#include <MinSG/Ext/States/MirrorState.h>


namespace E_MinSG {

EScript::Type * E_MirrorState::getTypeObject() {
	// E_MirrorState ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

void E_MirrorState::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<MinSG::MirrorState,E_MirrorState>();

	using namespace MinSG;

	//! [ESMF] MirrorState new MirrorState(Number textureSize)
	ES_CTOR(typeObject, 1, 1, EScript::create(new MinSG::MirrorState(parameter[0].toUInt())));

	//! [ESMF] self MirrorState.setRoot(Node)
	ES_MFUN(typeObject,MirrorState, "setRoot", 1, 1, (thisObj->setRoot((parameter[0].to<MinSG::GroupNode*>(rt))), thisEObj))

}

}
