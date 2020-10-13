/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_AbstractBehaviour_H
#define __E_AbstractBehaviour_H

#include "E_Behavior.h"
#include <MinSG/Core/Behaviours/AbstractBehaviour.h>

namespace E_MinSG{

/***
 **   E_AbstractBehaviour ---|> E_Behavior
 **/
class E_AbstractBehaviour : public E_Behavior{
	ES_PROVIDES_TYPE_NAME(AbstractBehaviour)

	public:

		// ---
		EMINSGAPI static EScript::Type* getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		E_AbstractBehaviour(MinSG::AbstractBehaviour * behaviour, EScript::Type* type=nullptr) : E_Behavior(behaviour,type?type:getTypeObject()) {}
		virtual ~E_AbstractBehaviour()	{}

		MinSG::AbstractBehaviour * operator*()const	{	return static_cast<MinSG::AbstractBehaviour*>(ref().get());	}
		MinSG::AbstractBehaviour * get()const		{	return static_cast<MinSG::AbstractBehaviour*>(ref().get());	}
};


//!   E_AbstractNodeBehaviour ---|> E_AbstractBehaviour
class E_AbstractNodeBehaviour : public E_AbstractBehaviour{
	ES_PROVIDES_TYPE_NAME(AbstractNodeBehaviour)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// ---
		EMINSGAPI static EScript::Type* getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib); //!< called by E_AbstractBehaviour::init(...)

		virtual ~E_AbstractNodeBehaviour()	{}

		MinSG::AbstractNodeBehaviour * operator*()const	{	return static_cast<MinSG::AbstractNodeBehaviour*>(ref().get());	}
		MinSG::AbstractNodeBehaviour * get()const		{	return static_cast<MinSG::AbstractNodeBehaviour*>(ref().get());	}

	// protected: \todo make this protected as soon as __createSimplePhyics is removed!
		E_AbstractNodeBehaviour(MinSG::AbstractNodeBehaviour * behaviour, EScript::Type* type=nullptr) : E_AbstractBehaviour(behaviour,type?type:getTypeObject()) {}
};

//!   E_AbstractStateBehaviour ---|> E_AbstractBehaviour
class E_AbstractStateBehaviour : public E_AbstractBehaviour{
	ES_PROVIDES_TYPE_NAME(AbstractStateBehaviour)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// ---
		EMINSGAPI static EScript::Type* getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib); //!< called by E_AbstractBehaviour::init(...)

		virtual ~E_AbstractStateBehaviour()	{}

		MinSG::AbstractStateBehaviour * operator*()const	{	return static_cast<MinSG::AbstractStateBehaviour*>(ref().get());	}
		MinSG::AbstractStateBehaviour * get()const			{	return static_cast<MinSG::AbstractStateBehaviour*>(ref().get());	}

	protected:
		E_AbstractStateBehaviour(MinSG::AbstractStateBehaviour * behaviour, EScript::Type* type=nullptr) : E_AbstractBehaviour(behaviour,type?type:getTypeObject()) {}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_AbstractBehaviour,		MinSG::AbstractBehaviour*,			**eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::AbstractBehaviour*, 			E_MinSG::E_AbstractBehaviour,		dynamic_cast<E_MinSG::E_AbstractBehaviour*>(E_MinSG::E_Behavior::create(obj)))

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_AbstractNodeBehaviour,	MinSG::AbstractNodeBehaviour*,		**eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::AbstractNodeBehaviour*, 		E_MinSG::E_AbstractNodeBehaviour,	dynamic_cast<E_MinSG::E_AbstractNodeBehaviour*>(E_MinSG::E_Behavior::create(obj)))

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_AbstractStateBehaviour,	MinSG::AbstractStateBehaviour*,		**eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::AbstractStateBehaviour*, 	E_MinSG::E_AbstractStateBehaviour,	dynamic_cast<E_MinSG::E_AbstractStateBehaviour*>(E_MinSG::E_Behavior::create(obj)))


#endif // __E_AbstractBehaviour_H
