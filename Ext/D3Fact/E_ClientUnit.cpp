/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2010-2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT

#include <MinSG/Ext/D3Fact/Session.h>
#include <MinSG/Ext/D3Fact/ClientUnit.h>
#include <Util/GenericAttribute.h>
#include <EScript/Utils/DeprecatedMacros.h>
#include <E_Util/E_Utils.h>
#include "E_Session.h"
#include "E_ClientUnit.h"

using namespace EScript;
using namespace D3Fact;

namespace E_MinSG {

Type* E_ClientUnit::typeObject = nullptr;

/**
 * [E_ClientUnit] initMembers
 */
void E_ClientUnit::init(EScript::Namespace & lib) {
	/// [E_ClientUnit] ----|> [Object]
	typeObject = new EScript::Type(Object::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);

	ES_CTOR(typeObject, 3, 5,
			new E_ClientUnit(new ClientUnit(parameter[0].toString(),parameter[1].toInt(),parameter[2].toInt(),parameter[3].toInt(1),parameter[4].toInt(2000))));

	ESMF_DECLARE(typeObject, E_ClientUnit, "connect",0,0,
			Bool::create(self->ref()->connect()));

	ESMF_DECLARE(typeObject, E_ClientUnit, "close",0,0,
			(self->ref()->close(), caller));

	ESMF_DECLARE(typeObject, E_ClientUnit, "isConnected",0,0,
			Bool::create(self->ref()->isConnected()));

	ESMF_DECLARE(typeObject, E_ClientUnit, "getClientId",0,0,
			Number::create(self->ref()->getClientId()));

	ESMF_DECLARE(typeObject, E_ClientUnit, "startSession",0,0,
			Number::create(self->ref()->startSession()));

	ES_MFUNCTION_DECLARE(typeObject, E_ClientUnit, "getSession",1,1,{
			if(self->ref()->getSession(parameter[0].toInt()))
				return new E_Session((**self)->getSession(parameter[0].toInt()));
			else
				return EScript::create(nullptr);
	});

	ESMF_DECLARE(typeObject, E_ClientUnit, "dispatchMessages",0,1,
			(self->ref()->dispatchMessages(parameter[0].toUInt(0xffffffff)), caller));

	ES_MFUNCTION_DECLARE(typeObject, E_ClientUnit,"pollEvent",0,0,{
		Util::GenericAttribute* event = self->ref()->pollEvent();
		return E_Util::E_Utils::convertGenericAttributeToEScriptObject(event);
	});
}

}

#endif // MINSG_EXT_D3FACT
