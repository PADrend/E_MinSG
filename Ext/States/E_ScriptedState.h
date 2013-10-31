/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_ScriptedState_H
#define __E_ScriptedState_H

#include "../../Core/States/E_State.h"

namespace E_MinSG{

class E_ScriptedState;

//! ScriptedState ---|> MinSG::State
class ScriptedState : public MinSG::State {
		PROVIDES_TYPE_NAME(ScriptedState)

	public:
		ScriptedState(EScript::EPtr<EScript::Type> type,EScript::Runtime & runtime);
		virtual ~ScriptedState()				{}

		EScript::EPtr<EScript::Type> getEType(){	return eType;	}

		/// ---|> State
		virtual ScriptedState * clone() const 	{	return new ScriptedState(*this);	}
	private:
		virtual stateResult_t doEnableState(MinSG::FrameContext & context, MinSG::Node * node, const MinSG::RenderParam & rp);
		virtual void doDisableState(MinSG::FrameContext & context, MinSG::Node * node, const MinSG::RenderParam & rp);

		ScriptedState(const ScriptedState & other) : State(other), runtime(other.runtime) {}
		EScript::Runtime & runtime;
		EScript::ERef<EScript::Type> eType;
};

/***
 **   E_ScriptedState ---|> E_State ---|> EScript::Object
 **                                      |
 **                                      ------> MinSG::State
 **/
class E_ScriptedState : public E_State{
		ES_PROVIDES_TYPE_NAME(ScriptedState)
	public:
		// ---
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_ScriptedState()				{}

		const E_MinSG::ScriptedState * operator*()const		{	return static_cast<const E_MinSG::ScriptedState*>(ref().get());	}
		E_MinSG::ScriptedState * operator*()				{	return static_cast<E_MinSG::ScriptedState*>(ref().get());	}

	protected:
		E_ScriptedState(ScriptedState * behaviour);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ScriptedState, E_MinSG::ScriptedState *, **eObj)

#endif // __E_ScriptedState_H
