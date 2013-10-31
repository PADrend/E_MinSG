/*
	This file is part of the MinSG library extension Behaviours.
	Copyright (C) 2011 Sascha Brandt
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_SimplePhysics2_H
#define __E_SimplePhysics2_H

#include "../../Core/Behaviours/E_Behavior.h"
#include <MinSG/Ext/Behaviours/SimplePhysics.h>

namespace E_MinSG{

/**
 *  [E_SimplePhysics2] ---|> [E_Behavior]
 */
class E_SimplePhysics2 : public E_Behavior {
	ES_PROVIDES_TYPE_NAME(SimplePhysics2)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// ---
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_SimplePhysics2(){}

		const MinSG::SimplePhysics2 * operator*()const	{	return static_cast<const MinSG::SimplePhysics2*>(ref().get());	}
		MinSG::SimplePhysics2 * operator*()				{	return static_cast<MinSG::SimplePhysics2*>(ref().get());	}

	protected:
		E_SimplePhysics2(MinSG::SimplePhysics2 * c) : E_Behavior(c,getTypeObject()) {}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_SimplePhysics2,		MinSG::SimplePhysics2*,		**eObj)

#endif // __E_SimplePhysics2_H
