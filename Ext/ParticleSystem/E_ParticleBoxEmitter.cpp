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

#include "E_ParticleBoxEmitter.h"

#include "E_ParticleSystemNode.h"

#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/EScript.h>
#include "../../ELibMinSG.h"

#include <E_Geometry/E_Box.h>

using namespace MinSG;

namespace E_MinSG {

EScript::Type* E_ParticleBoxEmitter::typeObject=nullptr;

//! (static)	
void E_ParticleBoxEmitter::init(EScript::Namespace & lib) {

	// MinSG.ParticleBoxEmitter ---|> MinSG.ParticleEmitter ---|> MinSG.AbstractBehaviour ---|> [Object]
	typeObject=new EScript::Type(E_ParticleEmitter::typeObject);

	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] new MinSG.ParticleBoxEmitter( particleSystem )	
	ES_CTOR(typeObject,1,1,E_Behavior::create(
					new ParticleBoxEmitter(**EScript::assertType<E_ParticleSystemNode>(rt,parameter[0]))))

	//!	[ESMF] Box MinSG.ParticleBoxEmitter.getDirection()
	ESMF_DECLARE(typeObject,E_ParticleBoxEmitter,"getEmitBounds",0,0,EScript::create((**self)->getEmitBounds()))

	//! [ESMF] self MinSG.ParticleBoxEmitter.setDirection(Box)	
	ESMF_DECLARE(typeObject,E_ParticleBoxEmitter,"setEmitBounds",1,1,((**self)->setEmitBounds(
				parameter[0].to<const Geometry::Box&>(runtime)), self))


	addFactory<MinSG::ParticleBoxEmitter, E_ParticleBoxEmitter>();
}

E_ParticleBoxEmitter::E_ParticleBoxEmitter(ParticleBoxEmitter * c,EScript::Type * type):E_ParticleEmitter(c,type?type:typeObject) {
}

E_ParticleBoxEmitter::~E_ParticleBoxEmitter() {
}

}

#endif
