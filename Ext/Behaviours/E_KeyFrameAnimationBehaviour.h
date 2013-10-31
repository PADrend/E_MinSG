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
#ifndef __E_KeyFrameAnimationBehaviour_H
#define __E_KeyFrameAnimationBehaviour_H

#include "../../Core/Behaviours/E_AbstractBehaviour.h"
#include <MinSG/Ext/Behaviours/KeyFrameAnimationBehaviour.h>

namespace E_MinSG{

/***
 **   E_KeyFrameAnimationBehaviour ---|> E_AbstractNodeBehaviour ---|> EScript::Object
 **                                      |
 **                                      ------> MinSG::AbstractBehaviour
 **/
class E_KeyFrameAnimationBehaviour : public E_AbstractNodeBehaviour{
	ES_PROVIDES_TYPE_NAME(KeyFrameAnimationBehaviour)

	public:
		// ---
		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		E_KeyFrameAnimationBehaviour(MinSG::KeyFrameAnimationBehaviour * _behaviour);
		virtual ~E_KeyFrameAnimationBehaviour();

		MinSG::KeyFrameAnimationBehaviour * operator*()const	{	return static_cast<MinSG::KeyFrameAnimationBehaviour*>(ref().get());	}
		MinSG::KeyFrameAnimationBehaviour * get()const			{	return static_cast<MinSG::KeyFrameAnimationBehaviour*>(ref().get());	}

};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_KeyFrameAnimationBehaviour,	MinSG::KeyFrameAnimationBehaviour*,		**eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::KeyFrameAnimationBehaviour*, 	E_MinSG::E_KeyFrameAnimationBehaviour,	dynamic_cast<E_MinSG::E_KeyFrameAnimationBehaviour*>(E_MinSG::E_Behavior::create(obj)))

#endif // __E_KeyFrameAnimationBehaviour_H
