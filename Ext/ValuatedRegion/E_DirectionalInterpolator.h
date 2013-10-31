/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_DirectionalInterpolator_H
#define __E_DirectionalInterpolator_H

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/ValuatedRegion/DirectionalInterpolator.h>

namespace E_MinSG {
/**
 *  E_DirectionalInterpolator ---|> [EScript::Object]
 *     |
 *     ------> MinSG::DirectionalInterpolator
 */
class E_DirectionalInterpolator : public EScript::ReferenceObject<MinSG::DirectionalInterpolator, EScript::Policies::SameEObjects_ComparePolicy> {
	ES_PROVIDES_TYPE_NAME(DirectionalInterpolator)
	public:

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		E_DirectionalInterpolator(EScript::Type* type=nullptr) : ReferenceObject_t(type?type:typeObject) {}
		virtual ~E_DirectionalInterpolator() = default;

};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_DirectionalInterpolator,		MinSG::DirectionalInterpolator*,		&(**eObj))

#endif // __E_DirectionalInterpolator_H
