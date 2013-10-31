/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_CameraNode.h"

#include "../E_FrameContext.h"
#include "../../ELibMinSG.h"

#include <EScript/EScript.h>
#include <E_Geometry/E_Vec3.h>
#include <E_Geometry/E_Rect.h>

#include <iostream>
#include <sstream>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

//! (static)
EScript::Type * E_CameraNode::getTypeObject() {
	// E_CameraNode ---|> E_AbstractCameraNode ---|> E_Node ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractCameraNode::getTypeObject());
	return typeObject.get();
}

// -----

//! (static)
void E_CameraNode::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());	
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::CameraNode,E_CameraNode>();

	//! [ESMF] new MinSG.CameraNode([angle,[ratio,[near,[far]]]])
	ES_CONSTRUCTOR(typeObject,0,4,{
		CameraNode * c=new CameraNode();
		c->applyVerticalAngle( parameter[0].toDouble(60.0) );
		c->setViewport(Geometry::Rect_i(0,0,1.0,parameter[1].toDouble(1.0)) );
		c->setNearFar(parameter[2].toDouble(1.0),parameter[3].toDouble(10000.0) );
		return EScript::create(c);
	})

	//! [ESMF] Array cam.getAngles(  )
	ES_MFUNCTION(typeObject,const CameraNode,"getAngles",0,0,{
		const CameraNode * c=thisObj;
		Array * a=Array::create();
		float f[4];
		f[0] = f[1] = f[2] = f[3] = 0.0f;
		c->getAngles(f[0],f[1],f[2],f[3]);
		a->pushBack(Number::create(f[0]));
		a->pushBack(Number::create(f[1]));
		a->pushBack(Number::create(f[2]));
		a->pushBack(Number::create(f[3]));
		return a;
	})

	//! [ESMF] self cam.setAngles( array[4] | fovLeft,fovRight,fovBottom,fovTop)
	ES_MFUNCTION(typeObject,CameraNode,"setAngles",1,4,{
		CameraNode * c=thisObj;
		if(parameter.count()==1){
			Array * a = parameter[0].to<EScript::Array*>(rt);
			int i=0;
			float f[4];
			f[0] = f[1] = f[2] = f[3] = 0.0f;
			for(EScript::ERef<Iterator> it=a->getIterator();!it->end() && i<4;it->next(),i++){
				EScript::ObjRef value=(it)->value();
				f[i]=value.toFloat();
			}
			c->setAngles(f[0],f[1],f[2],f[3]);
		}else{
			c->setAngles(parameter[0].toFloat(),parameter[1].toFloat(),parameter[2].toFloat(),parameter[3].toFloat());
		}
		return thisEObj;
	})

	//! [ESMF] self MinSG.Camera.applyHorizontalAngle(number a)
	ES_MFUN(typeObject,CameraNode,"applyHorizontalAngle",1,1,
		(thisObj->applyHorizontalAngle(parameter[0].toFloat()),thisEObj))

	//! [ESMF] self MinSG.Camera.applyVerticalAngle(number a)
	ES_MFUN(typeObject,CameraNode,"applyVerticalAngle",1,1,
		(thisObj->applyVerticalAngle(parameter[0].toFloat()),thisEObj))

}

}
