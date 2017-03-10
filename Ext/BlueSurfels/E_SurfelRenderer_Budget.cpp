/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017 Sascha Brandt <myeti@mail.uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_SurfelRenderer_Budget.h"
#include "../../ELibMinSG.h"
#include "../ELibMinSGExt.h"
#include <EScript/EScript.h>

namespace E_MinSG {
namespace BlueSurfels{

using namespace MinSG;
using namespace MinSG::BlueSurfels;


EScript::Type* E_SurfelRendererBudget::typeObject=nullptr;

//! (static) initMembers
void E_SurfelRendererBudget::init(EScript::Namespace & lib) {
	// E_SurfelRendererBudget ---|> E_NodeRendererState ---|> E_State ---|> Object
	typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<SurfelRendererBudget,E_SurfelRendererBudget>();

	//! [ESF] new MinSG.SurfelRendererBudget
	ES_CTOR(typeObject, 0, 0, EScript::create(new SurfelRendererBudget))

	//! [ESMF] Number surfelRenderer.getCountFactor()
	ES_MFUN(typeObject,const SurfelRendererBudget,"getCountFactor",0,0,thisObj->getCountFactor())

	//! [ESMF] Number surfelRenderer.getSizeFactor()
	ES_MFUN(typeObject,const SurfelRendererBudget,"getSizeFactor",0,0,thisObj->getSizeFactor())

	//! [ESMF] Number surfelRenderer.getMaxSurfelSize()
	ES_MFUN(typeObject,const SurfelRendererBudget,"getMaxSurfelSize",0,0,thisObj->getMaxSurfelSize())

	//! [ESMF] Bool surfelRenderer.getDebugHideSurfels()
	ES_MFUN(typeObject,const SurfelRendererBudget,"getDebugHideSurfels",0,0,thisObj->getDebugHideSurfels())
	
	//! [ESMF] Bool surfelRenderer.isDebugCameraEnabled()
	ES_MFUN(typeObject,const SurfelRendererBudget,"isDebugCameraEnabled",0,0,thisObj->isDebugCameraEnabled())

	//! [ESMF] self surfelRenderer.setCountFactor( Number )
	ES_MFUN(typeObject,SurfelRendererBudget,"setCountFactor",1,1, (thisObj->setCountFactor(parameter[0].to<float>(rt)),thisEObj) )

	//! [ESMF] self surfelRenderer.setSizeFactor( Number )
	ES_MFUN(typeObject,SurfelRendererBudget,"setSizeFactor",1,1, (thisObj->setSizeFactor(parameter[0].to<float>(rt)),thisEObj) )
	
	//! [ESMF] self surfelRenderer.setMaxSurfelSize( Number )
	ES_MFUN(typeObject,SurfelRendererBudget,"setMaxSurfelSize",1,1, (thisObj->setMaxSurfelSize(parameter[0].to<float>(rt)),thisEObj) )
	
	//! [ESMF] self surfelRenderer.setDebugHideSufels( Bool )
	ES_MFUN(typeObject,SurfelRendererBudget,"setDebugHideSufels",1,1, (thisObj->setDebugHideSufels(parameter[0].toBool()),thisEObj) )
	
	//! [ESMF] self surfelRenderer.setDebugCameraEnabled( Bool )
	ES_MFUN(typeObject,SurfelRendererBudget,"setDebugCameraEnabled",1,1, (thisObj->setDebugCameraEnabled(parameter[0].toBool()),thisEObj) )
}
//---

//! (ctor)
E_SurfelRendererBudget::E_SurfelRendererBudget(SurfelRendererBudget * _obj, EScript::Type * type):E_NodeRendererState(_obj,type?type:typeObject){
}

//! (ctor)
E_SurfelRendererBudget::~E_SurfelRendererBudget(){
}

}
}

#endif // MINSG_EXT_BLUE_SURFELS
