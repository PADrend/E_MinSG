/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_MULTIALGORENDERING

#include "E_SampleRegion.h"

#include "E_SampleContext.h"
#include "E_SampleStorage.h"

#include <E_Geometry/E_Box.h>
#include <E_Geometry/E_Vec3.h>

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_MinSG{
	namespace E_MAR{
		
		using namespace MinSG::MAR;

//! (static)
EScript::Type * E_SampleRegion::getTypeObject() {
	// E_SampleRegion ---|> [ReferenceObject]
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_SampleRegion::init(EScript::Namespace & lib) {
	
	declareConstant(&lib,getClassName(),getTypeObject());

	//! [ESMF] Number SampleRegion.getSampleCount()
	ES_MFUN(getTypeObject(),const SampleRegion,"getSampleCount",0,0, thisObj->getSampleCount())

	//! [ESMF] Geometry.Box SampleRegion.getBounds()
	ES_MFUN(getTypeObject(),const SampleRegion,"getBounds",0,0, EScript::create(thisObj->getBounds()))

	//! [ESMF] Geometry.Vec3 SampleRegion.createSamplePosition([SampleContext, Geometry.Vec3])
	ES_MFUNCTION(getTypeObject(),SampleRegion,"createSamplePosition",1,1,{
		if(parameter[0].toType<E_SampleContext>())
			return EScript::create(thisObj->createSamplePosition(parameter[0].to<SampleContext*>(rt)));
		else
			return EScript::create(thisObj->createSamplePosition(parameter[0].to<const Geometry::Vec3&>(rt)));
		
	})

	//! [ESMF] EScript::create(nullptr) SampleRegion.addSample(SampleResult)
	ES_MFUN(getTypeObject(),SampleRegion,"addSample",1,1, (thisObj->addSample(parameter[0].to<SampleResult*>(rt)), EScript::create(nullptr)))

	//! [ESMF] EScript::create(nullptr) SampleRegion.finalizeSample(SampleContext)
	ES_MFUN(getTypeObject(),SampleRegion,"finalizeSample",1,1, (thisObj->finalizeSample(parameter[0].to<SampleContext*>(rt)), EScript::create(nullptr)))
	
	ES_MFUN(getTypeObject(),SampleRegion,"debug",1,1, thisObj->debug(parameter[0].to<SampleContext*>(rt)))
}

}
}
#endif // MINSG_EXT_MULTIALGORENDERING
