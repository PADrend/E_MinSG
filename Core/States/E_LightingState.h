/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_LIGHTINGSTATE_H_
#define E_LIGHTINGSTATE_H_

#include "E_State.h"
#include <MinSG/Core/States/LightingState.h>

namespace E_MinSG {

class E_LightingState : public E_State {
	ES_PROVIDES_TYPE_NAME(LightingState)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		EMINSGAPI static EScript::Type* getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		virtual ~E_LightingState() {	}
	
		const MinSG::LightingState * operator*()const	{	return static_cast<const MinSG::LightingState*>(ref().get());	}
		MinSG::LightingState * operator*()				{	return static_cast<MinSG::LightingState*>(ref().get());	}

	protected:
		E_LightingState(MinSG::LightingState * s, EScript::Type * type=nullptr) : E_State(s, type == nullptr ? getTypeObject() : type){};
	};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_LightingState,		MinSG::LightingState*,		**eObj)	

#endif /* E_LIGHTINGSTATE_H_ */
