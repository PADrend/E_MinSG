/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2010-2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT

#ifndef E_CLIENTUNIT_H_
#define E_CLIENTUNIT_H_

#include <EScript/EScript.h>
#include <EScript/Objects/ReferenceObject.h>
#include <E_Util/E_Utils.h>
#include <MinSG/Ext/D3Fact/ClientUnit.h>


namespace E_MinSG{

class E_ClientUnit : public EScript::ReferenceObject<Util::Reference<D3Fact::ClientUnit>> {
	ES_PROVIDES_TYPE_NAME(ClientUnit)
public:
	static EScript::Type* typeObject;
	static void init(EScript::Namespace & lib);

	E_ClientUnit(D3Fact::ClientUnit * _obj) : ReferenceObject_t(_obj,typeObject) {}
	virtual ~E_ClientUnit()	{}
};

}

#endif /* E_CLIENTUNIT_H_ */
#endif // MINSG_EXT_D3FACT
