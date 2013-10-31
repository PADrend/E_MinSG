/*
	This file is part of the E_MinSG library extension Evaluator.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_EVALUATORS

#ifndef E_MINSG_EVALUATOR_E_OVERDRAWFACTOREVALUATOR_H
#define E_MINSG_EVALUATOR_E_OVERDRAWFACTOREVALUATOR_H

#include "E_Evaluator.h"
#include <MinSG/Ext/Evaluator/Evaluator.h>

namespace MinSG {
namespace Evaluators {
class OverdrawFactorEvaluator;
}
}
namespace E_MinSG {

/***
 **   E_OverdrawFactorEvaluator ---|> E_Evaluator ---|> Object
 **/
class E_OverdrawFactorEvaluator : public E_Evaluator {
		ES_PROVIDES_TYPE_NAME(OverdrawFactorEvaluator)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_OverdrawFactorEvaluator(MinSG::Evaluators::Evaluator::DirectionMode mode);
		virtual ~E_OverdrawFactorEvaluator();

		const MinSG::Evaluators::OverdrawFactorEvaluator * operator*()const;
		MinSG::Evaluators::OverdrawFactorEvaluator * operator*();
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_OverdrawFactorEvaluator,		MinSG::Evaluators::OverdrawFactorEvaluator*,		**eObj)

#endif /* E_MINSG_EVALUATOR_E_OVERDRAWFACTOREVALUATOR_H */

#endif /* MINSG_EXT_EVALUATORS */
