/*
	This file is part of the E_MinSG library extension SVS.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SVS

#include "E_SamplePoint.h"
#include "../VisibilitySubdivision/E_VisibilityVector.h"
#include <E_Geometry/E_Vec3.h>
#include <Geometry/Vec3.h>
#include <MinSG/Ext/SVS/SamplePoint.h>
#include <Util/References.h>

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <sstream>
#include <string>

namespace MinSG {
namespace VisibilitySubdivision {
class VisibilityVector;
}
}
namespace E_MinSG {
namespace SVS {

EScript::Type * E_SamplePoint::getTypeObject() {
	// E_SamplePoint ---|> ExtObject
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::ExtObject::getTypeObject());
	return typeObject.get();
}

void E_SamplePoint::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_SamplePoint::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	using namespace MinSG::SVS;
	
	//! [ESF] new SamplePoint(Vec3)
	ES_CTOR(typeObject, 1, 1,
				new E_SamplePoint(parameter[0].to<const Geometry::Vec3 &>(rt)))

	//! [ESMF] Vec3 SamplePoint.getPosition()
	ES_MFUN(typeObject, const SamplePoint, "getPosition", 0, 0,	EScript::create(thisObj->getPosition()))

	//! [ESMF] VisibilityVector SamplePoint.getValue()
	ES_MFUN(typeObject, const SamplePoint, "getValue", 0, 0, new E_VisibilityVector(thisObj->getValue()))

	//! [ESMF] self SamplePoint.setValue(VisibilityVector)
	ES_MFUN(typeObject, SamplePoint, "setValue", 1, 1,
				(thisObj->setValue( parameter[0].to<const MinSG::VisibilitySubdivision::VisibilityVector&>(rt)), thisEObj))
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

#endif /* MINSG_EXT_SVS */
