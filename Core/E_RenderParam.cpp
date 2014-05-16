/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_RenderParam.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_MinSG{

//! (static)
EScript::Type * E_RenderParam::getTypeObject() {
	// E_RenderParam ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_RenderParam::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_RenderParam::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace MinSG;
	
	//! [ESF] new RenderParam(p0)
	ES_CTOR(typeObject,0,0,
				new E_RenderParam)

	//! [ESMF] String RenderParam.getChannel()
	ES_MFUN(typeObject, const RenderParam,"getChannel",0,0,
				thisObj->getChannel().toString())

	//! [ESMF] Bool RenderParam.getFlag(p0)
	ES_MFUN(typeObject, const RenderParam,"getFlag",1,1,
				thisObj->getFlag(parameter[0].toUInt()))

	//! [ESMF] Number RenderParam.getFlags()
	ES_MFUN(typeObject, const RenderParam,"getFlags",0,0,
				thisObj->getFlags())

	//!	[ESMF] Number MinSG.Node.getRenderingLayers()	
	ES_MFUN(typeObject, const RenderParam, "getRenderingLayers", 0,  0, 
				static_cast<uint32_t>(thisObj->getRenderingLayers()))

	//! [ESMF] thisEObj RenderParam.setChannel(String)
	ES_MFUN(typeObject, RenderParam,"setChannel",1,1,
				(thisObj->setChannel(parameter[0].toString()),thisEObj))

	//! [ESMF] thisEObj RenderParam.setFlag(Number)
	ES_MFUN(typeObject, RenderParam,"setFlag",1,1,
				(thisObj->setFlag(parameter[0].toUInt()),thisEObj))

	//! [ESMF] thisEObj RenderParam.setFlags(Number)
	ES_MFUN(typeObject, RenderParam,"setFlags",1,1,
				(thisObj->setFlags(parameter[0].toUInt()),thisEObj))
				
	//!	[ESMF] thisEObj MinSG.Node.setRenderingLayers(Number)
	ES_MFUN(typeObject, RenderParam, "setRenderingLayers", 1, 1,  
				(thisObj->setRenderingLayers(static_cast<renderingLayerMask_t>(parameter[0].to<uint32_t>(rt))), thisEObj))

	//! [ESMF] thisEObj RenderParam.unsetFlag(Number)
	ES_MFUN(typeObject, RenderParam,"unsetFlag",1,1,
				(thisObj->unsetFlag(parameter[0].toUInt()),thisEObj))
}
}
