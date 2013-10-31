/*
	This file is part of the E_MinSG library extension SkeletalAnimation.
	Copyright (C) 2011-2012 Lukas Kopecki
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_SKELETAL_ANIMATION

#include "E_JointNode.h"

#include "../../../ELibMinSG.h"

#include <E_Util/E_Utils.h>

#include <E_Geometry/E_Matrix4x4.h>

#include <MinSG/Ext/SkeletalAnimation/Util/SkeletalAnimationUtils.h>

#include <iostream>

#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;
using namespace E_Geometry;

namespace E_MinSG {

EScript::Type * E_JointNode::getTypeObject() {
	// E_ListNode ---|> E_GroupNode ---|> E_Node ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_ListNode::getTypeObject());
	return typeObject.get();
}


//! [static] initMembers	
void E_JointNode::init(EScript::Namespace & lib) {
	// MinSG.JointNode ---|> MinSGG.Node ---|> Object
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::JointNode,E_JointNode>();

	//! [ESMF] new MinSG.JointNode( id, name )	
	ES_CTOR(typeObject,2,2,new JointNode(parameter[0].to<uint32_t>(rt), parameter[1].to<std::string>(rt)))
    
    ES_MFUN(typeObject, JointNode, "getInverseBindMatrix", 0, 0, (thisObj->getInverseBindMatrix(), thisEObj))

    ES_MFUN(typeObject, JointNode, "getName", 0, 0, thisObj->getName())

    ES_MFUN(typeObject, JointNode, "getId", 0, 0, thisObj->getId())
    
    ES_MFUN(typeObject, JointNode, "setBindMatrix", 0, 0, (thisObj->setBindMatrix(parameter[0].to<const Geometry::Matrix4x4&>(rt)), thisEObj))

}
// ------------------------------------------------------------

//! (ctor)	
E_JointNode::E_JointNode(JointNode * gNode,EScript::Type * type):
E_ListNode( gNode,type?type:getTypeObject()){
}

//! (dtor)	
E_JointNode::~E_JointNode(){
}

}

#endif
