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
#include "E_BehaviourGroup.h"

#include "../../ELibMinSG.h"

#include <EScript/EScript.h>

using namespace MinSG;

namespace E_MinSG {

EScript::Type* E_BehaviourGroup::typeObject=nullptr;


// -----
//! (static)
void E_BehaviourGroup::init(EScript::Namespace & lib) {
	// MinSG.BehaviourGroup ---|> E_AbstractNodeBehaviour
	typeObject=new EScript::Type(E_AbstractNodeBehaviour::getTypeObject());

	declareConstant(&lib,getClassName(),typeObject);

	//! new BehaviourGroup( )
	ES_CTOR(typeObject,0,0,			EScript::create( new BehaviourGroup( )))

	//! [ESMF] self MinSG.BehaviourGroup.addBehaviour(AbstractBehaviour)
	ES_MFUN(typeObject, BehaviourGroup,"addBehaviour",1,1,		(thisObj->addBehaviour(EScript::assertType<E_AbstractBehaviour>(rt, parameter[0])->get()),thisEObj))

	//! [ESMF] self MinSG.BehaviourGroup.removeBehaviour(AbstractBehaviour)
	ES_MFUN(typeObject, BehaviourGroup,"removeBehaviour",1,1,	(thisObj->removeBehaviour(EScript::assertType<E_AbstractBehaviour>(rt, parameter[0])->get()),thisEObj))

	//! [ESMF] Number MinSG.BehaviourGroup.count()
	ES_MFUN(typeObject, BehaviourGroup,"count",0,0,				static_cast<uint32_t>(thisObj->count()))

	addFactory<MinSG::BehaviourGroup,E_BehaviourGroup>();
}

// ------------------------------------------------------------
//! (ctor)
E_BehaviourGroup::E_BehaviourGroup(BehaviourGroup * _behaviour) :
		E_AbstractNodeBehaviour(_behaviour,typeObject) {
}

//! (dtor)
E_BehaviourGroup::~E_BehaviourGroup() {
	//dtor
}

}
