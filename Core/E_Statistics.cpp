/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Statistics.h"

#include <EScript/EScript.h>
#include <MinSG/Ext/OcclusionCulling/OcclusionCullingStatistics.h>

namespace E_MinSG {

EScript::Type * E_Statistics::getTypeObject() {
	// E_Statistics ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

// TODO: countMesh

void E_Statistics::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	using namespace MinSG;
	
	//!	[ESMF] Number MinSG.Statistics.addCounter(String, String)
	ES_MFUN(typeObject, Statistics, "addCounter", 2, 2,						thisObj->addCounter(parameter[0].toString(), parameter[1].toString()))

	//!	[ESMF] Number MinSG.Statistics.getValue(Number)
	ES_MFUN(typeObject, Statistics, "getValue", 1, 1,						thisObj->getValueAsDouble(parameter[0].toUInt()))

	//!	[ESMF] Number MinSG.Statistics.setValue(Number, Number)
	ES_MFUN(typeObject, Statistics,"setValue", 2, 2,
		(thisObj->setValue(parameter[0].toUInt(), parameter[1].toDouble()), thisEObj))

	//!	[ESMF] thisEObj MinSG.Statistics.beginFrame( [frameNumer] )
	ES_MFUNCTION(typeObject, Statistics,"beginFrame",0,1,{
		if(parameter.count()>0)
			thisObj->beginFrame(parameter[0].toInt());
		else
			thisObj->beginFrame();
		return thisEObj;
	})

	//!	[ESMF] thisEObj MinSG.Statistics.endFrame()
	ES_MFUN(typeObject, Statistics, "endFrame", 0, 0,						(thisObj->endFrame(), thisEObj))

	//!	[ESMF] String MinSG.Statistics.getDescription(Number)
	ES_MFUN(typeObject, Statistics, "getDescription", 1, 1,					thisObj->getDescription(parameter[0].toUInt()))

	//!	[ESMF] String MinSG.Statistics.getUnit(Number)
	ES_MFUN(typeObject, Statistics, "getUnit", 1, 1,						thisObj->getUnit(parameter[0].toUInt()))

	//!	[ESMF] Number MinSG.Statistics.getNumCounters()
	ES_MFUN(typeObject, Statistics, "getNumCounters", 0, 0,					static_cast<uint32_t>(thisObj->getNumCounters()))

	//!	[ESMF] [Number|Void] MinSG.Statistics.getCounterForDescription(String)
	ES_MFUNCTION(typeObject, const Statistics, "getCounterForDescription", 1, 1, {
		const auto counterKey = thisObj->getCounterForDescription(parameter[0].toString());
		if(counterKey == MinSG::Statistics::COUNTER_KEY_INVALID) {
			return EScript::create(nullptr);
		}
		return counterKey;
	})

	//!	[ESMF] Number MinSG.Statistics.getFrameDurationCounter()
	ES_MFUN(typeObject,const  Statistics, "getFrameDurationCounter", 0, 0,	thisObj->getFrameDurationCounter())


	//!	[ESMF] Number MinSG.Statistics.getTrianglesCounter()
	ES_MFUN(typeObject, const Statistics, "getTrianglesCounter", 0, 0,		thisObj->getTrianglesCounter())

	//!	[ESMF] Number MinSG.Statistics.getLinesCounter()
	ES_MFUN(typeObject, const Statistics, "getLinesCounter", 0, 0,			thisObj->getLinesCounter())

	//!	[ESMF] Number MinSG.Statistics.getPointsCounter()
	ES_MFUN(typeObject, const Statistics, "getPointsCounter", 0, 0,			thisObj->getPointsCounter())
	
	//!	[ESMF] Number MinSG.Statistics.getVBOCounter()
	ES_MFUN(typeObject, const Statistics, "getVBOCounter", 0, 0,			thisObj->getVBOCounter())
	
	//!	[ESMF] Number MinSG.Statistics.getNodeCounter()
	ES_MFUN(typeObject, const Statistics, "getNodeCounter", 0, 0,			thisObj->getNodeCounter())

	//!	[ESMF] Number MinSG.Statistics.getOccTestCounter()
	ES_MFUN(typeObject, Statistics, "getOccTestCounter", 0, 0,				MinSG::OcclusionCullingStatistics::instance(*thisObj).getOccTestCounter())

	//!	[ESMF] Number MinSG.Statistics.getOccTestVisibleCounter()
	ES_MFUN(typeObject, Statistics, "getOccTestVisibleCounter", 0, 0,		MinSG::OcclusionCullingStatistics::instance(*thisObj).getOccTestVisibleCounter())
	
	//!	[ESMF] Number MinSG.Statistics.getOccTestInvisibleCounter()
	ES_MFUN(typeObject, Statistics, "getOccTestInvisibleCounter", 0, 0,		MinSG::OcclusionCullingStatistics::instance(*thisObj).getOccTestInvisibleCounter())

	//!	[ESMF] Number MinSG.Statistics.getCulledGeometryNodeCounter()
	ES_MFUN(typeObject, Statistics, "getCulledGeometryNodeCounter", 0, 0,	MinSG::OcclusionCullingStatistics::instance(*thisObj).getCulledGeometryNodeCounter())

	//!	[ESMF] bool MinSG.Statistics.areEventsEnabled()
	ES_MFUN(typeObject, const Statistics, "areEventsEnabled", 0, 0, 		thisObj->areEventsEnabled())
			
	//!	[ESMF] thisEObj MinSG.Statistics.enableEvents()
	ES_MFUN(typeObject, Statistics, "enableEvents", 0, 0, 					(thisObj->enableEvents(), thisEObj))

	//!	[ESMF] thisEObj MinSG.Statistics.disableEvents()
	ES_MFUN(typeObject, Statistics, "disableEvents", 0, 0, 					(thisObj->disableEvents(), thisEObj))

}

E_Statistics::E_Statistics(MinSG::Statistics & s, EScript::Type * type) :
	ExtObject(type ? type : getTypeObject()), myStats(s) {
}

E_Statistics::~E_Statistics() {
}

}
