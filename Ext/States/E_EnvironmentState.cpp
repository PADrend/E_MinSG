/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_EnvironmentState.h"
#include "../../ELibMinSG.h"
#include "../ELibMinSGExt.h"
#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

Type* E_EnvironmentState::typeObject=nullptr;

//! initMembers
void E_EnvironmentState::init(EScript::Namespace & lib) {
	// E_EnvironmentState ----|> E_State ----|> Object
	typeObject = new EScript::Type(E_State::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::EnvironmentState,E_EnvironmentState>();

	//! [ESMF] new MinSG.EnvironmentState()   
	ES_CTOR(typeObject,0,0,EScript::create( new EnvironmentState))

	//! [ESMF] self MinSG.EnvironmentState.setEnvironment(Node)   
	ES_MFUN(typeObject,EnvironmentState,"setEnvironment",1,1,(thisObj->setEnvironment(parameter[0].to<MinSG::Node*>(rt)),thisEObj))

	//! [ESMF] Node MinSG.EnvironmentState.getEnvironment()   
	ES_MFUN(typeObject,EnvironmentState,"getEnvironment",0,0,EScript::create( thisObj->getEnvironment()))
}
//---

//! [ctor]
E_EnvironmentState::E_EnvironmentState(EnvironmentState * _obj, EScript::Type * type):
		E_State(_obj,type?type:typeObject){
}
//! [dtor]
E_EnvironmentState::~E_EnvironmentState(){
}

}
