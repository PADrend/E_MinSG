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
#include "E_AbstractBehaviourDecorator.h"

#include "../../ELibMinSG.h"

#include <EScript/EScript.h>

using namespace MinSG;

namespace E_MinSG {

EScript::Type* E_AbstractBehaviourDecorator::typeObject=nullptr;

// -----
//! (static)
void E_AbstractBehaviourDecorator::init(EScript::Namespace & lib) {
	// MinSG.AbstractBehaviourDecorator ---|> MinSG.AbstractBehaviour ---|> Object
	typeObject=new EScript::Type(E_AbstractBehaviour::getTypeObject());

	declareConstant(&lib,getClassName(),typeObject);

	//! AbstractBehaviour AbstractBehaviourDecorator.getDecorated()
	ES_MFUN(typeObject, AbstractBehaviourDecorator,"getDecorated",0,0,		EScript::create( thisObj->getDecorated() ));

	//! AbstractBehaviour AbstractBehaviourDecorator.getDecoratedRoot()
	ES_MFUN(typeObject, AbstractBehaviourDecorator,"getDecoratedRoot",0,0,	EScript::create( thisObj->getDecoratedRoot() ));

	addFactory<MinSG::AbstractBehaviourDecorator,E_AbstractBehaviourDecorator>();
}

// ------------------------------------------------------------
//! (ctor)
E_AbstractBehaviourDecorator::E_AbstractBehaviourDecorator(AbstractBehaviourDecorator * _behaviour, EScript::Type* type) :
		E_AbstractBehaviour(_behaviour,type?type:typeObject) {
}

//! (dtor)
E_AbstractBehaviourDecorator::~E_AbstractBehaviourDecorator() {
	//dtor
}

}
