/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_CameraNodeOrtho.h"

#include "../E_FrameContext.h"
#include "../../ELibMinSG.h"

#include <EScript/EScript.h>
#include <E_Geometry/E_Vec3.h>
#include <E_Geometry/E_Rect.h>

#include <iostream>
#include <sstream>

using namespace MinSG;

namespace E_MinSG {

//! (static)
EScript::Type * E_CameraNodeOrtho::getTypeObject() {
	// E_CameraNodeOrtho ---|> E_AbstractCameraNode ---|> E_Node ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractCameraNode::getTypeObject());
	return typeObject.get();
}

// -----

//! (static)
void E_CameraNodeOrtho::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::CameraNodeOrtho,E_CameraNodeOrtho>();

	//! [ESMF] new MinSG.CameraNodeOrtho([near=1,[far=10000]])
	ES_CONSTRUCTOR(typeObject,0,2,{
		CameraNodeOrtho * c=new CameraNodeOrtho;
		c->setNearFar(parameter[0].toDouble(1.0),parameter[1].toDouble(10000.0) );
		return EScript::create(c);
	})

	//! [ESMF] Number MinSG.CameraNodeOrtho.getLeftClippingPlane()
	ES_MFUN(typeObject,const CameraNodeOrtho, "getLeftClippingPlane", 0, 0,
			thisObj->getLeftClippingPlane())

	//! [ESMF] Number MinSG.CameraNodeOrtho.getRightClippingPlane()
	ES_MFUN(typeObject,const CameraNodeOrtho, "getRightClippingPlane", 0, 0,
			thisObj->getRightClippingPlane())

	//! [ESMF] Number MinSG.CameraNodeOrtho.getBottomClippingPlane()
	ES_MFUN(typeObject,const CameraNodeOrtho, "getBottomClippingPlane", 0, 0,
			thisObj->getBottomClippingPlane())

	//! [ESMF] Number MinSG.CameraNodeOrtho.getTopClippingPlane()
	ES_MFUN(typeObject,const CameraNodeOrtho, "getTopClippingPlane", 0, 0,
			thisObj->getTopClippingPlane())

	//! [ESMF] self MinSG.CameraNodeOrtho.setLeftClippingPlane(Number)
	ES_MFUN(typeObject,CameraNodeOrtho, "setLeftClippingPlane", 1, 1,
			(thisObj->setLeftClippingPlane(parameter[0].toFloat()),thisEObj))

	//! [ESMF] self MinSG.CameraNodeOrtho.setRightClippingPlane(Number)
	ES_MFUN(typeObject,CameraNodeOrtho, "setRightClippingPlane", 1, 1,
			(thisObj->setRightClippingPlane(parameter[0].toFloat()),thisEObj))

	//! [ESMF] self MinSG.CameraNodeOrtho.setBottomClippingPlane(Number)
	ES_MFUN(typeObject,CameraNodeOrtho, "setBottomClippingPlane", 1, 1,
			(thisObj->setBottomClippingPlane(parameter[0].toFloat()),thisEObj))

	//! [ESMF] self MinSG.CameraNodeOrtho.setTopClippingPlane(Number)
	ES_MFUN(typeObject,CameraNodeOrtho, "setTopClippingPlane", 1, 1,
			(thisObj->setTopClippingPlane(parameter[0].toFloat()),thisEObj))

	//! [ESMF] self MinSG.CameraNodeOrtho.setClippingPlanes(Number, Number, Number, Number)
	ES_MFUN(typeObject,CameraNodeOrtho, "setClippingPlanes", 4, 4,
			(thisObj->setClippingPlanes(parameter[0].toFloat(), parameter[1].toFloat(), parameter[2].toFloat(), parameter[3].toFloat()),thisEObj))

	//! [ESMF] self MinSG.CameraNodeOrtho.setFrustumFromScaledViewport(Number)
	ES_MFUN(typeObject,CameraNodeOrtho, "setFrustumFromScaledViewport", 1, 1,
			(thisObj->setFrustumFromScaledViewport(parameter[0].toFloat()),thisEObj))

}

}
