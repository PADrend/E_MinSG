/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2010-2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT

#ifndef E_SCRIPTEDMESSAGEHANDLER_H_
#define E_SCRIPTEDMESSAGEHANDLER_H_

#include "E_MessageHandler.h"

namespace E_MinSG{

class E_ScriptedMessageHandler;

class ScriptedMessageHandler : public D3Fact::MessageHandler {
	PROVIDES_TYPE_NAME(ScriptedMessageHandler)

public:
	ScriptedMessageHandler(EScript::EPtr<EScript::Type> type,EScript::Runtime & runtime);
	virtual ~ScriptedMessageHandler()	{}

	EScript::EPtr<EScript::Type> getEType(){	return eType;	}

	virtual ScriptedMessageHandler* clone() const 	{	return new ScriptedMessageHandler(*this);	}
protected:
	virtual void handleMessage(D3Fact::Message* msg);
private:
	ScriptedMessageHandler(const ScriptedMessageHandler & other) : MessageHandler(MessageHandler::SYNC), runtime(other.runtime) {}

	EScript::Runtime & runtime;
	EScript::ERef<EScript::Type> eType;
};

class E_ScriptedMessageHandler : public E_MessageHandler {
	ES_PROVIDES_TYPE_NAME(ScriptedMessageHandler)

public:
	// ---
	template<class, class, class> friend class Util::PolymorphicWrapperCreator;
	static EScript::Type * getTypeObject();
	static void init(EScript::Namespace & lib);

	virtual ~E_ScriptedMessageHandler()	{}
	inline ScriptedMessageHandler * get()const		{	return static_cast<ScriptedMessageHandler*>(ref().get());	}

protected:
	E_ScriptedMessageHandler(ScriptedMessageHandler* handler);
};

}
#endif /* E_SCRIPTEDMESSAGEHANDLER_H_ */
#endif /* MINSG_EXT_D3FACT */
