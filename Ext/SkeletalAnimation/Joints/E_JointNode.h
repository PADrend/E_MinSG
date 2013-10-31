/*
	This file is part of the E_MinSG library extension SkeletalAnimation.
	Copyright (C) 2011-2012 Lukas Kopecki
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_SKELETAL_ANIMATION

#ifndef PADrend_E_JointNode_h
#define PADrend_E_JointNode_h

#include "../../../Core/Nodes/E_ListNode.h"
#include <MinSG/Ext/SkeletalAnimation/Joints/JointNode.h>

namespace MinSG{
	class JointNode;
}

namespace E_MinSG {

/**
 **   [E_JointNode] ---|> [E_ListNode]
 **/

class E_JointNode : public E_ListNode{
	ES_PROVIDES_TYPE_NAME(JointNode)
public:
	template<class, class, class> friend class Util::PolymorphicWrapperCreator;
	// ---
	static EScript::Type * getTypeObject();
	static void init(EScript::Namespace & lib);

	virtual ~E_JointNode();

	const MinSG::JointNode * operator*()const	{	return static_cast<const MinSG::JointNode*>(ref().get());	}
	MinSG::JointNode * operator*()				{	return static_cast<MinSG::JointNode*>(ref().get());	}

protected:
	E_JointNode(MinSG::JointNode * gNode, EScript::Type * type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_JointNode,		MinSG::JointNode*,		**eObj)

#endif
#endif
