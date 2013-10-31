/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_MULTIALGORENDERING
#include <MinSG/Ext/MultiAlgoRendering/Dependencies.h>

#ifndef E_MINSG_E_MAR_E_SURFELRENDERER_H_
#define E_MINSG_E_MAR_E_SURFELRENDERER_H_

#include <MinSG/Ext/MultiAlgoRendering/SurfelRenderer.h>
#include "../../Core/States/E_NodeRendererState.h"

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG {
namespace E_MAR {


/*!	EScript wrapper class for MinSG::MAR::SurfelRenderer
	E_SurfelRenderer ---|> E_NodeRendererState ---|> EScript::ReferenceObject < MinSG::MAR::SurfelRenderer >
		|
		--------------> MinSG::MAR::SurfelRenderer ---|> MinSG::NodeRendererState
*/
class E_SurfelRenderer : public E_NodeRendererState {
		ES_PROVIDES_TYPE_NAME(SurfelRenderer)
		
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_SurfelRenderer() = default;

		const MinSG::MAR::SurfelRenderer * operator*()const	{ return static_cast<const MinSG::MAR::SurfelRenderer *>(ref().get()); }
		MinSG::MAR::SurfelRenderer * operator*()				{ return static_cast<MinSG::MAR::SurfelRenderer *>(ref().get()); }
		
	protected:
		E_SurfelRenderer(MinSG::MAR::SurfelRenderer * _obj, EScript::Type * type = nullptr) : E_NodeRendererState(_obj, type ? type : E_SurfelRenderer::getTypeObject()) {}
};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_MAR::E_SurfelRenderer, MinSG::MAR::SurfelRenderer *, **eObj)

#endif // E_MINSG_E_MAR_E_SURFELRENDERER_H_
#endif // MINSG_EXT_MULTIALGORENDERING

