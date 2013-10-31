/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_BehaviorStatus.h"
#include "E_Behavior.h"
#include "../Nodes/E_Node.h"
#include "../States/E_State.h"

#include <MinSG/Core/Behaviours/BehaviorStatusExtensions.h>
#include <Util/ObjectExtension.h>

#include <EScript/EScript.h>


namespace E_MinSG {


//! (static)
EScript::Type * E_BehaviorStatus::getTypeObject() {
	// E_BehaviorStatus ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

// -----

//! [static]
void E_BehaviorStatus::init(EScript::Namespace & lib) {
	// converter for Util::ReferenceAttribute<MinSG::BehaviorStatus>   < -- > E_MinSG::E_BehaviorStatus
	class Converter : public E_Util::E_Utils::AbstractGenericAttributeConverter {
	public:
		virtual ~Converter() {}

		typedef  Util::ReferenceAttribute<MinSG::BehaviorStatus> attr_t;
		
		Object * convertToEScript(const Util::GenericAttribute * const attribute) override {
			const auto * attr = dynamic_cast<const attr_t*>(attribute);
			return attr ? EScript::create(attr->ref().get()) : nullptr;
		}

		Util::GenericAttribute * convertFromEScript(const EScript::ObjPtr & eObject) override {
			auto * eStatus = eObject.toType<E_BehaviorStatus>();
			return eStatus ? new attr_t(**eStatus) : nullptr;
		}
	};
	E_Util::E_Utils::registerConverter(new Converter);
	
	// --------------------------------------------------
		
	using namespace EScript;
	using namespace MinSG;

	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());	
	declareConstant(&lib,getClassName(),typeObject);


	//! Number BehaviorStatus.getBehavior()
	ES_MFUN(typeObject, const BehaviorStatus, "getBehavior", 0,0, EScript::create(thisObj->getBehavior()))

	//! Number BehaviorStatus.getCurrentTime()
	ES_MFUN(typeObject, const BehaviorStatus, "getCurrentTime", 0,0, thisObj->getCurrentTime())

	//! Number BehaviorStatus.getTimeDelta()
	ES_MFUN(typeObject, const BehaviorStatus, "getTimeDelta", 0,0, thisObj->getTimeDelta())

	//! Number BehaviorStatus.getLastTime()
	ES_MFUN(typeObject, const BehaviorStatus, "getLastTime", 0,0, thisObj->getLastTime())

	//! Number BehaviorStatus.getStartingTime()
	ES_MFUN(typeObject, const BehaviorStatus, "getStartingTime", 0,0, thisObj->getStartingTime())
	
	//! Bool BehaviorStatus.isActive()
	ES_MFUN(typeObject, const BehaviorStatus, "isActive", 0,0, thisObj->isActive())

	//! Bool BehaviorStatus.isFinished()
	ES_MFUN(typeObject, const BehaviorStatus, "isFinished", 0,0, thisObj->isFinished())

	//! Bool BehaviorStatus.isNew()
	ES_MFUN(typeObject, const BehaviorStatus, "isNew", 0,0, thisObj->isNew())
	
	
	//! Node|void getReferencedNode()
	ES_MFUNCTION(typeObject, const BehaviorStatus, "getReferencedNode" ,0,0,{
		const auto nodeRef = Util::getObjectExtension<BehaviorNodeReference>( thisObj ); 	//! 	\see BehaviorNodeReference
		if(nodeRef){
			return EScript::create( nodeRef->getNode() );
		}else{
			return EScript::create(nullptr);
		}
	})
	//! State|void getReferencedState()
	ES_MFUNCTION(typeObject, const BehaviorStatus, "getReferencedState" ,0,0,{
		const auto nodeRef = Util::getObjectExtension<BehaviorStateReference>( thisObj ); 	//! 	\see BehaviorStateReference
		if(nodeRef){
			return EScript::create( nodeRef->getState() );
		}else{
			return EScript::create(nullptr);
		}
	})

}

}
