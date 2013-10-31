/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_EVALUATORS

#ifndef E_STATSEVALUATOR_H_
#define E_STATSEVALUATOR_H_

#include "E_Evaluator.h"
#include <MinSG/Ext/Evaluator/Evaluator.h>
#include <cstddef>

namespace EScript {
class Namespace;
class Object;
class Type;
}
namespace MinSG {
namespace Evaluators {
class StatsEvaluator;
}
}
namespace E_MinSG {

/**
 *   E_StatsEvaluator ---|> E_Evaluator ---|> Object
 */
class E_StatsEvaluator : public E_Evaluator {
		ES_PROVIDES_TYPE_NAME(StatsEvaluator)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_StatsEvaluator(MinSG::Evaluators::Evaluator::DirectionMode mode, EScript::Type * type = nullptr);
		virtual ~E_StatsEvaluator() = default;

		const MinSG::Evaluators::StatsEvaluator * operator*()const;
		MinSG::Evaluators::StatsEvaluator * operator*();
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_StatsEvaluator,		MinSG::Evaluators::StatsEvaluator*,		**eObj)

#endif /* E_STATSEVALUATOR_H_ */
#endif /* MINSG_EXT_EVALUATORS */
