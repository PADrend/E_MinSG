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
#include <MinSG/Ext/D3Fact/MessageHandler.h>
#include <MinSG/Ext/D3Fact/MessageDispatcher.h>

#include "E_Session.h"
#include "E_MessageHandler.h"
#include "E_MessageDispatcher.h"

using namespace EScript;
using namespace D3Fact;

namespace E_MinSG {

Type* E_MessageDispatcher::typeObject = nullptr;

/**
 * [E_ClientUnit] initMembers
 */
void E_MessageDispatcher::init(EScript::Namespace & lib) {
	/// [E_ClientUnit] ----|> [Object]
	typeObject = new EScript::Type(Object::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);

	/*ES_CTOR(typeObject, 1, 1,
			new E_MessageDispatcher(new MessageDispatcher(EScript::assertType<E_Session>(runtime, parameter[0])->ref())));*/

	ESMF_DECLARE(typeObject, E_MessageDispatcher, "dispatch",0,0,
			(self->ref()->dispatch(), caller));

	//! [ESMF] self MessageDispatcher.register(String)
	ES_MFUNCTION_DECLARE(typeObject, E_MessageDispatcher,"register",2,2,{
		Array * a = dynamic_cast<Array *>(parameter[1].get());
		MessageHandler * handler = EScript::assertType<E_MessageHandler>(runtime, parameter[0])->getMessageHandler();
		if (a == nullptr) {
			self->ref()->registerHandler(handler, parameter[1].toInt());
		} else {
			for(EScript::ERef<Iterator> it=a->getIterator();!it->end();it->next()){
				EScript::ObjRef value=(it)->value();
				self->ref()->registerHandler(handler, value.toInt());
			}
		}
		return self;
	});

	ESMF_DECLARE(typeObject, E_MessageDispatcher, "unregister",1,1,
			(self->ref()->unregisterHandler(parameter[0].toInt()), caller));

	ESMF_DECLARE(typeObject, E_MessageDispatcher, "hasHandler",1,1,
			Bool::create(self->ref()->hasHandler(parameter[0].toInt())));

}

}

#endif /* MINSG_EXT_D3FACT */
