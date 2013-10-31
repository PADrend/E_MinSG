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

#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/EScript.h>
#include <E_Util/E_Utils.h>

#include "../../ELibMinSG.h"

#include "../../Core/Behaviours/E_BehaviourManager.h"

#include <MinSG/Ext/ParticleSystem/ParticleEmitters.h>
#include <MinSG/Ext/ParticleSystem/ParticleAffectors.h>

#include "E_ParticleStates.h"

// affectors
#include "E_ParticleGravityAffector.h"
#include "E_ParticleFadeOutAffector.h"

// emitters
#include "E_ParticlePointEmitter.h"

namespace E_MinSG {

EScript::Type * E_ParticleSystemNode::typeObject = nullptr;

//! initMembers
void E_ParticleSystemNode::init(EScript::Namespace & lib) {
	/// [E_ParticleSystemNode] ---|> [E_Node]
	typeObject = new EScript::Type(E_Node::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] new MinSG.ParticleSystemNode
	ES_CTOR(typeObject,0,0,EScript::create(new MinSG::ParticleSystemNode))

	//! [ESMF] Number ParticleSystemNode.getRendererType()	
	ESMF_DECLARE(typeObject,const E_ParticleSystemNode,"getRendererType",0,0,static_cast<uint32_t>((**self)->getRendererType()))

	//! [ESMF] Number ParticleSystemNode.getMaxParticleCount()	
	ESMF_DECLARE(typeObject,const E_ParticleSystemNode,"getMaxParticleCount",0,0,EScript::Number::create((**self)->getMaxParticleCount()))

	//! [ESMF] self ParticleSystemNode.setMaxParticleCount(Number)	
	ESMF_DECLARE(typeObject,E_ParticleSystemNode,"setMaxParticleCount",1,1,((**self)->setMaxParticleCount(parameter[0].toInt()), caller))

	//! [ESMF] self ParticleSystemNode.setRenderer(Number)	
	ESMF_DECLARE(typeObject,E_ParticleSystemNode,"setRenderer",1,1,
					((**self)->setRenderer(static_cast<MinSG::ParticleSystemNode::renderer_t>(parameter[0].toUInt())), caller))

	declareConstant(typeObject,"POINT_RENDERER",static_cast<uint32_t>(MinSG::ParticleSystemNode::POINT_RENDERER));
	declareConstant(typeObject,"BILLBOARD_RENDERER",static_cast<uint32_t>(MinSG::ParticleSystemNode::BILLBOARD_RENDERER));

	addFactory<MinSG::ParticleSystemNode,E_ParticleSystemNode>();
}

//! [ctor]
E_ParticleSystemNode::E_ParticleSystemNode(MinSG::ParticleSystemNode * gNode, EScript::Type * type) :
		E_Node(gNode, type ? type : typeObject) {
}

//! [dtor]
E_ParticleSystemNode::~E_ParticleSystemNode() {
}

}

#endif
