/*
 This file is part of the E_MinSG library extension SkeletalAnimation.
 Copyright (C) 2011-2012 Lukas Kopecki
 
 This library is subject to the terms of the Mozilla Public License, v. 2.0.
 You should have received a copy of the MPL along with this library; see the
 file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifdef MINSG_EXT_SKELETAL_ANIMATION
#include "E_SkeletalMatrixPose.h"

#include "../../../Core/Nodes/E_Node.h"
#include "../Joints/E_JointNode.h"

#include <MinSG/Ext/SkeletalAnimation/JointPose/MatrixPose.h>
#include <E_Geometry/E_Matrix4x4.h>
#include <MinSG/Ext/SkeletalAnimation/Joints/JointNode.h>

#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;
using namespace Geometry;

namespace E_MinSG {

EScript::Type * E_SkeletalMatrixPose::getTypeObject() {
	// E_SkeletalMatrixPose ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_SkeletalAbstractPose::getTypeObject());
	return typeObject.get();
}

void E_SkeletalMatrixPose::init(EScript::Namespace & lib)
{
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
    
    //! [ESMF] new MinSG.SkeletalMatrixPose(E_JointNode)
	ES_CONSTRUCTOR(typeObject,1,1, {
        return new E_SkeletalMatrixPose(new MatrixPose(**(parameter[0].toType<E_JointNode>())));
    })
    
    ES_MFUN(typeObject, MatrixPose, "updateValueAtIndex", 2, 2,(thisObj->updateValue(parameter[0].to<const Geometry::Matrix4x4&>(rt), parameter[0].toInt()), thisEObj))
}

//! (ctor)
E_SkeletalMatrixPose::E_SkeletalMatrixPose(MatrixPose * _pose,EScript::Type * type):
E_SkeletalAbstractPose(_pose, type?type:getTypeObject()) { }

//! (dtor)
E_SkeletalMatrixPose::~E_SkeletalMatrixPose() {
}

}

#endif
