/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_VISIBILITY_SUBDIVISION

#ifndef E_MINSG_VISIBILITYSUBDIVISION_E_VISIBILITYVECTOR_H_
#define E_MINSG_VISIBILITYSUBDIVISION_E_VISIBILITYVECTOR_H_

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/VisibilitySubdivision/VisibilityVector.h>
#include <string>
#include <utility>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG {

class E_VisibilityVector : public EScript::ReferenceObject<MinSG::VisibilitySubdivision::VisibilityVector> {
		ES_PROVIDES_TYPE_NAME(VisibilityVector)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename ... Types>
		explicit E_VisibilityVector(Types && ... params) :
			ReferenceObject_t(E_VisibilityVector::getTypeObject(), std::forward<Types>(params) ...) {
		}
		virtual ~E_VisibilityVector();
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_VisibilityVector,		MinSG::VisibilitySubdivision::VisibilityVector*,		&**eObj)	
ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_VisibilityVector,		MinSG::VisibilitySubdivision::VisibilityVector&,		**eObj)	

#endif /* E_MINSG_VISIBILITYSUBDIVISION_E_VISIBILITYVECTOR_H_ */

#endif /* MINSG_EXT_VISIBILITY_SUBDIVISION */
