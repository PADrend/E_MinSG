/*
	This file is part of the E_MinSG library extension SVS.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SVS

#ifndef E_MINSG_SVS_E_VISIBILITYSPHERE_H_
#define E_MINSG_SVS_E_VISIBILITYSPHERE_H_

#include <EScript/Objects/ExtReferenceObject.h>
#include <MinSG/Ext/SVS/VisibilitySphere.h>
#include <cstddef>
#include <string>
#include <utility>

namespace EScript {
class Namespace;
class Runtime;
class Type;
}
namespace E_MinSG {
namespace SVS {

//!	EScript wrapper class for MinSG::SVS::VisibilitySphere
class E_VisibilitySphere : public EScript::ExtReferenceObject<MinSG::SVS::VisibilitySphere> {
		ES_PROVIDES_TYPE_NAME(VisibilitySphere)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename ... Types>
		explicit E_VisibilitySphere(Types && ... params) :
			ExtReferenceObject_t(E_VisibilitySphere::getTypeObject(), std::forward<Types>(params) ...) {
		}
		virtual ~E_VisibilitySphere();
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::SVS::E_VisibilitySphere,	MinSG::SVS::VisibilitySphere*,	&**eObj)

#endif /* E_MINSG_SVS_E_VISIBILITYSPHERE_H_ */

#endif /* MINSG_EXT_SVS */
