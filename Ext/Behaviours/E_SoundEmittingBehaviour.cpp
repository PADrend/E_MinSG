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
#ifdef MINSG_EXT_SOUND

#include "E_SoundEmittingBehaviour.h"
#include "../KeyFrameAnimation/E_KeyFrameAnimationNode.h"

#include "../../ELibMinSG.h"

#include <E_Sound/E_Source.h>
#include <EScript/EScript.h>
#include <iostream>

using namespace MinSG;

namespace E_MinSG {

EScript::Type* E_SoundEmittingBehaviour::typeObject=nullptr;


// -----
//! (static)
void E_SoundEmittingBehaviour::init(EScript::Namespace & lib) {
	// MinSG.SoundEmittingBehaviour ---|> MinSG.AbstractBehaviour ---|> Object
	typeObject=new EScript::Type(E_AbstractNodeBehaviour::getTypeObject());

	declareConstant(&lib,getClassName(),typeObject);

	//! new SoundEmittingBehaviour( Node )
	ES_CTOR(typeObject,1,1,	EScript::create( new SoundEmittingBehaviour( parameter[0].to<MinSG::Node*>(rt))))

	//! Sound.Source SoundEmittingBehaviour.getSource()
	ES_MFUN(typeObject, const SoundEmittingBehaviour,"getSource",0,0,		E_Sound::E_Source::create(thisObj->getSource()))

	//! Bool SoundEmittingBehaviour.isRemoveWhenStopped()
	ES_MFUN(typeObject, SoundEmittingBehaviour,"isRemoveWhenStopped",0,0,	thisObj->isRemoveWhenStopped())

	//! self SoundEmittingBehaviour.setRemoveWhenStopped(bool)
	ES_MFUN(typeObject, SoundEmittingBehaviour,"isRemoveWhenStopped",1,1,	(thisObj->setRemoveWhenStopped(parameter[0].toBool()),thisEObj))


	addFactory<MinSG::SoundEmittingBehaviour,E_SoundEmittingBehaviour>();
}

// ------------------------------------------------------------
//! (ctor)
E_SoundEmittingBehaviour::E_SoundEmittingBehaviour(SoundEmittingBehaviour * _behaviour) :
		E_AbstractNodeBehaviour(_behaviour,typeObject) {
}

//! (dtor)
E_SoundEmittingBehaviour::~E_SoundEmittingBehaviour() {
	//dtor
}

}

#endif // MINSG_EXT_SOUND
