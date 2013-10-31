/*
	This file is part of the E_MinSG library.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_VISIBILITY_SUBDIVISION

#ifndef E_MINSG_VISIBILITYSUBDIVISION_E_PVSRENDERER_H
#define E_MINSG_VISIBILITYSUBDIVISION_E_PVSRENDERER_H

#include "../../Core/States/E_State.h"
#include <MinSG/Ext/VisibilitySubdivision/PVSRenderer.h>

namespace E_MinSG {

//! EScript wrapper for MinSG::VisibilitySubdivision::PVSRenderer
class E_PVSRenderer : public E_State {
		ES_PROVIDES_TYPE_NAME(PVSRenderer)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_PVSRenderer();

		const MinSG::VisibilitySubdivision::PVSRenderer * operator*() const {
			return static_cast<const MinSG::VisibilitySubdivision::PVSRenderer *>(ref().get());
		}
		MinSG::VisibilitySubdivision::PVSRenderer * operator*() {
			return static_cast<MinSG::VisibilitySubdivision::PVSRenderer *>(ref().get());
		}

	protected:
		E_PVSRenderer(MinSG::VisibilitySubdivision::PVSRenderer * gNode, EScript::Type * type = nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_PVSRenderer, MinSG::VisibilitySubdivision::PVSRenderer *, **eObj)

#endif /* E_MINSG_VISIBILITYSUBDIVISION_E_PVSRENDERER_H */
#endif /* MINSG_EXT_VISIBILITY_SUBDIVISION */
