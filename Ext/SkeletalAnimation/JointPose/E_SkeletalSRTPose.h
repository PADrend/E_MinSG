/*
 This file is part of the E_MinSG library extension SkeletalAnimation.
 Copyright (C) 2011-2012 Lukas Kopecki
 
 This library is subject to the terms of the Mozilla Public License, v. 2.0.
 You should have received a copy of the MPL along with this library; see the
 file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifdef MINSG_EXT_SKELETAL_ANIMATION

#ifndef __PADrend__E_SkeletalSRTPose__
#define __PADrend__E_SkeletalSRTPose__

#include <EScript/Objects/Object.h>
#include <MinSG/Ext/SkeletalAnimation/JointPose/SRTPose.h>

#include "E_SkeletalAbstractPose.h"

namespace MinSG {
    class SRTPose;
}

namespace E_MinSG {
    class E_SkeletalSRTPose : public E_SkeletalAbstractPose
    {
        ES_PROVIDES_TYPE_NAME(SkeletalSRTPose)
 	public:        
		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);
        
		virtual ~E_SkeletalSRTPose() {}
        
        E_SkeletalSRTPose(MinSG::SRTPose * _pose,EScript::Type* type=nullptr) : E_SkeletalAbstractPose(_pose, type?type:getTypeObject()) {}
        
        const MinSG::SRTPose * operator*()const	{	return static_cast<const MinSG::SRTPose*>(get());	}
		MinSG::SRTPose * operator*()				{	return static_cast<MinSG::SRTPose*>(get());	}
	};
    
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_SkeletalSRTPose,		MinSG::SRTPose*,		**eObj)

#endif /* defined(__PADrend__E_SkeletalSRTPose__) */
#endif
