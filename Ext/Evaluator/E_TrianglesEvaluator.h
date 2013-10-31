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

#ifndef __E_TrianglesEvaluator_H
#define __E_TrianglesEvaluator_H

#include "E_Evaluator.h"

namespace MinSG {
	namespace Evaluators {
		class TrianglesEvaluator;
	}
}
namespace E_MinSG {
	/***
	 **   E_TrianglesEvaluator ---|> E_Evaluator ---|> Object
	 **/
	/**
	 * EScript wrapper for TrianglesEvaluator.
	 *
	 * @author Benjamin Eikel
	 * @date 2009-07-28
	 */
	class E_TrianglesEvaluator : public E_Evaluator {
		ES_PROVIDES_TYPE_NAME(TrianglesEvaluator)
		public:
			static EScript::Type * typeObject;
			static void init(EScript::Namespace & lib);

			E_TrianglesEvaluator();
			virtual ~E_TrianglesEvaluator();

	};
}
#endif // __E_TrianglesEvaluator_H

#endif /* MINSG_EXT_EVALUATORS */
