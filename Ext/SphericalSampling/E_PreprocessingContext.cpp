/*
	This file is part of the E_MinSG library extension SphericalSampling.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SPHERICALSAMPLING

#include "E_PreprocessingContext.h"
#include "../../Core/Nodes/E_GroupNode.h"
#include "../../Core/E_FrameContext.h"
#include "../../SceneManagement/E_SceneManager.h"
#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <E_Geometry/E_Vec3.h>
#include <MinSG/Ext/SphericalSampling/PreprocessingContext.h>
#include <Util/References.h>
#include <cstdint>
#include <string>
#include <utility>

namespace E_MinSG {
namespace SphericalSampling {

EScript::Type * E_PreprocessingContext::getTypeObject() {
	// E_PreprocessingContext ---|> E_Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

void E_PreprocessingContext::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_PreprocessingContext::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	//! [ESF] new SphericalSampling.PreprocessingContext(SceneManager, FrameContext, GroupNode, Array, Number, Bool, Bool)
	ES_CONSTRUCTOR(typeObject, 7, 7, {
		MinSG::SceneManagement::SceneManager & sceneManager = ***EScript::assertType<E_SceneManager>(rt, parameter[0]);
		MinSG::FrameContext & frameContext = parameter[1].to<MinSG::FrameContext&>(rt);
		MinSG::GroupNode * rootNode = parameter[2].to<MinSG::GroupNode*>(rt);
		EScript::Array * array = EScript::assertType<EScript::Array>(rt, parameter[3]);
		const uint32_t resolution = parameter[4].to<uint32_t>(rt);
		const bool useExistingVisibilityResults = parameter[5].to<bool>(rt);
		const bool computeTightInnerBoundingSpheres = parameter[6].to<bool>(rt);
		std::vector<Geometry::Vec3f> positions;
		for(EScript::Array::const_iterator it = array->begin(); it != array->end(); ++it) {
			positions.emplace_back(EScript::assertType<E_Geometry::E_Vec3>(rt, *it)->ref());
		}
		return new E_PreprocessingContext(sceneManager,
										  frameContext,
										  rootNode,
										  positions,
										  resolution,
										  useExistingVisibilityResults,
										  computeTightInnerBoundingSpheres);
	})

	//! [ESMF] Void PreprocessingContext.preprocessSingleNode()
	ESMF_DECLARE(typeObject, E_PreprocessingContext, "preprocessSingleNode", 0, 0,
				((**self).preprocessSingleNode(), EScript::create(nullptr)))

	//! [ESMF] Bool PreprocessingContext.isFinished()
	ESMF_DECLARE(typeObject, const E_PreprocessingContext, "isFinished", 0, 0,
				EScript::Bool::create((**self).isFinished()))

	//! [ESMF] Number PreprocessingContext.getNumRemainingNodes()
	ESMF_DECLARE(typeObject, const E_PreprocessingContext, "getNumRemainingNodes", 0, 0,
				EScript::Number::create((**self).getNumRemainingNodes()))
}

E_PreprocessingContext::~E_PreprocessingContext() = default;

}
}

#endif /* MINSG_EXT_SPHERICALSAMPLING */
