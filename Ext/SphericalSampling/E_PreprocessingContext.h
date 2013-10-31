/*
	This file is part of the E_MinSG library extension SphericalSampling.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SPHERICALSAMPLING

#ifndef E_MINSG_SPHERICALSAMPLING_E_PREPROCESSINGCONTEXT_H_
#define E_MINSG_SPHERICALSAMPLING_E_PREPROCESSINGCONTEXT_H_

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/SphericalSampling/PreprocessingContext.h>
#include <cstddef>
#include <string>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG {
namespace SphericalSampling {

//!	EScript wrapper class for MinSG::SphericalSampling::PreprocessingContext
class E_PreprocessingContext : public EScript::ReferenceObject<MinSG::SphericalSampling::PreprocessingContext,
															   EScript::Policies::SameEObjects_ComparePolicy> {
	ES_PROVIDES_TYPE_NAME(PreprocessingContext)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename ... Types>
		explicit E_PreprocessingContext(Types && ... params) :
			ReferenceObject_t(E_PreprocessingContext::getTypeObject(), std::forward<Types>(params) ...) {
		}
		virtual ~E_PreprocessingContext();
};

}
}

#endif /* E_MINSG_SPHERICALSAMPLING_E_PREPROCESSINGCONTEXT_H_ */

#endif /* MINSG_EXT_SPHERICALSAMPLING */
