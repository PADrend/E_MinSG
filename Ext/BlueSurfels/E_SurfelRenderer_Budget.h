/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017 Sascha Brandt <myeti@mail.uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#ifndef __E_SurfelRendererBudget_H
#define __E_SurfelRendererBudget_H

#include "../../Core/States/E_NodeRendererState.h"
#include <MinSG/Ext/BlueSurfels/SurfelRenderer_Budget.h>


namespace E_MinSG{
namespace BlueSurfels{
	
/***
 **   E_SurfelRendererBudget ---|> E_NodeRendererState ---|> E_State ---|> Object
 **/
class E_SurfelRendererBudget : public E_NodeRendererState{
		ES_PROVIDES_TYPE_NAME(SurfelRendererBudget)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_SurfelRendererBudget();

		const MinSG::BlueSurfels::SurfelRendererBudget * operator*()const		{	return static_cast<const MinSG::BlueSurfels::SurfelRendererBudget*>(ref().get());	}
		MinSG::BlueSurfels::SurfelRendererBudget * operator*()				{	return static_cast<MinSG::BlueSurfels::SurfelRendererBudget*>(ref().get());	}
	protected:
		E_SurfelRendererBudget(MinSG::BlueSurfels::SurfelRendererBudget * obj, EScript::Type * type=nullptr);
};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_SurfelRendererBudget, MinSG::BlueSurfels::SurfelRendererBudget *, **eObj)

#endif // __E_SurfelRendererBudget_H
#endif // MINSG_EXT_BLUE_SURFELS
