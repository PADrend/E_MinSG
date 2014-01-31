/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_MULTIALGORENDERING

#include "E_SampleContext.h"

#include "E_SampleRegion.h"
#include "E_SampleStorage.h"

#include "../../Core/E_FrameContext.h"

#include <E_Geometry/E_Vec3.h>
#include <E_Geometry/E_Box.h>

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_MinSG{
	namespace E_MAR{
		
		using namespace MinSG::MAR;

//! (static)
EScript::Type * E_SampleContext::getTypeObject() {
	// E_SampleContext ---|> [ReferenceObject]
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_SampleContext::init(EScript::Namespace & lib) {
	
	declareConstant(&lib,getClassName(),getTypeObject());

	//! [ESF] new SampleContext(Geometry.Box bounds)
	ES_CTOR(getTypeObject(), 1, 1, EScript::create(new SampleContext(parameter[0].to<const Geometry::Box&>(rt))))

	//! [ESMF] SampleRegion SampleContext.getMinSampleRegion()
	ES_MFUN(getTypeObject(),const SampleContext,"getMinSampleRegion",0,0, EScript::create(thisObj->getMinSampleRegion()))

	//! [ESMF] SampleRegion SampleContext.getSampleRegionAtPosition(Geometry.Vec3)
	ES_MFUN(getTypeObject(),const SampleContext,"getSampleRegionAtPosition",1,1, EScript::create(thisObj->getSampleRegionAtPosition(parameter[0].to<Geometry::Vec3>(rt))))

	//! [ESMF] Number SampleContext.getRegionCount()
	ES_MFUN(getTypeObject(),const SampleContext,"getRegionCount",0,0, thisObj->getRegionCount())

	//! [ESMF] void SampleContext.splitLowQualityRegion()
	ES_MFUN(getTypeObject(),SampleContext,"splitLowQualityRegion",0,0, (thisObj->splitLowQualityRegion(), EScript::create(nullptr)))

	//! [ESMF] Number SampleContext.getSampleStorage()
	ES_MFUN(getTypeObject(),const SampleContext,"getSampleStorage",0,0, EScript::create(thisObj->getSampleStorage()))

	//! [ESMF] Number SampleContext.getMemoryUsage()
	ES_MFUN(getTypeObject(),const SampleContext,"getMemoryUsage",0,0, static_cast<double>(thisObj->getMemoryUsage()))

	//! [ESMF] SampleRegion SampleContext.displayRegions(FrameContext, Vec3 position, Number alpha, Number redGreenThreshold)
	ES_MFUN(getTypeObject(), const SampleContext, "displayRegions",3,3, (thisObj->displayRegions(parameter[0].to<MinSG::FrameContext&>(rt),parameter[1].to<float>(rt),parameter[2].to<float>(rt)), thisEObj))

	//! [ESMF] SampleRegion SampleContext.displaySamples(FrameContext, Vec3 position, Number alpha)
	ES_MFUN(getTypeObject(), const SampleContext, "displaySamples",1,1, (thisObj->displaySamples(parameter[0].to<MinSG::FrameContext&>(rt)), thisEObj))
	
	//! [ESMF] Array SampleContext.getSampleRegions()
	ES_MFUN(getTypeObject(), const SampleContext, "getSampleRegions",0,0, EScript::Array::create(thisObj->getSampleRegions()))
}
}}
#endif // MINSG_EXT_MULTIALGORENDERING
