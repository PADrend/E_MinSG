/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2014 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2016-2017 Sascha Brandt <myeti@mail.uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#ifndef __E_SurfelRendererFixedSize_H
#define __E_SurfelRendererFixedSize_H

#include "../../Core/States/E_NodeRendererState.h"
#include <MinSG/Ext/BlueSurfels/SurfelRenderer_FixedSize.h>


namespace E_MinSG{
namespace BlueSurfels{
	
/***
 **   E_SurfelRendererFixedSize ---|> E_NodeRendererState ---|> E_State ---|> Object
 **/
class E_SurfelRendererFixedSize : public E_NodeRendererState{
		ES_PROVIDES_TYPE_NAME(SurfelRendererFixedSize)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_SurfelRendererFixedSize();

		const MinSG::BlueSurfels::SurfelRendererFixedSize * operator*()const		{	return static_cast<const MinSG::BlueSurfels::SurfelRendererFixedSize*>(ref().get());	}
		MinSG::BlueSurfels::SurfelRendererFixedSize * operator*()				{	return static_cast<MinSG::BlueSurfels::SurfelRendererFixedSize*>(ref().get());	}
	protected:
		E_SurfelRendererFixedSize(MinSG::BlueSurfels::SurfelRendererFixedSize * obj, EScript::Type * type=nullptr);
};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_SurfelRendererFixedSize, MinSG::BlueSurfels::SurfelRendererFixedSize *, **eObj)

#endif // __E_SurfelRendererFixedSize_H
#endif // MINSG_EXT_BLUE_SURFELS
