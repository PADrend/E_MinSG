/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_OCCLUDEERENDERER_H
#define E_OCCLUDEERENDERER_H

#include "../../Core/States/E_State.h"
#include <MinSG/Ext/OcclusionCulling/OccludeeRenderer.h>

namespace E_MinSG {

/***
**   E_OccludeeRenderer ---|> E_State ---|> Object
**/
class E_OccludeeRenderer : public E_State {
		ES_PROVIDES_TYPE_NAME(OccludeeRenderer)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_OccludeeRenderer(MinSG::OccludeeRenderer * _obj, EScript::Type * type = nullptr) : E_State(_obj, type ? type : getTypeObject()) {
		}
		virtual ~E_OccludeeRenderer() {
		}

		const MinSG::OccludeeRenderer * operator*()const	{	return static_cast<const MinSG::OccludeeRenderer*>(ref().get());	}
		MinSG::OccludeeRenderer * operator*()				{	return static_cast<MinSG::OccludeeRenderer*>(ref().get());	}
		
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_OccludeeRenderer, MinSG::OccludeeRenderer *, **eObj)

#endif /* E_OCCLUDEERENDERER_H */
