/*
	This file is part of the E_MinSG library extension
	AdaptiveGlobalVisibilitySampling.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_ADAPTIVEGLOBALVISIBILITYSAMPLING

#ifndef E_MINSG_AGVS_E_ADAPTIVEGLOBALVISIBILITYSAMPLING_H_
#define E_MINSG_AGVS_E_ADAPTIVEGLOBALVISIBILITYSAMPLING_H_

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/AdaptiveGlobalVisibilitySampling/AdaptiveGlobalVisibilitySampling.h>
#include <cstddef>
#include <string>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG {
namespace AGVS {

//!	EScript wrapper class for MinSG::AGVS::AdaptiveGlobalVisibilitySampling
class E_AdaptiveGlobalVisibilitySampling : public EScript::ReferenceObject<MinSG::AGVS::AdaptiveGlobalVisibilitySampling,
																		   EScript::Policies::SameEObjects_ComparePolicy> {
	ES_PROVIDES_TYPE_NAME(AdaptiveGlobalVisibilitySampling)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename ... Types>
		explicit E_AdaptiveGlobalVisibilitySampling(Types && ... params) :
			ReferenceObject_t(E_AdaptiveGlobalVisibilitySampling::getTypeObject(), std::forward<Types>(params) ...) {
		}
		virtual ~E_AdaptiveGlobalVisibilitySampling();
};

}
}

namespace EScript {
template<>
inline MinSG::AGVS::AdaptiveGlobalVisibilitySampling * convertTo<MinSG::AGVS::AdaptiveGlobalVisibilitySampling *>(Runtime & rt, ObjPtr obj) {
	return &**assertType<E_MinSG::AGVS::E_AdaptiveGlobalVisibilitySampling>(rt, obj);
}
template<>
inline const MinSG::AGVS::AdaptiveGlobalVisibilitySampling * convertTo<const MinSG::AGVS::AdaptiveGlobalVisibilitySampling *>(Runtime & rt, ObjPtr obj) {
	return &**assertType<E_MinSG::AGVS::E_AdaptiveGlobalVisibilitySampling>(rt, obj);
}
}

#endif /* E_MINSG_AGVS_E_ADAPTIVEGLOBALVISIBILITYSAMPLING_H_ */

#endif /* MINSG_EXT_ADAPTIVEGLOBALVISIBILITYSAMPLING */
