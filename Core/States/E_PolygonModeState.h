/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_POLYGONMODESTATE_H_
#define E_POLYGONMODESTATE_H_
#include "../../Core/States/E_State.h"
#include <MinSG/Core/States/PolygonModeState.h>
#include <Util/References.h>
#include <cstddef>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG {

/**
 *   [E_PolygonModeState] ---|> [E_State]
 */
class E_PolygonModeState : public E_State {
		ES_PROVIDES_TYPE_NAME(PolygonModeState)

	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_PolygonModeState() {}
	
		const MinSG::PolygonModeState * operator*()const	{	return static_cast<const MinSG::PolygonModeState*>(ref().get());	}
		MinSG::PolygonModeState * operator*()				{	return static_cast<MinSG::PolygonModeState*>(ref().get());	}

	protected:
		E_PolygonModeState(MinSG::PolygonModeState * node, EScript::Type * type = nullptr) :
				E_State(node, type != nullptr ? type : getTypeObject()) {
		}
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_PolygonModeState,		MinSG::PolygonModeState*,		**eObj)	

#endif /* E_POLYGONMODESTATE_H_ */
