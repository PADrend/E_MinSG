/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2010-2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT
#include "E_SyncHandler.h"

#include "E_Session.h"
#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/EScript.h>
#include "../../ELibMinSG.h"

#include <MinSG/Ext/D3Fact/Session.h>

using namespace MinSG;
using namespace D3Fact;
namespace E_MinSG{

//! (static)
EScript::Type * E_SyncHandler::getTypeObject() {
	// MinSG.ShaderState ---|> MinSG.State ---|> [Object]
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_MessageHandler::getTypeObject());
	return typeObject.get();
}

// -----

//! (static)
void E_SyncHandler::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<SyncHandler,E_SyncHandler>();

	//! [ESMF] new MinSG.SyncHandler(Session s, Number syncPeriod = 1.0)
	ES_CTOR(typeObject,1,2,(
			E_MessageHandler::create( new SyncHandler((**EScript::assertType<E_Session>(rt, parameter[0])).get(), parameter[1].toFloat(1.0f)))))


	//! [ESMF] MinSG.SyncHandler.getSyncTime()
	ESMF_DECLARE(typeObject,E_SyncHandler,"getSyncTime",0,0,self->getMessageHandler()->getSyncTime())

	//! [ESMF] MinSG.SyncHandler.getPing()
	ESMF_DECLARE(typeObject,E_SyncHandler,"getPing",0,0,self->getMessageHandler()->getPing())


}

// ------------------------------------------------------------

E_SyncHandler::E_SyncHandler(SyncHandler * h,EScript::Type* type):E_MessageHandler(h,type?type:getTypeObject()) {
}

E_SyncHandler::~E_SyncHandler() {
	//dtor
}

} /* namespace E_MinSG */

#endif
