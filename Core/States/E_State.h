/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_STATE_H
#define E_STATE_H

#include <EScript/Objects/ExtReferenceObject.h>
#include <E_Util/E_ObjectFactory.h>
#include <E_Util/E_Utils.h>
#include <MinSG/Core/States/State.h>
#include <Util/Factory/WrapperFactory.h>

namespace E_MinSG {

/**
 *  [E_State] ---|> [ReferenceObject<Util::Reference<MinSG::State> >]
 */
class E_State : public EScript::ExtReferenceObject< Util::Reference<MinSG::State>,EScript::Policies::EqualContent_ComparePolicy,E_Util::Policies::StoreAttrsInAttributeProvider>{
	ES_PROVIDES_TYPE_NAME(State)

		EMINSGAPI static E_Util::E_ObjectFactory<MinSG::State, E_State> factorySystem;
	protected:
		template<class StateType, class E_StateType>
		static void addFactory() {
			factorySystem.registerType(StateType::getClassId(), Util::PolymorphicWrapperCreator<MinSG::State, StateType, E_StateType>());
		}
	public:
		static E_State * create(MinSG::State * state) {
			if(state == nullptr) {
				return nullptr;
			}
			return factorySystem.create(state->getTypeId(), state);
		}
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// --------------

		EMINSGAPI static EScript::Type * getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		EMINSGAPI virtual ~E_State();
		
		const MinSG::State * operator*()const	{	return static_cast<const MinSG::State*>(ref().get());	}
		MinSG::State * operator*()				{	return static_cast<MinSG::State*>(ref().get());	}

		/// --- |> EScript::Object
		EMINSGAPI E_State * clone() const override;
		EMINSGAPI std::string toString() const override;
	protected:
		EMINSGAPI E_State(MinSG::State * s, EScript::Type * type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_State,						MinSG::State*,		**eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::State*, 							E_MinSG::E_State,	obj ? E_MinSG::E_State::create(obj) : nullptr)
ES_CONV_OBJ_TO_EOBJ(Util::Reference<MinSG::State>,			E_MinSG::E_State,	obj.isNotNull() ? E_MinSG::E_State::create(obj.get()) : nullptr)

#endif // E_STATE_H
