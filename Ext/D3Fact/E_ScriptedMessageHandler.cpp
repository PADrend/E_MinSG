/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2010-2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT

#include <EScript/EScript.h>
#include "../../ELibMinSG.h"
#include <E_Util/E_Utils.h>
#include <Util/Macros.h>

#include <MinSG/Ext/D3Fact/Session.h>
#include <MinSG/Ext/D3Fact/Message.h>
#include <MinSG/Ext/D3Fact/MessageHandler.h>
#include <MinSG/Ext/D3Fact/MessageDispatcher.h>

#include "E_Message.h"
#include "E_Session.h"
#include "E_MessageDispatcher.h"
#include "E_ScriptedMessageHandler.h"

using namespace EScript;
using namespace D3Fact;

namespace E_MinSG {

ScriptedMessageHandler::ScriptedMessageHandler(EPtr<Type> type,Runtime & _runtime) :
		MessageHandler(MessageHandler::SYNC), runtime(_runtime), eType(type)  {
}

void ScriptedMessageHandler::handleMessage(Message* msg) {
	ObjRef eThis = E_MessageHandler::create(this); // create a temporary E_MessageHandler
	if(eThis.isNull()){
		WARN("ScriptedMessageHandler::handleMessage");
		return;
	}
	static const EScript::StringId attrName("handleMessage");
	EScript::ObjRef result=EScript::callMemberFunction(runtime, eThis.get(), attrName, ParameterValues( new E_Message(msg) ));
}

// ------------------------------------------------------------------------------------------------

EScript::Type * E_ScriptedMessageHandler::getTypeObject() {
	// E_ScriptedState ---|> E_State
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_MessageHandler::getTypeObject());
	return typeObject.get();
}


//! [E_ClientUnit] initMembers
void E_ScriptedMessageHandler::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<ScriptedMessageHandler,E_ScriptedMessageHandler>();
	typeObject->allowUserInheritance(true);

	ES_CTOR(typeObject, 0, 0, E_MessageHandler::create(new ScriptedMessageHandler(thisType,rt)));

	ES_FUN(typeObject,"handleMessage",1,1,EScript::create(nullptr))
	EScript::markAttributeAsObjectAttribute(typeObject,"handleMessage");
	
}

// ------------------------------------------------------------
//! (ctor)
E_ScriptedMessageHandler::E_ScriptedMessageHandler(ScriptedMessageHandler* _handler) :
		E_MessageHandler(_handler, _handler->getEType().get()) {
}

}

#endif /* MINSG_EXT_D3FACT */
