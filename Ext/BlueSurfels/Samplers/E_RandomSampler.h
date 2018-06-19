/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#ifndef E_MINSG_EXT_RANDOM_SURFEL_GENERATOR_H_
#define E_MINSG_EXT_RANDOM_SURFEL_GENERATOR_H_

#include "E_AbstractSurfelSampler.h"

#include <MinSG/Ext/BlueSurfels/Samplers/RandomSampler.h>

namespace E_MinSG {
namespace BlueSurfels {

class E_RandomSampler : public E_AbstractSurfelSampler {
  ES_PROVIDES_TYPE_NAME(RandomSampler)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		
	  static EScript::Type * getTypeObject();
	  static void init(EScript::Namespace & lib);

	  E_RandomSampler(MinSG::BlueSurfels::RandomSampler* obj, EScript::Type* type=nullptr) : E_AbstractSurfelSampler(obj, type ? type : getTypeObject()) {}
	  virtual ~E_RandomSampler() = default;
	
		const MinSG::BlueSurfels::RandomSampler * operator*() const { return static_cast<const MinSG::BlueSurfels::RandomSampler*>(ref().get()); }
		MinSG::BlueSurfels::RandomSampler * operator*() { return static_cast<MinSG::BlueSurfels::RandomSampler*>(ref().get()); }
};	

} /* BlueSurfels */
} /* MinSG */

ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_RandomSampler, MinSG::BlueSurfels::RandomSampler*, **eObj)

#endif /* end of include guard: E_MINSG_EXT_RANDOM_SURFEL_GENERATOR_H_ */
#endif // MINSG_EXT_BLUE_SURFELS