/*
	This file is part of the MinSG library extension Behaviours.
	Copyright (C) 2011 Sascha Brandt
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SOUND

#ifndef __E_SoundReceivingBehaviour_H
#define __E_SoundReceivingBehaviour_H

#include "../../Core/Behaviours/E_AbstractBehaviour.h"
#include <MinSG/Ext/Behaviours/SoundReceivingBehaviour.h>

namespace E_MinSG{

/***
 **   E_SoundReceivingBehaviour ---|> E_AbstractNodeBehaviour
 **/
class E_SoundReceivingBehaviour : public E_AbstractNodeBehaviour{
	ES_PROVIDES_TYPE_NAME(SoundReceivingBehaviour)

	public:
		// ---
		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		E_SoundReceivingBehaviour(MinSG::SoundReceivingBehaviour * _behaviour);
		virtual ~E_SoundReceivingBehaviour();

		MinSG::SoundReceivingBehaviour * operator*()const	{	return static_cast<MinSG::SoundReceivingBehaviour*>(ref().get());	}
		MinSG::SoundReceivingBehaviour * get()const			{	return static_cast<MinSG::SoundReceivingBehaviour*>(ref().get());	}

};
}
ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_SoundReceivingBehaviour,	MinSG::SoundReceivingBehaviour*,		**eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::SoundReceivingBehaviour*, 	E_MinSG::E_SoundReceivingBehaviour,		dynamic_cast<E_MinSG::E_SoundReceivingBehaviour*>(E_MinSG::E_Behavior::create(obj)))

#endif // __E_SoundReceivingBehaviour_H
#endif // MINSG_EXT_SOUND
