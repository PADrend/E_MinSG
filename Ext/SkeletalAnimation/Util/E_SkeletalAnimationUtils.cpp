/*
 This file is part of the E_MinSG library extension SkeletalAnimation.
 Copyright (C) 2011-2012 Lukas Kopecki
 
 This library is subject to the terms of the Mozilla Public License, v. 2.0.
 You should have received a copy of the MPL along with this library; see the
 file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifdef MINSG_EXT_SKELETAL_ANIMATION

#include "E_SkeletalAnimationUtils.h"
#include "../Joints/E_ArmatureNode.h"
#include "../E_SkeletalNode.h"
#include "../E_SkeletalAnimationBehaviour.h"

#include "../../../ELibMinSG.h"
#include "../../../Core/Nodes/E_GeometryNode.h"


#include <EScript/EScript.h>

#include <MinSG/Ext/SkeletalAnimation/Util/SkeletalAnimationUtils.h>
#include <MinSG/Ext/SkeletalAnimation/Joints/ArmatureNode.h>
#include <MinSG/Ext/SkeletalAnimation/SkeletalNode.h>

#include <MinSG/Core/Nodes/GeometryNode.h>

#include <Rendering/Mesh/Mesh.h>
#include <Rendering/Mesh/MeshVertexData.h>


namespace E_MinSG {
    
    using namespace EScript;
    using namespace MinSG;
    
    void initSkeletalAnimationUtils(EScript::Namespace * lib)
    {
        //! [ESF] SkeletalNode MinSG.generateSkeletalNode(MinSG.GeometryNode, MinSG.ArmatureNode, weightRadius, precision)
        ES_FUNCTION(lib, "generateSkeletalNode", 2, 4, {
            E_GeometryNode * geoNode = EScript::assertType<E_GeometryNode>(rt, parameter[0]);
            E_ArmatureNode * armNode = EScript::assertType<E_ArmatureNode>(rt, parameter[1]);
            
            return EScript::create(SkeletalAnimationUtils::generateSkeletalNode(**geoNode, **armNode, parameter[2].toFloat(1.0), parameter[3].toInt(0)));
        })
        
        ES_FUNCTION(lib, "normalizeAnimationDuration", 1, 1, {
            E_SkeletalAnimationBehaviour *aniBehaviour = parameter[0].toType<E_SkeletalAnimationBehaviour>();
            if(**aniBehaviour != nullptr)
                SkeletalAnimationUtils::normalizeAnimationDuration(***aniBehaviour);
            
            return nullptr;
        })
        
        ES_FUNCTION(lib, "normalizeSkeletalWeights", 1, 2, {
            E_GeometryNode *geoNode = EScript::assertType<E_GeometryNode>(rt, parameter[0]);
            SkeletalAnimationUtils::normalizeWeights(&(**geoNode)->getMesh()->openVertexData(), parameter[1].toFloat(0.01));
            
            return nullptr;
        })
        
        ES_FUNCTION(lib, "convertJointsToRigids", 1, 2, {
            E_ArmatureNode *armature = EScript::assertType<E_ArmatureNode>(rt, parameter[0]);
            SkeletalAnimationUtils::convertJointNodesToRigidNodes(**armature, parameter[1].toBool(true));
            
            return nullptr;
        })
        
        ES_FUNCTION(lib, "removeGeometryFromSkeleton", 1, 1, {
            E_SkeletalNode *skeleton = EScript::assertType<E_SkeletalNode>(rt, parameter[0]);
            SkeletalAnimationUtils::removeGeometryFromSkeleton(**skeleton);
            
            return nullptr;
        })
    }   
}

#endif

