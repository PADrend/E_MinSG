/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_ScriptedNodeRendererState_H
#define __E_ScriptedNodeRendererState_H

#include "../../Core/States/E_NodeRendererState.h"
#include <MinSG/Core/States/NodeRendererState.h>

namespace E_MinSG{

class E_ScriptedNodeRendererState;

//! ScriptedNodeRendererState ---|> MinSG::NodeRendererState
class ScriptedNodeRendererState : public MinSG::NodeRendererState {
		PROVIDES_TYPE_NAME(ScriptedNodeRendererState)

	public:
		ScriptedNodeRendererState(const std::string & channel, EScript::EPtr<EScript::Type> type,EScript::Runtime & runtime);
		virtual ~ScriptedNodeRendererState()				{}

		EScript::EPtr<EScript::Type> getEType(){	return eType;	}

		/// ---|> State
		virtual ScriptedNodeRendererState * clone() const 	{	return new ScriptedNodeRendererState(*this);	}
	private:
		//! ---|> NodeRendererState
		virtual MinSG::NodeRendererResult displayNode(MinSG::FrameContext & context, MinSG::Node * node, const MinSG::RenderParam & rp);

		ScriptedNodeRendererState(const ScriptedNodeRendererState & other) : MinSG::NodeRendererState(other), runtime(other.runtime) {}
		EScript::Runtime & runtime;
		EScript::ERef<EScript::Type> eType;
};

/***
 **   E_ScriptedNodeRendererState ---|> E_NodeRendererState 
 **/
class E_ScriptedNodeRendererState : public E_NodeRendererState{
		ES_PROVIDES_TYPE_NAME(ScriptedNodeRendererState)
	public:
		// ---
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_ScriptedNodeRendererState()		{}
		
		const E_MinSG::ScriptedNodeRendererState * operator*()const	{	return static_cast<const E_MinSG::ScriptedNodeRendererState*>(ref().get());	}
		E_MinSG::ScriptedNodeRendererState * operator*()			{	return static_cast<E_MinSG::ScriptedNodeRendererState*>(ref().get());	}

	protected:
		E_ScriptedNodeRendererState(ScriptedNodeRendererState * behaviour);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ScriptedNodeRendererState, E_MinSG::ScriptedNodeRendererState *, **eObj)

#endif // __E_ScriptedNodeRendererState_H
