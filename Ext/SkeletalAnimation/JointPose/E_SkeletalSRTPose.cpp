/*
 This file is part of the E_MinSG library extension SkeletalAnimation.
 Copyright (C) 2011-2012 Lukas Kopecki
 
 This library is subject to the terms of the Mozilla Public License, v. 2.0.
 You should have received a copy of the MPL along with this library; see the
 file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifdef MINSG_EXT_SKELETAL_ANIMATION
#include "E_SkeletalSRTPose.h"

#include "../../../Core/Nodes/E_Node.h"
#include "../Joints/E_JointNode.h"

#include <EScript/EScript.h>

#include <MinSG/Ext/SkeletalAnimation/JointPose/SRTPose.h>
#include <E_Geometry/E_Matrix4x4.h>
#include <E_Geometry/E_Vec4.h>
#include <MinSG/Ext/SkeletalAnimation/Joints/JointNode.h>
#include "E_SkeletalAbstractPose.h"

using namespace EScript;
using namespace MinSG;
using namespace Geometry;

namespace E_MinSG {

    EScript::Type * E_SkeletalSRTPose::getTypeObject() {
        // E_SkeletalSRTPose ---|> Object
        static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_SkeletalAbstractPose::getTypeObject());
        return typeObject.get();
    }

    void E_SkeletalSRTPose::init(EScript::Namespace & lib)
    {
        EScript::Type * typeObject = getTypeObject();
        declareConstant(&lib,getClassName(),typeObject);
        
        //! [ESMF] new MinSG.SkeletalSRTPose(E_JointNode node)
        ES_CONSTRUCTOR(typeObject,1,1, {
            return new E_SkeletalSRTPose(new SRTPose(**parameter[0].to<E_JointNode*>(rt)));
        })

    }

}

#endif
