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

#ifndef __E_AreaEvaluator_H
#define __E_AreaEvaluator_H

#include "E_Evaluator.h"
#include <MinSG/Ext/Evaluator/Evaluator.h>

namespace MinSG{
namespace Evaluators{
class AreaEvaluator;
}}

namespace E_MinSG {
/***
 **   E_AreaEvaluator ---|> E_Evaluator ---|> Object
 **/
class E_AreaEvaluator : public E_Evaluator{
		ES_PROVIDES_TYPE_NAME(AreaEvaluator)
	public:
		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		E_AreaEvaluator(MinSG::Evaluators::Evaluator::DirectionMode mode);
		virtual ~E_AreaEvaluator();

};

}
#endif // __E_AreaEvaluator_H

#endif /* MINSG_EXT_EVALUATORS */
