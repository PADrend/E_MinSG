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

#include "E_ParticleSystemNode.h"
#include <E_Util/E_Utils.h>
#include "../../ELibMinSG.h"

#include <EScript/EScript.h>

namespace E_MinSG {

EScript::Type * E_ParticleSystemNode::typeObject = nullptr;

//! initMembers
void E_ParticleSystemNode::init(EScript::Namespace & lib) {
	using namespace MinSG;
	
	/// [E_ParticleSystemNode] ---|> [E_Node]
	typeObject = new EScript::Type(E_Node::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] new MinSG.ParticleSystemNode
	ES_CTOR(typeObject,0,0,EScript::create(new ParticleSystemNode))

	//! [ESMF] Number ParticleSystemNode.getRendererType()	
	ES_MFUN(typeObject,const ParticleSystemNode,"getRendererType",0,0,static_cast<uint32_t>(thisObj->getRendererType()))

	//! [ESMF] Number ParticleSystemNode.getMaxParticleCount()	
	ES_MFUN(typeObject,const ParticleSystemNode,"getMaxParticleCount",0,0,EScript::Number::create(thisObj->getMaxParticleCount()))

	//! [ESMF] self ParticleSystemNode.setMaxParticleCount(Number)	
	ES_MFUN(typeObject, ParticleSystemNode,"setMaxParticleCount",1,1,(thisObj->setMaxParticleCount(parameter[0].toInt()), thisEObj))

	//! [ESMF] self ParticleSystemNode.setRenderer(Number)	
	ES_MFUN(typeObject, ParticleSystemNode,"setRenderer",1,1,
					(thisObj->setRenderer(static_cast<ParticleSystemNode::renderer_t>(parameter[0].toUInt())), thisEObj))

	declareConstant(typeObject,"POINT_RENDERER",static_cast<uint32_t>(ParticleSystemNode::POINT_RENDERER));
	declareConstant(typeObject,"BILLBOARD_RENDERER",static_cast<uint32_t>(ParticleSystemNode::BILLBOARD_RENDERER));

	addFactory<ParticleSystemNode,E_ParticleSystemNode>();
}

}

#endif
