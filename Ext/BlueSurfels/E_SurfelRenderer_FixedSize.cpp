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

	//! [ESMF] Number surfelRenderer.getSizeFactor()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"getSizeFactor",0,0,thisObj->getSizeFactor())

	//! [ESMF] Number surfelRenderer.getMaxSurfelSize()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"getMaxSurfelSize",0,0,thisObj->getMaxSurfelSize())

	//! [ESMF] Bool surfelRenderer.getDebugHideSurfels()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"getDebugHideSurfels",0,0,thisObj->getDebugHideSurfels())
	
	//! [ESMF] Bool surfelRenderer.isDebugCameraEnabled()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"isDebugCameraEnabled",0,0,thisObj->isDebugCameraEnabled())
	
	//! [ESMF] Bool surfelRenderer.getDeferredSurfels()
	ES_MFUN(typeObject,const SurfelRendererFixedSize,"getDeferredSurfels",0,0,thisObj->getDeferredSurfels())

	//! [ESMF] self surfelRenderer.setCountFactor( Number )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setCountFactor",1,1, (thisObj->setCountFactor(parameter[0].to<float>(rt)),thisEObj) )

	//! [ESMF] self surfelRenderer.setSizeFactor( Number )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setSizeFactor",1,1, (thisObj->setSizeFactor(parameter[0].to<float>(rt)),thisEObj) )
	
	//! [ESMF] self surfelRenderer.setMaxSurfelSize( Number )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setMaxSurfelSize",1,1, (thisObj->setMaxSurfelSize(parameter[0].to<float>(rt)),thisEObj) )
	
	//! [ESMF] self surfelRenderer.setDebugHideSufels( Bool )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setDebugHideSufels",1,1, (thisObj->setDebugHideSufels(parameter[0].toBool()),thisEObj) )
	
	//! [ESMF] self surfelRenderer.setDebugCameraEnabled( Bool )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setDebugCameraEnabled",1,1, (thisObj->setDebugCameraEnabled(parameter[0].toBool()),thisEObj) )
	
	//! [ESMF] self surfelRenderer.setDeferredSurfels( Bool )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"setDeferredSurfels",1,1, (thisObj->setDeferredSurfels(parameter[0].toBool()),thisEObj) )

	//! [ESMF] self surfelRenderer.drawSurfels( FrameContext )
	ES_MFUN(typeObject,SurfelRendererFixedSize,"drawSurfels",1,1, (thisObj->drawSurfels(parameter[0].to<MinSG::FrameContext&>(rt)),thisEObj) )
	
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
