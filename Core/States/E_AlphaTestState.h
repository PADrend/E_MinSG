/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_ALPHATESTSTATE_H_
#define E_ALPHATESTSTATE_H_
#include "../../Core/States/E_State.h"
#include <MinSG/Core/States/AlphaTestState.h>
#include <Util/References.h>
#include <cstddef>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG {

/**
 *   [E_AlphaTestState] ---|> [E_State]
 */
class E_AlphaTestState : public E_State {
		ES_PROVIDES_TYPE_NAME(AlphaTestState)

	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_AlphaTestState() {}
		
		const MinSG::AlphaTestState * operator*()const	{	return static_cast<const MinSG::AlphaTestState*>(ref().get());	}
		MinSG::AlphaTestState * operator*()				{	return static_cast<MinSG::AlphaTestState*>(ref().get());	}

	protected:
		E_AlphaTestState(MinSG::AlphaTestState * node, EScript::Type * type = nullptr) :
				E_State(node, type != nullptr ? type : getTypeObject()) {
		}
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_AlphaTestState,		MinSG::AlphaTestState*,		**eObj)	

#endif /* E_ALPHATESTSTATE_H_ */
