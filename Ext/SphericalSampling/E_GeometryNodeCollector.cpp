/*
	This file is part of the E_MinSG library extension SphericalSampling.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SPHERICALSAMPLING

#include "E_GeometryNodeCollector.h"
#include "../../Core/Nodes/E_GeometryNode.h"
#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <MinSG/Ext/SphericalSampling/GeometryNodeCollector.h>
#include <cstdint>
#include <unordered_map>

namespace E_MinSG {
namespace SphericalSampling {

EScript::Type * E_GeometryNodeCollector::getTypeObject() {
	// E_GeometryNodeCollector ---|> E_NodeRendererState ---|> E_State
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	return typeObject.get();
}

void E_GeometryNodeCollector::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_GeometryNodeCollector::getTypeObject();
	declareConstant(&lib, "GeometryNodeCollector", typeObject);
	addFactory<MinSG::SphericalSampling::GeometryNodeCollector, E_GeometryNodeCollector>();

	//! [ESF] new MinSG.SphericalSampling.GeometryNodeCollector()
	ES_CTOR(typeObject, 0, 0, EScript::create(new MinSG::SphericalSampling::GeometryNodeCollector()))

	//! [ESMF] Array GeometryNodeCollector.getCollectedNodes()
	ES_MFUNCTION_DECLARE(typeObject, E_GeometryNodeCollector, "getCollectedNodes", 0, 0, {
		const auto & collectedNodes = (**self)->getCollectedNodes();
		auto array = EScript::Array::create();
		for(const auto & node : collectedNodes) {
			E_Node * eNode = EScript::create(node);
			if(eNode != nullptr) {
				array->pushBack(eNode);
			}
		}
		return array;
	})
}

E_GeometryNodeCollector::E_GeometryNodeCollector(MinSG::SphericalSampling::GeometryNodeCollector * collector) :
		E_NodeRendererState(collector, E_GeometryNodeCollector::getTypeObject()) {
}

E_GeometryNodeCollector::~E_GeometryNodeCollector() = default;

}
}

#endif /* MINSG_EXT_SPHERICALSAMPLING */
