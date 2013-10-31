/*
 This file is part of the E_MinSG library extension SkeletalAnimation.
 Copyright (C) 2011-2012 Lukas Kopecki
 
 This library is subject to the terms of the Mozilla Public License, v. 2.0.
 You should have received a copy of the MPL along with this library; see the
 file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifdef MINSG_EXT_SKELETAL_ANIMATION

#ifndef PADrend_E_RigidJoint_h
#define PADrend_E_RigidJoint_h

#include "E_JointNode.h"
#include <MinSG/Ext/SkeletalAnimation/Joints/RigidJoint.h>

namespace MinSG{
	class RigidJoint;
}

namespace E_MinSG {
    
/**
 **   [E_JointNode] ---|> [E_ListNode]
 **/

class E_RigidJoint : public E_JointNode{
	ES_PROVIDES_TYPE_NAME(RigidJoint)
public:
	template<class, class, class> friend class Util::PolymorphicWrapperCreator;
	// ---
	static EScript::Type * getTypeObject();
	static void init(EScript::Namespace & lib);
	
	virtual ~E_RigidJoint();
	
	const MinSG::RigidJoint * operator*()const	{	return static_cast<const MinSG::RigidJoint*>(ref().get());	}
	MinSG::RigidJoint * operator*()				{	return static_cast<MinSG::RigidJoint*>(ref().get());	}
	
protected:
	E_RigidJoint(MinSG::RigidJoint * gNode, EScript::Type * type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_RigidJoint,		MinSG::RigidJoint*,		**eObj)

#endif
#endif
