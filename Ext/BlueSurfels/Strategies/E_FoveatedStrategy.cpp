/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_FoveatedStrategy.h"

#include <E_Util/E_Utils.h>

#include <E_Geometry/E_Vec2.h>

#include <EScript/EScript.h>

namespace E_MinSG {
namespace BlueSurfels {
using namespace MinSG::BlueSurfels;

//! (static)
EScript::Type * E_FoveatedStrategy::getTypeObject() {
	// E_FoveatedStrategy ---|> E_AbstractSurfelStrategy ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractSurfelStrategy::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_FoveatedStrategy::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<FoveatedStrategy,E_FoveatedStrategy>();

	//! [ESMF] new FoveatedStrategy
	ES_CTOR(typeObject, 0, 0, new FoveatedStrategy)
    
	//! [ESMF] Bool FoveatedStrategy.getFoveaZones()
	ES_MFUNCTION(typeObject,const FoveatedStrategy,"getFoveaZones",0,0,{
		auto zones = thisObj->getFoveaZones();
		auto a = EScript::Array::create();
		for(const auto& zone : zones) {
			a->pushBack(EScript::Number::create(zone.first));
			a->pushBack(EScript::Number::create(zone.second));
		}
		return a;
	})
	
	//! [ESMF] self FoveatedStrategy.setFoveaZones( Array )
	ES_MFUNCTION(typeObject,FoveatedStrategy,"setFoveaZones",1,1, {
		auto a = parameter[0].to<EScript::Array*>(rt);
		auto zones = thisObj->getFoveaZones();
		zones.clear();
		for(uint32_t i=1; i<a->count(); i+=2) {
			zones.push_back({a->get(i-1)->toFloat(), a->get(i)->toFloat()});
		}
		thisObj->setFoveaZones(zones);
		return thisEObj;
	})
  
  ES_MGETSET(FoveatedStrategy, Geometry::Vec2, Offset)
  ES_MGETSET(FoveatedStrategy, bool, Debug)
}

} /* BlueSurfels */
} /* MinSG */
#endif // MINSG_EXT_BLUE_SURFELS