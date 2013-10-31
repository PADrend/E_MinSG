/*
 This file is part of the E_MinSG library extension SkeletalAnimation.
 Copyright (C) 2011-2012 Lukas Kopecki
 
 This library is subject to the terms of the Mozilla Public License, v. 2.0.
 You should have received a copy of the MPL along with this library; see the
 file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifdef MINSG_EXT_SKELETAL_ANIMATION

#include "E_RigidJoint.h"

#include <E_Geometry/E_Matrix4x4.h>
#include <Geometry/Matrix4x4.h>

#include <EScript/EScript.h>

using namespace MinSG;
using namespace E_Geometry;
using namespace Geometry;

namespace E_MinSG {

    EScript::Type * E_RigidJoint::getTypeObject() {
        // E_ListNode ---|> E_GroupNode ---|> E_Node ---|> Object
        static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_ListNode::getTypeObject());
        return typeObject.get();
    }

    //! [static] initMembers	
    void E_RigidJoint::init(EScript::Namespace & lib) {
        // MinSG.JointNode ---|> MinSG.ListNode ---|> MinSG.GroupNode ---|> MinSG.Node ---|> Object
        EScript::Type * typeObject = getTypeObject();
        declareConstant(&lib,getClassName(),typeObject);
        addFactory<MinSG::RigidJoint,E_RigidJoint>();
        
        //! [ESMF] new MinSG.RigidJoint(Number,String)	
        ES_CTOR(typeObject,2,2,new RigidJoint(parameter[0].to<uint32_t>(rt), parameter[1].to<std::string>(rt)))
        
        ES_MFUN(typeObject, RigidJoint, "setOffsetMatrix", 0, 0, (thisObj->setOffsetMatrix(parameter[0].to<const Geometry::Matrix4x4&>(rt)), thisEObj))
    }
    // ------------------------------------------------------------

    //! (ctor)  
    E_RigidJoint::E_RigidJoint(RigidJoint * gNode,EScript::Type * type):
    E_JointNode( gNode,type?type:getTypeObject()){
    }

    //! (dtor)	
    E_RigidJoint::~E_RigidJoint(){
    }

}

#endif
