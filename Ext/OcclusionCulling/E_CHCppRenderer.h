/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_CHCppRenderer_H
#define __E_CHCppRenderer_H

#include "../../Core/States/E_State.h"
#include <MinSG/Ext/OcclusionCulling/CHCppRenderer.h>

namespace E_MinSG {
/***
 **   E_CHCppRenderer ---|> E_State ---|> Object
 **/
class E_CHCppRenderer : public E_State{
		ES_PROVIDES_TYPE_NAME(CHCppRenderer)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_CHCppRenderer();

		const MinSG::CHCppRenderer * operator*()const	{	return static_cast<const MinSG::CHCppRenderer*>(ref().get());	}
		MinSG::CHCppRenderer * operator*()				{	return static_cast<MinSG::CHCppRenderer*>(ref().get());	}
	protected:
		E_CHCppRenderer(MinSG::CHCppRenderer * obj, EScript::Type * type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_CHCppRenderer, MinSG::CHCppRenderer *, **eObj)

#endif // __E_CHCppRenderer_H
