/*
	This file is part of the E_MinSG library extension ColorCubes.
	Copyright (C) 2010-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2010-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2010 Paul Justus <paul.justus@gmx.net>
	Copyright (C) 2010-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_COLORCUBES

#ifndef E_COLORCUBERENDERER_H_
#define E_COLORCUBERENDERER_H_

#include "../../Core/States/E_NodeRendererState.h"
#include <MinSG/Ext/ColorCubes/ColorCubeRenderer.h>

namespace E_MinSG {
/***
 **   E_ColorCubeRenderer ---|> E_NodeRendererState ---|> E_State ---|> Object
 **/
class E_ColorCubeRenderer : public E_NodeRendererState {
		ES_PROVIDES_TYPE_NAME(ColorCubeRenderer)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_ColorCubeRenderer();

		const MinSG::ColorCubeRenderer * operator*()const	{	return static_cast<const MinSG::ColorCubeRenderer*>(ref().get());	}
		MinSG::ColorCubeRenderer * operator*()				{	return static_cast<MinSG::ColorCubeRenderer*>(ref().get());	}

	protected:
		E_ColorCubeRenderer(MinSG::ColorCubeRenderer * obj, EScript::Type * type=nullptr);
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ColorCubeRenderer, MinSG::ColorCubeRenderer*, **eObj)

#endif /* E_COLORCUBERENDERER_H_ */
#endif // MINSG_EXT_COLORCUBES
