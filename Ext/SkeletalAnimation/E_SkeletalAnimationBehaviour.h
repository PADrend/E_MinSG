/*
	This file is part of the E_MinSG library extension SkeletalAnimation.
	Copyright (C) 2011-2012 Lukas Kopecki
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_SKELETAL_ANIMATION

#ifndef E_SKELETAL_ANIMATION_H_
#define E_SKELETAL_ANIMATION_H_

#include "../../Core/Behaviours/E_AbstractBehaviour.h"
#include <MinSG/Ext/SkeletalAnimation/AnimationBehaviour.h>

namespace MinSG{
	class AnimationBehaviour;
}

namespace E_MinSG {

	/**
	 **   [E_Animation] ---|> [E_AbstractNodeBehaviour]
	 **/

	class E_SkeletalAnimationBehaviour : public E_AbstractNodeBehaviour{
		ES_PROVIDES_TYPE_NAME(SkeletalAnimationBehaviour)

	public:
		// ---
		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);

		E_SkeletalAnimationBehaviour(MinSG::AnimationBehaviour * behaviour, EScript::Type *type = nullptr);
		virtual ~E_SkeletalAnimationBehaviour();

        const MinSG::AnimationBehaviour * operator*()const	{	return static_cast<const MinSG::AnimationBehaviour*>(ref().get());	}
		MinSG::AnimationBehaviour * operator*()				{	return static_cast<MinSG::AnimationBehaviour*>(ref().get());	}

	private:
		Util::Reference<MinSG::AnimationBehaviour> animation;
	};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_SkeletalAnimationBehaviour,		MinSG::AnimationBehaviour*,		**eObj)

#endif
#endif
