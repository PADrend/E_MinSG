/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2012-2013 Claudius J�hn <claudius@uni-paderborn.de>
	Copyright (C) 2013 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_StreamedSurfelGenerator.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <E_Util/Graphics/E_PixelAccessor.h>
#include <E_Rendering/Mesh/E_Mesh.h>
#include <Util/Graphics/PixelAccessor.h>

namespace E_MinSG{
namespace BlueSurfels{


//! (static)
EScript::Type * E_StreamedSurfelGenerator::getTypeObject() {
	// E_StreamedSurfelGenerator ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members 
void E_StreamedSurfelGenerator::init(EScript::Namespace & lib) {

	EScript::Type * typeObject = E_StreamedSurfelGenerator::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace MinSG::BlueSurfels;
	
	//!	[ESMF] StreamedSurfelGenerator new MinSG.StreamedSurfelGenerator
	ES_CTOR(typeObject,0,0,new E_StreamedSurfelGenerator(thisType))

	//! [ESMF] self StreamedSurfelGenerator.clearBenchmarkResults()
	ES_MFUN(typeObject,StreamedSurfelGenerator,"clearBenchmarkResults",0,0,			(thisObj->clearBenchmarkResults(),thisEObj))
	
	//! [ESMF] self StreamedSurfelGenerator.createSurfels(PixelAccessor,PixelAccessor,PixelAccessor,PixelAccessor)
	ES_MFUN(typeObject,StreamedSurfelGenerator,"begin",4,4,
			(thisObj->begin(parameter[0].to<Util::PixelAccessor&>(rt),
			parameter[1].to<Util::PixelAccessor&>(rt),
			parameter[2].to<Util::PixelAccessor&>(rt),
			parameter[3].to<Util::PixelAccessor&>(rt)), thisEObj))

	//! [ESMF] bool StreamedSurfelGenerator.step()
	ES_MFUN(typeObject,StreamedSurfelGenerator,"step",0,0, thisObj->step())

	ES_MFUNCTION(typeObject,StreamedSurfelGenerator,"getResult",0,0,{
		const auto surfelResult = thisObj->getResult();
		static const EScript::StringId meshAttr("mesh");
		static const EScript::StringId relativeCoveringAttr("relativeCovering");
		EScript::ExtObject * result = new EScript::ExtObject;
		result->setAttribute(meshAttr, EScript::create(surfelResult.first.get()));
		result->setAttribute(relativeCoveringAttr, EScript::Number::create(surfelResult.second));
		return result;
	})
	
	//! [ESMF] Map StreamedSurfelGenerator.getBenchmarkResults()
	ES_MFUNCTION(typeObject,const StreamedSurfelGenerator,"getBenchmarkResults",0,0,{
		EScript::Map* m = new EScript::Map;
		for(const auto& entry : thisObj->getBenchmarkResults()) // string -> number
			m->setValue( EScript::create(entry.first), EScript::create(entry.second) );
		return m;
	})

	//! [ESMF] Number StreamedSurfelGenerator.getTimeLimit()
	ES_MFUN(typeObject,const StreamedSurfelGenerator,"getTimeLimit",0,0,		thisObj->getTimeLimit())

	//! [ESMF] self StreamedSurfelGenerator.setTimeLimit(Number)
	ES_MFUN(typeObject,StreamedSurfelGenerator,"setTimeLimit",1,1,				(thisObj->setTimeLimit(parameter[0].toFloat()),thisEObj))

	//! [ESMF] Number StreamedSurfelGenerator.getMaxAbsSurfels()
	ES_MFUN(typeObject,const StreamedSurfelGenerator,"getMaxAbsSurfels",0,0,		thisObj->getMaxAbsSurfels())
				
	//! [ESMF] self StreamedSurfelGenerator.setMaxAbsSurfels(Number)
	ES_MFUN(typeObject,StreamedSurfelGenerator,"setMaxAbsSurfels",1,1,				(thisObj->setMaxAbsSurfels(parameter[0].toUInt()),thisEObj))
				
	//! [ESMF] self StreamedSurfelGenerator.setBenchmarkingEnabled(Bool)
	ES_MFUN(typeObject,StreamedSurfelGenerator,"setBenchmarkingEnabled",1,1,		(thisObj->setBenchmarkingEnabled(parameter[0].toBool()),thisEObj))


}
}

}
#endif // MINSG_EXT_BLUE_SURFELS

