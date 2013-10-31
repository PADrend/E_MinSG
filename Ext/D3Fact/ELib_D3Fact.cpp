/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2010-2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT
#include "ELib_D3Fact.h"

#include "E_ObjectRegistry.h"
#include "E_ClientUnit.h"
#include "E_Session.h"
#include "E_Message.h"
#include "E_MessageDispatcher.h"
#include "E_MessageHandler.h"
#include "E_ScriptedMessageHandler.h"
#include "E_SyncHandler.h"
#include "E_ConsoleStream.h"

#include <EScript/Utils/DeprecatedMacros.h>

#include <E_Geometry/E_SRT.h>
#include <E_Geometry/E_Vec3.h>

#include <E_Rendering/Mesh/E_Mesh.h>

#include <MinSG/Ext/D3Fact/Message.h>
#include <MinSG/Ext/D3Fact/ClientUnit.h>
#include <MinSG/Ext/D3Fact/Tools.h>
#include <MinSG/Ext/D3Fact/ObjectRegistry.h>
#include <MinSG/Ext/D3Fact/StreamFSProvider.h>
#include <MinSG/Ext/D3Fact/Shape.h>

#include "../../Core/Nodes/E_Node.h"
#include <MinSG/Core/Nodes/Node.h>

#include <Geometry/Matrix3x3.h>
#include <Geometry/SRT.h>
#include <Geometry/Vec3.h>

#include <Util/Encoding.h>
#include <Util/StringIdentifier.h>
#include <Util/GenericAttribute.h>
#include <Util/References.h>

#include <Rendering/Mesh/Mesh.h>

#include <cstdint>
#include <iostream>
#include <vector>
#include <functional>

using namespace D3Fact;
using namespace EScript;

namespace E_MinSG {

static inline void convertSRT(Geometry::SRT & srt, std::vector<uint8_t> & body, size_t offset) {
	Geometry::Matrix3x3f rot;
	Geometry::Vec3f trans;
	size_t off = offset;
	srt.setScale(Tools::getFloat(body,off));
	off+=sizeof(float);

	for(uint_fast8_t r=0; r<3; ++r) {
		for(uint_fast8_t c=0; c<3; ++c) {
			rot.set(r,c, Tools::getFloat(body,off));
			off+=sizeof(float);
		}
	}
	srt.setRotation(rot);

	trans.setX(Tools::getFloat(body,off));
	off+=sizeof(float);
	trans.setY(Tools::getFloat(body,off));
	off+=sizeof(float);
	trans.setZ(Tools::getFloat(body,off));
	off+=sizeof(float);
	srt.setTranslation(trans);
}

static inline void writeSRT(Geometry::SRT & srt, std::vector<uint8_t> & body, size_t offset) {
	size_t off = offset;
	Tools::putFloatBig(body, off, srt.getScale());
	off+=sizeof(float);

	for(uint_fast8_t r=0; r<3; ++r) {
		for(uint_fast8_t c=0; c<3; ++c) {
			Tools::putFloatBig(body, off, srt.getRotation().at(r,c));
			off+=sizeof(float);
		}
	}

	Tools::putFloatBig(body, off, srt.getTranslation().getX());
	off+=sizeof(float);
	Tools::putFloatBig(body, off, srt.getTranslation().getY());
	off+=sizeof(float);
	Tools::putFloatBig(body, off, srt.getTranslation().getZ());
}

static void updateNodePositions(Runtime & runtime, std::vector<uint8_t> & body, size_t offset, ObjectRegistry<Object> * reg) {
	static const StringId ignoreUpdates("ignoreUpdates");
	static const Util::StringIdentifier noSRTUpdates("noSRTUpdates");
	size_t off = offset;
	int32_t size = Tools::getInt(body,off);
	off += sizeof(int32_t);
	int32_t id = 0;
	Object * obj;
	MinSG::Node * node;
	Geometry::SRT srt;
	for(int_fast32_t i=0; i<size; ++i) {

		id = Tools::getInt(body,off);
		off += sizeof(int32_t);
		obj = reg->getRegisteredObject(Util::StringIdentifier(id)); // this is evil!

		if(!obj) {
			off += 13 * sizeof(float);
			continue;
		}

		Attribute attr = obj->getAttribute(ignoreUpdates);
		if(attr.isNotNull() && attr.getValue()->toBool()) {
			off += 13 * sizeof(float);
			continue;
		}

		node = **EScript::assertType<E_Node>(runtime, obj);

		convertSRT(srt, body, off);
		off += 13 * sizeof(float);

		node->setAttribute(noSRTUpdates, Util::GenericAttribute::createBool(true));
		node->setSRT(srt);
		node->unsetAttribute(noSRTUpdates);
	}
}

static void onSRTChanged(Runtime & runtime, MinSG::Node* node) {
	static const EScript::StringId attrName("onSRTChanged");
	static const Util::StringIdentifier noSRTUpdates("noSRTUpdates");
	if(node->isAttributeSet(noSRTUpdates))
		return;
	ObjRef eNode = EScript::create(node);
	const Attribute & fun = eNode->getAttribute(attrName).getValue();
	if(fun.isNotNull())
		EScript::callMemberFunction(runtime, eNode.get(), attrName, ParameterValues());
}

static void fileCopied(uint32_t clientId, const std::string& src, const std::string& dest, bool success) {
	static const Util::StringIdentifier EVENT_SRC("source");
	static const Util::StringIdentifier EVENT_DEST("destination");
	static const Util::StringIdentifier EVENT_SUCC("success");

	ClientUnit* client = ClientUnit::getClient(clientId);
	if(!client)
		return;

	Util::GenericAttributeMap* event = client->createEvent("EVENT_FILE_LOADED", 0);
	event->setValue(EVENT_SUCC, Util::GenericAttribute::createBool(success));
	event->setString(EVENT_SRC, src);
	event->setString(EVENT_DEST, dest);
	client->postEvent(event);

}

void E_D3Fact::init(EScript::Namespace * minsg) {

	Namespace * lib = new Namespace();
	declareConstant(minsg, "D3Fact", lib);

	StreamFSProvider::init();

	E_ObjectRegistry::init(*lib);
	E_ClientUnit::init(*lib);
	E_Session::init(*lib);
	E_Message::init(*lib);
	E_MessageDispatcher::init(*lib);
	E_MessageHandler::init(*lib);
	E_ScriptedMessageHandler::init(*lib);
	E_SyncHandler::init(*lib);
	E_ConsoleStream::init(*lib);

	ES_FUNCTION2(lib, "crc32", 1, 1, {
		return Number::create(Tools::crc32(parameter[0].toString()));
	})

	ES_FUNCTION2(lib, "handleGetAllPositions",2,2,{
		Message * msg = EScript::assertType<E_Message>(rt, parameter[1])->ref();
		ObjectRegistry<Object> * reg = EScript::assertType<E_ObjectRegistry>(rt, parameter[0])->getObjectRegistry();
		updateNodePositions(rt, msg->accessBody(), sizeof(int64_t), reg);
		return EScript::create(nullptr);
	})

	ES_FUNCTION2(lib, "handleSRTUpdate",2,2,{
		Message * msg = EScript::assertType<E_Message>(rt, parameter[1])->ref();
		ObjectRegistry<Object> * reg = EScript::assertType<E_ObjectRegistry>(rt, parameter[0])->getObjectRegistry();
		updateNodePositions(rt, msg->accessBody(), sizeof(int32_t) + sizeof(int64_t), reg);
		return EScript::create(nullptr);
	})

	ES_FUNCTION2(lib, "decodeSRT",1,1,{
		Geometry::SRT srt;
		std::vector<uint8_t> data = Util::decodeBase64(parameter[0].toString());
		convertSRT(srt, data, 0);
		return EScript::create(srt);
	})

	ES_FUNCTION2(lib, "encodeSRT",1,1,{
		Geometry::SRT srt = EScript::assertType<E_Geometry::E_SRT>(rt, parameter[0])->ref();
		std::vector<uint8_t> data(13*sizeof(float));
		writeSRT(srt, data, 0);
		std::string encoded = Util::encodeBase64(data);
		return EScript::create(encoded);
	})

	ES_FUNCTION2(lib, "initSRTListener",1,1,{
		MinSG::Node* root = parameter[0].to<MinSG::Node*>(rt);
		//node->clearTransformationObservers();
 		root->addTransformationObserver(std::bind(onSRTChanged, std::ref(rt), std::placeholders::_1));
		return EScript::create(nullptr);
	})

	ES_FUNCTION2(lib, "copyD3FactFileAsync",3,3,{
		using namespace std::placeholders;
		std::string src = parameter[1].toString();
		std::string dest = parameter[2].toString();
		return EScript::create(Tools::asyncCopy(src, dest, std::bind(fileCopied, parameter[0].toInt(), _1, _2, _3)));
	})

	ES_FUNCTION2(lib, "createShape",2,2,{
		std::string shape = parameter[0].toString();
		Array * points = parameter[1].to<EScript::Array*>(rt);
		std::vector<Geometry::Vec3> v;
		for(const auto & p : *points) {
			v.push_back(EScript::assertType<E_Geometry::E_Vec3>(rt, p.get())->ref());
		}
		return EScript::create(Shape::createShape(shape, v));
	})

	ES_FUNCTION2(lib, "updateShape",3,3,{
		std::string shape = parameter[0].toString();
		Util::Reference<Rendering::Mesh> mesh = parameter[1].to<Rendering::Mesh*>(rt);
		Array * points = parameter[2].to<EScript::Array*>(rt);
		std::vector<Geometry::Vec3> v;
		for(const auto & p : *points) {
			v.push_back(EScript::assertType<E_Geometry::E_Vec3>(rt, p.get())->ref());
		}
		Shape::updateShape(shape, mesh.get(), v);
		return EScript::create(nullptr);
	})
}

}

#endif /* MINSG_EXT_D3FACT */
