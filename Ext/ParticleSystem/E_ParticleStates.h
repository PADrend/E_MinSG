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


#ifndef E_PARTICLEEMITTER_H_
#define E_PARTICLEEMITTER_H_

#include <MinSG/Ext/ParticleSystem/ParticleEmitters.h>
#include <MinSG/Ext/ParticleSystem/ParticleAffectors.h>
#include <EScript/EScript.h>

#include "../../Core/Behaviours/E_AbstractBehaviour.h"

namespace E_MinSG {


class E_ParticleEmitter : public E_AbstractNodeBehaviour {
	ES_PROVIDES_TYPE_NAME(ParticleEmitter)
public:

	static EScript::Type* typeObject;
	static void init(EScript::Namespace & lib);

	E_ParticleEmitter(MinSG::ParticleEmitter * c,EScript::Type * type=nullptr);
	virtual ~E_ParticleEmitter();

	const MinSG::ParticleEmitter * operator*()const		{	return static_cast<const MinSG::ParticleEmitter*>(ref().get());	}
	MinSG::ParticleEmitter * operator*()				{	return static_cast<MinSG::ParticleEmitter*>(ref().get());	}
};

class E_ParticleAffector : public E_AbstractNodeBehaviour {
	ES_PROVIDES_TYPE_NAME(ParticleAffector)
public:

	static EScript::Type* typeObject;
	static void init(EScript::Namespace & lib);

	E_ParticleAffector(MinSG::ParticleAffector * c,EScript::Type * type=nullptr);
	virtual ~E_ParticleAffector();

	const MinSG::ParticleAffector * operator*()const		{	return static_cast<const MinSG::ParticleAffector*>(ref().get());	}
	MinSG::ParticleAffector * operator*()					{	return static_cast<MinSG::ParticleAffector*>(ref().get());	}

};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ParticleEmitter,		MinSG::ParticleEmitter*,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ParticleAffector,	MinSG::ParticleAffector*,		**eObj)


#endif /* E_PARTICLEEMITTER_H_ */
#endif
