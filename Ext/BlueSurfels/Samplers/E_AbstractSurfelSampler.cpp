/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_AbstractSurfelSampler.h"

#include <E_Rendering/Mesh/E_Mesh.h>

#include <E_Util/E_Utils.h>

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_MinSG {
namespace BlueSurfels {
using namespace MinSG::BlueSurfels;

//! (static)
E_Util::E_ObjectFactory<AbstractSurfelSampler,E_AbstractSurfelSampler> E_AbstractSurfelSampler::factorySystem;

// ----------------------------------------------------------------------

EScript::Type * E_AbstractSurfelSampler::getTypeObject() {
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

// ----------------------------------------------------------------------

//! [static] initMembers
void E_AbstractSurfelSampler::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<AbstractSurfelSampler,E_AbstractSurfelSampler>();

	// -----------------------------------
  
	//! [ESMF] Mesh AbstractSurfelSampler.sampleSurfels(Mesh sourceMesh)
	ES_MFUN(typeObject,AbstractSurfelSampler,"sampleSurfels",1,1, EScript::create(thisObj->sampleSurfels(parameter[0].to<Rendering::Mesh*>(rt))))
  
	//! [ESMF] Mesh AbstractSurfelSampler.finalizeMesh(Mesh sourceMesh, Array indices)    
	ES_FUNCTION(typeObject, "finalizeMesh", 2, 2, {
		auto* mesh = parameter[0].to<Rendering::Mesh*>(rt);
		auto* array = parameter[1].to<EScript::Array*>(rt);
		std::vector<uint32_t> indices;
		for(uint32_t i=0; i<array->count(); ++i)
			indices.emplace_back(array->at(i).toUInt());
		return EScript::create(AbstractSurfelSampler::finalizeMesh(mesh, indices));
	})
  
	//! [ESMF] self AbstractSurfelSampler.clearStatistics()
	ES_MFUN(typeObject,AbstractSurfelSampler,"clearStatistics",0,0, (thisObj->clearStatistics(),thisEObj))
  
	//! [ESMF] Map AbstractSurfelSampler.getStatistics()
	ES_MFUNCTION(typeObject,const AbstractSurfelSampler,"getStatistics",0,0, {
		auto* m = new EScript::Map;
		for(const auto& entry : thisObj->getStatistics()) // string -> number
			m->setValue(EScript::create(entry.first), EScript::create(entry.second));
		return m;
	})
  
  ES_MGETSET(AbstractSurfelSampler, uint32_t, TargetCount)
  ES_MGETSET(AbstractSurfelSampler, uint32_t, Seed)
  ES_MGETSET(AbstractSurfelSampler, bool, StatisticsEnabled)
}

} /* BlueSurfels */
} /* MinSG */
#endif // MINSG_EXT_BLUE_SURFELS