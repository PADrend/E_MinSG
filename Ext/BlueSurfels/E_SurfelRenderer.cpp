/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2014 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2016-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_SurfelRenderer.h"
#include "Strategies/E_AbstractSurfelStrategy.h"

#include <EScript/EScript.h>

#include <functional>
#include <typeinfo>
#include <iostream>

namespace E_MinSG {
namespace BlueSurfels {
using namespace MinSG::BlueSurfels;

//! (static)
EScript::Type * E_SurfelRenderer::getTypeObject() {
	//  E_SurfelRenderer ---|> E_NodeRendererState ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	return typeObject.get();
}

//! (static)
void E_SurfelRenderer::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<SurfelRenderer,E_SurfelRenderer>();

	//! [ESF] new MinSG.SurfelRenderer()
	ES_CTOR(typeObject, 0, 0, EScript::create(new SurfelRenderer))

  ES_MFUN(typeObject, SurfelRenderer, "addSurfelStrategy", 1, 1, 
    (thisObj->addSurfelStrategy(parameter[0].to<AbstractSurfelStrategy*>(rt)),thisEObj))

  ES_MFUN(typeObject, SurfelRenderer, "removeSurfelStrategy", 1, 1, 
    (thisObj->removeSurfelStrategy(parameter[0].to<AbstractSurfelStrategy*>(rt)),thisEObj))
    
  ES_MFUN(typeObject, SurfelRenderer, "clearSurfelStrategies", 0, 0, 
    (thisObj->clearSurfelStrategies(),thisEObj))
    
  ES_MFUNCTION(typeObject, const SurfelRenderer, "getSurfelStrategies", 0, 0, {
		return EScript::Array::create(thisObj->getSurfelStrategies());
  })
}
//---

//! (ctor)
E_SurfelRenderer::E_SurfelRenderer(SurfelRenderer * _obj, EScript::Type * type) :
		E_NodeRendererState(_obj,type?type:getTypeObject()){
}

}
}

#endif // MINSG_EXT_BLUE_SURFELS