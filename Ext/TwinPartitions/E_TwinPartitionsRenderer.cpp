/*
	This file is part of the E_MinSG library extension TwinPartitions.
	Copyright (C) 2010-2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_TWIN_PARTITIONS

#include "E_TwinPartitionsRenderer.h"
#include "../ValuatedRegion/E_ValuatedRegionNode.h"
#include "../../SceneManagement/E_SceneManager.h"

#include <EScript/EScript.h>
#include <E_Geometry/E_Box.h>
#include <E_Geometry/E_Vec3.h>
#include <E_Util/E_Utils.h>

namespace E_MinSG {

EScript::Type * E_TwinPartitionsRenderer::typeObject = nullptr;

void E_TwinPartitionsRenderer::init(EScript::Namespace & lib) {
	using namespace MinSG::TwinPartitions;

	/// [E_TwinPartitionsRenderer] ---|> [E_State]
	typeObject = new EScript::Type(E_State::getTypeObject());
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<TwinPartitionsRenderer, E_TwinPartitionsRenderer>();

	//! [ESMF] Bool TwinPartitionsRenderer.getDrawTexturedDepthMeshes()
	ES_MFUN(typeObject, TwinPartitionsRenderer, "getDrawTexturedDepthMeshes", 0, 0, EScript::Bool::create(thisObj->getDrawTexturedDepthMeshes()));

	//! [ESMF] Number TwinPartitionsRenderer.getMaximumRuntime()
	ES_MFUN(typeObject, TwinPartitionsRenderer, "getMaximumRuntime", 0, 0, EScript::Number::create(thisObj->getMaximumRuntime()));

	//! [ESMF] Number TwinPartitionsRenderer.getPolygonOffsetFactor()
	ES_MFUN(typeObject, TwinPartitionsRenderer, "getPolygonOffsetFactor", 0, 0, EScript::Number::create(thisObj->getPolygonOffsetFactor()));

	//! [ESMF] Number TwinPartitionsRenderer.getPolygonOffsetUnits()
	ES_MFUN(typeObject, TwinPartitionsRenderer, "getPolygonOffsetUnits", 0, 0, EScript::Number::create(thisObj->getPolygonOffsetUnits()));

	//! [ESMF] self TwinPartitionsRenderer.setDrawTexturedDepthMeshes(Bool)
	ES_MFUN(typeObject, TwinPartitionsRenderer, "setDrawTexturedDepthMeshes", 1, 1, (thisObj->setDrawTexturedDepthMeshes(parameter[0].toBool()), thisEObj));

	//! [ESMF] self TwinPartitionsRenderer.setMaximumRuntime(Number)
	ES_MFUN(typeObject, TwinPartitionsRenderer, "setMaximumRuntime", 1, 1, (thisObj->setMaximumRuntime(parameter[0].toUInt()), thisEObj));

	//! [ESMF] self TwinPartitionsRenderer.setPolygonOffsetFactor(Number)
	ES_MFUN(typeObject, TwinPartitionsRenderer, "setPolygonOffsetFactor", 1, 1, (thisObj->setPolygonOffsetFactor(parameter[0].toFloat()), thisEObj));

	//! [ESMF] self TwinPartitionsRenderer.setPolygonOffsetUnits(Number)
	ES_MFUN(typeObject, TwinPartitionsRenderer, "setPolygonOffsetUnits", 1, 1, (thisObj->setPolygonOffsetUnits(parameter[0].toFloat()), thisEObj));
}

}

#endif /* MINSG_EXT_TWIN_PARTITIONS */
