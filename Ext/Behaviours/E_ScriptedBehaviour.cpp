/*
	This file is part of the MinSG library extension Behaviours.
	Copyright (C) 2011 Sascha Brandt
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_ScriptedBehaviour.h"
#include <MinSG/Core/Nodes/Node.h>
#include "../../ELibMinSG.h"
#include "../../Core/States/E_State.h"
#include <EScript/EScript.h>
#include <Util/Macros.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

// ------------------------------------------------------------------------------------------------
// ScriptedNodeBehaviour

//!	---|> AbstractBehaviour
AbstractBehaviour::behaviourResult_t ScriptedNodeBehaviour::doExecute() {
	ObjRef eThis = E_Behavior::create(this); // create a temporary E_ScriptedNodeBehaviour
	static const EScript::StringId attrName("doExecute");
	ObjRef result = EScript::callMemberFunction(runtime, eThis.get(), attrName, ParameterValues());
	return static_cast<AbstractBehaviour::behaviourResult_t>(result.toInt());
}
//!	---|> AbstractBehaviour
void ScriptedNodeBehaviour::onInit() {
	ObjRef eThis = E_Behavior::create(this); // create a temporary E_ScriptedNodeBehaviour
	static const EScript::StringId attrName("onInit");
	ObjRef result = EScript::callMemberFunction(runtime, eThis.get(), attrName, ParameterValues());
}

// ------------------------------------------------------------------------------------------------
// E_ScriptedNodeBehaviour

//! (static)
EScript::Type * E_ScriptedNodeBehaviour::getTypeObject() {
	// E_ScriptedNodeBehaviour ---|> E_AbstractNodeBehaviour
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractNodeBehaviour::getTypeObject());
	return typeObject.get();
}


// -----
//! (static)
void E_ScriptedNodeBehaviour::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<ScriptedNodeBehaviour,E_ScriptedNodeBehaviour>();
	typeObject->allowUserInheritance(true);

	//! [ESF] new MinSG.ScriptedNodeBehaviour(Node)
	ES_CTOR(typeObject,1,1, EScript::create(new ScriptedNodeBehaviour( (parameter[0].to<MinSG::Node*>(rt)),thisType,rt) ))

	//!	[ESMF] Number MinSG.ScriptedNodeBehaviour.doExecute() \note ObjectAttribute
	ES_FUN(typeObject,"doExecute",0,0,Number::create(AbstractBehaviour::CONTINUE))
	EScript::markAttributeAsObjectAttribute(typeObject,"doExecute");
																				
	//!	[ESMF] void MinSG.ScriptedNodeBehaviour.onInit() \note ObjectAttribute
	ES_FUN(typeObject,"onInit",0,0,EScript::create(nullptr))
	EScript::markAttributeAsObjectAttribute(typeObject,"onInit");
																				
}


// ------------------------------------------------------------------------------------------------
// ScriptedStateBehaviour

//!	---|> AbstractBehaviour
AbstractBehaviour::behaviourResult_t ScriptedStateBehaviour::doExecute() {
	ObjRef eThis = E_Behavior::create(this); // create a temporary E_ScriptedStateBehaviour
	static const EScript::StringId attrName("doExecute");
	ObjRef result = EScript::callMemberFunction(runtime, eThis.get(), attrName, ParameterValues());
	return static_cast<AbstractBehaviour::behaviourResult_t>(result.toInt());
}
//!	---|> AbstractBehaviour
void ScriptedStateBehaviour::onInit() {
	ObjRef eThis = E_Behavior::create(this); // create a temporary E_ScriptedStateBehaviour
	static const EScript::StringId attrName("onInit");
	ObjRef result = EScript::callMemberFunction(runtime, eThis.get(), attrName, ParameterValues());
}

// ------------------------------------------------------------------------------------------------
// E_ScriptedStateBehaviour

//! (static)
EScript::Type * E_ScriptedStateBehaviour::getTypeObject() {
	// E_ScriptedStateBehaviour ---|> E_AbstractStateBehaviour
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractStateBehaviour::getTypeObject());
	return typeObject.get();
}

// -----
//! (static)
void E_ScriptedStateBehaviour::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<ScriptedStateBehaviour,E_ScriptedStateBehaviour>();
	typeObject->allowUserInheritance(true);

	//! [ESF] new MinSG.ScriptedStateBehaviour(State)
	ES_CTOR(typeObject,1,1, EScript::create(new ScriptedStateBehaviour( parameter[0].to<MinSG::State*>(rt),thisType,rt) ))

	//!	[ESMF] Number MinSG.ScriptedStateBehaviour.doExecute() \note ObjectAttribute
	ES_FUN(typeObject,"doExecute",0,0,Number::create(AbstractBehaviour::CONTINUE))
	EScript::markAttributeAsObjectAttribute(typeObject,"doExecute");
																				
	//!	[ESMF] void MinSG.ScriptedStateBehaviour.onInit() \note ObjectAttribute
	ES_FUN(typeObject,"onInit",0,0,EScript::create(nullptr))
	EScript::markAttributeAsObjectAttribute(typeObject,"onInit");

}

}
