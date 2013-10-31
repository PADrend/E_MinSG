/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2010-2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT

#ifndef E_MESSAGE_H_
#define E_MESSAGE_H_

#include <EScript/EScript.h>
#include <EScript/Objects/ReferenceObject.h>

namespace D3Fact{
class Message;
}

namespace E_MinSG{

class E_Message : public EScript::ReferenceObject<D3Fact::Message*> {
	ES_PROVIDES_TYPE_NAME(Message)
public:
	static EScript::Type* typeObject;
	static void init(EScript::Namespace & lib);

	E_Message(D3Fact::Message * _obj) : ReferenceObject_t(_obj,typeObject) {}
	virtual ~E_Message()	{}
};

}

#endif /* E_MESSAGE_H_ */
#endif /* MINSG_EXT_D3FACT */
