/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2010-2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT
#include "E_ObjectRegistry.h"
#include <EScript/Utils/DeprecatedMacros.h>

using namespace EScript;
using namespace D3Fact;

namespace E_MinSG {

Type* E_ObjectRegistry::typeObject = nullptr;

/**
 * [E_ObjectRegistry] initMembers
 */
void E_ObjectRegistry::init(EScript::Namespace & lib) {
	/// [E_ObjectRegistry] ----|> [Object]
	typeObject = new EScript::Type(Object::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] ObjectRegistry new ObjectRegistry()
	ES_CTOR(typeObject,0,0,
		new E_ObjectRegistry(new ObjectRegistry<Object>())
	)

	ES_MFUNCTION_DECLARE(typeObject, E_ObjectRegistry, "registerObject", 1, 2, {
		if(parameter.count() > 1) {
			if( dynamic_cast<String *>(parameter[0].get()) )
				self->getObjectRegistry()->registerObject(parameter[0].toString(), EScript::assertType<Object>(runtime, parameter[1]));
			else
				self->getObjectRegistry()->registerObject(Util::StringIdentifier(parameter[0].toUInt()), EScript::assertType<Object>(runtime, parameter[1]));
		} else {
			self->getObjectRegistry()->registerObject(EScript::assertType<Object>(runtime, parameter[0]));
		}
		return self;
	})

	ES_MFUNCTION_DECLARE(typeObject, E_ObjectRegistry, "unregisterObject", 1, 1, {
		if( dynamic_cast<String *>(parameter[0].get()) )
			self->getObjectRegistry()->unregisterObject(parameter[0].toString());
		else
			self->getObjectRegistry()->unregisterObject(Util::StringIdentifier(parameter[0].toUInt()));
		return self;
	})

	ESMF_DECLARE(typeObject, E_ObjectRegistry, "getRegisteredObject", 1, 1,
		dynamic_cast<String *>(parameter[0].get()) ?
			self->getObjectRegistry()->getRegisteredObject( parameter[0].toString() ) :
			self->getObjectRegistry()->getRegisteredObject( Util::StringIdentifier(parameter[0].toUInt() ))
	)

	ES_MFUNCTION_DECLARE(typeObject, E_ObjectRegistry, "clear", 0, 0, {
		self->getObjectRegistry()->clear();
		return self;
	})

	ES_MFUNCTION_DECLARE(typeObject, E_ObjectRegistry, "getRegisteredObjects", 0, 0, {
		std::list<Util::Reference<Object> > objects;
		self->getObjectRegistry()->getRegisteredObjects(objects);
		Array* out = Array::create();
		for(auto obj : objects) {
			ObjPtr ptr = obj.get();
			out->pushBack(ptr);
		}
		return out;
	})
}

E_ObjectRegistry::E_ObjectRegistry(ObjectRegistry<Object> * reg, EScript::Type * type):
	Object(type?type:typeObject), objRegistry(reg) {
}

E_ObjectRegistry::~E_ObjectRegistry() {
	delete objRegistry;
	objRegistry = nullptr;
}

}

#endif
