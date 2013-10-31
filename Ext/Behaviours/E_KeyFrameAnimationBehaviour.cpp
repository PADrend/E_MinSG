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
#include "E_KeyFrameAnimationBehaviour.h"
#include "../KeyFrameAnimation/E_KeyFrameAnimationNode.h"

#include "../../ELibMinSG.h"

#include <EScript/EScript.h>
#include <iostream>
#include <sstream>

using namespace MinSG;
using namespace EScript;

namespace E_MinSG {

Type* E_KeyFrameAnimationBehaviour::typeObject=nullptr;

// -----
//! [static]
void E_KeyFrameAnimationBehaviour::init(EScript::Namespace & lib) {
	// MinSG.KeyFrameAnimationBehaviour ---|> MinSG.E_AbstractNodeBehaviour
	typeObject = new EScript::Type(E_AbstractNodeBehaviour::getTypeObject());

	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] new MinSG.KeyFrameAnimationBehaviour(E_KeyFrameAnimationNode  )	
	ES_CTOR(typeObject,1,1,EScript::create( new KeyFrameAnimationBehaviour(**EScript::assertType<E_KeyFrameAnimationNode>(rt,parameter[0])) ))

	addFactory<MinSG::KeyFrameAnimationBehaviour,E_KeyFrameAnimationBehaviour>();
}

// ------------------------------------------------------------
//! [ctor]
E_KeyFrameAnimationBehaviour::E_KeyFrameAnimationBehaviour(KeyFrameAnimationBehaviour * _behaviour):E_AbstractNodeBehaviour(_behaviour,typeObject) {
}

//! [dtor]
E_KeyFrameAnimationBehaviour::~E_KeyFrameAnimationBehaviour() {
	//dtor
}

}
