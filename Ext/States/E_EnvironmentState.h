/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_EnvironmentState_H
#define __E_EnvironmentState_H

#include "../../Core/States/E_State.h"
#include <MinSG/Ext/States/EnvironmentState.h>

namespace E_MinSG {

/***
 **   E_EnvironmentState ---|> E_State ---|> Object
 **/
class E_EnvironmentState : public E_State{
		ES_PROVIDES_TYPE_NAME(EnvironmentState)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		E_EnvironmentState(MinSG::EnvironmentState * obj, EScript::Type * type=nullptr);
		virtual ~E_EnvironmentState();

		const MinSG::EnvironmentState * operator*()const	{	return static_cast<const MinSG::EnvironmentState*>(ref().get());	}
		MinSG::EnvironmentState * operator*()				{	return static_cast<MinSG::EnvironmentState*>(ref().get());	}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_EnvironmentState,		MinSG::EnvironmentState*,		**eObj)	

#endif // __E_EnvironmentState_H
