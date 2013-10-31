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
#ifndef __E_ScriptedBehaviour_H
#define __E_ScriptedBehaviour_H

#include "../../Core/Behaviours/E_AbstractBehaviour.h"

namespace E_MinSG{


/*!	ScriptedNodeBehaviour ---|> AbstractNodeBehaviour */
class ScriptedNodeBehaviour : public MinSG::AbstractNodeBehaviour {
		PROVIDES_TYPE_NAME(ScriptedNodeBehaviour)
	public:
		ScriptedNodeBehaviour(MinSG::Node * node, EScript::EPtr<EScript::Type> _eType,  EScript::Runtime & _runtime) :
				MinSG::AbstractNodeBehaviour(node),runtime(_runtime),eType(_eType) {}
		virtual ~ScriptedNodeBehaviour(){}

		EScript::EPtr<EScript::Type> getEType()const	{	return eType;	}
	private:

		/// ---|> AbstractBehaviour
		virtual behaviourResult_t doExecute();

		/// ---|> AbstractBehaviour
		virtual void onInit();

		EScript::Runtime & runtime;
		EScript::ERef<EScript::Type> eType;
};

/***
 **   E_ScriptedNodeBehaviour ---|> E_AbstractNodeBehaviour ---|> EScript::Object
 **                                      |
 **                                      ------> MinSG::AbstractBehaviour
 **/
class E_ScriptedNodeBehaviour : public E_AbstractNodeBehaviour{
		ES_PROVIDES_TYPE_NAME(ScriptedNodeBehaviour)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);


		virtual ~E_ScriptedNodeBehaviour()			{}
		
		ScriptedNodeBehaviour * operator*()const		{	return static_cast<ScriptedNodeBehaviour*>(ref().get());	}
		ScriptedNodeBehaviour * get()const				{	return static_cast<ScriptedNodeBehaviour*>(ref().get());	}

	protected:
		E_ScriptedNodeBehaviour(ScriptedNodeBehaviour * behaviour) : E_AbstractNodeBehaviour(behaviour, behaviour->getEType().get()) {}
};
// --------------------------------------------------------------------------------

/*!	ScriptedStateBehaviour ---|> AbstractStateBehaviour */
class ScriptedStateBehaviour : public MinSG::AbstractStateBehaviour {
		PROVIDES_TYPE_NAME(ScriptedStateBehaviour)
	public:
		ScriptedStateBehaviour(MinSG::State * node, EScript::EPtr<EScript::Type> _eType,  EScript::Runtime & _runtime) :
				MinSG::AbstractStateBehaviour(node),runtime(_runtime),eType(_eType) {}
		virtual ~ScriptedStateBehaviour(){}

		EScript::EPtr<EScript::Type> getEType()const	{	return eType;	}
	private:

		/// ---|> AbstractBehaviour
		virtual behaviourResult_t doExecute()override;

		/// ---|> AbstractBehaviour
		virtual void onInit();

		EScript::Runtime & runtime;
		EScript::ERef<EScript::Type> eType;
};

/***
 **   E_ScriptedStateBehaviour ---|> E_AbstractStateBehaviour ---|> EScript::Object
 **                                      |
 **                                      ------> MinSG::AbstractBehaviour
 **/
class E_ScriptedStateBehaviour : public E_AbstractStateBehaviour{
		ES_PROVIDES_TYPE_NAME(ScriptedStateBehaviour)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);


		virtual ~E_ScriptedStateBehaviour()			{}
		
		ScriptedStateBehaviour * operator*()const	{	return static_cast<ScriptedStateBehaviour*>(ref().get());	}
		ScriptedStateBehaviour * get()const			{	return static_cast<ScriptedStateBehaviour*>(ref().get());	}

	protected:
		E_ScriptedStateBehaviour(ScriptedStateBehaviour * behaviour) : E_AbstractStateBehaviour(behaviour, behaviour->getEType().get()) {}
};
}


ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ScriptedNodeBehaviour,	E_MinSG::ScriptedNodeBehaviour*,	**eObj)
ES_CONV_OBJ_TO_EOBJ(E_MinSG::ScriptedNodeBehaviour*, 	E_MinSG::E_ScriptedNodeBehaviour,	dynamic_cast<E_MinSG::E_ScriptedNodeBehaviour*>(E_MinSG::E_Behavior::create(obj)))

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ScriptedStateBehaviour,	E_MinSG::ScriptedStateBehaviour*,	**eObj)
ES_CONV_OBJ_TO_EOBJ(E_MinSG::ScriptedStateBehaviour*, 	E_MinSG::E_ScriptedStateBehaviour,	dynamic_cast<E_MinSG::E_ScriptedStateBehaviour*>(E_MinSG::E_Behavior::create(obj)))

#endif // __E_ScriptedBehaviour_H
