/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2013 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT

#include "E_ConsoleStream.h"
#include "E_Session.h"

#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

using namespace EScript;
using namespace D3Fact;

namespace E_MinSG {


//! (static)
EScript::Type * E_ConsoleStream::getTypeObject() {
	// E_ConsoleStream ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members 
void E_ConsoleStream::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_ConsoleStream::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	//!	[ESMF] ConsoleStream new ConsoleStream()
	ES_CTOR(typeObject,0,0,new E_ConsoleStream(thisType))

	// void close()
	//! [ESMF] self ConsoleStream.close()
	ESMF_DECLARE(typeObject,E_ConsoleStream,"close",0,0,
				((**self)->close(),self))

	// bool isOpen()
	//! [ESMF] Bool ConsoleStream.isOpen()
	ESMF_DECLARE(typeObject,E_ConsoleStream,"isOpen",0,0,
			Bool::create((**self)->isOpen()))

	// bool open(Session* session)
	//! [ESMF] RESULT ConsoleStream.open(session)
	ESMF_DECLARE(typeObject,E_ConsoleStream,"open",1,1,
			Bool::create((**self)->open((**EScript::assertType<E_Session>(runtime, parameter[0])).get())))

	// std::string read()
	//! [ESMF] String ConsoleStream.read()
	ESMF_DECLARE(typeObject,E_ConsoleStream,"read",0,0,
			String::create((**self)->read()))

	// void write(const std::string& text)
	//! [ESMF] self ConsoleStream.write(String)
	ESMF_DECLARE(typeObject,E_ConsoleStream,"write",1,1,
				((**self)->write(parameter[0].toString()),self))

	// \todo Insert into ELibXXX.cpp:
	//		#ifdef MINSG_EXT_D3FACT

	//		#include "E_ConsoleStream.h"
	//		#endif // MINSG_EXT_D3FACT

	//		...
	//		E_ConsoleStream::init(*lib);
}

}
#endif // MINSG_EXT_D3FACT

