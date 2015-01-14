/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012,2015 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_CHCRenderer_H
#define __E_CHCRenderer_H

#include "../../Core/States/E_State.h"
#include <MinSG/Ext/OcclusionCulling/CHCRenderer.h>

namespace E_MinSG {

/***
 **   E_CHCRenderer ---|> E_State ---|> Object
 **/
class E_CHCRenderer : public E_State{
		ES_PROVIDES_TYPE_NAME(CHCRenderer)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_CHCRenderer(){}

		const MinSG::CHCRenderer * operator*()const	{	return static_cast<const MinSG::CHCRenderer*>(ref().get());	}
		MinSG::CHCRenderer * operator*()				{	return static_cast<MinSG::CHCRenderer*>(ref().get());	}

	private:
		E_CHCRenderer(MinSG::CHCRenderer * _obj, EScript::Type * type=nullptr) : E_State(_obj,type?type:getTypeObject()){}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_CHCRenderer, MinSG::CHCRenderer *, **eObj)

#endif // __E_CHCRenderer_H
