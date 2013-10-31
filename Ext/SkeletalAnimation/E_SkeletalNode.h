/*
	This file is part of the E_MinSG library extension SkeletalAnimation.
	Copyright (C) 2011-2012 Lukas Kopecki
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_SKELETAL_ANIMATION

#ifndef E_SKELETALNODE_H_
#define E_SKELETALNODE_H_

#include "../../Core/Nodes/E_ListNode.h"
#include "../../Core/Behaviours/E_AbstractBehaviour.h"
#include <MinSG/Ext/SkeletalAnimation/SkeletalNode.h>


namespace MinSG{
	class SkeletalNode;
}

namespace E_MinSG {

	/**
	 **   [E_Skeleton] ---|> [E_ListNode]
	 **/

	class E_SkeletalNode : public E_ListNode{
		ES_PROVIDES_TYPE_NAME(SkeletalNode)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// ---
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_SkeletalNode();

		const MinSG::SkeletalNode * operator*()const	{	return static_cast<const MinSG::SkeletalNode*>(ref().get());	}
		MinSG::SkeletalNode * operator*()				{	return static_cast<MinSG::SkeletalNode*>(ref().get());	}

	protected:
		E_SkeletalNode(MinSG::SkeletalNode * gNode, EScript::Type * type=nullptr);
	};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_SkeletalNode,		MinSG::SkeletalNode*,		**eObj)

#endif
#endif
