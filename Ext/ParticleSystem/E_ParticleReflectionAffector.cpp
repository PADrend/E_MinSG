/*
	This file is part of the E_MinSG library extension ParticleSystem.
	Copyright (C) 2014 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_PARTICLE

#include "E_ParticleReflectionAffector.h"
#include <E_Geometry/E_Vec3.h>
#include <E_Geometry/E_Plane.h>

#include "E_ParticleSystemNode.h"
#include "../../ELibMinSG.h"
#include <EScript/Basics.h>


using namespace MinSG;

namespace E_MinSG {

EScript::Type* E_ParticleReflectionAffector::typeObject=nullptr;


//! (static)	
void E_ParticleReflectionAffector::init(EScript::Namespace & lib) {

	// MinSG.ParticlePointEmitter ---|> MinSG.ParticleEmitter ---|> MinSG.State ---|> [Object]
	typeObject = new EScript::Type(E_ParticleAffector::typeObject);

	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] new MinSG.ParticleReflectionAffector( particleSystem )	
	ES_CTOR(typeObject,1,1,E_Behavior::create(new ParticleReflectionAffector(parameter[0].to<ParticleSystemNode*>(rt))))

	//! [ESMF] Number MinSG.ParticleEmitter.getAdherence()	
	ES_MFUN(typeObject, const ParticleReflectionAffector,"getAdherence",0,0, thisObj->getAdherence())

	//! [ESMF] Plane MinSG.ParticleEmitter.getPlane()	
	ES_MFUN(typeObject, const ParticleReflectionAffector,"getPlane",0,0, thisObj->getPlane())

	//! [ESMF] Number MinSG.ParticleEmitter.getReflectiveness()	
	ES_MFUN(typeObject, const ParticleReflectionAffector,"getReflectiveness",0,0, thisObj->getReflectiveness())

	//! [ESMF] self MinSG.ParticleEmitter.setAdherence( f )	
	ES_MFUN(typeObject, ParticleReflectionAffector,"setAdherence",1,1, (thisObj->setAdherence( parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self MinSG.ParticleEmitter.setPlane( Plane )	
	ES_MFUN(typeObject, ParticleReflectionAffector,"setPlane",1,1, (thisObj->setPlane( parameter[0].to<Geometry::Plane>(rt)),thisEObj))

	
	//! [ESMF] self MinSG.ParticleEmitter.setReflectiveness( f )	
	ES_MFUN(typeObject, ParticleReflectionAffector,"setReflectiveness",1,1, (thisObj->setReflectiveness( parameter[0].to<float>(rt)),thisEObj))

	addFactory<MinSG::ParticleReflectionAffector, E_ParticleReflectionAffector>();
}



}

#endif
