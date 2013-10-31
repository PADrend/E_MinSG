/*
	This file is part of the MinSG library extension Behaviours.
	Copyright (C) 2011 Sascha Brandt
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
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
	EScript::Namespace * nsBlueSurfels = new EScript::Namespace;
	declareConstant(&lib,"BlueSurfels",nsBlueSurfels);
	
	EScript::Type * typeObject = E_SurfelGenerator::getTypeObject();
	declareConstant(nsBlueSurfels,getClassName(),typeObject);

	using namespace MinSG::BlueSurfels;
	
	//!	[ESMF] SurfelGenerator new MinSG.SurfelGenerator
	ES_CTOR(typeObject,0,0,new E_SurfelGenerator(thisType))

	//! [ESMF] ExtObject SurfelGenerator.createSurfels(PixelAccessor,PixelAccessor,PixelAccessor,PixelAccessor)
	ES_MFUNCTION(typeObject,SurfelGenerator,"createSurfels",4,4,{
		const auto surfelResult = thisObj->createSurfels(
												parameter[0].to<Util::PixelAccessor&>(rt),
												parameter[1].to<Util::PixelAccessor&>(rt),
												parameter[2].to<Util::PixelAccessor&>(rt),
												parameter[3].to<Util::PixelAccessor&>(rt));
		static const EScript::StringId meshAttr("mesh");
		static const EScript::StringId relativeCoveringAttr("relativeCovering");
		EScript::ExtObject * result = new EScript::ExtObject;
		result->setAttribute(meshAttr, EScript::create(surfelResult.first.get()));
		result->setAttribute(relativeCoveringAttr, EScript::Number::create(surfelResult.second));
		return result;
	})
		
		
	//! [ESMF] Number SurfelGenerator.getReusalRate()
	ES_MFUN(typeObject,const SurfelGenerator,"getReusalRate",0,0,			thisObj->getReusalRate())

	//! [ESMF] Number SurfelGenerator.getMaxAbsSurfels()
	ES_MFUN(typeObject,const SurfelGenerator,"getMaxAbsSurfels",0,0,		thisObj->getMaxAbsSurfels())
				
	//! [ESMF] self SurfelGenerator.setMaxAbsSurfels(Number)
	ES_MFUN(typeObject,SurfelGenerator,"setMaxAbsSurfels",1,1,				(thisObj->setMaxAbsSurfels(parameter[0].toUInt()),thisEObj))
				
	//! [ESMF] self SurfelGenerator.setReusalRate(Number)
	ES_MFUN(typeObject,SurfelGenerator,"setReusalRate",1,1,					(thisObj->setReusalRate(parameter[0].toFloat()),thisEObj))

}
}

}
#endif // MINSG_EXT_BLUE_SURFELS

