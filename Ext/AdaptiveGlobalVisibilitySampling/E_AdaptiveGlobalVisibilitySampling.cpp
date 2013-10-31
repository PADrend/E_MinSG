/*
	This file is part of the E_MinSG library extension
	AdaptiveGlobalVisibilitySampling.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_ADAPTIVEGLOBALVISIBILITYSAMPLING

#include "E_AdaptiveGlobalVisibilitySampling.h"
#include "../../Core/Nodes/E_GroupNode.h"
#include "../ValuatedRegion/E_ValuatedRegionNode.h"
#include <EScript/Basics.h>
#include <E_Rendering/Mesh/E_Mesh.h>

namespace E_MinSG {
namespace AGVS {

EScript::Type * E_AdaptiveGlobalVisibilitySampling::getTypeObject() {
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

void E_AdaptiveGlobalVisibilitySampling::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_AdaptiveGlobalVisibilitySampling::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	//! [ESF] new AGVS.AdaptiveGlobalVisibilitySampling(GroupNode, ValuatedRegionNode)
	ES_CTOR(typeObject, 2, 2,
			new E_AdaptiveGlobalVisibilitySampling(
				parameter[0].to<MinSG::GroupNode *>(rt),
				parameter[1].to<MinSG::ValuatedRegionNode *>(rt)
			));

	//! [ESMF] Bool AdaptiveGlobalVisibilitySampling.performSampling(Number)
	ES_MFUN(typeObject, MinSG::AGVS::AdaptiveGlobalVisibilitySampling, "performSampling", 1, 1,
				 thisObj->performSampling(parameter[0].to<uint32_t>(rt)))

	//! [ESMF] E_Rendering::E_Mesh AdaptiveGlobalVisibilitySampling.createMeshFromSamples()
	ES_MFUN(typeObject, const MinSG::AGVS::AdaptiveGlobalVisibilitySampling, "createMeshFromSamples", 0, 0,
			EScript::create(thisObj->createMeshFromSamples()))

	//! [ESMF] ValuatedRegionNode AdaptiveGlobalVisibilitySampling.getViewCellHierarchy()
	ES_MFUN(typeObject, const MinSG::AGVS::AdaptiveGlobalVisibilitySampling, "getViewCellHierarchy", 0, 0,
			EScript::create(thisObj->getViewCellHierarchy()))
}

E_AdaptiveGlobalVisibilitySampling::~E_AdaptiveGlobalVisibilitySampling() = default;

}
}

#endif /* MINSG_EXT_ADAPTIVEGLOBALVISIBILITYSAMPLING */
