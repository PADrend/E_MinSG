/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2014 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#ifndef __E_SurfelRenderer2_H
#define __E_SurfelRenderer2_H

#include "../../Core/States/E_NodeRendererState.h"
#include <MinSG/Ext/BlueSurfels/SurfelRenderer2.h>


namespace E_MinSG{
namespace BlueSurfels{
	
/***
 **   E_SurfelRenderer2 ---|> E_NodeRendererState ---|> E_State ---|> Object
 **/
class E_SurfelRenderer2 : public E_NodeRendererState{
		ES_PROVIDES_TYPE_NAME(SurfelRenderer2)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_SurfelRenderer2();

		const MinSG::BlueSurfels::SurfelRenderer2 * operator*()const		{	return static_cast<const MinSG::BlueSurfels::SurfelRenderer2*>(ref().get());	}
		MinSG::BlueSurfels::SurfelRenderer2 * operator*()				{	return static_cast<MinSG::BlueSurfels::SurfelRenderer2*>(ref().get());	}
	protected:
		E_SurfelRenderer2(MinSG::BlueSurfels::SurfelRenderer2 * obj, EScript::Type * type=nullptr);
};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_SurfelRenderer2, MinSG::BlueSurfels::SurfelRenderer2 *, **eObj)

#endif // __E_SurfelRenderer2_H
#endif // MINSG_EXT_BLUE_SURFELS
