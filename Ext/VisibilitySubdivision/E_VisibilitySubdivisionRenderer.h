/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_VISIBILITY_SUBDIVISION

#ifndef __E_VisibilitySubdivisionRenderer_H
#define __E_VisibilitySubdivisionRenderer_H

#include "../../Core/States/E_State.h"
#include "../../ELibMinSG.h"
#include <MinSG/Ext/VisibilitySubdivision/VisibilitySubdivisionRenderer.h>

namespace E_MinSG {

/**
 *   [E_VisibilitySubdivisionRenderer] ---|> [E_State]
 */
class E_VisibilitySubdivisionRenderer : public E_State {
		ES_PROVIDES_TYPE_NAME(VisibilitySubdivisionRenderer)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// ---
		static EScript::Type * typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_VisibilitySubdivisionRenderer();

		const MinSG::VisibilitySubdivision::VisibilitySubdivisionRenderer * operator*()const		{	return static_cast<const MinSG::VisibilitySubdivision::VisibilitySubdivisionRenderer*>(ref().get());	}
		MinSG::VisibilitySubdivision::VisibilitySubdivisionRenderer * operator*()					{	return static_cast<MinSG::VisibilitySubdivision::VisibilitySubdivisionRenderer*>(ref().get());	}

	protected:
		E_VisibilitySubdivisionRenderer(MinSG::VisibilitySubdivision::VisibilitySubdivisionRenderer * gNode, EScript::Type * type = nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_VisibilitySubdivisionRenderer, MinSG::VisibilitySubdivision::VisibilitySubdivisionRenderer *, **eObj)

#endif // __E_VisibilitySubdivisionRenderer_H
#endif // MINSG_EXT_VISIBILITY_SUBDIVISION
