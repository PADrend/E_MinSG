/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_StatChart.h"

#include "../../Core/E_Statistics.h"
#include "../ELibMinSGExt.h"
#include <E_Util/Graphics/E_Bitmap.h>
#include <E_Util/Graphics/E_Color.h>
#include <Util/Graphics/Bitmap.h>
#include <EScript/EScript.h>

namespace E_MinSG {

//! (static)
EScript::Type * E_StatChart::getTypeObject() {
	// MinSG.StatChart ----|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(Object::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_StatChart::init(EScript::Namespace & lib) {
	auto typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());	
	declareConstant(&lib,getClassName(),typeObject);
	
	using namespace MinSG;

	//! [ESMF] MinSG.StatChart new MinSG.StatChart(width,height,timeRange)
	ES_CTOR(typeObject,3,3,									new E_StatChart(parameter[0].toInt(),parameter[1].toInt(),parameter[2].toFloat()))

	//! [ESMF] self MinSG.StatChart.update(Statistics)
	ES_MFUN(typeObject, StatChart,"update",1,1,				(thisObj->update( parameter[0].to<const MinSG::Statistics&>(rt)), thisEObj))

	//! [ESMF] number MinSG.StatChart.getWidth()
	ES_MFUN(typeObject,const  StatChart,"getWidth",0,0,		(thisObj->getWidth()))

	//! [ESMF] number MinSG.StatChart.getHeight()
	ES_MFUN(typeObject, const StatChart,"getHeight",0,0,	(thisObj->getHeight()))

	//! [ESMF] ImagePtr MinSG.StatChart.getBitmap()
	ES_MFUN(typeObject, const StatChart,"getBitmap",0,0,	EScript::create(thisObj->getBitmap()))

	//! [ESMF] Number MinSG.StatChart.getTimeRange()
	ES_MFUN(typeObject, const StatChart,"getTimeRange",0,0,	(thisObj->getTimeRange()))

	//! [ESMF] self MinSG.StatChart.setTimeRange(number)
	ES_MFUN(typeObject, StatChart,"setTimeRange",1,1,		(thisObj->setTimeRange(parameter[0].toFloat()),thisEObj))

	//! [ESMF] Number MinSG.StatChart.getRowCount()
	ES_MFUN(typeObject, const StatChart,"getRowCount",0,0,	(thisObj->getRowCount()))

	//!	[ESMF] String MinSG.StatChart.getDescription(row)
	ES_MFUN(typeObject, const StatChart,"getDescription",1,1,	(thisObj->getDescription(parameter[0].toInt())))

	//! [ESMF] self MinSG.StatChart.setDescription(row,description)
	ES_MFUN(typeObject, StatChart,"setDescription",2,2,		(thisObj->setDescription(parameter[0].toInt(),parameter[1].toString()),thisEObj))

	//! [ESMF] Number MinSG.StatChart.getRange(row)
	ES_MFUN(typeObject, const StatChart,"getRange",1,1,		(thisObj->getRange(parameter[0].toInt())))

	//! [ESMF] self MinSG.StatChart.setRange(row,range)
	ES_MFUN(typeObject, StatChart,"setRange",2,2,			(thisObj->setRange(parameter[0].toInt(),parameter[1].toFloat()),thisEObj))

	//! [ESMF] Color4f MinSG.StatChart.getColor(row)
	ES_MFUNCTION(typeObject, const StatChart,"getColor",1,1, {
		auto color = thisObj->getColor(parameter[0].toInt());
		return EScript::create(color);
	})

	//! [ESMF] self MinSG.StatChart.setColor(row,range)
	ES_MFUN(typeObject, StatChart,"setColor",2,2,			(thisObj->setColor(parameter[0].toInt(),*parameter[1].to<Util::Color4ub*>(rt)),thisEObj))
}

//---

//! [ctor]
E_StatChart::E_StatChart(int width,int height,float timeScale,EScript::Type * type):
		ReferenceObject( MinSG::StatChart(width,height,timeScale),type?type:getTypeObject()) {
}

//! [dtor]
E_StatChart::~E_StatChart() = default;

}
