/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_GroupState.h"

#include "../../ELibMinSG.h"
#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

//! (static)
EScript::Type * E_GroupState::getTypeObject() {
	// E_GroupState ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

//! (static)
void E_GroupState::init(EScript::Namespace & lib) {
	EScript::Type * const typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::GroupState,E_GroupState>();

	//! [ESMF] GroupState new MinSG.GroupState( )
	ES_CTOR(typeObject, 0, 0, EScript::create(	new GroupState))

	//! [ESMF] thisEObj MinSG.Node.addState(State)
	ES_MFUN(typeObject, GroupState, "addState", 1, 1,
				(thisObj->addState(parameter[0].to<MinSG::State*>(rt)),thisEObj))

	//! [ESMF] Array MinSG.Node.getStates()
	ES_MFUN(typeObject, const GroupState, "getStates",0, 0, EScript::Array::create(thisObj->getStates()))

	//! [ESMF] bool MinSG.Node.hasStates()
	ES_MFUN(typeObject, const GroupState, "hasStates", 0, 0,Bool::create(thisObj->hasStates()))

	//! [ESMF] thisEObj MinSG.Node.removeState(State)
	ES_MFUN(typeObject, GroupState, "removeState",1, 1, 
				(thisObj->removeState(parameter[0].to<MinSG::State*>(rt)),thisEObj))


	//! [ESMF] thisEObj MinSG.Node.removeStates()
	ES_MFUN(typeObject, GroupState, "removeStates",0, 0, 
				(thisObj->removeStates(),thisEObj))

}

}
