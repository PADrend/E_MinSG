/*
	This file is part of the E_MinSG library extension SkeletalAnimation.
	Copyright (C) 2011-2012 Lukas Kopecki
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_SKELETAL_ANIMATION

#ifndef PADrend_E_ArmatureNode_h
#define PADrend_E_ArmatureNode_h

#include "../../../Core/Nodes/E_ListNode.h"
#include <MinSG/Ext/SkeletalAnimation/Joints/ArmatureNode.h>

namespace MinSG{
	class ArmatureNode;
}

namespace E_MinSG {

	/**
	 **   [E_Skeleton] ---|> [E_ListNode]
	 **/

	class E_ArmatureNode : public E_ListNode{
		ES_PROVIDES_TYPE_NAME(ArmatureNode)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// ---
		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_ArmatureNode();

		const MinSG::ArmatureNode * operator*()const	{	return static_cast<const MinSG::ArmatureNode*>(ref().get());	}
		MinSG::ArmatureNode * operator*()				{	return static_cast<MinSG::ArmatureNode*>(ref().get());	}

	protected:
		E_ArmatureNode(MinSG::ArmatureNode * gNode, EScript::Type * type=nullptr);
	};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ArmatureNode,		MinSG::ArmatureNode*,		**eObj)

#endif
#endif
