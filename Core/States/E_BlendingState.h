/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_BlendingState_H
#define E_BlendingState_H

#include "E_State.h"
#include <MinSG/Core/States/BlendingState.h>
namespace E_MinSG{

/**
 *  [E_BlendingState] ---|> [E_State]
 */
class E_BlendingState : public E_State{
	ES_PROVIDES_TYPE_NAME(BlendingState)

	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		EMINSGAPI static EScript::Type* typeObject;
		EMINSGAPI static void init(EScript::Namespace & lib);

		virtual ~E_BlendingState(){}
	
		const MinSG::BlendingState * operator*()const	{	return static_cast<const MinSG::BlendingState*>(ref().get());	}
		MinSG::BlendingState * operator*()				{	return static_cast<MinSG::BlendingState*>(ref().get());	}

	protected:
		EMINSGAPI E_BlendingState(MinSG::BlendingState * c,EScript::Type * type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_BlendingState,		MinSG::BlendingState*,		**eObj)	

#endif // E_BlendingState_H
