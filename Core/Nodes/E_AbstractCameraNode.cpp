/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_AbstractCameraNode.h"

#include "../E_FrameContext.h"
#include "../../ELibMinSG.h"

#include <EScript/EScript.h>
#include <E_Geometry/E_Vec3.h>
#include <E_Geometry/E_Rect.h>
#include <E_Geometry/E_Box.h>
#include <E_Geometry/E_Frustum.h>

#include <E_Util/Graphics/E_Color.h>

#include <iostream>
#include <sstream>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

//! (static)
EScript::Type * E_AbstractCameraNode::getTypeObject() {
	// E_AbstractCameraNode ---|> E_Node ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_Node::getTypeObject());
	return typeObject.get();
}

// -----

//! (static)
void E_AbstractCameraNode::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	initPrintableName(typeObject,getClassName());
	addFactory<MinSG::AbstractCameraNode,E_AbstractCameraNode>();

	//! [ESMF] Number cam.getFarPlane()
	ES_MFUN(typeObject,const AbstractCameraNode,"getFarPlane",0,0,
			Number::create(thisObj->getFarPlane()))

	//! [ESMF] Frustum cam.getFrustum(  )
	ES_MFUN(typeObject,const AbstractCameraNode,"getFrustum",0,0,
			EScript::create(thisObj->getFrustum()))

	//! [ESMF] Number cam.getHeight()
	ES_MFUN(typeObject,const AbstractCameraNode, "getHeight",0,0,Number::create(thisObj->getHeight()))

	//! [ESMF] Number cam.getNearPlane()
	ES_MFUN(typeObject,const AbstractCameraNode,"getNearPlane",0,0,
			Number::create(thisObj->getNearPlane()))

	//! [ESMF] Rect cam.getScissor(  )
	ES_MFUN(typeObject,const AbstractCameraNode,"getScissor",0,0,
			EScript::create(Geometry::Rect(thisObj->getScissor())))

	//! [ESMF] Rect cam.getViewport(  )
	ES_MFUN(typeObject,const AbstractCameraNode,"getViewport",0,0,
			EScript::create(Geometry::Rect(thisObj->getViewport())))

	//! [ESMF] Number cam.getWidth()
	ES_MFUN(typeObject,const AbstractCameraNode,"getWidth",0,0,Number::create(thisObj->getWidth()))

	//! [ESMF] bool cam.isScissorEnabled(  )
	ES_MFUN(typeObject,const AbstractCameraNode,"isScissorEnabled",0,0,
			thisObj->isScissorEnabled())

	//! [ESMF] self cam.setNearFar(number near,number far)
	ES_MFUN(typeObject,AbstractCameraNode,"setNearFar",2,2,
			(thisObj->setNearFar(parameter[0].toFloat(),parameter[1].toFloat()),thisEObj))

	//! [ESMF] self cam.setScissor( Rect )
	ES_MFUN(typeObject,AbstractCameraNode,"setScissor",1,1,
			(thisObj->setScissor(Geometry::Rect_i(parameter[0].to<const Geometry::Rect&>(rt))),thisEObj))

	//! [ESMF] self cam.setScissorEnabled( bool )
	ES_MFUN(typeObject,AbstractCameraNode,"setScissorEnabled",1,1,
			(thisObj->setScissorEnabled(parameter[0].toBool()),thisEObj))

	//! [ESMF] self cam.setViewport( Rect, [scissor=true] )
	ES_MFUN(typeObject,AbstractCameraNode,"setViewport",1,2,
			(thisObj->setViewport(Geometry::Rect_i(parameter[0].to<const Geometry::Rect&>(rt)),parameter[1].toBool(true)),thisEObj))

	//! [ESMF] Number|false cam.isBoxInFrustum(Box)
	ES_MFUN(typeObject,const AbstractCameraNode, "testBoxFrustumIntersection", 1, 1,
			Number::create(static_cast<int>(thisObj->testBoxFrustumIntersection(parameter[0].to<const Geometry::Box&>(rt)))))
}

}
