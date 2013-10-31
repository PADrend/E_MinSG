/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2010-2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT

#include <EScript/Utils/DeprecatedMacros.h>
#include <MinSG/Ext/D3Fact/Message.h>
#include <MinSG/Ext/D3Fact/ClientUnit.h>
#include <MinSG/Ext/D3Fact/Session.h>
#include "E_Message.h"
#include "E_MessageDispatcher.h"
#include "E_ClientUnit.h"
#include "E_Session.h"

using namespace EScript;
using namespace D3Fact;

namespace E_MinSG {

Type* E_Session::typeObject = nullptr;

/**
 * [E_Session] initMembers
 */
void E_Session::init(EScript::Namespace & lib) {
	/// [E_Session] ----|> [Object]
	typeObject = new EScript::Type(Object::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] Number Session.getSessionId()
	ESMF_DECLARE(typeObject, E_Session, "getSessionId",0,0,
			Number::create(self->ref()->getSessionId()));

	//! [ESMF] ClientUnit Session.getClient()
	ESMF_DECLARE(typeObject, E_Session, "getClient",0,0,
			new E_ClientUnit(self->ref()->getClient()));

	//! [ESMF] self Session.close()
	ESMF_DECLARE(typeObject, E_Session, "close",0,0,
			(self->ref()->close(), caller));

	//! [ESMF] Bool Session.isClosed()
	ESMF_DECLARE(typeObject, E_Session, "isClosed",0,0,
			Bool::create(self->ref()->isClosed()));

	//! [ESMF] Bool Session.hasReceivedMSG()
	ESMF_DECLARE(typeObject, E_Session, "hasReceivedMSG",0,0,
			Bool::create(self->ref()->hasReceivedMSG()));

	//! [ESMF] Message Session.receiveMSG()
	ESMF_DECLARE(typeObject, E_Session, "receiveMSG",0,0,
			new E_Message(self->ref()->receiveMSG()));

	//! [ESMF] Message Session.createMessage(type, [bodySize, [protocol]])
	ESMF_DECLARE(typeObject, E_Session, "createMessage",1,3,
			new E_Message(self->ref()->createMessage(parameter[0].toInt(), parameter[1].toInt(0), parameter[2].toInt(0))));

	//! [ESMF] self Session.send(Message)
	ESMF_DECLARE(typeObject, E_Session, "send", 1,1,
			(self->ref()->send(EScript::assertType<E_Message>(runtime, parameter[0])->ref()), caller));

	//! [ESMF] Message Session.getDispatcher()
	ESMF_DECLARE(typeObject, E_Session, "getDispatcher",0,0,
			new E_MessageDispatcher(self->ref()->getDispatcher()));
}

}

#endif // MINSG_EXT_D3FACT
