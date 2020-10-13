/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_TransparencyRenderer_H
#define __E_TransparencyRenderer_H

#include "E_NodeRendererState.h"
#include <MinSG/Core/States/TransparencyRenderer.h>
namespace E_MinSG {

/***
 **   E_TransparencyRenderer ---|> E_NodeRendererState ---|> E_State ---|> Object
 **/
class E_TransparencyRenderer : public E_NodeRendererState{
		ES_PROVIDES_TYPE_NAME(TransparencyRenderer)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		EMINSGAPI static EScript::Type* getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		virtual ~E_TransparencyRenderer(){}
	
		const MinSG::TransparencyRenderer * operator*()const	{	return static_cast<const MinSG::TransparencyRenderer*>(ref().get());	}
		MinSG::TransparencyRenderer * operator*()				{	return static_cast<MinSG::TransparencyRenderer*>(ref().get());	}

	protected:
		EMINSGAPI E_TransparencyRenderer(MinSG::TransparencyRenderer * obj, EScript::Type * type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_TransparencyRenderer,		MinSG::TransparencyRenderer*,		**eObj)	

#endif // __E_TransparencyRenderer_H
