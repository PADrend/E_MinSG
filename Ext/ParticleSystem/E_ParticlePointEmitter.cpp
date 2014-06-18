/*
	This file is part of the E_MinSG library extension ParticleSystem.
	Copyright (C) 2010-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2010-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2010 Jan Krems
	Copyright (C) 2010-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_PARTICLE

#include "E_ParticlePointEmitter.h"

#include "E_ParticleSystemNode.h"

#include <EScript/EScript.h>
#include "../../ELibMinSG.h"

using namespace MinSG;

namespace E_MinSG {

EScript::Type* E_ParticlePointEmitter::typeObject=nullptr;

//! (static)	
void E_ParticlePointEmitter::init(EScript::Namespace & lib) {

	// MinSG.ParticlePointEmitter ---|> MinSG.ParticleEmitter ---|> MinSG.AbstractBehaviour ---|> [Object]
	typeObject = new EScript::Type(E_ParticleEmitter::typeObject);

	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] new MinSG.ParticlePointEmitter( particleSystem )	
	ES_CTOR(typeObject,1,1,E_Behavior::create(new ParticlePointEmitter(parameter[0].to<ParticleSystemNode*>(rt))))

	//! [ESMF] Number ParticlePointEmitter.getMinOffset()	
	ES_MFUN(typeObject, const ParticlePointEmitter,"getMinOffset",0,0, thisObj->getMinOffset())

	//! [ESMF] self ParticlePointEmitter.setMinOffset(Number)	
	ES_MFUN(typeObject, ParticlePointEmitter,"setMinOffset",1,1,(thisObj->setMinOffset(parameter[0].toFloat()), thisEObj))

	//! [ESMF] Number ParticlePointEmitter.getMaxOffset()	
	ES_MFUN(typeObject, const ParticlePointEmitter,"getMaxOffset",0,0, thisObj->getMaxOffset())

	//! [ESMF] self ParticlePointEmitter.setMaxOffset(Number)	
	ES_MFUN(typeObject, ParticlePointEmitter,"setMaxOffset",1,1,(thisObj->setMaxOffset(parameter[0].toFloat()), thisEObj))


	addFactory<MinSG::ParticlePointEmitter, E_ParticlePointEmitter>();
}

}

#endif
