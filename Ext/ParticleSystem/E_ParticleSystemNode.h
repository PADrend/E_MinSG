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

#ifndef E_PARTICLESYSTEM_H_
#define E_PARTICLESYSTEM_H_

#include <MinSG/Ext/ParticleSystem/ParticleSystemNode.h>
#include <E_Util/E_Utils.h>

#include "../../Core/Nodes/E_Node.h"

namespace E_MinSG {

class E_ParticleSystemNode: public E_Node {
	ES_PROVIDES_TYPE_NAME(ParticleSystemNode)
public:
	template<class, class, class> friend class Util::PolymorphicWrapperCreator;
	static EScript::Type * typeObject;
	static void init(EScript::Namespace & lib);

	virtual ~E_ParticleSystemNode();

	const MinSG::ParticleSystemNode * operator*()const	{	return static_cast<const MinSG::ParticleSystemNode*>(ref().get());	}
	MinSG::ParticleSystemNode * operator*()				{	return static_cast<MinSG::ParticleSystemNode*>(ref().get());	}

protected:
	E_ParticleSystemNode(MinSG::ParticleSystemNode * gNode, EScript::Type * type = nullptr);
};

}

#endif /* E_PARTICLESYSTEM_H_ */
#endif
