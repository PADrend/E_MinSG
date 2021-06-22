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
#ifndef __E_PbrMaterialState_H
#define __E_PbrMaterialState_H

#include "../../Core/States/E_State.h"
#include <MinSG/Ext/States/PbrMaterialState.h>

namespace E_MinSG {

/***
 **   E_PbrMaterialState ---|> E_State ---|> Object
 **/
class E_PbrMaterialState : public E_State{
		ES_PROVIDES_TYPE_NAME(PbrMaterialState)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		E_PbrMaterialState(MinSG::PbrMaterialState * obj, EScript::Type * type=nullptr);
		virtual ~E_PbrMaterialState();

		const MinSG::PbrMaterialState * operator*()const	{	return static_cast<const MinSG::PbrMaterialState*>(ref().get());	}
		MinSG::PbrMaterialState * operator*()				{	return static_cast<MinSG::PbrMaterialState*>(ref().get());	}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_PbrMaterialState,		MinSG::PbrMaterialState*,		**eObj)	

#endif // __E_PbrMaterialState_H
