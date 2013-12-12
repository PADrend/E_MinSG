/*
	This file is part of the E_MinSG library extension SVS.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SVS

#include "E_VisibilitySphere.h"
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
#include <MinSG/Ext/SVS/Definitions.h>
#include <MinSG/Ext/SVS/Helper.h>
#include <MinSG/Ext/SVS/VisibilitySphere.h>
#include <Util/GenericAttribute.h>
#include <Util/References.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace MinSG::SVS;

namespace MinSG {
namespace VisibilitySubdivision {
class VisibilityVector;
}
}
namespace E_MinSG {
namespace SVS {

EScript::Type * E_VisibilitySphere::getTypeObject() {
	// E_VisibilitySphere ---|> ExtObject
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::ExtObject::getTypeObject());
	return typeObject.get();
}

void E_VisibilitySphere::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_VisibilitySphere::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	//! [ESF] new VisibilitySphere(Sphere, Array)
	ES_CONSTRUCTOR(typeObject, 2, 2, {
		const Geometry::Sphere_f & sphere = parameter[0].to<const Geometry::Sphere_f&>(rt);
		EScript::Array * array = parameter[1].to<EScript::Array*>(rt);
		std::vector<SamplePoint> samples;
		samples.reserve(array->size());
		for(EScript::Array::iterator it = array->begin(); it != array->end(); ++it) {
			samples.emplace_back(EScript::assertType<E_SamplePoint>(rt, *it)->ref());
		}
		return new E_VisibilitySphere(VisibilitySphere(sphere, samples));
	})

	//! [ESMF] Sphere VisibilitySphere.getSphere()
	ESMF_DECLARE(typeObject, const E_VisibilitySphere, "getSphere", 0, 0,
				new E_Geometry::E_Sphere((**self).getSphere()))

	//! [ESMF] Array VisibilitySphere.getSamples()
	ES_MFUNCTION_DECLARE(typeObject, const E_VisibilitySphere, "getSamples", 0, 0, {
		const std::vector<SamplePoint> & samples = (**self).getSamples();
		EScript::Array * array = EScript::Array::create();
		array->reserve(samples.size());
		for(std::vector<SamplePoint>::const_iterator it = samples.begin(); it != samples.end(); ++it) {
			array->pushBack(new E_SamplePoint(*it));
		}
		return array;
	})

	//! [ESMF] Sphere VisibilitySphere.getMemoryUsage()
	ESMF_DECLARE(typeObject, const E_VisibilitySphere, "getMemoryUsage", 0, 0,
				static_cast<double>((**self).getMemoryUsage()))

	//! [ESMF] Node VisibilitySphere.getTriangulationMinSGNodes()
	ESMF_DECLARE(typeObject, const E_VisibilitySphere, "getTriangulationMinSGNodes", 0, 0, 
				EScript::create((**self).getTriangulationMinSGNodes()))

	//! [ESMF] self VisibilitySphere.evaluateAllSamples(FrameContext, Evaluator, CameraNodeOrtho, Node)
	ES_MFUNCTION_DECLARE(typeObject, E_VisibilitySphere, "evaluateAllSamples", 4, 4, {
		MinSG::FrameContext & frameContext = parameter[0].to<MinSG::FrameContext&>(runtime);
		MinSG::Evaluators::Evaluator * evaluator = parameter[1].to<MinSG::Evaluators::Evaluator*>(runtime);
		Util::Reference<MinSG::CameraNodeOrtho> camera = **EScript::assertType<E_CameraNodeOrtho>(runtime, parameter[2]);
		Util::Reference<MinSG::Node> node = parameter[3].to<MinSG::Node*>(runtime);
		(**self).evaluateAllSamples(frameContext, *evaluator, camera.get(), node.get());
		return self;
	})

	//! [ESMF] VisibilityVector VisibilitySphere.queryValue(Vec3, Number)
	ES_MFUNCTION_DECLARE(typeObject, const E_VisibilitySphere, "queryValue", 2, 2, {
		const auto & query = parameter[0].to<const Geometry::Vec3 &>(runtime);
		const auto interpolation = interpolationFromUInt(parameter[1].to<uint32_t>(runtime));
		return new E_VisibilityVector((**self).queryValue(query, interpolation));
	})

	//! @note The converter creates a copy of the object. Changes will not be visible "on the other side".
	struct VisibilitySphereConverter : public E_Util::E_Utils::AbstractGenericAttributeConverter {
		typedef Util::WrapperAttribute<VisibilitySphere> VisibilitySphereAttribute;

		virtual ~VisibilitySphereConverter() {
		}

		virtual Object * convertToEScript(const Util::GenericAttribute * const attribute) {
			const VisibilitySphereAttribute * visibilitySphereAttribute = dynamic_cast<const VisibilitySphereAttribute *>(attribute);
			if (visibilitySphereAttribute != nullptr) {
				return new E_VisibilitySphere(visibilitySphereAttribute->ref());
			}
			return nullptr;
		}

		virtual Util::GenericAttribute * convertFromEScript(const EScript::ObjPtr & object) {
			const E_VisibilitySphere * eVisibilitySphere = object.toType<const E_VisibilitySphere>();
			if (eVisibilitySphere != nullptr) {
				return new VisibilitySphereAttribute(eVisibilitySphere->ref());
			}
			return nullptr;
		}
	};
	E_Util::E_Utils::registerConverter(new VisibilitySphereConverter);
}

E_VisibilitySphere::~E_VisibilitySphere() = default;

}
}

#endif /* MINSG_EXT_SVS */
