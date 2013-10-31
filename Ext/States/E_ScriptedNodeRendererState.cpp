/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_ScriptedNodeRendererState.h"
#include <Util/StringIdentifier.h>
#include <MinSG/Core/Nodes/Node.h>
#include <MinSG/Core/FrameContext.h>
#include "../../ELibMinSG.h"
#include "../../Core/E_RenderParam.h"
#include <EScript/EScript.h>
#include <E_Util/E_Utils.h>
#include <Util/Macros.h>

using namespace MinSG;

namespace E_MinSG {

//! (ctor)
ScriptedNodeRendererState::ScriptedNodeRendererState(const std::string & channel,EScript::EPtr<EScript::Type> type, EScript::Runtime & _runtime) :
		NodeRendererState(channel), runtime(_runtime), eType(type) {
}

//! ---|> State
NodeRendererResult ScriptedNodeRendererState::displayNode(FrameContext & /*context*/, Node * node, const RenderParam & rp){
	EScript::ObjRef eThis = EScript::create(this); // create a temporary E_ScriptedNodeRendererState
	if(eThis.isNull()){
		WARN("ScriptedNodeRendererState::displayNode");
		return NodeRendererResult::PASS_ON;
	}
	EScript::ObjRef eRp = new E_RenderParam(rp);
	EScript::ObjRef eNode = EScript::create(node);

	// call obj.displayNode(Node,RenderParam)
	// \note the 'context'-parameter is ignored, as the E_FrameContext can not be reconstructed from an existing FrameContext-object.
	static const EScript::StringId attrName("displayNode");
	EScript::ObjRef result = EScript::callMemberFunction(runtime, eThis.get(), attrName,EScript::ParameterValues(eNode,eRp));
	return static_cast<NodeRendererResult>(result.toBool());

}


// ------------------------------------------------------------------------------------------------


//! (static)
EScript::Type * E_ScriptedNodeRendererState::getTypeObject() {
	// E_ScriptedNodeRendererState ---|> E_NodeRendererState
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	return typeObject.get();
}



// -----
//! [static]
void E_ScriptedNodeRendererState::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<ScriptedNodeRendererState,E_ScriptedNodeRendererState>();
	typeObject->allowUserInheritance(true);

	//! [ESF] new MinSG.ScriptedNodeRendererState([channel])
	ES_CTOR(typeObject,0,1, EScript::create(
									new ScriptedNodeRendererState( parameter[0].toString( FrameContext::DEFAULT_CHANNEL.toString() ), thisType,rt) ))

	//!	[ESMF] void MinSG.ScriptedNodeRendererState.displayNode((Node,RenderParam) \note ObjectAttribute
	ES_FUN(typeObject,"displayNode",2,2,static_cast<uint32_t>(State::STATE_OK))
	EScript::markAttributeAsObjectAttribute(typeObject,"displayNode");

}

// ------------------------------------------------------------
//! (ctor)
E_ScriptedNodeRendererState::E_ScriptedNodeRendererState(ScriptedNodeRendererState * _state) :
		E_NodeRendererState(_state, _state->getEType().get()) {
}

}
