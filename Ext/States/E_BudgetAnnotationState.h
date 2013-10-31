/*
	This file is part of the E_MinSG library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef E_MINSG_E_BUDGETANNOTATIONSTATE_H
#define E_MINSG_E_BUDGETANNOTATIONSTATE_H

#include "../../Core/States/E_State.h"

namespace EScript {
class Namespace;
class Type;
}
namespace MinSG {
class BudgetAnnotationState;
}
namespace E_MinSG {

//! EScript wrapper class for MinSG::BudgetAnnotationState
class E_BudgetAnnotationState : public E_State {
		ES_PROVIDES_TYPE_NAME(BudgetAnnotationState)
	protected:
		E_BudgetAnnotationState(MinSG::BudgetAnnotationState * state);
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_BudgetAnnotationState();

		const MinSG::BudgetAnnotationState * operator*() const;
		MinSG::BudgetAnnotationState * operator*();
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_BudgetAnnotationState,		MinSG::BudgetAnnotationState*,		**eObj)	

#endif /* E_MINSG_E_BUDGETANNOTATIONSTATE_H */
