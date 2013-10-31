/*
	This file is part of the E_MinSG library extension SphericalSampling.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SPHERICALSAMPLING

#include "E_SamplePoint.h"
#include "../VisibilitySubdivision/E_VisibilityVector.h"
#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <E_Geometry/E_Vec3.h>
#include <Geometry/Vec3.h>
#include <MinSG/Ext/SphericalSampling/SamplePoint.h>
#include <Util/References.h>
#include <sstream>
#include <string>

namespace MinSG {
namespace VisibilitySubdivision {
class VisibilityVector;
}
}
namespace E_MinSG {
namespace SphericalSampling {

EScript::Type * E_SamplePoint::getTypeObject() {
	// E_SamplePoint ---|> ExtObject
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::ExtObject::getTypeObject());
	return typeObject.get();
}

void E_SamplePoint::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_SamplePoint::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	//! [ESF] new SamplePoint(Vec3)
	ES_CTOR(typeObject, 1, 1,
				new E_SamplePoint(parameter[0].to<const Geometry::Vec3 &>(rt)))

	//! [ESMF] Vec3 SamplePoint.getPosition()
	ESMF_DECLARE(typeObject, const E_SamplePoint, "getPosition", 0, 0,
				 new E_Geometry::E_Vec3((**self).getPosition()))

	//! [ESMF] VisibilityVector SamplePoint.getValue()
	ESMF_DECLARE(typeObject, const E_SamplePoint, "getValue", 0, 0,
				 new E_VisibilityVector((**self).getValue()))

	//! [ESMF] self SamplePoint.setValue(VisibilityVector)
	ESMF_DECLARE(typeObject, E_SamplePoint, "setValue", 1, 1,
				((**self).setValue(**EScript::assertType<E_VisibilityVector>(runtime, parameter[0])), self))
}

E_SamplePoint::~E_SamplePoint() = default;

E_SamplePoint * E_SamplePoint::clone() const {
	return new E_SamplePoint(ref());
}

std::string E_SamplePoint::toString() const {
	std::ostringstream stream;
	stream << getClassName() << '(' << ref().getPosition() << ", "
									<< &ref().getValue() << ')';
	return stream.str();
}

}
}

#endif /* MINSG_EXT_SPHERICALSAMPLING */
