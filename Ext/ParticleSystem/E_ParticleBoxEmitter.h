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


#ifndef E_PARTICLEBOXEMITTER_H_
#define E_PARTICLEBOXEMITTER_H_

#include "E_ParticleStates.h"
#include <MinSG/Ext/ParticleSystem/ParticleEmitters.h>


namespace E_MinSG {

class E_ParticleBoxEmitter : public E_ParticleEmitter {
	ES_PROVIDES_TYPE_NAME(ParticleBoxEmitter)
public:
	static EScript::Type* typeObject;
	static void init(EScript::Namespace & lib);

	E_ParticleBoxEmitter(MinSG::ParticleBoxEmitter * c, EScript::Type * type=nullptr):E_ParticleEmitter(c,type?type:typeObject){}
	virtual ~E_ParticleBoxEmitter(){}

	const MinSG::ParticleBoxEmitter * operator*()const		{	return static_cast<const MinSG::ParticleBoxEmitter*>(ref().get());	}
	MinSG::ParticleBoxEmitter * operator*()					{	return static_cast<MinSG::ParticleBoxEmitter*>(ref().get());	}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ParticleBoxEmitter,	MinSG::ParticleBoxEmitter*,	**eObj)

#endif /* E_PARTICLEBOXEMITTER_H_ */
#endif
