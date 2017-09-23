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

#include <E_Geometry/E_Vec2.h>

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
	ES_CTOR(typeObject,0,0,new E_PathTracer(new PathTracer, thisType))

	// void reset()
	//! [ESMF] self PathTracer.reset()
	ES_MFUN(typeObject,PathTracer,"reset",0,0,
				(thisObj->reset(),thisEObj))

	// void start()
	//! [ESMF] self PathTracer.start()
	ES_MFUN(typeObject,PathTracer,"start",0,0,
				(thisObj->start(),thisEObj))

	// void pause()
	//! [ESMF] self PathTracer.pause()
	ES_MFUN(typeObject,PathTracer,"pause",0,0,
				(thisObj->pause(),thisEObj))
				

	// uint32_t getSamplesPerPixel()
	//! [ESMF] Number PathTracer.getSamplesPerPixel()
	ES_MFUN(typeObject,const PathTracer,"getSamplesPerPixel",0,0,
		EScript::Number::create(thisObj->getSamplesPerPixel()))
	
	// bool isFinished()
	//! [ESMF] Bool PathTracer.isFinished()
	ES_MFUN(typeObject,const PathTracer,"isFinished",0,0,
				EScript::Bool::create(thisObj->isFinished()))

	// void download(Util::Reference<Util::PixelAccessor> image)
	//! [ESMF] self PathTracer.download(image)
	ES_MFUN(typeObject,PathTracer,"download",1,2,
				(thisObj->download(parameter[0].to<Util::PixelAccessor&>(rt), parameter[1].toFloat(2.2)),thisEObj))
											
	// void setScene(GroupNode* scene)
	//! [ESMF] self PathTracer.setScene(GroupNode scene)
	ES_MFUN(typeObject,PathTracer,"setScene",1,1,
				(thisObj->setScene(parameter[0].to<GroupNode*>(rt)),thisEObj))
				
	// void setCamera(AbstractCameraNode* camera)
	//! [ESMF] self PathTracer.setCamera(AbstractCameraNode camera)
	ES_MFUN(typeObject,PathTracer,"setCamera",1,1,
		(thisObj->setCamera(parameter[0].to<AbstractCameraNode*>(rt)),thisEObj))

	// void setMaxBounces(uint32_t maxBounces)
	//! [ESMF] self PathTracer.setMaxBounces(Number maxBounces)
	ES_MFUN(typeObject,PathTracer,"setMaxBounces",1,1,
				(thisObj->setMaxBounces(parameter[0].toUInt()),thisEObj))

	// void setMaxSamples(uint32_t maxSamples)
	//! [ESMF] self PathTracer.setMaxSamples(Number maxSamples)
	ES_MFUN(typeObject,PathTracer,"setMaxSamples",1,1,
				(thisObj->setMaxSamples(parameter[0].toUInt()),thisEObj))
							
	// void setSeed(uint32_t seed)
	//! [ESMF] self PathTracer.setSeed(Number seed)
	ES_MFUN(typeObject,PathTracer,"setSeed",1,1,
				(thisObj->setSeed(parameter[0].toUInt()),thisEObj))
			
	// void setUseGlobalLight(uint32_t useGlobalLight)
	//! [ESMF] self PathTracer.setUseGlobalLight(Bool useGlobalLight)
	ES_MFUN(typeObject,PathTracer,"setUseGlobalLight",1,1,
				(thisObj->setUseGlobalLight(parameter[0].toBool()),thisEObj))
			
	// void setAntiAliasing(uint32_t antiAliasing)
	//! [ESMF] self PathTracer.setAntiAliasing(Bool antiAliasing)
	ES_MFUN(typeObject,PathTracer,"setAntiAliasing",1,1,
				(thisObj->setAntiAliasing(parameter[0].toBool()),thisEObj))
				
	// void setResolution(const Geometry::Vec2& resolution)
	//! [ESMF] self PathTracer.setResolution(Geometry.Vec2 resolution)
	ES_MFUN(typeObject,PathTracer,"setResolution",1,1,
		(thisObj->setResolution(parameter[0].to<Geometry::Vec2&>(rt)),thisEObj))

	// void setThreadCount(uint32_t count)
	//! [ESMF] self PathTracer.setThreadCount(Number count)
	ES_MFUN(typeObject,PathTracer,"setThreadCount",1,1,
				(thisObj->setThreadCount(parameter[0].toUInt()),thisEObj))

	// void setTileSize(uint32_t size)
	//! [ESMF] self PathTracer.setTileSize(Number size)
	ES_MFUN(typeObject,PathTracer,"setTileSize",1,1,
				(thisObj->setTileSize(parameter[0].toUInt()),thisEObj))
}

}
#endif // MINSG_EXT_PATHTRACING

