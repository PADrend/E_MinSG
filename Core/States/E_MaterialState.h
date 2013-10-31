/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_MATERIALSTATE_H_
#define E_MATERIALSTATE_H_
#include "E_State.h"
#include <MinSG/Core/States/MaterialState.h>
namespace E_MinSG{

/**
 *  [E_MaterialState] ---|> [E_State]
 */
class E_MaterialState : public E_State{
	ES_PROVIDES_TYPE_NAME(MaterialState)

	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_MaterialState(){}
	
		const MinSG::MaterialState * operator*()const	{	return static_cast<const MinSG::MaterialState*>(ref().get());	}
		MinSG::MaterialState * operator*()				{	return static_cast<MinSG::MaterialState*>(ref().get());	}

	protected:
		E_MaterialState(MinSG::MaterialState * c,EScript::Type * type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_MaterialState,		MinSG::MaterialState*,		**eObj)	

#endif /* E_MATERIALSTATE_H_ */
