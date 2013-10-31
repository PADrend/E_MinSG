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
#include "E_TimedBehaviourDecorator.h"

#include "../../ELibMinSG.h"

#include <EScript/EScript.h>

using namespace MinSG;

namespace E_MinSG {

EScript::Type* E_TimedBehaviourDecorator::typeObject=nullptr;

// -----
//! (static)
void E_TimedBehaviourDecorator::init(EScript::Namespace & lib) {
	// MinSG.TimedBehaviourDecorator ---|> MinSG.AbstractBehaviourDecorator ---|> MinSG.AbstractBehaviour ---|> Object
	typeObject=new EScript::Type(E_AbstractBehaviourDecorator::typeObject);

	declareConstant(&lib,getClassName(),typeObject);

	//! new TimedBehaviourDecorator( AbstractBehaviour, startTime, relative )
	ES_CTOR(typeObject,1,3,	EScript::create( new TimedBehaviourDecorator(
								EScript::assertType<E_AbstractBehaviour>(rt,parameter[0])->get(),
								parameter[1].toDouble(0), parameter[2].toBool(false) )))

	//! Int TimedBehaviourDecorator.getStartTime()
	ES_MFUN(typeObject, TimedBehaviourDecorator,"getStartTime",0,0,			(thisObj->getStartTime()))

	//! self TimedBehaviourDecorator.setStartTime(Number, Bool)
	ES_MFUN(typeObject, TimedBehaviourDecorator,"setStartTime",1,2,			(thisObj->setStartTime(parameter[0].toDouble(),parameter[1].toBool(false)),thisEObj))

	addFactory<MinSG::TimedBehaviourDecorator,E_TimedBehaviourDecorator>();
}

// ------------------------------------------------------------
//! (ctor)
E_TimedBehaviourDecorator::E_TimedBehaviourDecorator(TimedBehaviourDecorator * _behaviour) :
		E_AbstractBehaviourDecorator(_behaviour,typeObject) {
}

//! (dtor)
E_TimedBehaviourDecorator::~E_TimedBehaviourDecorator() {
	//dtor
}

}
