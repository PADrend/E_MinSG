/*
 This file is part of the E_MinSG library extension SkeletalAnimation.
 Copyright (C) 2011-2012 Lukas Kopecki
 
 This library is subject to the terms of the Mozilla Public License, v. 2.0.
 You should have received a copy of the MPL along with this library; see the
 file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifdef MINSG_EXT_SKELETAL_ANIMATION
#include "E_SkeletalAbstractPose.h"
#include "../../../Core/Nodes/E_Node.h"

#include <MinSG/Ext/SkeletalAnimation/JointPose/AbstractPose.h>
#include <MinSG/Ext/SkeletalAnimation/Joints/JointNode.h>
#include <E_Geometry/E_Matrix4x4.h>

#include <EScript/EScript.h>

using namespace MinSG;
using namespace EScript;
using namespace Geometry;

namespace E_MinSG {

EScript::Type * E_SkeletalAbstractPose::getTypeObject() {
	// E_SkeletalAbstractPose ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

void E_SkeletalAbstractPose::init(EScript::Namespace & lib)
{
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
    
    declareConstant(typeObject,"LINEAR", Number::create(AbstractPose::LINEAR));
	declareConstant(typeObject,"CONSTANT", Number::create(AbstractPose::CONSTANT));
    declareConstant(typeObject,"BEZIER", Number::create(AbstractPose::BEZIER));
    
    //! [ESMF] new AbstractPose()
    ES_CONSTRUCTOR(typeObject, 0, 0, {
        EScript::throwRuntimeException("MinSG.AbstractPose is abstract");
        return nullptr;
    })

    ES_MFUN(typeObject,AbstractPose, "getNode", 0, 0,(dynamic_cast<JointNode*>(thisObj->getBindetJoint())))
    
    ES_MFUN(typeObject,AbstractPose,"getName", 0, 0,thisObj->getBindetJoint()->getName())
    
    ES_MFUN(typeObject,AbstractPose,"restart", 0, 0,(thisObj->play(), thisEObj))
    
    ES_MFUN(typeObject,AbstractPose,"update", 1, 1,(thisObj->update(parameter[0].to<float>(rt)), thisEObj))
    
    //! [ESMF] void SkeletalAbstractPose.addValue(Matrix4x4 value, float time, int interpolationType=LINEAR)
	ES_MFUNCTION(typeObject,AbstractPose,"addValue", 2, 4,{
        const Matrix4x4 mat = parameter[0].to<const Geometry::Matrix4x4&>(rt);
        int interpolationType = AbstractPose::LINEAR;
        if(parameter.size() > 2)
            interpolationType = parameter[2].toInt();
        
        if(parameter.size() < 4)
            thisObj->addValue(mat, parameter[1].to<float>(rt), interpolationType, static_cast<uint32_t>(thisObj->getTimeline().size()));
        else
            thisObj->addValue(mat, parameter[1].to<float>(rt), interpolationType, parameter[3].to<uint32_t>(rt));
        
        return nullptr;
	})
    
    ES_MFUNCTION(typeObject, AbstractPose, "getValues", 0, 0, {
        Array *a = Array::create();
        std::deque<Matrix4x4> values = thisObj->getKeyframes();
        
        for(const auto value : values)
            a->pushBack(new E_Geometry::E_Matrix4x4(value));
        
        return a;
    })
    
    ES_MFUNCTION(typeObject, AbstractPose, "getTimeline", 0, 0, {
        Array *a = Array::create();
        std::deque<double> &values = thisObj->getTimeline();
        
        for(const auto value : values)
            a->pushBack(Number::create(value));
        
        return a;
    })
    
    ES_MFUNCTION(typeObject, AbstractPose, "setTimeline", 1, 1, {
        Array *timeline = parameter[0].toType<Array>();
        std::deque<double> times;
        for(auto time : *timeline)
            times.emplace_back(time->toFloat());
        
        return thisObj->setTimeline(times);
    })
    
    ES_MFUNCTION(typeObject, AbstractPose, "removeValue", 1, 1, {
        if(parameter[0].toInt() < 0)
            return nullptr;
        
        thisObj->removeValue(parameter[0].to<uint32_t>(rt));
        
        return nullptr;
    })
    
    //! [ESMF] bool SkeletalAbstractPose.addValues(Array[Matrix4x4] value, Array[float] time, Array[int] interpolationType=LINEAR)
	ES_MFUNCTION(typeObject,AbstractPose,"setValues", 2, 3,{
        Array *valueArray = parameter[0].toType<Array>();
        Array *timesArray = parameter[1].toType<Array>();
        if(valueArray->size() != timesArray->size())
            return false;
        
        Array *interpolTypeArray;
        if(parameter.size() == 3)
            interpolTypeArray = parameter[2].toType<Array>();
        else
        {
            interpolTypeArray = Array::create();
            for(uint32_t i=0; i<valueArray->size(); ++i)
                interpolTypeArray->pushBack(Number::create(AbstractPose::LINEAR));
        }
        
        std::deque<Geometry::Matrix4x4> values;
        std::deque<double> times;
        std::deque<uint32_t> types;
        
        for(auto value : *valueArray)
            values.emplace_back(value.toType<E_Geometry::E_Matrix4x4>()->ref());
        for(auto time : *timesArray)
            times.emplace_back(time->toFloat());
        for(auto type : *interpolTypeArray)
            types.emplace_back(type->toInt());
        
        thisObj->setValues(values, times, types);
        
        return Bool::create(true);
	})
    
}

//! (ctor)
E_SkeletalAbstractPose::E_SkeletalAbstractPose(AbstractPose * _pose,EScript::Type * type):
Object(type?type:getTypeObject()) {
    if(_pose != nullptr)
        pose = _pose;
}

//! (dtor)
E_SkeletalAbstractPose::~E_SkeletalAbstractPose() {
}

}

#endif
