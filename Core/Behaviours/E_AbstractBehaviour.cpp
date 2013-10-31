/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_AbstractBehaviour.h"

#include "../../ELibMinSG.h"
#include "../Nodes/E_Node.h"
#include "../States/E_State.h"
#include <E_Rendering/E_ParameterStructs.h>

#include <EScript/EScript.h>

#include <iostream>
#include <sstream>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

// --------------------------------------------------------------------------------------------------
// E_AbstractBehaviour

//! (static)
EScript::Type * E_AbstractBehaviour::getTypeObject() {
	// E_AbstractBehaviour ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

// -----

//! [static]
void E_AbstractBehaviour::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());	
	declareConstant(&lib,getClassName(),typeObject);

	//! Number AbstractBehaviour.getCurrentTime()
	ES_MFUN(typeObject, const AbstractBehaviour, "getCurrentTime", 0,0,Number::create(thisObj->getCurrentTime()))

	//! Number AbstractBehaviour.getLastTime()
	ES_MFUN(typeObject, const AbstractBehaviour, "getLastTime", 0,0,Number::create(thisObj->getLastTime()))

	//! Number AbstractBehaviour.getTimeDelta()
	ES_MFUN(typeObject, const AbstractBehaviour, "getTimeDelta", 0,0,Number::create(thisObj->getTimeDelta()))

//	//! Bool AbstractBehaviour.isActive()
//	ES_MFUN(typeObject, const AbstractBehaviour, "isActive", 0,0,Bool::create(thisObj->isActive()))

//	//! thisEObj AbstractBehaviour.activate()
//	ES_MFUN(typeObject, AbstractBehaviour, "activate", 0, 0, (thisObj->activate(), thisEObj))
//
//	//! thisEObj AbstractBehaviour.deactivate()
//	ES_MFUN(typeObject, AbstractBehaviour, "deactivate", 0, 0, (thisObj->deactivate(), thisEObj))

	declareConstant(typeObject,"CONTINUE", Number::create(AbstractBehaviour::CONTINUE));
	declareConstant(typeObject,"FINISHED", Number::create(AbstractBehaviour::FINISHED));

	addFactory<MinSG::AbstractBehaviour,E_AbstractBehaviour>();


	E_AbstractNodeBehaviour::init(lib);
	E_AbstractStateBehaviour::init(lib);
}

// --------------------------------------------------------------------------------------------------
// E_AbstractNodeBehaviour

//! (static)
EScript::Type * E_AbstractNodeBehaviour::getTypeObject() {
	// E_AbstractNodeBehaviour ---|> E_AbstractBehaviour
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractBehaviour::getTypeObject());
	return typeObject.get();
}


//! [static]
void E_AbstractNodeBehaviour::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] Node AbstractNodeBehaviour.getNode()
	ES_MFUN(typeObject, const AbstractNodeBehaviour, "getNode", 0,0,EScript::create(thisObj->getNode()))

	//! [ESMF] seld AbstractNodeBehaviour.setNode(Node)
	ES_MFUN(typeObject, AbstractNodeBehaviour, "setNode", 1,1,(thisObj->setNode(parameter[0].to<MinSG::Node*>(rt)),thisEObj))

	addFactory<MinSG::AbstractNodeBehaviour,E_AbstractNodeBehaviour>();
}

// --------------------------------------------------------------------------------------------------
// E_AbstractStateBehaviour

//! (static)
EScript::Type * E_AbstractStateBehaviour::getTypeObject() {
	// E_AbstractStateBehaviour ---|> E_AbstractBehaviour
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractBehaviour::getTypeObject());
	return typeObject.get();
}


//! [static]
void E_AbstractStateBehaviour::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] State AbstractStateBehaviour.getState()
	ES_MFUN(typeObject, const AbstractStateBehaviour, "getState", 0,0,EScript::create(thisObj->getState()))

	addFactory<MinSG::AbstractStateBehaviour,E_AbstractStateBehaviour>();
}

}
