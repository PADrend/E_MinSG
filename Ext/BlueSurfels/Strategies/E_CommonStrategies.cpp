/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_CommonStrategies.h"

#include <E_Util/E_Utils.h>

#include <EScript/EScript.h>


namespace E_MinSG {
namespace BlueSurfels {
using namespace MinSG::BlueSurfels;

//! FixedSizeStrategy
void E_FixedSizeStrategy::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<FixedSizeStrategy,E_FixedSizeStrategy>();

	//! [ESMF] new FixedSizeStrategy
	ES_CTOR(typeObject, 0, 0, new FixedSizeStrategy)
  
  ES_MGETSET(FixedSizeStrategy, float, Size)
}

//! FixedCountStrategy
void E_FixedCountStrategy::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<FixedCountStrategy,E_FixedCountStrategy>();

	//! [ESMF] new FixedCountStrategy
	ES_CTOR(typeObject, 0, 0, new FixedCountStrategy)
  
  ES_MGETSET(FixedCountStrategy, uint32_t, Count)
}

//! FactorStrategy
void E_FactorStrategy::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<FactorStrategy,E_FactorStrategy>();

	//! [ESMF] new FactorStrategy
	ES_CTOR(typeObject, 0, 0, new FactorStrategy)
  
  ES_MGETSET(FactorStrategy, float, CountFactor)
  ES_MGETSET(FactorStrategy, float, SizeFactor)
}

//! ReferencePointStrategy
void E_ReferencePointStrategy::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<ReferencePointStrategy,E_ReferencePointStrategy>();

	//! [ESMF] new FixedCountStrategy
	ES_CTOR(typeObject, 0, 0, new ReferencePointStrategy)
  
  ES_MFUN(typeObject, const ReferencePointStrategy, "getReferencePoint", 0, 0, 
		EScript::Number::create(thisObj->getReferencePoint()))  
  ES_MFUN(typeObject, ReferencePointStrategy, "setReferencePoint", 1, 1, 
		(thisObj->setReferencePoint(static_cast<ReferencePoint>(parameter[0].toUInt())), thisEObj))
}

//! BlendStrategy
void E_BlendStrategy::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<BlendStrategy,E_BlendStrategy>();

	//! [ESMF] new BlendStrategy
	ES_CTOR(typeObject, 0, 0, new BlendStrategy)
  
  ES_MGETSET(BlendStrategy, float, Blend)
}

//! DebugStrategy
void E_DebugStrategy::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<DebugStrategy,E_DebugStrategy>();

	//! [ESMF] new DebugStrategy
	ES_CTOR(typeObject, 0, 0, new DebugStrategy)
  
  ES_MGETSET(DebugStrategy, bool, HideSurfels)
  ES_MGETSET(DebugStrategy, bool, FixSurfels)
}

namespace E_CommonStrategies {
void init(EScript::Namespace & lib) {
	E_FixedSizeStrategy::init(lib);
	E_FixedCountStrategy::init(lib);
	E_FactorStrategy::init(lib);
	E_BlendStrategy::init(lib);
	E_ReferencePointStrategy::init(lib);
	E_DebugStrategy::init(lib);
}
} /* E_CommonStrategies */

} /* BlueSurfels */
} /* MinSG */
#endif // MINSG_EXT_BLUE_SURFELS