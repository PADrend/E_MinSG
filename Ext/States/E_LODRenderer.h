/*
	This file is part of the E_MinSG library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef E_MINSG_E_LODRENDERER_H
#define E_MINSG_E_LODRENDERER_H

#include "../../Core/States/E_NodeRendererState.h"

namespace EScript {
class Namespace;
class Type;
}
namespace MinSG {
class LODRenderer;
}
namespace E_MinSG {

//! EScript wrapper class for MinSG::LODRenderer
class E_LODRenderer : public E_NodeRendererState {
		ES_PROVIDES_TYPE_NAME(LODRenderer)
	protected:
		E_LODRenderer(MinSG::LODRenderer * state);
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_LODRenderer();

		const MinSG::LODRenderer * operator*() const;
		MinSG::LODRenderer * operator*();
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_LODRenderer, MinSG::LODRenderer *, **eObj)

#endif /* E_MINSG_E_LODRENDERER_H */
