/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_ProjSizeFilterState.h"
#include "../../ELibMinSG.h"
#include "../ELibMinSGExt.h"
#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

Type* E_ProjSizeFilterState::typeObject=nullptr;

//! (static) initMembers
void E_ProjSizeFilterState::init(EScript::Namespace & lib) {
	// E_ProjSizeFilterState ---|> E_NodeRendererState ---|> E_State ---|> Object
	typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::ProjSizeFilterState,E_ProjSizeFilterState>();

	/*! [ESF] new MinSG.ProjSizeFilterState()*/
	ES_CTOR(typeObject, 0, 0, EScript::create(new ProjSizeFilterState()))

	//! [ESMF] Number projSizeFilterState.getMinimumDistance()
	ES_MFUN(typeObject,ProjSizeFilterState,"getMinimumDistance",0,0,
				Number::create(thisObj->getMinimumDistance()))

	//! [ESMF] self projSizeFilterState.setMinimumDistance(float)
	ES_MFUN(typeObject,ProjSizeFilterState,"setMinimumDistance",1,1,
				(thisObj->setMinimumDistance(parameter[0].toFloat()),thisEObj))

	//! [ESMF] Number projSizeFilterState.getMaximumProjSize()
	ES_MFUN(typeObject,ProjSizeFilterState,"getMaximumProjSize",0,0,
				Number::create(thisObj->getMaximumProjSize()))

	//! [ESMF] self projSizeFilterState.setMaximumProjSize(float)
	ES_MFUN(typeObject,ProjSizeFilterState,"setMaximumProjSize",1,1,
				(thisObj->setMaximumProjSize(parameter[0].toFloat()),thisEObj))

	//! [ESMF] Bool projSizeFilterState.isForced()
	ES_MFUN(typeObject,ProjSizeFilterState,"isForceClosed",0,0,
				Bool::create(thisObj->isForceClosed()))

	//! [ESMF] self projSizeFilterState.setForced(bool)
	ES_MFUN(typeObject,ProjSizeFilterState,"setForceClosed",1,1,
				(thisObj->setForceClosed(parameter[0].toBool()),thisEObj))

	//! [ESMF] String projSizeFilterState.getTargetChannel()
	ES_MFUN(typeObject,ProjSizeFilterState,"getTargetChannel",0,0,
				String::create(thisObj->getTargetChannel().toString()))

	//! [ESMF] self projSizeFilterState.setTargetChannel(string)
	ES_MFUN(typeObject,ProjSizeFilterState,"setTargetChannel",1,1,
				(thisObj->setTargetChannel(parameter[0].toString()),thisEObj))

}
//---

//! (ctor)
E_ProjSizeFilterState::E_ProjSizeFilterState(ProjSizeFilterState * _obj, EScript::Type * type):E_NodeRendererState(_obj,type?type:typeObject){
}

//! (ctor)
E_ProjSizeFilterState::~E_ProjSizeFilterState(){
}

}
