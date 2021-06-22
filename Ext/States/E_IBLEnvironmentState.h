/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	Copyright (C) 2021 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_IBLEnvironmentState_H
#define __E_IBLEnvironmentState_H

#include "../../Core/States/E_State.h"
#include <MinSG/Ext/States/IBLEnvironmentState.h>

namespace E_MinSG {

/***
 **   E_IBLEnvironmentState ---|> E_State ---|> Object
 **/
class E_IBLEnvironmentState : public E_State{
		ES_PROVIDES_TYPE_NAME(IBLEnvironmentState)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		E_IBLEnvironmentState(MinSG::IBLEnvironmentState * obj, EScript::Type * type=nullptr);
		virtual ~E_IBLEnvironmentState();

		const MinSG::IBLEnvironmentState * operator*()const	{	return static_cast<const MinSG::IBLEnvironmentState*>(ref().get());	}
		MinSG::IBLEnvironmentState * operator*()				{	return static_cast<MinSG::IBLEnvironmentState*>(ref().get());	}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_IBLEnvironmentState,		MinSG::IBLEnvironmentState*,		**eObj)	

#endif // __E_IBLEnvironmentState_H
