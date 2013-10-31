/*
	This file is part of the E_MinSG library extension SphericalSampling.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SPHERICALSAMPLING

#include "E_Helper.h"
#include "E_SamplingSphere.h"
#include "../../Core/Nodes/E_CameraNodeOrtho.h"
#include "../../Core/Nodes/E_GroupNode.h"
#include "../../ELibMinSG.h"
#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <E_Geometry/E_Matrix4x4.h>
#include <E_Geometry/E_Sphere.h>
#include <E_Geometry/E_Vec3.h>
#include <E_Rendering/Texture/E_Texture.h>
#include <MinSG/Core/Nodes/AbstractCameraNode.h>
#include <MinSG/Core/Nodes/CameraNodeOrtho.h>
#include <MinSG/Ext/SphericalSampling/Definitions.h>
#include <MinSG/Ext/SphericalSampling/Helper.h>
#include <MinSG/Ext/SphericalSampling/SamplingSphere.h>
#include <vector>

using namespace MinSG::SphericalSampling;

namespace E_MinSG {
namespace SphericalSampling {
namespace E_Helper {

void init(EScript::Namespace & lib) {
	declareConstant(&lib, "INTERPOLATION_NEAREST", EScript::Number::create(INTERPOLATION_NEAREST));
	declareConstant(&lib, "INTERPOLATION_MAX3", EScript::Number::create(INTERPOLATION_MAX3));
	declareConstant(&lib, "INTERPOLATION_MAXALL", EScript::Number::create(INTERPOLATION_MAXALL));
	declareConstant(&lib, "INTERPOLATION_WEIGHTED3", EScript::Number::create(INTERPOLATION_WEIGHTED3));

	//! [ESF] CameraNodeOrtho SphericalSampling.createSamplingCamera(Sphere, Matrix4x4, Number)
	ES_FUN(&lib, "createSamplingCamera", 3, 3,
				EScript::create(createSamplingCamera(
					parameter[0].to<const Geometry::Sphere_f&>(rt),
					parameter[1].to<const Geometry::Matrix4x4&>(rt),
					parameter[2].to<int32_t>(rt)
				)))

	//! [ESF] Void SphericalSampling.transformCamera(AbstractCameraNode, Sphere, Matrix4x4, Vec3)
	ES_FUN(&lib, "transformCamera", 4, 4,
				(transformCamera(
					**EScript::assertType<E_AbstractCameraNode>(rt, parameter[0]),
					parameter[1].to<const Geometry::Sphere_f&>(rt),
					parameter[2].to<const Geometry::Matrix4x4&>(rt),
					parameter[3].to<const Geometry::Vec3&>(rt)
				 ), EScript::create(nullptr)))

	//! [ESF] Texture SphericalSampling.createColorTexture(Number, Number, SamplingSphere, Number)
	ES_FUNCTION2(&lib, "createColorTexture", 4, 4, {
		const uint32_t width = parameter[0].to<uint32_t>(rt);
		const uint32_t height = parameter[1].to<uint32_t>(rt);
		const SamplingSphere & samplingSphere = EScript::assertType<E_SamplingSphere>(rt, parameter[2])->ref();
		const interpolation_type_t interpolation = interpolationFromUInt(parameter[3].to<uint32_t>(rt));
		return new E_Rendering::E_Texture(createColorTexture(width, height, samplingSphere, interpolation));
	})

	//! [ESF] Bool SphericalSampling.hasSamplingSphere(GroupNode)
	ES_FUN(&lib, "hasSamplingSphere", 1, 1, 
		EScript::Bool::create(hasSamplingSphere(parameter[0].to<MinSG::GroupNode*>(rt)))
	)

	//! [ESF] SamplingSphere SphericalSampling.retrieveSamplingSphere(GroupNode)
	ES_FUN(&lib, "retrieveSamplingSphere", 1, 1, 
		new E_SamplingSphere(retrieveSamplingSphere(parameter[0].to<MinSG::GroupNode *>(rt)))
	)

	//! [ESF] Number SphericalSampling.getSphereMemoryUsage(GroupNode)
	ES_FUN(&lib, "getSphereMemoryUsage", 1, 1, 
		static_cast<double>(retrieveSamplingSphere(parameter[0].to<MinSG::GroupNode *>(rt)).getMemoryUsage())
	)

	//! [ESF] Sphere SphericalSampling.transformSphere(Sphere, Matrix4x4)
	ES_FUN(&lib, "transformSphere", 2, 2,
				new E_Geometry::E_Sphere(transformSphere(
					parameter[0].to<const Geometry::Sphere_f&>(rt),
					parameter[1].to<const Geometry::Matrix4x4&>(rt))))

	//! [ESF] Void SphericalSampling.transformSpheresFromWorldToLocal(GroupNode)
	ES_FUN(&lib, "transformSpheresFromWorldToLocal", 1, 1, 
		(transformSpheresFromWorldToLocal(parameter[0].to<MinSG::GroupNode*>(rt)), EScript::create(nullptr))
	)
}

}
}
}

#endif /* MINSG_EXT_SPHERICALSAMPLING */
