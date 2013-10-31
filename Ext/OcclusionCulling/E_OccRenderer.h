/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_OccRenderer_H
#define __E_OccRenderer_H

#include "../../Core/States/E_State.h"
#include <MinSG/Ext/OcclusionCulling/OccRenderer.h>

namespace E_MinSG {

/***
 **   E_OccRenderer ---|> E_State ---|> Object
 **/
class E_OccRenderer : public E_State{
		ES_PROVIDES_TYPE_NAME(OccRenderer)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_OccRenderer();

		const MinSG::OccRenderer * operator*()const		{	return static_cast<const MinSG::OccRenderer*>(ref().get());	}
		MinSG::OccRenderer * operator*()				{	return static_cast<MinSG::OccRenderer*>(ref().get());	}

	protected:
		E_OccRenderer(MinSG::OccRenderer * obj, EScript::Type * type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_OccRenderer, MinSG::OccRenderer *, **eObj)

#endif // __E_OccRenderer_H
