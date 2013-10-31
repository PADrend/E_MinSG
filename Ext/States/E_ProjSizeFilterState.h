/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_ProjSizeFilterState_H
#define __E_ProjSizeFilterState_H

#include "../../Core/States/E_NodeRendererState.h"
#include <MinSG/Ext/States/ProjSizeFilterState.h>


namespace E_MinSG {

/***
 **   E_ProjSizeFilterState ---|> E_NodeRendererState ---|> E_State ---|> Object
 **/
class E_ProjSizeFilterState : public E_NodeRendererState{
		ES_PROVIDES_TYPE_NAME(ProjSizeFilterState)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_ProjSizeFilterState();

		const MinSG::ProjSizeFilterState * operator*()const		{	return static_cast<const MinSG::ProjSizeFilterState*>(ref().get());	}
		MinSG::ProjSizeFilterState * operator*()				{	return static_cast<MinSG::ProjSizeFilterState*>(ref().get());	}
	protected:
		E_ProjSizeFilterState(MinSG::ProjSizeFilterState * obj, EScript::Type * type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ProjSizeFilterState, MinSG::ProjSizeFilterState *, **eObj)

#endif // __E_ProjSizeFilterState_H
