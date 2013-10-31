/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_VISIBILITY_SUBDIVISION

#include "E_VisibilitySubdivisionRenderer.h"
#include "../ValuatedRegion/E_ValuatedRegionNode.h"
#include "../../Core/E_FrameContext.h"
#include "../../SceneManagement/E_SceneManager.h"

#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/EScript.h>
#include <E_Geometry/E_Box.h>
#include <E_Geometry/E_Vec3.h>
#include <E_Util/E_Utils.h>

namespace E_MinSG {
using namespace EScript;

EScript::Type * E_VisibilitySubdivisionRenderer::typeObject = nullptr;

/**
 * initMembers
 */
void E_VisibilitySubdivisionRenderer::init(EScript::Namespace & lib) {
	/// [E_VisibilitySubdivisionRenderer] ---|> [E_State] ---|> [E_GroupNode] ---|> [E_Node]
	typeObject = new EScript::Type(E_State::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::VisibilitySubdivision::VisibilitySubdivisionRenderer,E_VisibilitySubdivisionRenderer>();

	using namespace MinSG::VisibilitySubdivision;

	//! [ESMF] VisibilitySubdivisionRenderer new VisibilitySubdivisionRenderer()
	ES_CTOR(typeObject, 0, 0, EScript::create(new MinSG::VisibilitySubdivision::VisibilitySubdivisionRenderer()));

	//! [ESMF] Void VisibilitySubdivisionRenderer.setViSu(E_ValuatedRegionNode)
	ES_MFUN(typeObject, VisibilitySubdivisionRenderer, "setViSu", 1, 1, (thisObj->setViSu((**EScript::assertType<E_ValuatedRegionNode>(rt, parameter[0]))), thisEObj))

	//! [ESMF] Void VisibilitySubdivisionRenderer.setMaximumRuntime(Number)
	ES_MFUN(typeObject, VisibilitySubdivisionRenderer, "setMaximumRuntime", 1, 1, (thisObj->setMaximumRuntime(parameter[0].toUInt()), thisEObj))

	//! [ESMF] Number VisibilitySubdivisionRenderer.getMaximumRuntime()
	ES_MFUN(typeObject, VisibilitySubdivisionRenderer, "getMaximumRuntime", 0, 0, Number::create(thisObj->getMaximumRuntime()));

	//! [ESMF] Void VisibilitySubdivisionRenderer.setHold(Bool)
	ES_MFUN(typeObject, VisibilitySubdivisionRenderer, "setHold", 1, 1, (thisObj->setHold(parameter[0].toBool()), thisEObj))

	//! [ESMF] Bool VisibilitySubdivisionRenderer.getHold()
	ES_MFUN(typeObject, VisibilitySubdivisionRenderer, "getHold", 0, 0, Bool::create(thisObj->getHold()));

	//! [ESMF] Void VisibilitySubdivisionRenderer.setDebugOutput(Bool)
	ES_MFUN(typeObject, VisibilitySubdivisionRenderer, "setDebugOutput", 1, 1, (thisObj->setDebugOutput(parameter[0].toBool()), thisEObj))

	//! [ESMF] Bool VisibilitySubdivisionRenderer.getDebugOutput()
	ES_MFUN(typeObject, VisibilitySubdivisionRenderer, "getDebugOutput", 0, 0, Bool::create(thisObj->getDebugOutput()));

	//! [ESMF] Void VisibilitySubdivisionRenderer.setAccumRendering(Bool)
	ES_MFUN(typeObject, VisibilitySubdivisionRenderer, "setAccumRendering", 1, 1, (thisObj->setAccumRendering(parameter[0].toBool()), EScript::create(nullptr)))

	//! [ESMF] Bool VisibilitySubdivisionRenderer.getAccumRendering()
	ES_MFUN(typeObject, VisibilitySubdivisionRenderer, "getAccumRendering", 0, 0, Bool::create(thisObj->getAccumRendering()))

	//! [ESF] Bool VisibilitySubdivisionRenderer.renderCellSubset(FrameContext, ValuatedRegionNode, Number, Number)
	ES_FUNCTION2(typeObject, "renderCellSubset", 4, 4, {
		MinSG::FrameContext & context = parameter[0].to<MinSG::FrameContext&>(rt);
		MinSG::ValuatedRegionNode * vrn = (**EScript::assertType<E_ValuatedRegionNode>(rt, parameter[1]));
		return Bool::create(MinSG::VisibilitySubdivision::VisibilitySubdivisionRenderer::renderCellSubset(context, vrn, parameter[2].toUInt(), parameter[3].toUInt()));
	});

	//! [ESMF] Void VisibilitySubdivisionRenderer.setUseTexturedDepthMeshes(Bool)
	ES_MFUN(typeObject, VisibilitySubdivisionRenderer, "setUseTexturedDepthMeshes", 1, 1, (thisObj->setUseTexturedDepthMeshes(parameter[0].toBool()), thisEObj))

	//! [ESMF] Bool VisibilitySubdivisionRenderer.getUseTexturedDepthMeshes()
	ES_MFUN(typeObject, VisibilitySubdivisionRenderer, "getUseTexturedDepthMeshes", 0, 0, Bool::create(thisObj->getUseTexturedDepthMeshes()));

	//! [ESMF] Number VisibilitySubdivisionRenderer.getPolygonOffsetFactor()
	ES_MFUN(typeObject, VisibilitySubdivisionRenderer, "getPolygonOffsetFactor", 0, 0, EScript::Number::create(thisObj->getPolygonOffsetFactor()));

	//! [ESMF] Void VisibilitySubdivisionRenderer.setPolygonOffsetFactor(Number)
	ES_MFUN(typeObject, VisibilitySubdivisionRenderer, "setPolygonOffsetFactor", 1, 1, (thisObj->setPolygonOffsetFactor(parameter[0].toFloat()), thisEObj))

	//! [ESMF] Number VisibilitySubdivisionRenderer.getPolygonOffsetUnits()
	ES_MFUN(typeObject, VisibilitySubdivisionRenderer, "getPolygonOffsetUnits", 0, 0, EScript::Number::create(thisObj->getPolygonOffsetUnits()));

	//! [ESMF] Void VisibilitySubdivisionRenderer.setPolygonOffsetUnits(Number)
	ES_MFUN(typeObject, VisibilitySubdivisionRenderer, "setPolygonOffsetUnits", 1, 1, (thisObj->setPolygonOffsetUnits(parameter[0].toFloat()), thisEObj))
}

// ------------------------------------------------------------

/**
 * [ctor]
 */
E_VisibilitySubdivisionRenderer::E_VisibilitySubdivisionRenderer(MinSG::VisibilitySubdivision::VisibilitySubdivisionRenderer * gNode, EScript::Type * type) :
		E_State(gNode, type ? type : typeObject) {
}

/**
 * [dtor]
 */
E_VisibilitySubdivisionRenderer::~E_VisibilitySubdivisionRenderer() {
}

}

#endif // MINSG_EXT_VISIBILITY_SUBDIVISION
