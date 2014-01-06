/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_ScriptedState.h"
#include <MinSG/Core/Nodes/Node.h>
#include "../../ELibMinSG.h"
#include "../../Core/E_RenderParam.h"
#include <EScript/EScript.h>
#include <E_Util/E_Utils.h>
#include <Util/Macros.h>

using namespace MinSG;

namespace E_MinSG {

//! (ctor)
ScriptedState::ScriptedState(EScript::EPtr<EScript::Type> type, EScript::Runtime & _runtime) :
		State(), runtime(_runtime), eType(type) {
}

//! ---|> State
State::stateResult_t ScriptedState::doEnableState(MinSG::FrameContext &, MinSG::Node * node, const MinSG::RenderParam & rp) {
	EScript::ObjRef eThis = EScript::create(this); // create a temporary E_ScriptedState
	if(eThis.isNull()){
		WARN("ScriptedState::doEnableState");
		return State::STATE_OK;
	}
	EScript::ObjRef eRp = new E_RenderParam(rp);
	EScript::ObjRef eNode = EScript::create(node);

	// call obj.doEnableState(Node,RenderParam)
	// \note the 'context'-parameter is ignored, as the E_FrameContext can not be reconstructed from an existing FrameContext-object.
	static const EScript::StringId attrName("doEnableState");
	EScript::ObjRef result = EScript::callMemberFunction(runtime, eThis.get(), attrName,
												EScript::ParameterValues(eNode,eRp));
	return static_cast<State::stateResult_t>(result.toUInt());

}

//! ---|> State
void ScriptedState::doDisableState(MinSG::FrameContext &,  MinSG::Node * node, const MinSG::RenderParam & rp) {
	EScript::ObjRef eThis = EScript::create(this); // create a temporary E_ScriptedState
	if(eThis.isNull()){
		WARN("ScriptedState::doDisableState");
		return;
	}
	EScript::ObjRef eRp = new E_RenderParam(rp);
	EScript::ObjRef eNode = EScript::create(node);

	// call obj.doDisableState(Node,RenderParam)
	// \note the 'context'-parameter is ignored, as the E_FrameContext can not be reconstructed from an existing FrameContext-object.
	static const EScript::StringId attrName("doDisableState");
	EScript::ObjRef result = EScript::callMemberFunction(runtime, eThis.get(), attrName,
												EScript::ParameterValues(eNode,eRp));
}


// ------------------------------------------------------------------------------------------------


//! (static)
EScript::Type * E_ScriptedState::getTypeObject() {
	// E_ScriptedState ---|> E_State
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}


// -----
//! [static]
void E_ScriptedState::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<ScriptedState,E_ScriptedState>();
	typeObject->allowUserInheritance(true);

	//! [ESF] new MinSG.ScriptedState()
	ES_CTOR(typeObject,0,0, EScript::create(new ScriptedState( thisType,rt) ))


	//!	[ESMF] void MinSG.ScriptedState.doEnableState(Node,RenderParam) \note ObjectAttribute
	ES_FUN(typeObject,"doEnableState",2,2,(EScript::Number::create(State::STATE_OK)))
	EScript::markAttributeAsObjectAttribute(typeObject,"doEnableState");

	//!	[ESMF] void MinSG.ScriptedState.doDisableState(Node,RenderParam) \note ObjectAttribute
	ES_FUN(typeObject,"doDisableState",2,2,(EScript::Number::create(State::STATE_OK)))
	EScript::markAttributeAsObjectAttribute(typeObject,"doDisableState");

}

// ------------------------------------------------------------
//! (ctor)
E_ScriptedState::E_ScriptedState(ScriptedState * _state) :
		E_State(_state, _state->getEType().get()) {
}

}
