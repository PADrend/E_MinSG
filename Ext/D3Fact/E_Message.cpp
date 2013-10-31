/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2010-2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT

#include <MinSG/Ext/D3Fact/Tools.h>
#include <MinSG/Ext/D3Fact/Message.h>
#include <EScript/Utils/DeprecatedMacros.h>
#include "E_Message.h"
#include <cstdint>
#include <sstream>
#include <vector>

using namespace EScript;
using namespace D3Fact;
using namespace Util;

namespace E_MinSG {

Type* E_Message::typeObject = nullptr;

/**
 * [E_Message] initMembers
 */
void E_Message::init(EScript::Namespace & lib) {
	/// [E_Message] ----|> [Object]
	typeObject = new EScript::Type(Object::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);

	declareConstant(&lib,"TCP",Number::create(Message::TCP));
	declareConstant(&lib,"UDP",Number::create(Message::UDP));

	//! [ESMF] self Message.dispose()
	ESMF_DECLARE(typeObject, E_Message, "dispose",0,0,
			(self->ref()->dispose(), caller));

	//! [ESMF] Message Message.clone()
	ESMF_DECLARE(typeObject, E_Message, "clone",0,0,
			new E_Message(self->ref()->clone()));

	//! [ESMF] Number Message.getClientId()
	ESMF_DECLARE(typeObject, E_Message, "getClientId",0,0,
			Number::create(self->ref()->getClientId()));

	//! [ESMF] Number Message.getSession()
	ESMF_DECLARE(typeObject, E_Message, "getSession",0,0,
			Number::create(self->ref()->getSession()));

	//! [ESMF] Number Message.getOrder()
	ESMF_DECLARE(typeObject, E_Message, "getOrder",0,0,
			Number::create(self->ref()->getOrder()));

	//! [ESMF] Number Message.getType()
	ESMF_DECLARE(typeObject, E_Message, "getType",0,0,
			Number::create(self->ref()->getType()));

	//! [ESMF] Number Message.getProtocol()
	ESMF_DECLARE(typeObject, E_Message, "getProtocol",0,0,
			Number::create(self->ref()->getProtocol()));

	//! [ESMF] Number Message.getBodyLength()
	ESMF_DECLARE(typeObject, E_Message, "getBodyLength",0,0,
			Number::create(self->ref()->getBodyLength()));

	//! [ESMF] Bool Message.getBool([offset])
	ESMF_DECLARE(typeObject, E_Message, "getBool",0,1,
			Bool::create(!self->ref()->getBody().empty() ? Tools::getBoolean(self->ref()->getBody(), parameter[0].toInt(0)) : false));

	//! [ESMF] Number Message.getByte([offset])
	ESMF_DECLARE(typeObject, E_Message, "getByte",0,1,
			Bool::create(!self->ref()->getBody().empty() ? Tools::getByte(self->ref()->getBody(), parameter[0].toInt(0)) : false));

	//! [ESMF] Number Message.getInt([offset])
	ESMF_DECLARE(typeObject, E_Message, "getInt",0,1,
			Number::create(!self->ref()->getBody().empty() ? Tools::getInt(self->ref()->getBody(), parameter[0].toInt(0)) : 0));

	//! [ESMF] Number Message.getLong([offset])
	ESMF_DECLARE(typeObject, E_Message, "getLong",0,1,
			Number::create(!self->ref()->getBody().empty() ? Tools::getLong(self->ref()->getBody(), parameter[0].toInt(0)) : 0));

	//! [ESMF] Number Message.getFloat([offset])
	ESMF_DECLARE(typeObject, E_Message, "getFloat",0,1,
			Number::create(!self->ref()->getBody().empty() ? Tools::getFloat(self->ref()->getBody(), parameter[0].toInt(0)) : 0));

	//! [ESMF] Number Message.getDouble([offset])
	ESMF_DECLARE(typeObject, E_Message, "getDouble",0,1,
			Number::create(!self->ref()->getBody().empty() ? Tools::getDouble(self->ref()->getBody(), parameter[0].toInt(0)) : 0));

	//! [ESMF] String Message.getString([offset])
	ESMF_DECLARE(typeObject, E_Message, "getString",0,1,
			String::create(!self->ref()->getBody().empty() ? Tools::getString(self->ref()->getBody(), parameter[0].toInt(0)) : ""));

	//! [ESMF] self Message.putBool(Bool,[offset])
	ES_MFUNCTION_DECLARE(typeObject, E_Message,"putBool",1,2,{
		std::vector<uint8_t> body = self->ref()->getBody();
		if(parameter.count() > 1 && body.size() >= parameter[1].toUInt() + sizeof(bool)) {
			Tools::putBoolean(body, parameter[1].toUInt(), parameter[0].toBool());
		} else {
			Tools::appendBoolean(body, parameter[0].toBool());
		}
		self->ref()->set(body);
		return self;
	});

	//! [ESMF] self Message.putByte(Number,[offset])
	ES_MFUNCTION_DECLARE(typeObject, E_Message,"putByte",1,2,{
		std::vector<uint8_t> body = self->ref()->getBody();
		if(parameter.count() > 1 && body.size() >= parameter[1].toUInt() + sizeof(int8_t)) {
			Tools::putByte(body, parameter[1].toUInt(), parameter[0].toInt());
		} else {
			Tools::appendByte(body, parameter[0].toInt());
		}
		self->ref()->set(body);
		return self;
	});

	//! [ESMF] self Message.putInt(Number)
	ES_MFUNCTION_DECLARE(typeObject, E_Message,"putInt",1,1,{
		std::vector<uint8_t> body = self->ref()->getBody();
		if(parameter.count() > 1 && body.size() >= parameter[1].toUInt() + sizeof(int32_t)) {
			Tools::putIntBig(body, parameter[1].toUInt(), parameter[0].toInt());
		} else {
			Tools::appendIntBig(body, parameter[0].toInt());
		}
		self->ref()->set(body);
		return self;
	});

	//! [ESMF] self Message.putLong(Number)
	ES_MFUNCTION_DECLARE(typeObject, E_Message,"putLong",1,1,{
		std::vector<uint8_t> body = self->ref()->getBody();
		if(parameter.count() > 1 && body.size() >= parameter[1].toUInt() + sizeof(int64_t)) {
			Tools::putLongBig(body, parameter[1].toUInt(), static_cast<int64_t>(parameter[0].toDouble()));
		} else {
			Tools::appendLongBig(body, static_cast<int64_t>(parameter[0].toDouble()));
		}
		self->ref()->set(body);
		return self;
	});

	//! [ESMF] self Message.putDouble(Number)
	ES_MFUNCTION_DECLARE(typeObject, E_Message,"putDouble",1,1,{
		std::vector<uint8_t> body = self->ref()->getBody();
		if(parameter.count() > 1 && body.size() >= parameter[1].toUInt() + sizeof(double)) {
			Tools::putDoubleBig(body, parameter[1].toUInt(), parameter[0].toDouble());
		} else {
			Tools::appendDoubleBig(body, parameter[0].toDouble());
		}
		self->ref()->set(body);
		return self;
	});

	//! [ESMF] self Message.putFloat(Number)
	ES_MFUNCTION_DECLARE(typeObject, E_Message,"putFloat",1,1,{
		std::vector<uint8_t> body = self->ref()->getBody();
		if(parameter.count() > 1 && body.size() >= parameter[1].toUInt() + sizeof(float)) {
			Tools::putFloatBig(body, parameter[1].toUInt(), parameter[0].toFloat());
		} else {
			Tools::appendFloatBig(body, parameter[0].toFloat());
		}
		self->ref()->set(body);
		return self;
	});

	//! [ESMF] self Message.putString(String)
	ES_MFUNCTION_DECLARE(typeObject, E_Message,"putString",1,1,{
		std::vector<uint8_t> body = self->ref()->getBody();
		if(parameter.count() > 1 && body.size() >= parameter[1].toUInt() + sizeof(int32_t) + parameter[0].toString().size()) {
			Tools::putString(body, parameter[1].toUInt(), parameter[0].toString());
		} else {
			Tools::appendString(body, parameter[0].toString());
		}
		self->ref()->set(body);
		return self;
	});

	//! [ESMF] String Message.toString()
	ES_MFUNCTION_DECLARE(typeObject, E_Message,"toString",0,0,{
		Message* msg = self->ref();
		std::stringstream ss;
		ss << "Message(session=" << msg->getSession() << "; order=" << msg->getOrder();
		ss << "; protocol=" << (msg->getProtocol() == Message::TCP ? "TCP" : "UDP");
		ss << "; type=" << msg->getType() << ")";
		return String::create(ss.str());
	});

}

}

#endif // MINSG_EXT_D3FACT
