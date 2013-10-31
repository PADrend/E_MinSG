/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2010-2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT

#ifndef E_OBJECTREGISTRY_H_
#define E_OBJECTREGISTRY_H_

#include <EScript/EScript.h>
#include <MinSG/Ext/D3Fact/ObjectRegistry.h>

namespace E_MinSG {

class E_ObjectRegistry: public EScript::Object {
	ES_PROVIDES_TYPE_NAME(ObjectRegistry)
	public:
		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		E_ObjectRegistry(D3Fact::ObjectRegistry<EScript::Object> * reg, EScript::Type * type=nullptr);
		virtual ~E_ObjectRegistry();


		D3Fact::ObjectRegistry<EScript::Object> * getObjectRegistry() const{
			return objRegistry;
		}
	protected:
		D3Fact::ObjectRegistry<EScript::Object> * objRegistry;
};
}

#endif /* E_OBJECTREGISTRY_H_ */
#endif
