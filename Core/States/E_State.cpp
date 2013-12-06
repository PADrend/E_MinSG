/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_State.h"
#include "../E_FrameContext.h"
#include "../../ELibMinSG.h"

#include <EScript/EScript.h>
#include <E_Util/E_Utils.h>

using namespace MinSG;

namespace E_MinSG {

//! (static)
E_Util::E_ObjectFactory<MinSG::State,E_State> E_State::factorySystem;

// -------------------------

EScript::Type * E_State::getTypeObject() {
	// E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(Object::getTypeObject());
	return typeObject.get();
}

// -----

//! (static)
void E_State::init(EScript::Namespace & lib) {
	
	// converter for Util::ReferenceAttribute<MinSG::State>>   < -- > E_MinSG::E_State
	class Converter : public E_Util::E_Utils::AbstractGenericAttributeConverter {
	public:
		virtual ~Converter() {}

		typedef  Util::ReferenceAttribute<MinSG::State> attr_t;
		
		Object * convertToEScript(const Util::GenericAttribute * const attribute) override {
			const auto * specificAttr = dynamic_cast<const attr_t*>(attribute);
			return specificAttr ? EScript::create(specificAttr->ref().get()) : nullptr;
		}

		Util::GenericAttribute * convertFromEScript(const EScript::ObjPtr & eObject) override {
			auto * eState = eObject.toType<E_State>();
			return eState ? new attr_t(**eState) : nullptr;
		}
	};
	E_Util::E_Utils::registerConverter(new Converter);
	
	// --------------------------------------------------
	
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::State,E_State>();

	declareConstant(&lib,"STATE_OK",				static_cast<uint32_t>(MinSG::State::STATE_OK));
	declareConstant(&lib,"STATE_SKIPPED",			static_cast<uint32_t>(MinSG::State::STATE_SKIPPED));
	declareConstant(&lib,"STATE_SKIP_OTHER_STATES",	static_cast<uint32_t>(MinSG::State::STATE_SKIP_OTHER_STATES));
	declareConstant(&lib,"STATE_SKIP_RENDERING",	static_cast<uint32_t>(MinSG::State::STATE_SKIP_RENDERING));

	//!	[ESMF] thisEObj MinSG.State.disableState(FrameContext, Node, flags)
	ES_MFUNCTION(typeObject, State, "disableState", 1, 3,{
		State * sn = thisObj;
		FrameContext & context = parameter[0].to<MinSG::FrameContext&>(rt);
		if (parameter.count() == 1) {
			sn->disableState(context, nullptr,RenderParam());
		} else {
			Node * node = parameter[1].to<MinSG::Node*>(rt);
			if (parameter.count() == 2) {
				sn->disableState(context, node,RenderParam());
			} else {
				sn->disableState(context, node, parameter[2].toUInt());
			}
		}
		return thisEObj;
	})

	//! [ESMF] thisEObj MinSG.State.enableState(FrameContext, Node, flags)
	ES_MFUNCTION(typeObject, State, "enableState",1, 3, {
		State * sn = thisObj;
		FrameContext & context = parameter[0].to<MinSG::FrameContext&>(rt);
		if (parameter.count() == 1) {
			sn->enableState(context, nullptr,RenderParam());
		} else {
			Node * node = parameter[1].to<MinSG::Node*>(rt);
			if (parameter.count() == 2) {
				sn->enableState(context, node,RenderParam());
			} else {
				sn->enableState(context, node, parameter[2].toUInt());
			}
		}
		return thisEObj;
	})


	//! [ESF] Object MinSG.State.getStateAttribute(String key)
	ES_MFUNCTION(typeObject, State, "getStateAttribute",1, 1, {
		State * state = thisObj;
		Util::GenericAttribute * attribute = state->getAttribute(parameter[0].toString());
		if (attribute == nullptr) {
			return nullptr;
		}
		return E_Util::E_Utils::convertGenericAttributeToEScriptObject(attribute);
	})

	//!	[ESMF] Bool MinSG.State.isActive()	*/
	ES_MFUN(typeObject, const State, "isActive", 0,  0,thisObj->isActive())

	//!	[ESMF] Bool MinSG.State.isTempState()	*/
	ES_MFUN(typeObject, const State, "isTempState", 0,  0,thisObj->isTempState())

	//!	[ESMF] thisEObj MinSG.State.activate()
	ES_MFUN(typeObject, State, "activate", 0, 0,  (thisObj->activate(), thisEObj))

	//!	[ESMF] thisEObj MinSG.State.deactivate()
	ES_MFUN(typeObject, State, "deactivate", 0, 0,  (thisObj->deactivate(), thisEObj))

	//! [ESF] thisEObj MinSG.State.setStateAttribute(string key,value)
	ES_MFUNCTION(typeObject, State, "setStateAttribute",2, 2, {
		Util::GenericAttribute * g=E_Util::E_Utils::convertEScriptObjectToGenericAttribute(parameter[1]);
		thisObj->setAttribute( parameter[0].toString(),g);
		return thisEObj;
	})

	//! [ESF] thisEObj MinSG.State.unsetStateAttribute(string key)
	ES_MFUN(typeObject, State, "unsetStateAttribute",1, 1, 
				(thisObj->unsetAttribute(parameter[0].toString()),thisEObj))


	//!	[ESMF] thisEObj MinSG.State.setTempState(bool)
	ES_MFUN(typeObject, State, "setTempState", 1, 1,  (thisObj->setTempState(parameter[0].to<bool>(rt)), thisEObj))

}

// ------------------------------------------------------------

//! (ctor)
E_State::E_State(State * s, EScript::Type * type) :
		ExtReferenceObject_t(s,type ? type : getTypeObject()) {
}

//! (dtor)
E_State::~E_State() {
	//dtor
}

//! ---|> [Object]
E_State * E_State::clone() const {
	return EScript::create((**this)->clone());
}

//! ---|> Object
std::string E_State::toString() const {
	std::ostringstream s;
	s << "[" << (**this)->getTypeName() << ":" << reinterpret_cast<const void *> ((**this)) << "]";
	return s.str();
}

}
