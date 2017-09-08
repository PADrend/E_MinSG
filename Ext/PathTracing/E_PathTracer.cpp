/*
	This file is part of the MinSG library extension PathTracing.
	Copyright (C) 2017 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_PATHTRACING

#include "E_PathTracer.h"

#include "../../Core/Nodes/E_AbstractCameraNode.h"
#include "../../Core/Nodes/E_GroupNode.h"

#include <E_Util/Graphics/E_PixelAccessor.h>

#include <Util/References.h>

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_MinSG{


//! (static)
EScript::Type * E_PathTracer::getTypeObject() {
	// E_PathTracer ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members 
void E_PathTracer::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_PathTracer::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace MinSG;
	using namespace MinSG::PathTracing;
	
	//!	[ESMF] PathTracer new PathTracer()
	ES_CTOR(typeObject,0,0,new E_PathTracer(thisType))

	// void reset()
	//! [ESMF] self PathTracer.reset()
	ES_MFUN(typeObject,PathTracer,"reset",0,0,
				(thisObj->reset(),thisEObj))

	// void trace(AbstractCameraNode* camera, GroupNode* scene, Util::Reference<Util::PixelAccessor> frameBuffer, uint32_t maxBounces)
	//! [ESMF] self PathTracer.trace(p0,p1,p2,p3)
	ES_MFUN(typeObject,PathTracer,"trace",3,3,
				(thisObj->trace(parameter[0].to<AbstractCameraNode*>(rt),parameter[1].to<GroupNode*>(rt),parameter[2].to<Util::PixelAccessor&>(rt)),thisEObj))
			
	// void setMaxBounces(uint32_t maxBounces)
	//! [ESMF] self PathTracer.setMaxBounces(Number maxBounces)
	ES_MFUN(typeObject,PathTracer,"setMaxBounces",1,1,
				(thisObj->setMaxBounces(parameter[0].toUInt()),thisEObj))
							
	// void setSeed(uint32_t seed)
	//! [ESMF] self PathTracer.setSeed(Number seed)
	ES_MFUN(typeObject,PathTracer,"setSeed",1,1,
				(thisObj->setSeed(parameter[0].toUInt()),thisEObj))
			
	// void setUseGlobalLight(uint32_t useGlobalLight)
	//! [ESMF] self PathTracer.setUseGlobalLight(Bool useGlobalLight)
	ES_MFUN(typeObject,PathTracer,"setUseGlobalLight",1,1,
				(thisObj->setUseGlobalLight(parameter[0].toBool()),thisEObj))
			
	// void setEmittersOnly(uint32_t emittersOnly)
	//! [ESMF] self PathTracer.setEmittersOnly(Bool emittersOnly)
	ES_MFUN(typeObject,PathTracer,"setEmittersOnly",1,1,
				(thisObj->setEmittersOnly(parameter[0].toBool()),thisEObj))
			
	// void setAntiAliasing(uint32_t antiAliasing)
	//! [ESMF] self PathTracer.setAntiAliasing(Bool antiAliasing)
	ES_MFUN(typeObject,PathTracer,"setAntiAliasing",1,1,
				(thisObj->setAntiAliasing(parameter[0].toBool()),thisEObj))
}

}
#endif // MINSG_EXT_PATHTRACING

