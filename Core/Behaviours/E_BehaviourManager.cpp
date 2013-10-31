/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_BehaviourManager.h"

#include "E_AbstractBehaviour.h"
#include "../Nodes/E_Node.h"
#include "../States/E_State.h"
#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

//! (static)
EScript::Type * E_BehaviourManager::getTypeObject() {
	// E_BehaviourManager ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) initMembers
void E_BehaviourManager::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] new MinSG.BehaviourManager()
	ES_CTOR(typeObject,0,0,EScript::create(new BehaviourManager()))

	//! [ESMF] self MinSG.BehaviourManager.clearBehaviours(AbstractBehaviour)
	ES_MFUN(typeObject,BehaviourManager,"clearBehaviours",0,0,
			(thisObj->clearBehaviours(),thisEObj))

	//! [ESMF] void MinSG.BehaviourManager.executeBehaviours(time [,finishedBhaviours ])
	ES_MFUNCTION(typeObject,BehaviourManager,"executeBehaviours",1,2,{
		if(parameter.count()<2){
			thisObj->executeBehaviours(parameter[0].toFloat());
		}else {
			Array * a = parameter[1].to<EScript::Array*>(rt);
			BehaviourManager::behaviourList_t finishedBehaviours;
			thisObj->executeBehaviours(parameter[0].toFloat(),finishedBehaviours);
			for(BehaviourManager::behaviourList_t::const_iterator it=finishedBehaviours.begin();
					it!=finishedBehaviours.end();++it){
				a->pushBack( E_Behavior::create( (*it).get() ));
			}
		}
		return nullptr;
	})

	//! [ESMF] Array MinSG.BehaviourManager.getBehavioursByNode(node)
	ES_MFUNCTION(typeObject,const BehaviourManager,"getBehavioursByNode",1,1,{
		Array * a = Array::create();
		for( auto & entry : thisObj->getBehavioursByNode(parameter[0].to<MinSG::Node*>(rt)))
			a->pushBack(E_Behavior::create( entry.get() ));
		return a;
	})

	//! [ESMF] self MinSG.BehaviourManager.registerBehaviour(AbstractBehaviour)
	ES_MFUN(typeObject,BehaviourManager,"registerBehaviour",1,1,
			(thisObj->registerBehaviour(EScript::assertType<E_AbstractBehaviour>(rt, parameter[0])->get()),thisEObj))

	//! [ESMF] self MinSG.BehaviourManager.removeBehaviour(AbstractBehaviour)
	ES_MFUN(typeObject,BehaviourManager,"removeBehaviour",1,1,
			(thisObj->removeBehaviour(EScript::assertType<E_AbstractBehaviour>(rt, parameter[0])->get()),thisEObj))

	//! [ESMF] self MinSG.BehaviourManager.startNodeBehavior(behavior,Node)
	ES_MFUN(typeObject,BehaviourManager,"startNodeBehavior",2,2,
			(thisObj->startNodeBehavior( parameter[0].to<Behavior*>(rt),parameter[1].to<Node*>(rt) ),thisEObj))

	//! [ESMF] self MinSG.BehaviourManager.startStateBehavior(behavior,State)
	ES_MFUN(typeObject,BehaviourManager,"startStateBehavior",2,2,
			(thisObj->startStateBehavior( parameter[0].to<Behavior*>(rt),parameter[1].to<State*>(rt) ),thisEObj))
}

}
