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

#include "E_SoundReceivingBehaviour.h"
#include "../KeyFrameAnimation/E_KeyFrameAnimationNode.h"

#include "../../ELibMinSG.h"

#include <E_Sound/E_Listener.h>
#include <EScript/EScript.h>
#include <iostream>

using namespace MinSG;

namespace E_MinSG {

EScript::Type* E_SoundReceivingBehaviour::typeObject=nullptr;


// -----
//! (static)
void E_SoundReceivingBehaviour::init(EScript::Namespace & lib) {
	// MinSG.SoundReceivingBehaviour ---|> MinSG.E_AbstractNodeBehaviour ---|> Object
	typeObject=new EScript::Type(E_AbstractNodeBehaviour::getTypeObject());

	declareConstant(&lib,getClassName(),typeObject);

	//! new SoundReceivingBehaviour( Node )
	ES_CTOR(typeObject,1,1,	EScript::create( new SoundReceivingBehaviour( (parameter[0].to<MinSG::Node*>(rt)))))

	//! Sound.Source SoundReceivingBehaviour.getListener()
	ES_MFUN(typeObject, const SoundReceivingBehaviour,"getListener",0,0,	new E_Sound::E_Listener((thisObj->getListener())))


	addFactory<MinSG::SoundReceivingBehaviour,E_SoundReceivingBehaviour>();
}

// ------------------------------------------------------------
//! (ctor)
E_SoundReceivingBehaviour::E_SoundReceivingBehaviour(SoundReceivingBehaviour * _behaviour) :
		E_AbstractNodeBehaviour(_behaviour,typeObject) {
}

//! (dtor)
E_SoundReceivingBehaviour::~E_SoundReceivingBehaviour() {
	//dtor
}

}

#endif // MINSG_EXT_SOUND
