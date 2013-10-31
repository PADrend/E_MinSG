/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_VISIBILITY_SUBDIVISION

#ifndef __E_CostEvaluator_H
#define __E_CostEvaluator_H

#include "../Evaluator/E_Evaluator.h"

namespace MinSG {
namespace VisibilitySubdivision {
class CostEvaluator;
}
}

namespace E_MinSG {

/***
 **   E_CostEvaluator ---|> E_Evaluator ---|> Object
 **/
class E_CostEvaluator : public E_Evaluator{
		ES_PROVIDES_TYPE_NAME(CostEvaluator)
	public:
		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		E_CostEvaluator(MinSG::VisibilitySubdivision::CostEvaluator * evaluator);
		virtual ~E_CostEvaluator();
};

}
#endif // __E_CostEvaluator_H
#endif // MINSG_EXT_VISIBILITY_SUBDIVISION
