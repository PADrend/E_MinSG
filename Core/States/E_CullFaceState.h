/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_CullFaceState_H
#define E_CullFaceState_H

#include "E_State.h"
#include <MinSG/Core/States/CullFaceState.h>
namespace E_MinSG{

/**
 *  [E_CullFaceState] ---|> [E_State]
 */
class E_CullFaceState : public E_State{
	ES_PROVIDES_TYPE_NAME(CullFaceState)

	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_CullFaceState(){}
	
		const MinSG::CullFaceState * operator*()const	{	return static_cast<const MinSG::CullFaceState*>(ref().get());	}
		MinSG::CullFaceState * operator*()				{	return static_cast<MinSG::CullFaceState*>(ref().get());	}

	protected:
		E_CullFaceState(MinSG::CullFaceState * c,EScript::Type * type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_CullFaceState,		MinSG::CullFaceState*,		**eObj)	

#endif // E_CullFaceState_H
