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
#include <EScript/Utils/DeprecatedMacros.h>
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

	//! [ESF] new MinSG.SVS.Renderer()
	ES_CTOR(typeObject, 0, 0, EScript::create(new MinSG::SVS::Renderer()))

	//! [ESMF] Number Renderer.getInterpolationMethod()
	ESMF_DECLARE(typeObject, const E_Renderer, "getInterpolationMethod", 0, 0, EScript::Number::create((**self)->getInterpolationMethod()))

	//! [ESMF] self Renderer.setInterpolationMethod(Number)
	ES_MFUNCTION_DECLARE(typeObject, E_Renderer, "setInterpolationMethod", 1, 1, {
		const uint32_t interpolationValue = parameter[0].to<uint32_t>(runtime);
		(**self)->setInterpolationMethod(MinSG::SVS::interpolationFromUInt(interpolationValue));
		return self;
	})

	//! [ESMF] Bool Renderer.isSphereOcclusionTestEnabled()
	ESMF_DECLARE(typeObject, const E_Renderer, "isSphereOcclusionTestEnabled", 0, 0, EScript::Bool::create((**self)->isSphereOcclusionTestEnabled()))

	//! [ESMF] self Renderer.enableSphereOcclusionTest()
	ESMF_DECLARE(typeObject, E_Renderer, "enableSphereOcclusionTest", 0, 0, ((**self)->enableSphereOcclusionTest(), self))

	//! [ESMF] self Renderer.disableSphereOcclusionTest()
	ESMF_DECLARE(typeObject, E_Renderer, "disableSphereOcclusionTest", 0, 0, ((**self)->disableSphereOcclusionTest(), self))

	//! [ESMF] Bool Renderer.isGeometryOcclusionTestEnabled()
	ESMF_DECLARE(typeObject, const E_Renderer, "isGeometryOcclusionTestEnabled", 0, 0, EScript::Bool::create((**self)->isGeometryOcclusionTestEnabled()))

	//! [ESMF] self Renderer.enableGeometryOcclusionTest()
	ESMF_DECLARE(typeObject, E_Renderer, "enableGeometryOcclusionTest", 0, 0, ((**self)->enableGeometryOcclusionTest(), self))

	//! [ESMF] self Renderer.disableGeometryOcclusionTest()
	ESMF_DECLARE(typeObject, E_Renderer, "disableGeometryOcclusionTest", 0, 0, ((**self)->disableGeometryOcclusionTest(), self))

}

E_Renderer::E_Renderer(MinSG::SVS::Renderer * renderer) :
		E_NodeRendererState(renderer, E_Renderer::getTypeObject()) {
}

E_Renderer::~E_Renderer() {
}

}
}

#endif /* MINSG_EXT_SVS */
