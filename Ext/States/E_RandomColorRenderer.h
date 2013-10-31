/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_RandomColorRenderer_H
#define __E_RandomColorRenderer_H

#include "../../Core/States/E_State.h"
#include "../../ELibMinSG.h"

#include <MinSG/Ext/States/RandomColorRenderer.h>

namespace E_MinSG {

/**
 *   [E_RandomColorRenderer] ---|> [E_State]
 */
class E_RandomColorRenderer : public E_State {
		ES_PROVIDES_TYPE_NAME(RandomColorRenderer)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// ---
		static EScript::Type * typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_RandomColorRenderer();

		const MinSG::RandomColorRenderer * operator*()const		{	return static_cast<const MinSG::RandomColorRenderer*>(ref().get());	}
		MinSG::RandomColorRenderer * operator*()				{	return static_cast<MinSG::RandomColorRenderer*>(ref().get());	}


	protected:
		E_RandomColorRenderer(MinSG::RandomColorRenderer * gNode, EScript::Type * type = nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_RandomColorRenderer, MinSG::RandomColorRenderer *, **eObj)

#endif // __E_RandomColorRenderer_H
