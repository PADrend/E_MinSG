/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#ifndef E_MINSG_EXT_BLUESURFELS_GreedyCluster_H_
#define E_MINSG_EXT_BLUESURFELS_GreedyCluster_H_

#include "E_AbstractSurfelSampler.h"

#include <MinSG/Ext/BlueSurfels/Samplers/GreedyCluster.h>

namespace E_MinSG {
namespace BlueSurfels {
	
class E_GreedyCluster : public E_AbstractSurfelSampler {
  ES_PROVIDES_TYPE_NAME(GreedyCluster)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		
	  static EScript::Type * getTypeObject();
	  static void init(EScript::Namespace & lib);

	  E_GreedyCluster(MinSG::BlueSurfels::GreedyCluster* obj, EScript::Type* type=nullptr) : E_AbstractSurfelSampler(obj, type ? type : getTypeObject()) {}
	  virtual ~E_GreedyCluster() = default;
	
		const MinSG::BlueSurfels::GreedyCluster * operator*() const { return static_cast<const MinSG::BlueSurfels::GreedyCluster*>(ref().get()); }
		MinSG::BlueSurfels::GreedyCluster * operator*() { return static_cast<MinSG::BlueSurfels::GreedyCluster*>(ref().get()); }
};	

} /* BlueSurfels */
} /* MinSG */

ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_GreedyCluster, MinSG::BlueSurfels::GreedyCluster*, **eObj)

#endif /* end of include guard: E_MINSG_EXT_BLUESURFELS_GreedyCluster_H_ */
#endif // MINSG_EXT_BLUE_SURFELS