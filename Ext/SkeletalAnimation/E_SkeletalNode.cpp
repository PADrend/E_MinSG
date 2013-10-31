/*
	This file is part of the E_MinSG library extension SkeletalAnimation.
	Copyright (C) 2011-2012 Lukas Kopecki
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_SKELETAL_ANIMATION

#include "E_SkeletalNode.h"

#include <MinSG/Ext/SkeletalAnimation/SkeletalNode.h>
#include <MinSG/Ext/SkeletalAnimation/AnimationBehaviour.h>
#include <MinSG/Ext/SkeletalAnimation/Util/SkeletalAnimationUtils.h>
#include <MinSG/Ext/SkeletalAnimation/Joints/RigidJoint.h>

#include "../../ELibMinSG.h"

#include "E_SkeletalAnimationBehaviour.h"
#include "../../Core/Behaviours/E_BehaviourManager.h"

#include <E_Util/E_Utils.h>

#include <unordered_map>

#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;
using namespace Geometry;
using namespace std;

namespace E_MinSG {

EScript::Type * E_SkeletalNode::getTypeObject() {
    // E_SkeletalNode ---|> E_ListNode ---|> E_GroupNode ---|> E_Node ---|> Object
    static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_ListNode::getTypeObject());
    return typeObject.get();
}

//! [static] initMembers	
void E_SkeletalNode::init(EScript::Namespace & lib) {
	// MinSG.SkeletalNode ---|> MinSG.GroupNode ---|> MinSG.Node ---|> Object
    EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),getTypeObject());
	addFactory<MinSG::SkeletalNode,E_SkeletalNode>();

	// overload node functions to cast it straight forward to mesh nodes

	//! [ESMF] new MinSG.E_SkeletalNode( )	
	ES_CTOR(typeObject, 0, 0,new SkeletalNode)

    ES_MFUN(typeObject,SkeletalNode,"getAnimationCount",0,0,Number::create(thisObj->getAnimationCount()))
    
    ES_MFUNCTION(typeObject,SkeletalNode,"getAnimation",1,1,{
        AnimationBehaviour *ani = thisObj->getAnimation(parameter[0].to<std::string>(rt));
        if(ani == nullptr)
            return nullptr;
        else
            return E_Behavior::create(ani);
	})
    
    ES_MFUNCTION(typeObject,SkeletalNode,"getAnimations",0,0,{
        Array *a = Array::create();        
        for(const auto ani : thisObj->getAnimations())
            a->pushBack(E_Behavior::create(ani.second));
        
        return a;
	})
    
    ES_MFUN(typeObject, SkeletalNode, "splitAnimation",3,3,(thisObj->splitAnimation(parameter[0].to<std::string>(rt), parameter[1].to<std::string>(rt), parameter[2].to<uint32_t>(rt))))

    ES_MFUNCTION(typeObject,SkeletalNode,"separateAnimations",4,4,{
        BehaviourManager *manager = parameter[3].toType<E_BehaviourManager>()->get();
        if(manager == nullptr)
            return false;
        
        string source = parameter[0].to<std::string>(rt);
        Array *names = parameter[1].toType<Array>();
        Array *indices = parameter[2].toType<Array>();
        
        vector<string> vectorNames;
        for(uint32_t i=0; i<names->size(); ++i)
            vectorNames.push_back(names->get(i)->toString());
        
        vector<uint32_t> vectorIndices;
        for(uint32_t i=0; i<indices->size(); ++i)
            vectorIndices.push_back(indices->get(i)->toInt());
        
        return thisObj->separateAnimation(source, vectorNames, vectorIndices, manager);
	})
    
    ES_MFUN(typeObject,SkeletalNode,"printAnimationNames",0,0,(thisObj->printAnimationNames(), thisEObj))

    ES_MFUNCTION(typeObject,SkeletalNode,"getAnimationNames",0,0,{
        Array *a = Array::create();
        for(auto name : thisObj->getAnimationNames())
            a->pushBack(String::create(name));
        
        return a;
	})
    
    ES_MFUN(typeObject,SkeletalNode,"hasAnimation",1,1,thisObj->hasAnimation(parameter[0].to<std::string>(rt)))
    
    ES_MFUNCTION(typeObject,SkeletalNode,"clearAnimation",2,2,{
        BehaviourManager *manager = parameter[1].toType<E_BehaviourManager>()->get();
        if(manager != nullptr)
            return thisObj->clearAnimation(parameter[0].to<std::string>(rt), manager);
        
        return false;
	})
    
    ES_MFUN(typeObject,SkeletalNode,"clearAnimations",1,1,(thisObj->clearAnimations(parameter[0].toType<E_BehaviourManager>()->get()), thisEObj))
    
    ES_MFUNCTION(typeObject,SkeletalNode,"addAnimation",1,1,{
        AnimationBehaviour *ani = (**parameter[0].toType<E_SkeletalAnimationBehaviour>());
        if(ani != nullptr)
        {
            ani->setNode(thisObj);
            thisObj->addAnimation(ani, ani->getName());
        }
        
        return nullptr;
	})
    
    ES_MFUN(typeObject,SkeletalNode,"setStartAnimation",1,1,(thisObj->setStartAnimation(parameter[0].to<std::string>(rt)), thisEObj))
    
    ES_MFUNCTION(typeObject,SkeletalNode,"attachObject",2,2,{
        Node *node = (**parameter[0].toType<E_Node>());
        
        if(node != nullptr)
            thisObj->attachObject(node, parameter[1].to<std::string>(rt));
        
        return nullptr;
	})
    
    ES_MFUNCTION(typeObject,SkeletalNode,"detachObject",2,2,{
        Node *node = (**parameter[0].toType<E_Node>());
        
        if(node != nullptr)
            thisObj->detachObject(node, parameter[1].to<std::string>(rt));
        
        return nullptr;
	})
}
// ------------------------------------------------------------

//! (ctor)	

E_SkeletalNode::E_SkeletalNode(SkeletalNode * gNode,EScript::Type * type):
E_ListNode( gNode,type?type:getTypeObject()){
}

//! (dtor)	
E_SkeletalNode::~E_SkeletalNode(){
}

}

#endif
