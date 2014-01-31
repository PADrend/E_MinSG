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

#include "E_ParticleStates.h"

#include "../../ELibMinSG.h"

#include <E_Geometry/E_Vec3.h>

#include <E_Util/Graphics/E_Color.h>
#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;
using E_Geometry::E_Vec3;

namespace E_MinSG {

EScript::Type* E_ParticleEmitter::typeObject=nullptr;

//! (static)	
void E_ParticleEmitter::init(EScript::Namespace & lib) {

	// MinSG.ParticleEmitter ---|> E_AbstractNodeBehaviour
	typeObject = new EScript::Type(E_AbstractNodeBehaviour::getTypeObject());

	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] Vec3 MinSG.ParticleEmitter.getDirection()	
	ES_MFUN(typeObject, const ParticleEmitter,"getDirection",0,0,EScript::create(thisObj->getDirection()))
	ES_MFUN(typeObject, const ParticleEmitter,"getDirectionVarianceAngle",0,0,thisObj->getDirectionVarianceAngle().deg())
	ES_MFUN(typeObject, const ParticleEmitter,"getMaxColor",0,0,EScript::create(thisObj->getMaxColor()))
	ES_MFUN(typeObject, const ParticleEmitter,"getMaxHeight",0,0,thisObj->getMaxHeight())
	ES_MFUN(typeObject, const ParticleEmitter,"getMaxLife",0,0,thisObj->getMaxLife())
	ES_MFUN(typeObject, const ParticleEmitter,"getMaxSpeed",0,0,thisObj->getMaxSpeed())
	ES_MFUN(typeObject, const ParticleEmitter,"getMaxWidth",0,0,thisObj->getMaxWidth())
	ES_MFUN(typeObject, const ParticleEmitter,"getMinColor",0,0,EScript::create(thisObj->getMinColor()))
	ES_MFUN(typeObject, const ParticleEmitter,"getMinLife",0,0,thisObj->getMinLife())
	ES_MFUN(typeObject, const ParticleEmitter,"getMinHeight",0,0,thisObj->getMinHeight())
	ES_MFUN(typeObject, const ParticleEmitter,"getMinSpeed",0,0,thisObj->getMinSpeed())
	ES_MFUN(typeObject, const ParticleEmitter,"getMinWidth",0,0,thisObj->getMinWidth())
	ES_MFUN(typeObject, const ParticleEmitter,"getParticlesPerSecond",0,0,thisObj->getParticlesPerSecond())

	//! [ESMF] void | Node ParticleEmitter.getSpawnNode()
	ES_MFUN(typeObject, const ParticleEmitter,"getSpawnNode",0,0,EScript::create(thisObj->getSpawnNode()))

	//! [ESMF] Number ParticleEmitter.getTimeOffset()
	ES_MFUN(typeObject, const ParticleEmitter, "getTimeOffset", 0, 0, thisObj->getTimeOffset())

	//! [ESMF] bool MinSG.ParticleEmitter.isEnabled()	
	ES_MFUN(typeObject, const ParticleEmitter,"isEnabled",0,0,thisObj->isEnabled())

	//! [ESMF] self MinSG.ParticleEmitter.setDirection(Vec3)	
	ES_MFUN(typeObject, ParticleEmitter,"setDirection",1,1,(thisObj->setDirection( parameter[0].to<Geometry::Vec3>(rt)), thisEObj))

	ES_MFUN(typeObject, ParticleEmitter,"setDirectionVarianceAngle",1,1,(thisObj->setDirectionVarianceAngle(Geometry::Angle::deg(parameter[0].toFloat())), thisEObj))
	ES_MFUN(typeObject, ParticleEmitter,"setParticlesPerSecond",1,1,(thisObj->setParticlesPerSecond(parameter[0].toFloat()), thisEObj))
	ES_MFUN(typeObject, ParticleEmitter,"setMaxColor",1,1,(thisObj->setMaxColor(parameter[0].to<Util::Color4f>(rt)), thisEObj))
	ES_MFUN(typeObject, ParticleEmitter,"setMaxHeight",1,1,(thisObj->setMaxHeight(parameter[0].toFloat()), thisEObj))
	ES_MFUN(typeObject, ParticleEmitter,"setMaxLife",1,1,(thisObj->setMaxLife(parameter[0].toFloat()), thisEObj))
	ES_MFUN(typeObject, ParticleEmitter,"setMaxSpeed",1,1,(thisObj->setMaxSpeed(parameter[0].toFloat()), thisEObj))
	ES_MFUN(typeObject, ParticleEmitter,"setMaxWidth",1,1,(thisObj->setMaxWidth(parameter[0].toFloat()), thisEObj))
	ES_MFUN(typeObject, ParticleEmitter,"setMinColor",1,1,(thisObj->setMinColor(parameter[0].to<Util::Color4f>(rt)), thisEObj))
	ES_MFUN(typeObject, ParticleEmitter,"setMinLife",1,1,(thisObj->setMinLife(parameter[0].toFloat()), thisEObj))
	ES_MFUN(typeObject, ParticleEmitter,"setMinHeight",1,1,(thisObj->setMinHeight(parameter[0].toFloat()), thisEObj))
	ES_MFUN(typeObject, ParticleEmitter,"setMinSpeed",1,1,(thisObj->setMinSpeed(parameter[0].toFloat()), thisEObj))
	ES_MFUN(typeObject, ParticleEmitter,"setMinWidth",1,1,(thisObj->setMinWidth(parameter[0].toFloat()), thisEObj))

	//! [ESMF] self ParticleEmitter.setSpawnNode(void | Node)
	ES_MFUN(typeObject, ParticleEmitter,"setSpawnNode", 1, 1,(thisObj->setSpawnNode(parameter[0].toBool()?parameter[0].to<MinSG::Node*>(rt):nullptr),thisEObj))

	//! [ESMF] self ParticleEmitter.setTimeOffset(Number)
	ES_MFUN(typeObject, ParticleEmitter, "setTimeOffset", 1, 1, (thisObj->setTimeOffset(parameter[0].toDouble()), thisEObj))
}

E_ParticleEmitter::E_ParticleEmitter(ParticleEmitter * c,Type * type):E_AbstractNodeBehaviour(c, type?type:typeObject) {
}

E_ParticleEmitter::~E_ParticleEmitter() {
}

// -----------------------------------------------------------------------------------------
// --------------------------------------- Affector ----------------------------------------
// -----------------------------------------------------------------------------------------

Type* E_ParticleAffector::typeObject=nullptr;

//! (static)	
void E_ParticleAffector::init(EScript::Namespace & lib) {

	// MinSG.ParticleAffector ---|> E_AbstractNodeBehaviour
	typeObject = new EScript::Type(E_AbstractNodeBehaviour::getTypeObject());

	declareConstant(&lib,getClassName(),typeObject);

//	ES_CTOR(typeObject,0,0,new E_ParticleAffector(new MinSG::ParticleAffector))
}

E_ParticleAffector::E_ParticleAffector(ParticleAffector * c,Type * type):E_AbstractNodeBehaviour(c, type?type:typeObject) {
}

E_ParticleAffector::~E_ParticleAffector() {
}

}

#endif
