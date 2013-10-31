/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/


#ifdef MINSG_EXT_MULTIALGORENDERING

#include "E_RegionEvaluator.h"

#include "E_Region.h"

#include "../../Core/Nodes/E_GroupNode.h"

#include <E_Util/E_Utils.h>

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

using namespace EScript;
using Util::GenericAttributeMap;

namespace E_MinSG {
namespace E_MAR {
	
	using namespace MinSG::MAR;

//!!!!!!!!!!!!!!! RegionEvaluator

//! (static)
Type * E_RegionEvaluator::getTypeObject(){
	// [E_RegionEvaluator] ---|> [ReferenceObject<Util::Reference<RegionEvaluator>>
	static EScript::Type * typeObject = new EScript::Type(Object::getTypeObject());
	return typeObject;
}

void E_RegionEvaluator::init(EScript::Namespace & lib) {

	declareConstant(&lib,getClassName(),getTypeObject());

	ES_MFUN(getTypeObject(), RegionEvaluator, "init", 3, 3,
		(thisObj->init(
			parameter[0].to<Region*>(rt),
			parameter[1].to<MinSG::GroupNode*>(rt),
			dynamic_cast<GenericAttributeMap*>(E_Util::E_Utils::convertEScriptObjectToGenericAttribute(EScript::assertType<Map>(rt, parameter[2])))
		), EScript::create(nullptr)));

	ES_MFUN(getTypeObject(), RegionEvaluator, "next", 1, 1, thisObj->next(parameter[0].to<uint32_t>(rt)))

	ES_MFUN(getTypeObject(), const Region, "getAttributes", 0, 0, E_Util::E_Utils::convertGenericAttributeToEScriptObject(thisObj->getAttributes()));
	ES_MFUN(getTypeObject(), const Region, "getAttribute", 1, 1, E_Util::E_Utils::convertGenericAttributeToEScriptObject(thisObj->getAttribute(parameter[0].to<std::string>(rt))))
	ES_MFUN(getTypeObject(), Region, "setAttribute", 2, 2, (thisObj->setAttribute( parameter[0].to<std::string>(rt),E_Util::E_Utils::convertEScriptObjectToGenericAttribute(parameter[1])), EScript::create(nullptr)))
	ES_MFUN(getTypeObject(), Region, "unsetAttribute", 1, 1, (thisObj->unsetAttribute(parameter[0].to<std::string>(rt)), EScript::create(nullptr)))

	E_PolygonDensityEvaluator::init(lib);
	E_PolygonCountEvaluator::init(lib);
	E_RegionSizeEvaluator::init(lib);
}

//!!!!!!!!!!!!!!! PolygonDensityEvaluator
Type * E_PolygonDensityEvaluator::getTypeObject(){
	// [E_PolygonDensityEvaluator] ---|> [E_RegionEvaluator] ---|> [Object]
	static EScript::Type * typeObject = new EScript::Type(E_RegionEvaluator::getTypeObject());
	return typeObject;
}
void E_PolygonDensityEvaluator::init(EScript::Namespace & lib) {
	declareConstant(&lib,getClassName(),getTypeObject());
	ES_CTOR(getTypeObject(), 0, 0, EScript::create(new PolygonDensityEvaluator()));
}

//!!!!!!!!!!!!!!! PolygonCountEvaluator
Type * E_PolygonCountEvaluator::getTypeObject(){
	// [E_PolygonCountEvaluator] ---|> [E_RegionEvaluator] ---|> [Object]
	static EScript::Type * typeObject = new EScript::Type(E_RegionEvaluator::getTypeObject());
	return typeObject;
}
void E_PolygonCountEvaluator::init(EScript::Namespace & lib) {
	declareConstant(&lib,getClassName(),getTypeObject());
	ES_CTOR(getTypeObject(), 0,0, EScript::create(new PolygonCountEvaluator()));
}

//!!!!!!!!!!!!!!! RegionSizeEvaluator
Type * E_RegionSizeEvaluator::getTypeObject(){
	// [E_RegionSizeEvaluator] ---|> [E_RegionEvaluator] ---|> [Object]
	static EScript::Type * typeObject = new EScript::Type(E_RegionEvaluator::getTypeObject());
	return typeObject;
}
void E_RegionSizeEvaluator::init(EScript::Namespace & lib) {
	declareConstant(&lib,getClassName(),getTypeObject());
	ES_CTOR(getTypeObject(), 0,0, EScript::create(new RegionSizeEvaluator()));
}

}
}

#endif // MINSG_EXT_MULTIALGORENDERING
