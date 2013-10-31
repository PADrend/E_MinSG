/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2010-2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT

#include <EScript/Utils/DeprecatedMacros.h>

#include <MinSG/Ext/D3Fact/Session.h>
#include <MinSG/Ext/D3Fact/Message.h>
#include <MinSG/Ext/D3Fact/MessageHandler.h>
#include <MinSG/Ext/D3Fact/MessageDispatcher.h>

#include "E_Message.h"
#include "E_Session.h"
#include "E_MessageHandler.h"
#include "E_MessageDispatcher.h"

using namespace EScript;
using namespace D3Fact;

namespace E_MinSG {

//! (static)
E_Util::E_ObjectFactory<D3Fact::MessageHandler,E_MessageHandler> E_MessageHandler::factorySystem;

// -------------------------

EScript::Type * E_MessageHandler::getTypeObject() {
	// E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(Object::getTypeObject());
	return typeObject.get();
}

/**
 * [E_ClientUnit] initMembers
 */
void E_MessageHandler::init(EScript::Namespace & lib) {
	/// [E_ClientUnit] ----|> [Object]
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MessageHandler,E_MessageHandler>();

	ESMF_DECLARE(typeObject, E_MessageHandler, "handleMessages",0,0,
			(self->getMessageHandler()->handleMessages(), caller));
}


// ------------------------------------------------------------

//! (ctor)
E_MessageHandler::E_MessageHandler(MessageHandler * mh, Type * type) :
		ExtReferenceObject_t(mh,type ? type : getTypeObject()) {
}

//! ---|> [Object]
E_MessageHandler * E_MessageHandler::clone() const {
	return E_MessageHandler::create(getMessageHandler()->clone());
}

//! ---|> Object
std::string E_MessageHandler::toString() const {
	std::ostringstream s;
	s << "[" << getMessageHandler()->getTypeName() << ":" << reinterpret_cast<const void *> (getMessageHandler()) << "]";
	return s.str();
}

}

#endif /* MINSG_EXT_D3FACT */
