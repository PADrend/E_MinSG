/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	Copyright (C) 2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_POINTPARAMETERSTATE_H_
#define E_POINTPARAMETERSTATE_H_
#include "../../Core/States/E_State.h"
#include <MinSG/Core/States/PointParameterState.h>
#include <Util/References.h>
#include <cstddef>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG {

/**
 *   [E_PointParameterState] ---|> [E_State]
 */
class E_PointParameterState : public E_State {
		ES_PROVIDES_TYPE_NAME(PointParameterState)

	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		EMINSGAPI static EScript::Type * getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		virtual ~E_PointParameterState() {}
	
		const MinSG::PointParameterState * operator*()const	{	return static_cast<const MinSG::PointParameterState*>(ref().get());	}
		MinSG::PointParameterState * operator*()				{	return static_cast<MinSG::PointParameterState*>(ref().get());	}

	protected:
		E_PointParameterState(MinSG::PointParameterState * node, EScript::Type * type = nullptr) :
				E_State(node, type != nullptr ? type : getTypeObject()) {
		}
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_PointParameterState,		MinSG::PointParameterState*,		**eObj)	

#endif /* E_POINTPARAMETERSTATE_H_ */
