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

#include "E_ParticleFadeOutAffector.h"

#include "E_ParticleSystemNode.h"

#include "../../ELibMinSG.h"

#include <E_Geometry/E_Vec3.h>

using namespace MinSG;
using E_Geometry::E_Vec3;

namespace E_MinSG {

EScript::Type* E_ParticleFadeOutAffector::typeObject=nullptr;

//! (static)	
void E_ParticleFadeOutAffector::init(EScript::Namespace & lib) {

	// MinSG.ParticlePointEmitter ---|> MinSG.ParticleEmitter ---|> MinSG.State ---|> [Object]
	typeObject=new EScript::Type(E_ParticleAffector::typeObject);

	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] new MinSG.ParticleFadeOutAffector( particleSystem )
	ES_CTOR(typeObject,1,1,E_Behavior::create(new ParticleFadeOutAffector(
			**EScript::assertType<E_ParticleSystemNode>(rt,parameter[0]))))

	addFactory<MinSG::ParticleFadeOutAffector, E_ParticleFadeOutAffector>();
}

E_ParticleFadeOutAffector::E_ParticleFadeOutAffector(ParticleFadeOutAffector * c,EScript::Type * type):E_ParticleAffector(c,type?type:typeObject) {
}

E_ParticleFadeOutAffector::~E_ParticleFadeOutAffector() {
}

}

#endif
