/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017 Sascha Brandt <myeti@mail.uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_SurfelRenderer_Budget.h"
#include "../../Core/E_FrameContext.h"
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

	//! [ESMF] Number surfelRenderer.getMaxSurfelSize()
	ES_MFUN(typeObject,const SurfelRendererBudget,"getMaxSurfelSize",0,0,thisObj->getMaxSurfelSize())

	//! [ESMF] Bool surfelRenderer.getDebugHideSurfels()
	ES_MFUN(typeObject,const SurfelRendererBudget,"getDebugHideSurfels",0,0,thisObj->getDebugHideSurfels())
	
	//! [ESMF] Bool surfelRenderer.isDebugCameraEnabled()
	ES_MFUN(typeObject,const SurfelRendererBudget,"isDebugCameraEnabled",0,0,thisObj->isDebugCameraEnabled())

	//! [ESMF] Number surfelRenderer.getBudget()
	ES_MFUN(typeObject,const SurfelRendererBudget,"getBudget",0,0,thisObj->getBudget())
	
	//! [ESMF] Bool surfelRenderer.getDeferredSurfels()
	ES_MFUN(typeObject,const SurfelRendererBudget,"getDeferredSurfels",0,0,thisObj->getDeferredSurfels())
	
	//! [ESMF] Bool surfelRenderer.getDebugAssignment()
	ES_MFUN(typeObject,const SurfelRendererBudget,"getDebugAssignment",0,0,thisObj->getDebugAssignment())
	
	//! [ESMF] Bool surfelRenderer.getMaxIncrement()
	ES_MFUN(typeObject,const SurfelRendererBudget,"getMaxIncrement",0,0,thisObj->getMaxIncrement())
	
	//! [ESMF] self surfelRenderer.setMaxSurfelSize( Number )
	ES_MFUN(typeObject,SurfelRendererBudget,"setMaxSurfelSize",1,1, (thisObj->setMaxSurfelSize(parameter[0].toFloat()),thisEObj) )
	
	//! [ESMF] self surfelRenderer.setDebugHideSurfels( Bool )
	ES_MFUN(typeObject,SurfelRendererBudget,"setDebugHideSurfels",1,1, (thisObj->setDebugHideSurfels(parameter[0].toBool()),thisEObj) )
	
	//! [ESMF] self surfelRenderer.setDebugCameraEnabled( Bool )
	ES_MFUN(typeObject,SurfelRendererBudget,"setDebugCameraEnabled",1,1, (thisObj->setDebugCameraEnabled(parameter[0].toBool()),thisEObj) )

	//! [ESMF] self surfelRenderer.setBudget( Number )
	ES_MFUN(typeObject,SurfelRendererBudget,"setBudget",1,1, (thisObj->setBudget(parameter[0].toDouble()),thisEObj) )
	
	//! [ESMF] self surfelRenderer.setDeferredSurfels( Bool )
	ES_MFUN(typeObject,SurfelRendererBudget,"setDeferredSurfels",1,1, (thisObj->setDeferredSurfels(parameter[0].toBool()),thisEObj) )
	
	//! [ESMF] self surfelRenderer.setDebugAssignment( Bool )
	ES_MFUN(typeObject,SurfelRendererBudget,"setDebugAssignment",1,1, (thisObj->setDebugAssignment(parameter[0].toBool()),thisEObj) )
	
	//! [ESMF] self surfelRenderer.setMaxIncrement( Number )
	ES_MFUN(typeObject,SurfelRendererBudget,"setMaxIncrement",1,1, (thisObj->setMaxIncrement(parameter[0].toDouble()),thisEObj) )
	
	//! [ESMF] self surfelRenderer.drawSurfels( FrameContext, [Number, Number] )
	ES_MFUN(typeObject,SurfelRendererBudget,"drawSurfels",1,3, (thisObj->drawSurfels(parameter[0].to<MinSG::FrameContext&>(rt), parameter[1].toFloat(0), parameter[2].toFloat(1024)),thisEObj) )
		
	//! [ESMF] self surfelRenderer.assignmentStep( )
	ES_MFUN(typeObject,SurfelRendererBudget,"assignmentStep",0,0, (thisObj->assignmentStep(),thisEObj) )
		
	//! [ESMF] self surfelRenderer.clearAssignment( )
	ES_MFUN(typeObject,SurfelRendererBudget,"clearAssignment",0,0, (thisObj->clearAssignment(),thisEObj) )
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
