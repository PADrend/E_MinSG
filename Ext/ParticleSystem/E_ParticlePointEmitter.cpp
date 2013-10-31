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

#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/EScript.h>
#include "../../ELibMinSG.h"

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

EScript::Type* E_ParticlePointEmitter::typeObject=nullptr;

//! (static)	
void E_ParticlePointEmitter::init(EScript::Namespace & lib) {

	// MinSG.ParticlePointEmitter ---|> MinSG.ParticleEmitter ---|> MinSG.AbstractBehaviour ---|> [Object]
	typeObject = new EScript::Type(E_ParticleEmitter::typeObject);

	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] new MinSG.ParticlePointEmitter( particleSystem )	
	ES_CTOR(typeObject,1,1,E_Behavior::create(
					new ParticlePointEmitter(**EScript::assertType<E_ParticleSystemNode>(rt,parameter[0]))))

	//! [ESMF] Number ParticlePointEmitter.getMinOffset()	
	ESMF_DECLARE(typeObject,E_ParticlePointEmitter,"getMinOffset",0,0,Number::create((**self)->getMinOffset()))

	//! [ESMF] self ParticlePointEmitter.setMinOffset(Number)	
	ESMF_DECLARE(typeObject,E_ParticlePointEmitter,"setMinOffset",1,1,((**self)->setMinOffset(parameter[0].toFloat()), self))

	//! [ESMF] Number ParticlePointEmitter.getMaxOffset()	
	ESMF_DECLARE(typeObject,E_ParticlePointEmitter,"getMaxOffset",0,0,Number::create((**self)->getMaxOffset()))

	//! [ESMF] self ParticlePointEmitter.setMaxOffset(Number)	
	ESMF_DECLARE(typeObject,E_ParticlePointEmitter,"setMaxOffset",1,1,((**self)->setMaxOffset(parameter[0].toFloat()), self))


	addFactory<MinSG::ParticlePointEmitter, E_ParticlePointEmitter>();
}

E_ParticlePointEmitter::E_ParticlePointEmitter(ParticlePointEmitter * c,Type * type):E_ParticleEmitter(c,type?type:typeObject) {
}

E_ParticlePointEmitter::~E_ParticlePointEmitter() {
}

}

#endif
