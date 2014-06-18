/*
	This file is part of the E_MinSG library extension SVS.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SVS

#ifndef E_MINSG_SVS_E_PREPROCESSINGCONTEXT_H_
#define E_MINSG_SVS_E_PREPROCESSINGCONTEXT_H_

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/SVS/PreprocessingContext.h>
#include <cstddef>
#include <string>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG {
namespace SVS {

//!	EScript wrapper class for MinSG::SVS::PreprocessingContext
class E_PreprocessingContext : public EScript::ReferenceObject<MinSG::SVS::PreprocessingContext,
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

ES_CONV_EOBJ_TO_OBJ(E_MinSG::SVS::E_PreprocessingContext,	MinSG::SVS::PreprocessingContext*,	&**eObj)

#endif /* E_MINSG_SVS_E_PREPROCESSINGCONTEXT_H_ */

#endif /* MINSG_EXT_SVS */
