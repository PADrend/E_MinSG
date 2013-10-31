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
#ifndef E_TIMEDBEHAVIOURDECORATOR_H_
#define E_TIMEDBEHAVIOURDECORATOR_H_

#include "E_AbstractBehaviourDecorator.h"
#include <MinSG/Ext/Behaviours/TimedBehaviourDecorator.h>

namespace E_MinSG {

class E_TimedBehaviourDecorator: public E_AbstractBehaviourDecorator {
		ES_PROVIDES_TYPE_NAME(TimedBehaviourDecorator)
	public:
		// ---
		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		E_TimedBehaviourDecorator(MinSG::TimedBehaviourDecorator * _behaviour);
		virtual ~E_TimedBehaviourDecorator();

		MinSG::TimedBehaviourDecorator * operator*()const	{	return static_cast<MinSG::TimedBehaviourDecorator*>(ref().get());	}
		MinSG::TimedBehaviourDecorator * get()const			{	return static_cast<MinSG::TimedBehaviourDecorator*>(ref().get());	}
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_TimedBehaviourDecorator,	MinSG::TimedBehaviourDecorator*,		**eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::TimedBehaviourDecorator*, 	E_MinSG::E_TimedBehaviourDecorator,		dynamic_cast<E_MinSG::E_TimedBehaviourDecorator*>(E_MinSG::E_Behavior::create(obj)))

#endif /* E_TIMEDBEHAVIOURDECORATOR_H_ */
