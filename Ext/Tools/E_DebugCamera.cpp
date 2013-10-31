/*
	This file is part of the E_MinSG library.
	Copyright (C) 2012-2013 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_DebugCamera.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <E_Rendering/E_RenderingContext.h>
#include <E_Rendering/E_FBO.h>

#include "../../Core/Nodes/E_AbstractCameraNode.h"

namespace E_MinSG{

//! (static)
EScript::Type * E_DebugCamera::getTypeObject() {
	// E_DebugCamera ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members 
void E_DebugCamera::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_DebugCamera::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace MinSG;

	//! [ESF] new DebugCamera
	ES_CTOR(typeObject, 0, 0, EScript::create(new MinSG::DebugCamera))
	
	//! [ESMF] self DebugCamera.disable(p0)
	ES_MFUN(typeObject,DebugCamera,"disable",1,1, (thisObj->disable(parameter[0].to<Rendering::RenderingContext&>(rt)),thisEObj))

	//! [ESMF] self DebugCamera.enable(p0,p1,p2,p3)
	ES_MFUN(typeObject,DebugCamera,"enable",4,4, (thisObj->enable(
		parameter[0].to<Rendering::RenderingContext&>(rt),
		parameter[1].to<AbstractCameraNode*>(rt),
		parameter[2].to<AbstractCameraNode*>(rt),
		parameter[3].to<Rendering::FBO*>(rt)
	),thisEObj))

}
}

