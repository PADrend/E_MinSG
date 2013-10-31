/*
 This file is part of the E_MinSG library extension SkeletalAnimation.
 Copyright (C) 2011-2012 Lukas Kopecki
 
 This library is subject to the terms of the Mozilla Public License, v. 2.0.
 You should have received a copy of the MPL along with this library; see the
 file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifdef MINSG_EXT_SKELETAL_ANIMATION

#ifndef PADrend_E_SkeletalPose_h
#define PADrend_E_SkeletalPose_h

#include "E_SkeletalAbstractPose.h"
#include <MinSG/Ext/SkeletalAnimation/JointPose/MatrixPose.h>

#include <EScript/Objects/Object.h>

namespace MinSG {
    class MatrixPose;
}

namespace E_MinSG {
    class E_SkeletalMatrixPose : public E_SkeletalAbstractPose
    {
        ES_PROVIDES_TYPE_NAME(SkeletalMatrixPose)
 	public:
		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);
        
		E_SkeletalMatrixPose(MinSG::MatrixPose * _pose,EScript::Type* type=nullptr);
		virtual ~E_SkeletalMatrixPose();
        
        const MinSG::MatrixPose * operator*()const	{	return static_cast<const MinSG::MatrixPose*>(get());	}
		MinSG::MatrixPose * operator*()				{	return static_cast<MinSG::MatrixPose*>(get());	}
	};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_SkeletalMatrixPose,		MinSG::MatrixPose*,		**eObj)

#endif
#endif
