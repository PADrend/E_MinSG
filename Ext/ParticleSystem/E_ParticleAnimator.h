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

#ifndef E_PARTICLEANIMATOR_H_
#define E_PARTICLEANIMATOR_H_

#include "E_ParticleStates.h"
#include <MinSG/Ext/ParticleSystem/ParticleAffectors.h>

namespace E_MinSG {

class E_ParticleAnimator : public E_ParticleAffector {
	ES_PROVIDES_TYPE_NAME(ParticleAnimator)
public:

	static EScript::Type* typeObject;
	static void init(EScript::Namespace & lib);

	E_ParticleAnimator(MinSG::ParticleAnimator * c, EScript::Type * type=nullptr);
	virtual ~E_ParticleAnimator();


	const MinSG::ParticleAnimator * operator*()const		{	return static_cast<const MinSG::ParticleAnimator*>(ref().get());	}
	MinSG::ParticleAnimator * operator*()					{	return static_cast<MinSG::ParticleAnimator*>(ref().get());	}
};

}

#endif /* E_PARTICLEANIMATOR_H_ */

#endif
