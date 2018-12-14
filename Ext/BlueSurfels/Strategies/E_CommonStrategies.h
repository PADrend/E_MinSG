/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#ifndef E_BLUE_SURFELS_STRATEGIES_COMMON_H_
#define E_BLUE_SURFELS_STRATEGIES_COMMON_H_

#include "E_AbstractSurfelStrategy.h"

#include <MinSG/Ext/BlueSurfels/Strategies/CommonStrategies.h>

namespace E_MinSG {
namespace BlueSurfels {
  
class E_FixedSizeStrategy : public E_AbstractSurfelStrategy {
	ES_PROVIDES_TYPE_NAME(FixedSizeStrategy)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		static EScript::Type * getTypeObject() {
			static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractSurfelStrategy::getTypeObject());
			return typeObject.get();
		}
		static void init(EScript::Namespace & lib);
		E_FixedSizeStrategy(MinSG::BlueSurfels::FixedSizeStrategy* obj, EScript::Type* type=nullptr) : E_AbstractSurfelStrategy(obj, type ? type : getTypeObject()) {}
		virtual ~E_FixedSizeStrategy() = default;
		const MinSG::BlueSurfels::FixedSizeStrategy * operator*() const { return static_cast<const MinSG::BlueSurfels::FixedSizeStrategy*>(ref().get()); }
		MinSG::BlueSurfels::FixedSizeStrategy * operator*() { return static_cast<MinSG::BlueSurfels::FixedSizeStrategy*>(ref().get()); }
};
  
class E_FixedCountStrategy : public E_AbstractSurfelStrategy {
	ES_PROVIDES_TYPE_NAME(FixedCountStrategy)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		static EScript::Type * getTypeObject() {
			static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractSurfelStrategy::getTypeObject());
			return typeObject.get();
		}
		static void init(EScript::Namespace & lib);
		E_FixedCountStrategy(MinSG::BlueSurfels::FixedCountStrategy* obj, EScript::Type* type=nullptr) : E_AbstractSurfelStrategy(obj, type ? type : getTypeObject()) {}
		virtual ~E_FixedCountStrategy() = default;
		const MinSG::BlueSurfels::FixedCountStrategy * operator*() const { return static_cast<const MinSG::BlueSurfels::FixedCountStrategy*>(ref().get()); }
		MinSG::BlueSurfels::FixedCountStrategy * operator*() { return static_cast<MinSG::BlueSurfels::FixedCountStrategy*>(ref().get()); }
};
  
class E_FactorStrategy : public E_AbstractSurfelStrategy {
	ES_PROVIDES_TYPE_NAME(FactorStrategy)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		static EScript::Type * getTypeObject() {
			static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractSurfelStrategy::getTypeObject());
			return typeObject.get();
		}
		static void init(EScript::Namespace & lib);
		E_FactorStrategy(MinSG::BlueSurfels::FactorStrategy* obj, EScript::Type* type=nullptr) : E_AbstractSurfelStrategy(obj, type ? type : getTypeObject()) {}
		virtual ~E_FactorStrategy() = default;
		const MinSG::BlueSurfels::FactorStrategy * operator*() const { return static_cast<const MinSG::BlueSurfels::FactorStrategy*>(ref().get()); }
		MinSG::BlueSurfels::FactorStrategy * operator*() { return static_cast<MinSG::BlueSurfels::FactorStrategy*>(ref().get()); }
};
  
class E_ReferencePointStrategy : public E_AbstractSurfelStrategy {
	ES_PROVIDES_TYPE_NAME(ReferencePointStrategy)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		static EScript::Type * getTypeObject() {
			static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractSurfelStrategy::getTypeObject());
			return typeObject.get();
		}
		static void init(EScript::Namespace & lib);
		E_ReferencePointStrategy(MinSG::BlueSurfels::ReferencePointStrategy* obj, EScript::Type* type=nullptr) : E_AbstractSurfelStrategy(obj, type ? type : getTypeObject()) {}
		virtual ~E_ReferencePointStrategy() = default;
		const MinSG::BlueSurfels::ReferencePointStrategy * operator*() const { return static_cast<const MinSG::BlueSurfels::ReferencePointStrategy*>(ref().get()); }
		MinSG::BlueSurfels::ReferencePointStrategy * operator*() { return static_cast<MinSG::BlueSurfels::ReferencePointStrategy*>(ref().get()); }
};

class E_BlendStrategy : public E_AbstractSurfelStrategy {
	ES_PROVIDES_TYPE_NAME(BlendStrategy)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		static EScript::Type * getTypeObject() {
			static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractSurfelStrategy::getTypeObject());
			return typeObject.get();
		}
		static void init(EScript::Namespace & lib);
		E_BlendStrategy(MinSG::BlueSurfels::BlendStrategy* obj, EScript::Type* type=nullptr) : E_AbstractSurfelStrategy(obj, type ? type : getTypeObject()) {}
		virtual ~E_BlendStrategy() = default;
		const MinSG::BlueSurfels::BlendStrategy * operator*() const { return static_cast<const MinSG::BlueSurfels::BlendStrategy*>(ref().get()); }
		MinSG::BlueSurfels::BlendStrategy * operator*() { return static_cast<MinSG::BlueSurfels::BlendStrategy*>(ref().get()); }
};

class E_DebugStrategy : public E_AbstractSurfelStrategy {
	ES_PROVIDES_TYPE_NAME(DebugStrategy)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		static EScript::Type * getTypeObject() {
			static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractSurfelStrategy::getTypeObject());
			return typeObject.get();
		}
		static void init(EScript::Namespace & lib);
		E_DebugStrategy(MinSG::BlueSurfels::DebugStrategy* obj, EScript::Type* type=nullptr) : E_AbstractSurfelStrategy(obj, type ? type : getTypeObject()) {}
		virtual ~E_DebugStrategy() = default;
		const MinSG::BlueSurfels::DebugStrategy * operator*() const { return static_cast<const MinSG::BlueSurfels::DebugStrategy*>(ref().get()); }
		MinSG::BlueSurfels::DebugStrategy * operator*() { return static_cast<MinSG::BlueSurfels::DebugStrategy*>(ref().get()); }
};

namespace E_CommonStrategies {
void init(EScript::Namespace & lib);
} /* E_CommonStrategies */

} /* BlueSurfels */
} /* MinSG */

ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_FixedSizeStrategy, MinSG::BlueSurfels::FixedSizeStrategy*, **eObj)
ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_FixedCountStrategy, MinSG::BlueSurfels::FixedCountStrategy*, **eObj)
ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_FactorStrategy, MinSG::BlueSurfels::FactorStrategy*, **eObj)
ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_BlendStrategy, MinSG::BlueSurfels::BlendStrategy*, **eObj)
ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_ReferencePointStrategy, MinSG::BlueSurfels::ReferencePointStrategy*, **eObj)
ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_DebugStrategy, MinSG::BlueSurfels::DebugStrategy*, **eObj)

#endif /* end of include guard: E_BLUE_SURFELS_STRATEGIES_COMMON_H_ */

#endif // MINSG_EXT_BLUE_SURFELS