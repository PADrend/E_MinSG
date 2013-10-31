/*
 This file is part of the E_MinSG library extension SkeletalAnimation.
 Copyright (C) 2011-2012 Lukas Kopecki
 
 This library is subject to the terms of the Mozilla Public License, v. 2.0.
 You should have received a copy of the MPL along with this library; see the
 file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifdef MINSG_EXT_SKELETAL_ANIMATION

#ifndef PADrend_E_SkeletalAbstractPose_h
#define PADrend_E_SkeletalAbstractPose_h

#include <MinSG/Ext/SkeletalAnimation/JointPose/AbstractPose.h>
#include <EScript/Objects/Object.h>

namespace MinSG {
    class AbstractPose;
}

namespace E_MinSG {
    class E_SkeletalAbstractPose : public EScript::Object
    {
        ES_PROVIDES_TYPE_NAME(SkeletalAbstractPose)
 	public:
		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);
        
		E_SkeletalAbstractPose(MinSG::AbstractPose * _pose,EScript::Type* type=nullptr);
		virtual ~E_SkeletalAbstractPose();
        
        MinSG::AbstractPose * get()const		{	return pose;	}
        
        const MinSG::AbstractPose * operator*()const	{	return static_cast<const MinSG::AbstractPose*>(get());	}
		MinSG::AbstractPose * operator*()				{	return static_cast<MinSG::AbstractPose*>(get());	}
        
	protected:
        MinSG::AbstractPose * pose;
	};
    
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_SkeletalAbstractPose,		MinSG::AbstractPose*,		**eObj)

#endif
#endif
