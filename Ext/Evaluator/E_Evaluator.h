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

#ifndef __E_Evaluator_H
#define __E_Evaluator_H

#include <EScript/Objects/ExtReferenceObject.h>
#include <memory>

namespace MinSG {
namespace Evaluators {
class Evaluator;
}
}

namespace E_MinSG {

/***
 **   E_Evaluator ---|> ExtReferenceObject
 **/
class E_Evaluator : public EScript::ExtReferenceObject<std::unique_ptr<MinSG::Evaluators::Evaluator>,
													   EScript::Policies::SameEObjects_ComparePolicy,
													   EScript::Policies::StoreAttrsInEObject_Policy> {
		ES_PROVIDES_TYPE_NAME(Evaluator)
	public:
		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);

	protected:
		E_Evaluator(MinSG::Evaluators::Evaluator * _obj, EScript::Type * type = nullptr);
	public:
		virtual ~E_Evaluator();

		const MinSG::Evaluators::Evaluator * operator*()const	{	return ref().get();	}
		MinSG::Evaluators::Evaluator * operator*()				{	return ref().get();	}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_Evaluator,	MinSG::Evaluators::Evaluator*,	**eObj)

#endif // __E_Evaluator_H

#endif /* MINSG_EXT_EVALUATORS */
