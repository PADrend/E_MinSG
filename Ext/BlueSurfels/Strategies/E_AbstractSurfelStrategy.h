/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#ifndef E_BLUESURFELS_STRATEGIES_ABSTRACT_STRATEGY_H_
#define E_BLUESURFELS_STRATEGIES_ABSTRACT_STRATEGY_H_

#include <MinSG/Ext/BlueSurfels/Strategies/AbstractSurfelStrategy.h>

#include <E_Util/E_ObjectFactory.h>

#include <EScript/Objects/ReferenceObject.h>
#include <EScript/Objects/Type.h>

namespace E_MinSG {
namespace BlueSurfels {
	
class E_AbstractSurfelStrategy : public EScript::ReferenceObject<Util::Reference<MinSG::BlueSurfels::AbstractSurfelStrategy>> {
		ES_PROVIDES_TYPE_NAME(AbstractSurfelStrategy)  
		static E_Util::E_ObjectFactory<MinSG::BlueSurfels::AbstractSurfelStrategy, E_AbstractSurfelStrategy> factorySystem;
	protected:
		template<class Type, class E_Type>
		static void addFactory() {
			factorySystem.registerType(Type::getClassId(), Util::PolymorphicWrapperCreator<MinSG::BlueSurfels::AbstractSurfelStrategy, Type, E_Type>());
		}
	public:
		static E_AbstractSurfelStrategy * create(MinSG::BlueSurfels::AbstractSurfelStrategy * strategy) {
			return strategy ? factorySystem.create(strategy->getTypeId(), strategy) : nullptr;
		}
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
	public:  
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);
	  
	  const MinSG::BlueSurfels::AbstractSurfelStrategy * operator*() const { return static_cast<const MinSG::BlueSurfels::AbstractSurfelStrategy*>(ref().get()); }
	  MinSG::BlueSurfels::AbstractSurfelStrategy * operator*() { return static_cast<MinSG::BlueSurfels::AbstractSurfelStrategy*>(ref().get()); }
	protected:
		E_AbstractSurfelStrategy(MinSG::BlueSurfels::AbstractSurfelStrategy * obj, EScript::Type * type = nullptr) 
			: ReferenceObject_t(Util::Reference<MinSG::BlueSurfels::AbstractSurfelStrategy>(obj), type ? type : getTypeObject()) { }
	public:
		virtual ~E_AbstractSurfelStrategy() = default;
};

} /* BlueSurfels */
} /* E_MinSG */

ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_AbstractSurfelStrategy, MinSG::BlueSurfels::AbstractSurfelStrategy*, **eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::BlueSurfels::AbstractSurfelStrategy*, E_MinSG::BlueSurfels::E_AbstractSurfelStrategy, E_MinSG::BlueSurfels::E_AbstractSurfelStrategy::create(obj))
ES_CONV_OBJ_TO_EOBJ(Util::Reference<MinSG::BlueSurfels::AbstractSurfelStrategy>, E_MinSG::BlueSurfels::E_AbstractSurfelStrategy, E_MinSG::BlueSurfels::E_AbstractSurfelStrategy::create(obj.get()))

#endif /* end of include guard: E_BLUESURFELS_STRATEGIES_ABSTRACT_STRATEGY_H_ */

#endif // MINSG_EXT_BLUE_SURFELS