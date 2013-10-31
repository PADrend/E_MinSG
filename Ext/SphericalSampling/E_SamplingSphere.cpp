/*
	This file is part of the E_MinSG library extension SphericalSampling.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SPHERICALSAMPLING

#include "E_SamplingSphere.h"
#include "E_SamplePoint.h"
#include "../Evaluator/E_Evaluator.h"
#include "../Triangulation/E_Delaunay3d.h"
#include "../VisibilitySubdivision/E_VisibilityVector.h"
#include "../../Core/Nodes/E_CameraNodeOrtho.h"
#include "../../Core/Nodes/E_Node.h"
#include "../../Core/E_FrameContext.h"
#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <E_Geometry/E_Sphere.h>
#include <E_Geometry/E_Vec3.h>
#include <E_Util/E_Utils.h>
#include <Geometry/Sphere.h>
#include <Geometry/Vec3.h>
#include <MinSG/Core/Nodes/ListNode.h>
#include <MinSG/Ext/SphericalSampling/Definitions.h>
#include <MinSG/Ext/SphericalSampling/Helper.h>
#include <MinSG/Ext/SphericalSampling/SamplingSphere.h>
#include <Util/GenericAttribute.h>
#include <Util/References.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace MinSG::SphericalSampling;

namespace MinSG {
namespace VisibilitySubdivision {
class VisibilityVector;
}
}
namespace E_MinSG {
namespace SphericalSampling {

EScript::Type * E_SamplingSphere::getTypeObject() {
	// E_SamplingSphere ---|> ExtObject
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::ExtObject::getTypeObject());
	return typeObject.get();
}

void E_SamplingSphere::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_SamplingSphere::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	//! [ESF] new SamplingSphere(Sphere, Array)
	ES_CONSTRUCTOR(typeObject, 2, 2, {
		const Geometry::Sphere_f & sphere = parameter[0].to<const Geometry::Sphere_f&>(rt);
		EScript::Array * array = parameter[1].to<EScript::Array*>(rt);
		std::vector<SamplePoint> samples;
		samples.reserve(array->size());
		for(EScript::Array::iterator it = array->begin(); it != array->end(); ++it) {
			samples.emplace_back(EScript::assertType<E_SamplePoint>(rt, *it)->ref());
		}
		return new E_SamplingSphere(SamplingSphere(sphere, samples));
	})

	//! [ESMF] Sphere SamplingSphere.getSphere()
	ESMF_DECLARE(typeObject, const E_SamplingSphere, "getSphere", 0, 0,
				new E_Geometry::E_Sphere((**self).getSphere()))

	//! [ESMF] Array SamplingSphere.getSamples()
	ES_MFUNCTION_DECLARE(typeObject, const E_SamplingSphere, "getSamples", 0, 0, {
		const std::vector<SamplePoint> & samples = (**self).getSamples();
		EScript::Array * array = EScript::Array::create();
		array->reserve(samples.size());
		for(std::vector<SamplePoint>::const_iterator it = samples.begin(); it != samples.end(); ++it) {
			array->pushBack(new E_SamplePoint(*it));
		}
		return array;
	})

	//! [ESMF] Sphere SamplingSphere.getMemoryUsage()
	ESMF_DECLARE(typeObject, const E_SamplingSphere, "getMemoryUsage", 0, 0,
				static_cast<double>((**self).getMemoryUsage()))

	//! [ESMF] Node SamplingSphere.getTriangulationMinSGNodes()
	ESMF_DECLARE(typeObject, const E_SamplingSphere, "getTriangulationMinSGNodes", 0, 0, 
				EScript::create((**self).getTriangulationMinSGNodes()))

	//! [ESMF] self SamplingSphere.evaluateAllSamples(FrameContext, Evaluator, CameraNodeOrtho, Node)
	ES_MFUNCTION_DECLARE(typeObject, E_SamplingSphere, "evaluateAllSamples", 4, 4, {
		MinSG::FrameContext & frameContext = parameter[0].to<MinSG::FrameContext&>(runtime);
		MinSG::Evaluators::Evaluator * evaluator = parameter[1].to<MinSG::Evaluators::Evaluator*>(runtime);
		Util::Reference<MinSG::CameraNodeOrtho> camera = **EScript::assertType<E_CameraNodeOrtho>(runtime, parameter[2]);
		Util::Reference<MinSG::Node> node = parameter[3].to<MinSG::Node*>(runtime);
		(**self).evaluateAllSamples(frameContext, *evaluator, camera.get(), node.get());
		return self;
	})

	//! [ESMF] VisibilityVector SamplingSphere.queryValue(Vec3, Number)
	ES_MFUNCTION_DECLARE(typeObject, const E_SamplingSphere, "queryValue", 2, 2, {
		const auto & query = parameter[0].to<const Geometry::Vec3 &>(runtime);
		const auto interpolation = interpolationFromUInt(parameter[1].to<uint32_t>(runtime));
		return new E_VisibilityVector((**self).queryValue(query, interpolation));
	})

	//! @note The converter creates a copy of the object. Changes will not be visible "on the other side".
	struct SamplingSphereConverter : public E_Util::E_Utils::AbstractGenericAttributeConverter {
		typedef Util::WrapperAttribute<SamplingSphere> SamplingSphereAttribute;

		virtual ~SamplingSphereConverter() {
		}

		virtual Object * convertToEScript(const Util::GenericAttribute * const attribute) {
			const SamplingSphereAttribute * samplingSphereAttribute = dynamic_cast<const SamplingSphereAttribute *>(attribute);
			if (samplingSphereAttribute != nullptr) {
				return new E_SamplingSphere(samplingSphereAttribute->ref());
			}
			return nullptr;
		}

		virtual Util::GenericAttribute * convertFromEScript(const EScript::ObjPtr & object) {
			const E_SamplingSphere * eSamplingSphere = object.toType<const E_SamplingSphere>();
			if (eSamplingSphere != nullptr) {
				return new SamplingSphereAttribute(eSamplingSphere->ref());
			}
			return nullptr;
		}
	};
	E_Util::E_Utils::registerConverter(new SamplingSphereConverter);
}

E_SamplingSphere::~E_SamplingSphere() = default;

}
}

#endif /* MINSG_EXT_SPHERICALSAMPLING */
