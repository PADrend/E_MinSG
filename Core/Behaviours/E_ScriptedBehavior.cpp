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
#include "E_ScriptedBehavior.h"

#include "E_BehaviorStatus.h"
#include "../../ELibMinSG.h"

#include <EScript/EScript.h>

namespace E_MinSG {

using namespace MinSG;
using namespace EScript;

//! ---|> Behavior
void ScriptedBehavior::doPrepareBehaviorStatus(BehaviorStatus & status){
	ObjRef eThis = E_Behavior::create(this); // create a temporary E_ScriptedNodeBehaviour
	static const EScript::StringId attrName("doPrepareBehaviorStatus");
	ObjRef result = EScript::callMemberFunction(runtime, eThis.get(), attrName, ParameterValues( EScript::create(&status) ));
}
//! ---|> Behavior
void ScriptedBehavior::doBeforeInitialExecute(BehaviorStatus & status){
	ObjRef eThis = E_Behavior::create(this); // create a temporary E_ScriptedNodeBehaviour
	static const EScript::StringId attrName("doBeforeInitialExecute");
	ObjRef result = EScript::callMemberFunction(runtime, eThis.get(), attrName, ParameterValues( EScript::create(&status) ));
}

//! ---|> Behavior
Behavior::behaviourResult_t ScriptedBehavior::doExecute2(BehaviorStatus & status){
	ObjRef eThis = E_Behavior::create(this); // create a temporary E_ScriptedNodeBehaviour
	static const EScript::StringId attrName("doExecute");
	ObjRef result = EScript::callMemberFunction(runtime, eThis.get(), attrName, ParameterValues( EScript::create(&status) ));
	if(static_cast<Behavior::behaviourResult_t>(result.toUInt()) == FINISHED){
		return FINISHED;
	}else{
		return CONTINUE;
	}
}
//! ---|> Behavior
void ScriptedBehavior::doFinalize(BehaviorStatus & status){
	ObjRef eThis = E_Behavior::create(this); // create a temporary E_ScriptedNodeBehaviour
	static const EScript::StringId attrName("doFinalize");
	ObjRef result = EScript::callMemberFunction(runtime, eThis.get(), attrName, ParameterValues( EScript::create(&status) ));
}


//! (static)
EScript::Type * E_ScriptedBehavior::getTypeObject() {
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_Behavior::getTypeObject());
	return typeObject.get();
}


//! [static] initMembers
void E_ScriptedBehavior::init(EScript::Namespace & lib) {
	using namespace MinSG;
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<E_MinSG::ScriptedBehavior,E_ScriptedBehavior>();
	typeObject->allowUserInheritance(true);
	
	//! [ESMF] new MinSG.E_ScriptedBehavior()
	ES_CTOR(typeObject,0,0,	EScript::create(new ScriptedBehavior(thisType,rt) ))
		
	//!	[ESMF] void MinSG.ScriptedNodeBehaviour.doPrepareBehaviorStatus(Status) 
	ES_FUN(typeObject,"doPrepareBehaviorStatus",1,1,EScript::create(nullptr))
	EScript::markAttributeAsObjectAttribute(typeObject,"doPrepareBehaviorStatus");
	
	//!	[ESMF] void MinSG.ScriptedNodeBehaviour.doBeforeInitialExecute(Status) 
	ES_FUN(typeObject,"doBeforeInitialExecute",1,1,EScript::create(nullptr))
	EScript::markAttributeAsObjectAttribute(typeObject,"doBeforeInitialExecute");
	
	//!	[ESMF] void MinSG.ScriptedNodeBehaviour.doExecute(Status) 
	ES_FUN(typeObject,"doExecute",1,1,static_cast<uint32_t>(Behavior::CONTINUE))
	EScript::markAttributeAsObjectAttribute(typeObject,"doExecute");
	
	//!	[ESMF] void MinSG.ScriptedNodeBehaviour.doFinalize(Status) 
	ES_FUN(typeObject,"doFinalize",1,1,EScript::create(nullptr))
	EScript::markAttributeAsObjectAttribute(typeObject,"doFinalize");
}

}
