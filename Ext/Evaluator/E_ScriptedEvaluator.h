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

#ifndef __E_ScriptedEvaluator_H
#define __E_ScriptedEvaluator_H

#include "E_Evaluator.h"
#include <MinSG/Ext/Evaluator/Evaluator.h>

namespace E_MinSG {

class E_ScriptedEvaluator;
/***
 **   ScriptedEvaluator ---|> Evaluator
 **/
class ScriptedEvaluator : public MinSG::Evaluators::Evaluator{
		PROVIDES_TYPE_NAME(ScriptedEvaluator)
	public:

		ScriptedEvaluator(EScript::Runtime & _runtime,Evaluator::DirectionMode _mode) : Evaluator(_mode),runtime(_runtime),eScriptedEvaluator(nullptr) {}
		virtual ~ScriptedEvaluator(){}

	// ---|> Evaluator
		virtual void beginMeasure();
		virtual void measure(MinSG::FrameContext & context, MinSG::Node & node, const Geometry::Rect & r);
		virtual void endMeasure(MinSG::FrameContext & context);
		virtual const Util::GenericAttributeList * getResults();

		void setEScriptedEvaluator(E_ScriptedEvaluator * _eScriptedEvaluator)	{	eScriptedEvaluator = _eScriptedEvaluator;	}

	private:
		EScript::Runtime & runtime;
		E_ScriptedEvaluator * eScriptedEvaluator;
};

/***
 **   E_ScriptedEvaluator ---|> E_Evaluator
 **/
class E_ScriptedEvaluator :  public E_Evaluator{
		ES_PROVIDES_TYPE_NAME(ScriptedEvaluator)
	public:
		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		E_ScriptedEvaluator(EScript::Runtime & runtime,MinSG::Evaluators::Evaluator::DirectionMode mode,EScript::Type * type) :
				E_Evaluator(new ScriptedEvaluator(runtime,mode),type){
			(**this)->setEScriptedEvaluator(this);
		}
		virtual ~E_ScriptedEvaluator() = default;

		const ScriptedEvaluator * operator*()const	{	return static_cast<const ScriptedEvaluator*>(ref().get());	}
		ScriptedEvaluator * operator*()				{	return static_cast<ScriptedEvaluator*>(ref().get());	}
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ScriptedEvaluator,		E_MinSG::ScriptedEvaluator*,		**eObj)	

#endif // __E_ScriptedEvaluator_H

#endif /* MINSG_EXT_EVALUATORS */
