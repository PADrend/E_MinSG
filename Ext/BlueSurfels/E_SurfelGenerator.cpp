/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2012-2013 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2013 Ralf Petring <ralf@petring.net>
	Copyright (C) 2016-2017 Sascha Brandt <myeti@mail.uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_SurfelGenerator.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <E_Util/Graphics/E_PixelAccessor.h>
#include <E_Rendering/Mesh/E_Mesh.h>
#include <E_Rendering/Mesh/E_VertexDescription.h>
#include <Util/Graphics/PixelAccessor.h>

namespace E_MinSG{
namespace BlueSurfels{


//! (static)
EScript::Type * E_SurfelGenerator::getTypeObject() {
	// E_SurfelGenerator ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members 
void E_SurfelGenerator::init(EScript::Namespace & lib) {

	EScript::Type * typeObject = E_SurfelGenerator::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace MinSG::BlueSurfels;
	
	//!	[ESMF] SurfelGenerator new MinSG.SurfelGenerator
	ES_CTOR(typeObject,0,0,new E_SurfelGenerator(thisType))

	//! [ESMF] self SurfelGenerator.clearBenchmarkResults()
	ES_MFUN(typeObject,SurfelGenerator,"clearBenchmarkResults",0,0,			(thisObj->clearBenchmarkResults(),thisEObj))
	
	//! [ESMF] ExtObject SurfelGenerator.createSurfels(PixelAccessor,PixelAccessor,PixelAccessor,PixelAccessor)
	ES_MFUNCTION(typeObject,SurfelGenerator,"createSurfels",4,4,{
		const auto surfelResult = thisObj->createSurfels(
												parameter[0].to<Util::PixelAccessor&>(rt),
												parameter[1].to<Util::PixelAccessor&>(rt),
												parameter[2].to<Util::PixelAccessor&>(rt),
												parameter[3].to<Util::PixelAccessor&>(rt));
		static const EScript::StringId meshAttr("mesh");
		static const EScript::StringId relativeCoveringAttr("relativeCovering");
		static const EScript::StringId minDist("minDist");
		static const EScript::StringId medianDist("medianDist");
		EScript::ExtObject * result = new EScript::ExtObject;
		result->setAttribute(meshAttr, EScript::create(surfelResult.mesh));
		result->setAttribute(relativeCoveringAttr, EScript::Number::create(0));
		result->setAttribute(minDist, EScript::Number::create(surfelResult.minDist));
		result->setAttribute(medianDist, EScript::Number::create(surfelResult.medianDist));
		return result;
	})

	//! [ESMF] Map SurfelGenerator.getBenchmarkResults()
	ES_MFUNCTION(typeObject,const SurfelGenerator,"getBenchmarkResults",0,0,{
		EScript::Map* m = new EScript::Map;
		for(const auto& entry : thisObj->getBenchmarkResults()) // string -> number
			m->setValue( EScript::create(entry.first), EScript::create(entry.second) );
		return m;
	})

	//! [ESMF] Number SurfelGenerator.getMaxAbsSurfels()
	ES_MFUN(typeObject,const SurfelGenerator,"getMaxAbsSurfels",0,0,		thisObj->getMaxAbsSurfels())
	
	//! [ESMF] self SurfelGenerator.setMaxAbsSurfels(Number)
	ES_MFUN(typeObject,SurfelGenerator,"setMaxAbsSurfels",1,1,				(thisObj->setMaxAbsSurfels(parameter[0].toUInt()),thisEObj))
				
	//! [ESMF] self SurfelGenerator.setBenchmarkingEnabled(Bool)
	ES_MFUN(typeObject,SurfelGenerator,"setBenchmarkingEnabled",1,1,		(thisObj->setBenchmarkingEnabled(parameter[0].toBool()),thisEObj))
					
	//! [ESMF] self SurfelGenerator.setVertexDescription(VertexDescription)
	ES_MFUN(typeObject,SurfelGenerator,"setVertexDescription",1,1,	(thisObj->setVertexDescription(parameter[0].to<const Rendering::VertexDescription&>(rt)),thisEObj))
	
	//! [ESMF] Map SurfelGenerator.setParameters(...)
	ES_MFUNCTION(typeObject,SurfelGenerator,"setParameters",1,6,{
		auto* m = parameter[0].toType<EScript::Map>();
		if(parameter.count() == 1 && m) {
			SurfelGenerator::Parameters params;
			params.maxAbsSurfels = m->getValue("maxAbsSurfels") ? m->getValue("maxAbsSurfels")->toUInt() : 10000;
			params.medianDistCount = m->getValue("medianDistCount") ? m->getValue("medianDistCount")->toUInt() : 1000;
			params.samplesPerRound = m->getValue("samplesPerRound") ? m->getValue("samplesPerRound")->toUInt() : 160;
			params.pureRandomStrategy = m->getValue("pureRandomStrategy") ? m->getValue("pureRandomStrategy")->toBool() : false;
			params.guessSurfelSize = m->getValue("guessSurfelSize") ? m->getValue("guessSurfelSize")->toBool() : false;
			params.benchmarkingEnabled = m->getValue("benchmarkingEnabled") ? m->getValue("benchmarkingEnabled")->toBool() : false;
			thisObj->setParameters(params);
		} else {
			thisObj->setParameters({
				parameter[0].toUInt(10000),
				parameter[1].toUInt(1000),
				parameter[2].toUInt(160),
				parameter[3].toBool(false),
				parameter[4].toBool(false),
				parameter[5].toBool(false)
			});
		}
		return thisEObj;
	})
		
	//! [ESMF] Map SurfelGenerator.getParameters()
	ES_MFUNCTION(typeObject,const SurfelGenerator,"getParameters",0,0,{
		const auto p = thisObj->getParameters();		
		EScript::Map* m = new EScript::Map;
		m->setValue( EScript::create("maxAbsSurfels"), EScript::Number::create(p.maxAbsSurfels) );
		m->setValue( EScript::create("medianDistCount"), EScript::Number::create(p.medianDistCount) );
		m->setValue( EScript::create("samplesPerRound"), EScript::Number::create(p.samplesPerRound) );
		m->setValue( EScript::create("pureRandomStrategy"), EScript::Number::create(p.pureRandomStrategy) );
		m->setValue( EScript::create("guessSurfelSize"), EScript::Number::create(p.guessSurfelSize) );
		m->setValue( EScript::create("benchmarkingEnabled"), EScript::Number::create(p.benchmarkingEnabled) );
		return m;
	})
	
	//! [ESMF] ExtObject SurfelGenerator.createSurfelsFromMesh(Rendering.Mesh)
	ES_MFUNCTION(typeObject,SurfelGenerator,"createSurfelsFromMesh",1,2,{
		const auto surfelResult = thisObj->createSurfelsFromMesh(*parameter[0].to<Rendering::Mesh*>(rt), parameter[1].toInt(-1));
		static const EScript::StringId meshAttr("mesh");
		static const EScript::StringId relativeCoveringAttr("relativeCovering");
		static const EScript::StringId minDist("minDist");
		static const EScript::StringId medianDist("medianDist");
		EScript::ExtObject * result = new EScript::ExtObject;
		result->setAttribute(meshAttr, EScript::create(surfelResult.mesh));
		result->setAttribute(relativeCoveringAttr, EScript::Number::create(0));
		result->setAttribute(minDist, EScript::Number::create(surfelResult.minDist));
		result->setAttribute(medianDist, EScript::Number::create(surfelResult.medianDist));
		return result;
	})
	
	
}
}

}
#endif // MINSG_EXT_BLUE_SURFELS

