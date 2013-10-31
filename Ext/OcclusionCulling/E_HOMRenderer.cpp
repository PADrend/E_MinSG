/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_HOMRenderer.h"
#include "../ELibMinSGExt.h"

#include <EScript/EScript.h>

namespace E_MinSG {

EScript::Type * E_HOMRenderer::getTypeObject() {
	// E_HOMRenderer ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

/**
 * initMembers
 */
void E_HOMRenderer::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<MinSG::HOMRenderer,E_HOMRenderer>();

	using namespace MinSG;

	//! [ESF] new MinSG.HOMRenderer([Number])
	ES_CONSTRUCTOR(typeObject, 0, 1, {
		if (parameter.count() == 1) {
			return EScript::create(new MinSG::HOMRenderer(parameter[0].toUInt()));
		} else {
			return EScript::create(new MinSG::HOMRenderer);
		}
	})

	//! [ESMF] Void HOMRenderer.initOccluderDatabase()
	ES_MFUN(typeObject,HOMRenderer, "initOccluderDatabase", 0, 0, (thisObj->initOccluderDatabase(), thisEObj))

	//! [ESMF] Number HOMRenderer.getSideLength()
	ES_MFUN(typeObject,HOMRenderer, "getSideLength", 0, 0, thisObj->getSideLength())
	//! [ESMF] Void HOMRenderer.setSideLength(Number)
	ES_MFUN(typeObject,HOMRenderer, "setSideLength", 1, 1, (thisObj->setSideLength(parameter[0].toUInt()), thisEObj))

	//! [ESMF] Number HOMRenderer.getMinOccluderSize()
	ES_MFUN(typeObject,HOMRenderer, "getMinOccluderSize", 0, 0, thisObj->getMinOccluderSize())
	//! [ESMF] Void HOMRenderer.setMinOccluderSize(Number)
	ES_MFUN(typeObject,HOMRenderer, "setMinOccluderSize", 1, 1, (thisObj->setMinOccluderSize(parameter[0].toDouble()), thisEObj))

	//! [ESMF] Number HOMRenderer.getMaxOccluderComplexity()
	ES_MFUN(typeObject,HOMRenderer, "getMaxOccluderComplexity", 0, 0, thisObj->getMaxOccluderComplexity())
	//! [ESMF] Void HOMRenderer.setMaxOccluderComplexity(Number)
	ES_MFUN(typeObject,HOMRenderer, "setMaxOccluderComplexity", 1, 1, (thisObj->setMaxOccluderComplexity(parameter[0].toUInt()), thisEObj))

	//! [ESMF] Number HOMRenderer.getMaxOccluderDepth()
	ES_MFUN(typeObject,HOMRenderer, "getMaxOccluderDepth", 0, 0, thisObj->getMaxOccluderDepth())
	//! [ESMF] Void HOMRenderer.setMaxOccluderDepth(Number)
	ES_MFUN(typeObject,HOMRenderer, "setMaxOccluderDepth", 1, 1, (thisObj->setMaxOccluderDepth(parameter[0].toDouble()), thisEObj))

	//! [ESMF] Number HOMRenderer.getTriangleLimit()
	ES_MFUN(typeObject,HOMRenderer, "getTriangleLimit", 0, 0, static_cast<double>(thisObj->getTriangleLimit()))
	//! [ESMF] Void HOMRenderer.setTriangleLimit(Number)
	ES_MFUN(typeObject,HOMRenderer, "setTriangleLimit", 1, 1, (thisObj->setTriangleLimit(parameter[0].toUInt()), thisEObj))

	//! [ESMF] Bool HOMRenderer.getShowOnlyOccluders()
	ES_MFUN(typeObject,HOMRenderer, "getShowOnlyOccluders", 0, 0, thisObj->getShowOnlyOccluders())
	//! [ESMF] Void HOMRenderer.setShowOnlyOccluders(Bool)
	ES_MFUN(typeObject,HOMRenderer, "setShowOnlyOccluders", 1, 1, (thisObj->setShowOnlyOccluders(parameter[0].toBool()), thisEObj))

	//! [ESMF] Bool HOMRenderer.getShowHOMPyramid()
	ES_MFUN(typeObject,HOMRenderer, "getShowHOMPyramid", 0, 0, thisObj->getShowHOMPyramid())
	//! [ESMF] Void HOMRenderer.setShowHOMPyramid(Bool)
	ES_MFUN(typeObject,HOMRenderer, "setShowHOMPyramid", 1, 1, (thisObj->setShowHOMPyramid(parameter[0].toBool()), thisEObj))

	//! [ESMF] Bool HOMRenderer.getShowCulledGeometry()
	ES_MFUN(typeObject,HOMRenderer, "getShowCulledGeometry", 0, 0, thisObj->getShowCulledGeometry())
	//! [ESMF] Void HOMRenderer.setShowCulledGeometry(Bool)
	ES_MFUN(typeObject,HOMRenderer, "setShowCulledGeometry", 1, 1, (thisObj->setShowCulledGeometry(parameter[0].toBool()), thisEObj))

}

}
