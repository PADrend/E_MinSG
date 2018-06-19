/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_AdaptiveStrategy.h"

#include <E_Util/E_Utils.h>

#include <EScript/EScript.h>

namespace E_MinSG {
namespace BlueSurfels {
using namespace MinSG::BlueSurfels;

//! (static)
EScript::Type * E_AdaptiveStrategy::getTypeObject() {
	// E_AdaptiveStrategy ---|> E_AbstractSurfelStrategy ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractSurfelStrategy::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_AdaptiveStrategy::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<AdaptiveStrategy,E_AdaptiveStrategy>();

	//! [ESMF] new AdaptiveStrategy
	ES_CTOR(typeObject, 0, 0, new AdaptiveStrategy)
  
  ES_MGETSET(AdaptiveStrategy, float, MaxSize)
  ES_MGETSET(AdaptiveStrategy, float, TargetTime)
}

} /* BlueSurfels */
} /* MinSG */
#endif // MINSG_EXT_BLUE_SURFELS