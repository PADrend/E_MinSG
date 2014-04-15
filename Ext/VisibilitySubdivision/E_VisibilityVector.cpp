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

#include "E_VisibilityVector.h"
#include "../../Core/Nodes/E_GeometryNode.h"
#include "../../Core/Nodes/E_Node.h"
#include "../../SceneManagement/E_SceneManager.h"
#include "../../ELibMinSG.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <E_Util/E_Utils.h>
#include <MinSG/Core/Nodes/GeometryNode.h>
#include <MinSG/Ext/VisibilitySubdivision/VisibilityVector.h>
#include <Util/GenericAttribute.h>
#include <Util/References.h>
#include <cstddef>
#include <map>
#include <utility>
#include <sstream>

using namespace MinSG::VisibilitySubdivision;

namespace MinSG {
namespace SceneManagement {
class SceneManager;
}
}
namespace E_MinSG {

EScript::Type * E_VisibilityVector::getTypeObject() {
	// E_VisibilityVector ---|> ExtObject
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::ExtObject::getTypeObject());
	return typeObject.get();
}

void E_VisibilityVector::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	using namespace MinSG;
	using namespace VisibilitySubdivision;

	//! [ESF] new VisibilityVector()
	ES_CTOR(typeObject, 0, 0, new E_VisibilityVector)

	//! [ESMF] VisibilityVector VisibilityVector.makeMin(VisibilityVector)
	ES_MFUNCTION(typeObject, const VisibilityVector, "makeMin", 1, 1, {
		const auto & vv1 = *thisObj;
		const auto & vv2 = parameter[0].to<const VisibilityVector&>(rt);
		return new E_VisibilityVector(VisibilityVector::makeMin(vv1, vv2));
	})

	//! [ESMF] VisibilityVector VisibilityVector.makeMax(VisibilityVector)
	ES_MFUNCTION(typeObject, const VisibilityVector, "makeMax", 1, 1, {
		const auto & vv1 = *thisObj;
		const auto & vv2 = parameter[0].to<const VisibilityVector&>(rt);
		return new E_VisibilityVector(VisibilityVector::makeMax(vv1, vv2));
	})

	//! [ESMF] VisibilityVector VisibilityVector.makeDifference(VisibilityVector)
	ES_MFUNCTION(typeObject, const VisibilityVector, "makeDifference", 1, 1, {
		const auto & vv1 = *thisObj;
		const auto & vv2 = parameter[0].to<const VisibilityVector&>(rt);
		return new E_VisibilityVector(VisibilityVector::makeDifference(vv1, vv2));
	})

	//! [ESMF] VisibilityVector VisibilityVector.makeSymmetricDifference(VisibilityVector)
	ES_MFUNCTION(typeObject, const VisibilityVector, "makeSymmetricDifference", 1, 1, {
		const auto & vv1 = *thisObj;
		const auto & vv2 = parameter[0].to<const VisibilityVector&>(rt);
		return new E_VisibilityVector(VisibilityVector::makeSymmetricDifference(vv1, vv2));
	})

	//! [ESMF] VisibilityVector VisibilityVector.makeWeightedThree(Number, VisibilityVector, Number, VisibilityVector, Number, VisibilityVector)
	ES_FUNCTION(typeObject, "makeWeightedThree", 6, 6, {
		const auto & vv1 = **EScript::assertType<E_VisibilityVector>(rt, parameter[1]);
		const auto & vv2 = **EScript::assertType<E_VisibilityVector>(rt, parameter[3]);
		const auto & vv3 = **EScript::assertType<E_VisibilityVector>(rt, parameter[5]);
		return new E_VisibilityVector(VisibilityVector::makeWeightedThree(parameter[0].toFloat(), vv1,
																		  parameter[2].toFloat(), vv2,
																		  parameter[4].toFloat(), vv3));
	})

	//! [ESMF] Array VisibilityVector.diff(VisibilityVector)
	ES_MFUNCTION(typeObject, VisibilityVector, "diff", 1, 1, {
		const auto & vv1 = *thisObj;
		const auto & vv2 = parameter[0].to<const VisibilityVector&>(rt);
		VisibilityVector::costs_t costsDiff;
		VisibilityVector::benefits_t benefitsDiff;
		std::size_t sameCount;
		VisibilityVector::diff(vv1, vv2, costsDiff, benefitsDiff, sameCount);
		EScript::Array * resultArray = EScript::Array::create();
		resultArray->pushBack(EScript::Number::create(costsDiff));
		resultArray->pushBack(EScript::Number::create(benefitsDiff));
		resultArray->pushBack(EScript::Number::create(sameCount));
		return resultArray;
	})

	//! [ESMF] self VisibilityVector.setNode(GeometryNode, Number)
	ES_MFUN(typeObject, VisibilityVector, "setNode", 2, 2,
				 (thisObj->setNode(parameter[0].to<GeometryNode*>(rt), parameter[1].toUInt()), thisEObj))

	//! [ESMF] Number VisibilityVector.getCosts(GeometryNode)
	ES_MFUN(typeObject, const VisibilityVector, "getCosts", 1, 1,
				 EScript::Number::create(thisObj->getCosts(parameter[0].to<GeometryNode*>(rt))))

	//! [ESMF] Number VisibilityVector.getBenefits(GeometryNode)
	ES_MFUN(typeObject, const VisibilityVector, "getBenefits", 1, 1,
				 EScript::Number::create(thisObj->getBenefits(parameter[0].to<GeometryNode*>(rt))))

	//! [ESMF] Number VisibilityVector.getTotalCosts()
	ES_MFUN(typeObject, const VisibilityVector, "getTotalCosts", 0, 0, EScript::Number::create(thisObj->getTotalCosts()))

	//! [ESMF] Number VisibilityVector.getTotalBenefits()
	ES_MFUN(typeObject, const VisibilityVector, "getTotalBenefits", 0, 0, EScript::Number::create(thisObj->getTotalBenefits()))

	//! [ESMF] Number VisibilityVector.getVisibleNodeCount()
	ES_MFUN(typeObject, const VisibilityVector, "getVisibleNodeCount", 0, 0, EScript::Number::create(thisObj->getVisibleNodeCount()))

	//! [ESMF] Array VisibilityVector.getNodes()
	ES_MFUNCTION(typeObject, const VisibilityVector, "getNodes", 0, 0, {
		const auto & vv = *thisObj;
		const uint32_t maxIndex = vv.getIndexCount();
		EScript::Array * array = EScript::Array::create();
		for(uint_fast32_t index = 0; index < maxIndex; ++index) {
			if(vv.getBenefits(index) > 0) {
				array->pushBack(EScript::create(vv.getNode(index)));
			}
		}
		return array;
	})

	//! [ESMF] Number VisibilityVector.getMemoryUsage()
	ES_MFUN(typeObject, const VisibilityVector, "getMemoryUsage", 0, 0, EScript::Number::create(thisObj->getMemoryUsage()))

	//! [ESMF] String VisibilityVector.serialize(SceneManager)
	ES_MFUNCTION(typeObject, const VisibilityVector, "serialize", 1, 1, {
		std::ostringstream stream;
		thisObj->serialize(stream, parameter[0].to<const SceneManagement::SceneManager&>(rt));
		return EScript::String::create(stream.str());
	})

	//! [ESMF] VisibilityVector VisibilityVector.unserialize(String, SceneManager)
	ES_FUNCTION(typeObject, "unserialize", 2, 2, {
		std::istringstream stream(parameter[0].toString());
		const MinSG::SceneManagement::SceneManager & sceneManager = ***EScript::assertType<E_SceneManager>(rt, parameter[1]);
		return new E_VisibilityVector(VisibilityVector::unserialize(stream, sceneManager));
	})

	class VVConverter : public E_Util::E_Utils::AbstractGenericAttributeConverter {
		public:
			virtual ~VVConverter() {
			}

			virtual Object * convertToEScript(const Util::GenericAttribute * const attribute) {
				const auto * visiContainer = dynamic_cast<const VisibilityVectorAttribute *>(attribute);
				if (visiContainer != nullptr) {
					return new E_VisibilityVector(visiContainer->ref());
				}
				return nullptr;
			}

			virtual Util::GenericAttribute * convertFromEScript(const EScript::ObjPtr & object) {
				const E_VisibilityVector * evv = object.toType<const E_VisibilityVector>();
				if (evv != nullptr) {
					return new VisibilityVectorAttribute(**evv);
				}
				return nullptr;
			}
	};
	E_Util::E_Utils::registerConverter(new VVConverter);
}

E_VisibilityVector::~E_VisibilityVector() = default;

}

#endif /* MINSG_EXT_VISIBILITY_SUBDIVISION */
