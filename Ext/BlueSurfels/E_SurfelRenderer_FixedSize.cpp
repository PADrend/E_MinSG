/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2014 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2016-2017 Sascha Brandt <myeti@mail.uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_SurfelRenderer_FixedSize.h"
#include "../../Core/E_FrameContext.h"
#include "../../ELibMinSG.h"
#include "../ELibMinSGExt.h"
#include <EScript/EScript.h>

namespace E_MinSG {
namespace BlueSurfels{

using namespace MinSG;
using namespace MinSG::BlueSurfels;


EScript::Type* E_SurfelRendererFixedSize::typeObject=nullptr;

//! (static) initMembers
void E_SurfelRendererFixedSize::init(EScript::Namespace & lib) {
	// E_SurfelRendererFixedSize ---|> E_NodeRendererState ---|> E_State ---|> Object
	typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<SurfelRendererFixedSize,E_SurfelRendererFixedSize>();

	//! [ESF] new MinSG.SurfelRendererFixedSize
	ES_CTOR(typeObject, 0, 0, EScript::create(new SurfelRendererFixedSize))

	//! [ESMF] Number surfelRenderer.getCountFactor()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"getCountFactor",0,0,thisObj->getCountFactor())

	//! [ESMF] self surfelRenderer.setCountFactor( Number )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setCountFactor",1,1, (thisObj->setCountFactor(parameter[0].to<float>(rt)),thisEObj) )

	//! [ESMF] Number surfelRenderer.getSizeFactor()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"getSizeFactor",0,0,thisObj->getSizeFactor())

	//! [ESMF] self surfelRenderer.setSizeFactor( Number )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setSizeFactor",1,1, (thisObj->setSizeFactor(parameter[0].to<float>(rt)),thisEObj) )

	//! [ESMF] Number surfelRenderer.getSurfelSize()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"getSurfelSize",0,0,thisObj->getSurfelSize())

	//! [ESMF] self surfelRenderer.setSurfelSize( Number )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setSurfelSize",1,1, (thisObj->setSurfelSize(parameter[0].to<float>(rt)),thisEObj) )

	//! [ESMF] Number surfelRenderer.getMaxSurfelSize()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"getMaxSurfelSize",0,0,thisObj->getMaxSurfelSize())
	
	//! [ESMF] self surfelRenderer.setMaxSurfelSize( Number )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setMaxSurfelSize",1,1, (thisObj->setMaxSurfelSize(parameter[0].to<float>(rt)),thisEObj) )

	//! [ESMF] Bool surfelRenderer.getDebugHideSurfels()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"getDebugHideSurfels",0,0,thisObj->getDebugHideSurfels())
	
	//! [ESMF] self surfelRenderer.setDebugHideSurfels( Bool )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setDebugHideSurfels",1,1, (thisObj->setDebugHideSurfels(parameter[0].toBool()),thisEObj) )
	
	//! [ESMF] Bool surfelRenderer.isDebugCameraEnabled()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"isDebugCameraEnabled",0,0,thisObj->isDebugCameraEnabled())
	
	//! [ESMF] self surfelRenderer.setDebugCameraEnabled( Bool )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setDebugCameraEnabled",1,1, (thisObj->setDebugCameraEnabled(parameter[0].toBool()),thisEObj) )
	
	//! [ESMF] Bool surfelRenderer.getDeferredSurfels()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"getDeferredSurfels",0,0,thisObj->getDeferredSurfels())
	
	//! [ESMF] self surfelRenderer.setDeferredSurfels( Bool )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setDeferredSurfels",1,1, (thisObj->setDeferredSurfels(parameter[0].toBool()),thisEObj) )
	
	//! [ESMF] Bool surfelRenderer.isAdaptive()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"isAdaptive",0,0,thisObj->isAdaptive())
	
	//! [ESMF] self surfelRenderer.setDeferredSurfels( Bool )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setAdaptive",1,1, (thisObj->setAdaptive(parameter[0].toBool()),thisEObj) )
	
	//! [ESMF] Bool surfelRenderer.getMaxFrameTime()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"getMaxFrameTime",0,0,thisObj->getMaxFrameTime())
	
	//! [ESMF] self surfelRenderer.setMaxFrameTime( Number )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setMaxFrameTime",1,1, (thisObj->setMaxFrameTime(parameter[0].toFloat()),thisEObj) )
	
	//! [ESMF] Bool surfelRenderer.getBlendFactor()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"getBlendFactor",0,0,thisObj->getBlendFactor())
	
	//! [ESMF] self surfelRenderer.setBlendFactor( Number )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setBlendFactor",1,1, (thisObj->setBlendFactor(parameter[0].toFloat()),thisEObj) )

	//! [ESMF] self surfelRenderer.drawSurfels( FrameContext, [Number, Number] )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"drawSurfels",1,3, (thisObj->drawSurfels(parameter[0].to<MinSG::FrameContext&>(rt), parameter[1].toFloat(0), parameter[2].toFloat(1024)),thisEObj) )
	
	//! [ESMF] Bool surfelRenderer.isFoveated()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"isFoveated",0,0,thisObj->isFoveated())
	
	//! [ESMF] self surfelRenderer.setFoveated( Bool )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setFoveated",1,1, (thisObj->setFoveated(parameter[0].toBool()),thisEObj) )
	
	//! [ESMF] Bool surfelRenderer.getDebugFoveated()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"getDebugFoveated",0,0,thisObj->getDebugFoveated())
	
	//! [ESMF] self surfelRenderer.setDebugFoveated( Bool )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setDebugFoveated",1,1, (thisObj->setDebugFoveated(parameter[0].toBool()),thisEObj) )
	
	
	//! [ESMF] Bool surfelRenderer.getFoveatZones()
	ES_MFUNCTION(typeObject,const SurfelRendererFixedSize,"getFoveatZones",0,0,{
		auto zones = thisObj->getFoveatZones();
		auto a = EScript::Array::create();
		for(const auto& zone : zones) {
			a->pushBack(EScript::Number::create(zone.first));
			a->pushBack(EScript::Number::create(zone.second));
		}
		return a;
	})
	
	//! [ESMF] self surfelRenderer.setFoveatZones( Array )
	ES_MFUNCTION(typeObject,SurfelRendererFixedSize,"setFoveatZones",1,1, {
		auto a = parameter[0].to<EScript::Array*>(rt);
		auto zones = thisObj->getFoveatZones();
		zones.clear();
		for(uint32_t i=1; i<a->count(); i+=2) {
			zones.push_back({a->get(i-1)->toFloat(), a->get(i)->toFloat()});
		}
		thisObj->setFoveatZones(zones);
		return thisEObj;
	})
}
//---

//! (ctor)
E_SurfelRendererFixedSize::E_SurfelRendererFixedSize(SurfelRendererFixedSize * _obj, EScript::Type * type):E_NodeRendererState(_obj,type?type:typeObject){
}

//! (ctor)
E_SurfelRendererFixedSize::~E_SurfelRendererFixedSize(){
}

}
}

#endif // MINSG_EXT_BLUE_SURFELS
