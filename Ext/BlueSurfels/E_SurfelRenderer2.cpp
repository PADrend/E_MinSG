/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2014 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_SurfelRenderer2.h"
#include "../../ELibMinSG.h"
#include "../ELibMinSGExt.h"
#include <EScript/EScript.h>

namespace E_MinSG {
namespace BlueSurfels{

using namespace MinSG;
using namespace MinSG::BlueSurfels;


EScript::Type* E_SurfelRenderer2::typeObject=nullptr;

//! (static) initMembers
void E_SurfelRenderer2::init(EScript::Namespace & lib) {
	// E_SurfelRenderer2 ---|> E_NodeRendererState ---|> E_State ---|> Object
	typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<SurfelRenderer2,E_SurfelRenderer2>();

	//! [ESF] new MinSG.SurfelRenderer2
	ES_CTOR(typeObject, 0, 0, EScript::create(new SurfelRenderer2))

	//! [ESMF] Number surfelRenderer.getCountFactor()
	ES_MFUN(typeObject,const SurfelRenderer2,"getCountFactor",0,0,thisObj->getCountFactor())

	//! [ESMF] Number surfelRenderer.getSizeFactor()
	ES_MFUN(typeObject,const SurfelRenderer2,"getSizeFactor",0,0,thisObj->getSizeFactor())

	//! [ESMF] Number surfelRenderer.getMaxSurfelSize()
	ES_MFUN(typeObject,const SurfelRenderer2,"getMaxSurfelSize",0,0,thisObj->getMaxSurfelSize())

	//! [ESMF] self surfelRenderer.setCountFactor( Number )
	ES_MFUN(typeObject,SurfelRenderer2,"setCountFactor",1,1, (thisObj->setCountFactor(parameter[0].to<float>(rt)),thisEObj) )

	//! [ESMF] self surfelRenderer.setSizeFactor( Number )
	ES_MFUN(typeObject,SurfelRenderer2,"setSizeFactor",1,1, (thisObj->setSizeFactor(parameter[0].to<float>(rt)),thisEObj) )
	
	//! [ESMF] self surfelRenderer.setMaxSurfelSize( Number )
	ES_MFUN(typeObject,SurfelRenderer2,"setMaxSurfelSize",1,1, (thisObj->setMaxSurfelSize(parameter[0].to<float>(rt)),thisEObj) )
}
//---

//! (ctor)
E_SurfelRenderer2::E_SurfelRenderer2(SurfelRenderer2 * _obj, EScript::Type * type):E_NodeRendererState(_obj,type?type:typeObject){
}

//! (ctor)
E_SurfelRenderer2::~E_SurfelRenderer2(){
}

}
}

#endif // MINSG_EXT_BLUE_SURFELS
