/*
	This file is part of the E_MinSG library extension SkeletalAnimation.
	Copyright (C) 2011-2012 Lukas Kopecki
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_SKELETAL_ANIMATION

#include "E_ArmatureNode.h"
#include <EScript/EScript.h>

using namespace MinSG;

namespace E_MinSG {

EScript::Type * E_ArmatureNode::getTypeObject() {
	// E_ListNode ---|> E_GroupNode ---|> E_Node ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_ListNode::getTypeObject());
	return typeObject.get();
}

//! [static] initMembers	
void E_ArmatureNode::init(EScript::Namespace & lib) {
	// MinSG.SkeletalNode ---|> MinSG.GroupNode ---|> MinSG.Node ---|> Object
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::ArmatureNode,E_ArmatureNode>();

	//! [ESMF] new MinSG.ArmatureNode( )	
	ES_CTOR(typeObject,0,0,new ArmatureNode)
}
// ------------------------------------------------------------

//! (ctor)  
E_ArmatureNode::E_ArmatureNode(ArmatureNode * gNode,EScript::Type * type):
E_ListNode( gNode,type?type:getTypeObject()){
}

//! (dtor)	
E_ArmatureNode::~E_ArmatureNode(){
}

}

#endif
