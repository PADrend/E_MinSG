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
#ifndef E_BEHAVIOURGROUP_H_
#define E_BEHAVIOURGROUP_H_

#include "../../Core/Behaviours/E_AbstractBehaviour.h"
#include <MinSG/Ext/Behaviours/BehaviourGroup.h>

namespace E_MinSG {

class E_BehaviourGroup: public E_AbstractNodeBehaviour {
		ES_PROVIDES_TYPE_NAME(BehaviourGroup)
	public:
		// ---
		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		E_BehaviourGroup(MinSG::BehaviourGroup * _behaviour);
		virtual ~E_BehaviourGroup();

		MinSG::BehaviourGroup * operator*()const	{	return static_cast<MinSG::BehaviourGroup*>(ref().get());	}
		MinSG::BehaviourGroup * get()const			{	return static_cast<MinSG::BehaviourGroup*>(ref().get());	}
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_BehaviourGroup,	MinSG::BehaviourGroup*,		**eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::BehaviourGroup*, 	E_MinSG::E_BehaviourGroup,	dynamic_cast<E_MinSG::E_BehaviourGroup*>(E_MinSG::E_Behavior::create(obj)))

#endif /* E_BEHAVIOURGROUP_H_ */
