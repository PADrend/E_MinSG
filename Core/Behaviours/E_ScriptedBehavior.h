/*
	This file is part of the MinSG library extension Behaviours.
	Copyright (C) 2011 Sascha Brandt
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_ScriptedBehavior_H
#define __E_ScriptedBehavior_H

#include "../../Core/Behaviours/E_Behavior.h"

namespace E_MinSG{


//!	ScriptedBehavior ---|> Behavior
class ScriptedBehavior : public MinSG::Behavior {
		PROVIDES_TYPE_NAME(ScriptedBehavior)
	public:
		ScriptedBehavior(EScript::Type* _eType,  EScript::Runtime & _runtime) :
				MinSG::Behavior(),runtime(_runtime),eType(_eType) {}
		virtual ~ScriptedBehavior() = default;

		EScript::Type* getEType()const	{	return eType.get();	}
	private:

		//! ---|> Behavior
		void doPrepareBehaviorStatus(MinSG::BehaviorStatus &) override;
		void doBeforeInitialExecute(MinSG::BehaviorStatus &) override;
		behaviourResult_t doExecute2(MinSG::BehaviorStatus &) override;
		void doFinalize(MinSG::BehaviorStatus &) override;

		EScript::Runtime & runtime;
		EScript::ERef<EScript::Type> eType;
};


//!  [E_ScriptedBehavior] ---|> [E_Behavior]
class E_ScriptedBehavior : public E_Behavior {
	ES_PROVIDES_TYPE_NAME(ScriptedBehavior)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// ---
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_ScriptedBehavior() = default;

		const ScriptedBehavior * operator*()const	{	return static_cast<const ScriptedBehavior*>(ref().get());	}
		ScriptedBehavior * operator*()				{	return static_cast<ScriptedBehavior*>(ref().get());	}

	private:
		E_ScriptedBehavior(ScriptedBehavior * c) : E_Behavior(c,c->getEType()) {}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ScriptedBehavior,		E_MinSG::ScriptedBehavior*,		**eObj)
ES_CONV_OBJ_TO_EOBJ(E_MinSG::ScriptedBehavior*, 		E_MinSG::E_ScriptedBehavior,	dynamic_cast<E_MinSG::E_ScriptedBehavior*>(E_MinSG::E_Behavior::create(obj)))


#endif // __E_ScriptedBehavior_H
