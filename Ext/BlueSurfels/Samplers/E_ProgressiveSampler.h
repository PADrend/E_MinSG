/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2014 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2016-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#ifndef E_MINSG_EXT_BLUESURFELS_PROGRESSIVE_SAMPLER_H_
#define E_MINSG_EXT_BLUESURFELS_PROGRESSIVE_SAMPLER_H_

#include "E_AbstractSurfelSampler.h"

#include <MinSG/Ext/BlueSurfels/Samplers/ProgressiveSampler.h>

namespace E_MinSG {
namespace BlueSurfels {	
		
class E_ProgressiveSampler : public E_AbstractSurfelSampler {
  ES_PROVIDES_TYPE_NAME(ProgressiveSampler)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		
	  static EScript::Type * getTypeObject();
	  static void init(EScript::Namespace & lib);

	  E_ProgressiveSampler(MinSG::BlueSurfels::ProgressiveSampler* obj, EScript::Type* type=nullptr) : E_AbstractSurfelSampler(obj, type ? type : getTypeObject()) {}
	  virtual ~E_ProgressiveSampler() = default;
	
		const MinSG::BlueSurfels::ProgressiveSampler * operator*() const { return static_cast<const MinSG::BlueSurfels::ProgressiveSampler*>(ref().get()); }
		MinSG::BlueSurfels::ProgressiveSampler * operator*() { return static_cast<MinSG::BlueSurfels::ProgressiveSampler*>(ref().get()); }
};
	
} /* BlueSurfels */
} /* E_MinSG */

ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_ProgressiveSampler, MinSG::BlueSurfels::ProgressiveSampler*, **eObj)

#endif /* end of include guard: E_MINSG_EXT_BLUESURFELS_PROGRESSIVE_SAMPLER_H_ */
#endif // MINSG_EXT_BLUE_SURFELS