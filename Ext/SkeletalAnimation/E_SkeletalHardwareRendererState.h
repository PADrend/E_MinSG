/*
	This file is part of the E_MinSG library extension SkeletalAnimation.
	Copyright (C) 2011-2012 Lukas Kopecki
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_SKELETAL_ANIMATION

#ifndef SKELETALHARDWARERENDERERSTATE_H_
#define SKELETALHARDWARERENDERERSTATE_H_

#include "../../Core/States/E_ShaderState.h"
#include <MinSG/Ext/SkeletalAnimation/Renderer/SkeletalHardwareRendererState.h>


namespace E_MinSG {

	/**
	 **   [E_SkeletelMeshRenderer] ---|> [E_ShaderState]  ---|> [E_State]
	 **/

	class E_SkeletalHardwareRendererState : public E_ShaderState{
		ES_PROVIDES_TYPE_NAME(SkeletalHardwareRendererState)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// ---
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_SkeletalHardwareRendererState();
		        
        const MinSG::SkeletalHardwareRendererState * operator*()const	{	return static_cast<const MinSG::SkeletalHardwareRendererState*>(ref().get());	}
		MinSG::SkeletalHardwareRendererState * operator*()				{	return static_cast<MinSG::SkeletalHardwareRendererState*>(ref().get());	}

	protected:
		E_SkeletalHardwareRendererState(MinSG::SkeletalHardwareRendererState * gNode, EScript::Type * type=nullptr);
	};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_SkeletalHardwareRendererState,		MinSG::SkeletalHardwareRendererState*,		**eObj)

#endif
#endif
