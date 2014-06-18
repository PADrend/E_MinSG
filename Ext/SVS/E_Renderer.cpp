/*
	This file is part of the E_MinSG library extension SVS.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SVS

#include "E_Renderer.h"
#include "../../ELibMinSG.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <MinSG/Ext/SVS/Definitions.h>
#include <MinSG/Ext/SVS/Helper.h>
#include <MinSG/Ext/SVS/Renderer.h>
#include <cstdint>

namespace E_MinSG {
namespace SVS {

EScript::Type * E_Renderer::getTypeObject() {
	// E_Renderer ---|> E_NodeRendererState ---|> E_State
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	return typeObject.get();
}

void E_Renderer::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Renderer::getTypeObject();
	declareConstant(&lib, "Renderer", typeObject);
	addFactory<MinSG::SVS::Renderer, E_Renderer>();

	using namespace MinSG::SVS;
	
	//! [ESF] new MinSG.SVS.Renderer()
	ES_CTOR(typeObject, 0, 0, EScript::create(new MinSG::SVS::Renderer()))

	//! [ESMF] Number Renderer.getInterpolationMethod()
	ES_MFUN(typeObject, const Renderer, "getInterpolationMethod", 0, 0, static_cast<uint32_t>(thisObj->getInterpolationMethod()))

	//! [ESMF] self Renderer.setInterpolationMethod(Number)
	ES_MFUNCTION(typeObject, Renderer, "setInterpolationMethod", 1, 1, {
		const uint32_t interpolationValue = parameter[0].to<uint32_t>(rt);
		thisObj->setInterpolationMethod(MinSG::SVS::interpolationFromUInt(interpolationValue));
		return thisEObj;
	})

	//! [ESMF] Bool Renderer.isSphereOcclusionTestEnabled()
	ES_MFUN(typeObject, const Renderer, "isSphereOcclusionTestEnabled", 0, 0, thisObj->isSphereOcclusionTestEnabled())

	//! [ESMF] self Renderer.enableSphereOcclusionTest()
	ES_MFUN(typeObject, Renderer, "enableSphereOcclusionTest", 0, 0, (thisObj->enableSphereOcclusionTest(), thisEObj))

	//! [ESMF] self Renderer.disableSphereOcclusionTest()
	ES_MFUN(typeObject, Renderer, "disableSphereOcclusionTest", 0, 0, (thisObj->disableSphereOcclusionTest(), thisEObj))

	//! [ESMF] Bool Renderer.isGeometryOcclusionTestEnabled()
	ES_MFUN(typeObject, const Renderer, "isGeometryOcclusionTestEnabled", 0, 0, thisObj->isGeometryOcclusionTestEnabled())

	//! [ESMF] self Renderer.enableGeometryOcclusionTest()
	ES_MFUN(typeObject, Renderer, "enableGeometryOcclusionTest", 0, 0, (thisObj->enableGeometryOcclusionTest(), thisEObj))

	//! [ESMF] self Renderer.disableGeometryOcclusionTest()
	ES_MFUN(typeObject, Renderer, "disableGeometryOcclusionTest", 0, 0, (thisObj->disableGeometryOcclusionTest(), thisEObj))

}

E_Renderer::E_Renderer(MinSG::SVS::Renderer * renderer) :
		E_NodeRendererState(renderer, E_Renderer::getTypeObject()) {
}

E_Renderer::~E_Renderer() {
}

}
}

#endif /* MINSG_EXT_SVS */
