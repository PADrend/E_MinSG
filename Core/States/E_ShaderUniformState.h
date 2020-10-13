/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_ShaderUniformState_H
#define E_ShaderUniformState_H

#include "../../Core/States/E_State.h"
#include <MinSG/Core/States/ShaderUniformState.h>
namespace E_MinSG{

/**
 *  [E_ShaderUniformState] ---|> [E_State]
 */
class E_ShaderUniformState : public E_State{
	ES_PROVIDES_TYPE_NAME(ShaderUniformState)

	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		EMINSGAPI static EScript::Type* getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		virtual ~E_ShaderUniformState(){}
	
		const MinSG::ShaderUniformState * operator*()const	{	return static_cast<const MinSG::ShaderUniformState*>(ref().get());	}
		MinSG::ShaderUniformState * operator*()				{	return static_cast<MinSG::ShaderUniformState*>(ref().get());	}

	protected:
		EMINSGAPI E_ShaderUniformState(MinSG::ShaderUniformState * c,EScript::Type* type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ShaderUniformState,		MinSG::ShaderUniformState*,		**eObj)	

#endif // E_ShaderUniformState_H
