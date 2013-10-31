/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2010-2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT

#ifndef E_MESSAGEDISPATCHER_H_
#define E_MESSAGEDISPATCHER_H_

#include <EScript/EScript.h>
#include <E_Util/E_Utils.h>
#include <MinSG/Ext/D3Fact/MessageDispatcher.h>

namespace E_MinSG{

class E_MessageDispatcher : public EScript::ReferenceObject<Util::Reference<D3Fact::MessageDispatcher>> {
	ES_PROVIDES_TYPE_NAME(MessageDispatcher)
public:
	static EScript::Type* typeObject;
	static void init(EScript::Namespace & lib);

	E_MessageDispatcher(D3Fact::MessageDispatcher * _obj) : ReferenceObject_t(_obj,typeObject) {}
	virtual ~E_MessageDispatcher()	{}
};

}
#endif /* E_MESSAGEDISPATCHER_H_ */
#endif /* MINSG_EXT_D3FACT */
