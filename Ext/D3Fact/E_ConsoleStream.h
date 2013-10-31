/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2013 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT

#ifndef E_D3FACT_E_CONSOLESTREAM_H_
#define E_D3FACT_E_CONSOLESTREAM_H_

#include <EScript/Objects/ReferenceObject.h>
#include <E_Util/E_Utils.h>
#include <MinSG/Ext/D3Fact/ConsoleStream.h>


namespace EScript {
class Namespace;
class Type;
}

namespace E_MinSG {


/*!	EScript wrapper class for D3Fact::ConsoleStream

		E_ConsoleStream ---|> EScript::ReferenceObject<D3Fact::ConsoleStream>
			|
			--------------> D3Fact::ConsoleStream		*/
class E_ConsoleStream : public EScript::ReferenceObject<Util::Reference<D3Fact::ConsoleStream>> {
		ES_PROVIDES_TYPE_NAME(ConsoleStream)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_ConsoleStream(EScript::Type * type=nullptr) : 
				ReferenceObject_t(new D3Fact::ConsoleStream(), type ? type : E_ConsoleStream::getTypeObject()) {}
		E_ConsoleStream(D3Fact::ConsoleStream* _obj,EScript::Type * type=nullptr) :
				ReferenceObject_t(_obj, type ? type : E_ConsoleStream::getTypeObject()) {}
		virtual ~E_ConsoleStream() {}

};
}

#endif // E_D3FACT_E_CONSOLESTREAM_H_
#endif // MINSG_EXT_D3FACT

