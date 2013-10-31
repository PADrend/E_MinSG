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

#ifndef E_COLORVISIBILITYEVALUATOR_H_
#define E_COLORVISIBILITYEVALUATOR_H_

#include "E_Evaluator.h"
#include <MinSG/Ext/Evaluator/ColorVisibilityEvaluator.h>

namespace E_MinSG {

/***
 **   E_ColorVisibilityEvaluator ---|> E_Evaluator ---|> Object
 **/
class E_ColorVisibilityEvaluator : public E_Evaluator {
	ES_PROVIDES_TYPE_NAME(ColorVisibilityEvaluator)
	public:
		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		E_ColorVisibilityEvaluator(MinSG::Evaluators::Evaluator::DirectionMode mode);
		virtual ~E_ColorVisibilityEvaluator();
};

}

#endif /* E_COLORVISIBILITYEVALUATOR_H_ */
#endif /* MINSG_EXT_EVALUATORS */
