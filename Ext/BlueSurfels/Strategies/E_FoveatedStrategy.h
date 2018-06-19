/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#ifndef E_BLUE_SURFELS_STRATEGIES_FOVEATEDSTRATEGY_H_
#define E_BLUE_SURFELS_STRATEGIES_FOVEATEDSTRATEGY_H_

#include "E_AbstractSurfelStrategy.h"

#include <MinSG/Ext/BlueSurfels/Strategies/FoveatedStrategy.h>

namespace E_MinSG {
namespace BlueSurfels {

class E_FoveatedStrategy : public E_AbstractSurfelStrategy {
  ES_PROVIDES_TYPE_NAME(FoveatedStrategy)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		
	  static EScript::Type * getTypeObject();
	  static void init(EScript::Namespace & lib);

	  E_FoveatedStrategy(MinSG::BlueSurfels::FoveatedStrategy* obj, EScript::Type* type=nullptr) : E_AbstractSurfelStrategy(obj, type ? type : getTypeObject()) {}
	  virtual ~E_FoveatedStrategy() = default;
	
		const MinSG::BlueSurfels::FoveatedStrategy * operator*() const { return static_cast<const MinSG::BlueSurfels::FoveatedStrategy*>(ref().get()); }
		MinSG::BlueSurfels::FoveatedStrategy * operator*() { return static_cast<MinSG::BlueSurfels::FoveatedStrategy*>(ref().get()); }
};
  
} /* BlueSurfels */
} /* E_MinSG */

ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_FoveatedStrategy, MinSG::BlueSurfels::FoveatedStrategy*, **eObj)

#endif /* end of include guard: E_BLUE_SURFELS_STRATEGIES_FOVEATEDSTRATEGY_H_ */

#endif // MINSG_EXT_BLUE_SURFELS