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

#ifndef __E_BoxQualityEvaluator_H
#define __E_BoxQualityEvaluator_H

#include "E_Evaluator.h"

namespace MinSG{
namespace Evaluators{
class BoxQualityEvaluator;
}
}
namespace E_MinSG {
/***
 **   E_BoxQualityEvaluator ---|> E_Evaluator ---|> Object
 **/
class E_BoxQualityEvaluator : public E_Evaluator{
		ES_PROVIDES_TYPE_NAME(BoxQualityEvaluator)
	public:
		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		E_BoxQualityEvaluator();
		virtual ~E_BoxQualityEvaluator();

};

}
#endif // __E_BoxQualityEvaluator_H

#endif /* MINSG_EXT_EVALUATORS */
