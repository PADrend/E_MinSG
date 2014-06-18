/*
	This file is part of the MinSG library extension ThesisJonas.
	Copyright (C) 2013 Jonas Knoll

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_THESISJONAS

#ifndef E_MINSG_THESISJONAS_E_RENDERER_H_
#define E_MINSG_THESISJONAS_E_RENDERER_H_

#include <MinSG/Ext/ThesisJonas/Renderer.h>

#include "../States/E_BudgetAnnotationState.h"
#include "../../Core/States/E_NodeRendererState.h"

namespace EScript {
class Namespace;
class Runtime;
class Type;
}
namespace MinSG {
namespace ThesisJonas {
class Renderer;
}
}
namespace E_MinSG {
namespace ThesisJonas {

//!	EScript wrapper class for MinSG::ThesisJonas::Renderer
class E_Renderer : public E_NodeRendererState { // TODO: inherit from E_BudgetAnnotationState but then wrong panel is used
	ES_PROVIDES_TYPE_NAME(ThesisJonasRenderer)
	protected:
		E_Renderer(MinSG::ThesisJonas::Renderer * renderer);
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_Renderer();

		const MinSG::ThesisJonas::Renderer * operator*()const	{	return static_cast<const MinSG::ThesisJonas::Renderer*>(ref().get());	}
		MinSG::ThesisJonas::Renderer * operator*()				{	return static_cast<MinSG::ThesisJonas::Renderer*>(ref().get());	}
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisJonas::E_Renderer,	MinSG::ThesisJonas::Renderer*,	**eObj)

#endif /* E_MINSG_THESISJONAS_E_RENDERER_H_ */

#endif /* MINSG_EXT_THESISJONAS */
