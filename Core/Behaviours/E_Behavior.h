/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_Behavior_H
#define __E_Behavior_H

#include <EScript/Objects/ExtReferenceObject.h>
#include <E_Util/E_Utils.h>
#include <E_Util/E_ObjectFactory.h>
#include <MinSG/Core/Behaviours/Behavior.h>
#include <Util/Factory/WrapperFactory.h>


namespace E_MinSG{

/***
 **   E_Behavior ---|> EScript::Object
 **     |
 **     ------> MinSG::Behavior
 **/
class E_Behavior : public EScript::ExtReferenceObject< Util::Reference<MinSG::Behavior>,EScript::Policies::EqualContent_ComparePolicy,E_Util::Policies::StoreAttrsInAttributeProvider>{
	ES_PROVIDES_TYPE_NAME(Behavior)

	//!	@name Behaviour -> E_Behaviour
	//	@{
	private:
		EMINSGAPI static E_Util::E_ObjectFactory<MinSG::Behavior, E_Behavior> factorySystem;
	protected:
		template<class BehaviorType, class E_BehaviorType>
		static void addFactory() {
			factorySystem.registerType(BehaviorType::getClassId(), Util::PolymorphicWrapperCreator<MinSG::Behavior, BehaviorType, E_BehaviorType>());
		}
	public:
		static E_Behavior * create(MinSG::Behavior * behavior) {
			if(behavior == nullptr) 
				return nullptr;
			return factorySystem.create(behavior->getTypeId(), behavior);
		}
	//	@}

		// ---
		EMINSGAPI static EScript::Type* getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		E_Behavior(MinSG::Behavior * behavior, EScript::Type* type=nullptr) : ExtReferenceObject_t(behavior,type?type:getTypeObject()) {}
		virtual ~E_Behavior()	{}

		MinSG::Behavior * operator*()const	{	return ref().get();	}
		MinSG::Behavior * get()const		{	return ref().get();	}
};


}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_Behavior,						MinSG::Behavior*,		**eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::Behavior*, 							E_MinSG::E_Behavior,	E_MinSG::E_Behavior::create(obj))

#endif // __E_Behavior_H
