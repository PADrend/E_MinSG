/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_ShaderState_H
#define E_ShaderState_H

#include "E_State.h"
#include <MinSG/Core/States/ShaderState.h>

namespace E_MinSG{

/**
 *  [E_ShaderState] ---|> [E_State]
 */
class E_ShaderState : public E_State{
	ES_PROVIDES_TYPE_NAME(ShaderState)

	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		EMINSGAPI static EScript::Type* getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		virtual ~E_ShaderState(){}
	
		const MinSG::ShaderState * operator*()const		{	return static_cast<const MinSG::ShaderState*>(ref().get());	}
		MinSG::ShaderState * operator*()				{	return static_cast<MinSG::ShaderState*>(ref().get());	}

	protected:
		EMINSGAPI E_ShaderState(MinSG::ShaderState * c,EScript::Type* type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ShaderState,		MinSG::ShaderState*,		**eObj)	

#endif // E_ShaderState_H
