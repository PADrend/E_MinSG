/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_AbstractSurfelStrategy.h"

#include <E_Util/E_Utils.h>

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <unordered_map>

namespace E_MinSG {
namespace BlueSurfels {
using namespace MinSG::BlueSurfels;

//! (static)
E_Util::E_ObjectFactory<AbstractSurfelStrategy,E_AbstractSurfelStrategy> E_AbstractSurfelStrategy::factorySystem;

// ----------------------------------------------------------------------

EScript::Type * E_AbstractSurfelStrategy::getTypeObject() {
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

// ----------------------------------------------------------------------

//! [static] initMembers
void E_AbstractSurfelStrategy::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<AbstractSurfelStrategy,E_AbstractSurfelStrategy>();

	// -----------------------------------
  ES_MFUN(typeObject,const AbstractSurfelStrategy,"isEnabled", 0, 0, thisObj->isEnabled())	
  ES_MFUN(typeObject,AbstractSurfelStrategy,"setEnabled",1,1, (thisObj->setEnabled(parameter[0].toBool()),thisEObj) )
}


} /* BlueSurfels */
} /* MinSG */
#endif // MINSG_EXT_BLUE_SURFELS