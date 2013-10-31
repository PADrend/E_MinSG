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
#ifndef E_ABSTRACTBEHAVIOURDECORATOR_H_
#define E_ABSTRACTBEHAVIOURDECORATOR_H_

#include "../../Core/Behaviours/E_AbstractBehaviour.h"
#include <MinSG/Ext/Behaviours/AbstractBehaviourDecorator.h>

namespace E_MinSG {

class E_AbstractBehaviourDecorator: public E_AbstractBehaviour {
	ES_PROVIDES_TYPE_NAME(AbstractBehaviourDecorator)
public:
	// ---
	static EScript::Type* typeObject;
	static void init(EScript::Namespace & lib);

	E_AbstractBehaviourDecorator(MinSG::AbstractBehaviourDecorator * _behaviour, EScript::Type * type=nullptr);
	virtual ~E_AbstractBehaviourDecorator();

	MinSG::AbstractBehaviourDecorator * operator*()const	{	return static_cast<MinSG::AbstractBehaviourDecorator*>(ref().get());	}
	MinSG::AbstractBehaviourDecorator * get()const			{	return static_cast<MinSG::AbstractBehaviourDecorator*>(ref().get());	}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_AbstractBehaviourDecorator,	MinSG::AbstractBehaviourDecorator*,		**eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::AbstractBehaviourDecorator*, 	E_MinSG::E_AbstractBehaviourDecorator,	dynamic_cast<E_MinSG::E_AbstractBehaviourDecorator*>(E_MinSG::E_Behavior::create(obj)))

#endif /* E_ABSTRACTBEHAVIOURDECORATOR_H_ */
