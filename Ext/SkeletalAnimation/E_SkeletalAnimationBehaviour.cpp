/*
	This file is part of the E_MinSG library extension SkeletalAnimation.
	Copyright (C) 2011-2012 Lukas Kopecki
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_SKELETAL_ANIMATION

#include "E_SkeletalAnimationBehaviour.h"
#include "E_SkeletalNode.h"
#include "JointPose/E_SkeletalAbstractPose.h"
#include "JointPose/E_SkeletalMatrixPose.h"
#include "JointPose/E_SkeletalSRTPose.h"

#include <MinSG/Ext/SkeletalAnimation/AnimationBehaviour.h>
#include <MinSG/Ext/SkeletalAnimation/JointPose/AbstractPose.h>
#include <MinSG/Ext/SkeletalAnimation/JointPose/MatrixPose.h>
#include <MinSG/Ext/SkeletalAnimation/JointPose/SRTPose.h>

#include "../../Core/Behaviours/E_AbstractBehaviour.h"
#include <EScript/EScript.h>
#include "../../ELibMinSG.h"

#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

EScript::Type * E_SkeletalAnimationBehaviour::getTypeObject() {
    // E_AbstractNodeBehaviour ---|> E_AbstractBehaviour
    static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractNodeBehaviour::getTypeObject());
    return typeObject.get();
}

//! [static] initMembers	
void E_SkeletalAnimationBehaviour::init(EScript::Namespace & lib) {
	// E_SkeletalAnimationBehaviour ---|> E_AbstractNodeBehaviour
	Type * typeObject=getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::AnimationBehaviour,E_SkeletalAnimationBehaviour>();

	//! [ESMF] new MinSG.VisibilityEvaluator( string animationName, SkeletonRoot node=null )	
	ES_CONSTRUCTOR(typeObject,1,2,{
		if(parameter.size() == 2){
			E_SkeletalNode *saNode = parameter[1].toType<E_SkeletalNode>();
			if(saNode != nullptr)
				return new E_SkeletalAnimationBehaviour(new AnimationBehaviour(**saNode, parameter[0].to<std::string>(rt)));
		}
		return new E_SkeletalAnimationBehaviour(new AnimationBehaviour(nullptr, parameter[0].to<std::string>(rt)));
	})
	
	//! [ESMF] int MinSG.Animation.getPoseCount()
	ES_MFUN(typeObject,AnimationBehaviour,"getPoseCount",0,0,thisObj->getPoseCount())

	ES_MFUN(typeObject,AnimationBehaviour,"getName",0,0,thisObj->getName())

	ES_MFUN(typeObject,AnimationBehaviour,"getAnimationStatus",0,0,thisObj->getStatus())
    
    ES_MFUN(typeObject,AnimationBehaviour,"destroy",0,0,(thisObj->_destroy(), thisEObj))
    
    ES_MFUN(typeObject,AnimationBehaviour,"playAnimation",0,0,(thisObj->play(), thisEObj))
    
    ES_MFUN(typeObject,AnimationBehaviour,"stopAnimation",0,0,(thisObj->stop(), thisEObj))
    
    ES_MFUN(typeObject,AnimationBehaviour,"getMinTime",0,0,thisObj->getMinTime())

    ES_MFUN(typeObject,AnimationBehaviour,"getMaxTime",0,0,thisObj->getMaxTime())

    ES_MFUN(typeObject,AnimationBehaviour,"setAnimationSpeed",1,1,(thisObj->setAnimationSpeed(parameter[0].to<float>(rt)), thisEObj))
    
    ES_MFUN(typeObject,AnimationBehaviour,"getAnimationSpeed",0,0,thisObj->getAnimationSpeed())
    
    ES_MFUN(typeObject,AnimationBehaviour,"getAnimationStatus",0,0,thisObj->getStatus())
    
    ES_MFUN(typeObject,AnimationBehaviour,"startLoop",0,0,(thisObj->startLoop(), thisEObj))
    
    ES_MFUN(typeObject,AnimationBehaviour,"stopLoop",0,0,(thisObj->startLoop(), thisEObj))
    
    ES_MFUN(typeObject,AnimationBehaviour,"gotoTime",1,1,(thisObj->gotoTime(parameter[0].toFloat()), thisEObj))
    
    ES_MFUN(typeObject,AnimationBehaviour,"getDuration",0,0,thisObj->getDuration())
    
    ES_MFUN(typeObject,AnimationBehaviour,"getStartTime",0,0,thisObj->getStartTime())
 
    ES_MFUNCTION(typeObject,AnimationBehaviour,"getPoses",0,0,{
        std::vector<AbstractPose *> &poses = thisObj->getPoses();
        
        Array *a = Array::create();
        for(const auto pose : poses) {
            if(dynamic_cast<MatrixPose *>(pose) != nullptr)
                a->pushBack(new E_SkeletalMatrixPose(dynamic_cast<MatrixPose *>(pose)));
            else if(dynamic_cast<SRTPose *>(pose) != nullptr)
                a->pushBack(new E_SkeletalSRTPose(dynamic_cast<SRTPose *>(pose)));
        }
        return a;
	})
    
    ES_MFUNCTION(typeObject,AnimationBehaviour,"addPose",1,1,{
        if(parameter[0].toType<E_SkeletalMatrixPose>() != nullptr)
            thisObj->addPose(parameter[0].toType<E_SkeletalMatrixPose>()->get());
        else if(parameter[0].toType<E_SkeletalSRTPose>() != nullptr)
            thisObj->addPose(parameter[0].toType<E_SkeletalSRTPose>()->get());
        return nullptr;
	})
    
    ES_MFUNCTION(typeObject,AnimationBehaviour,"addPoseArray",1,1,{
        Array *a = parameter[0].to<EScript::Array*>(rt);
        if(a == nullptr)
            return nullptr;
        std::vector<AbstractPose*> poseArray;
        for(uint32_t i=0; i<a->count(); ++i) {
            E_SkeletalAbstractPose *element = dynamic_cast<E_SkeletalAbstractPose*> (a->get(i));
            if(element != nullptr)
                poseArray.emplace_back(element->get());
        }
        thisObj->addPoseArray(poseArray);
        return nullptr;
	})
}

//! [ctor]
E_SkeletalAnimationBehaviour::E_SkeletalAnimationBehaviour(AnimationBehaviour * c,Type * type):E_AbstractNodeBehaviour(c, type?type:getTypeObject()), animation(c) {
}

E_SkeletalAnimationBehaviour::~E_SkeletalAnimationBehaviour() {
}

}

#endif
