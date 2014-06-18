/*
	This file is part of the E_MinSG library extension SVS.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SVS

#include "E_PreprocessingContext.h"
#include "../../Core/Nodes/E_GroupNode.h"
#include "../../Core/E_FrameContext.h"
#include "../../SceneManagement/E_SceneManager.h"

#include <E_Geometry/E_Vec3.h>
#include <MinSG/Ext/SVS/PreprocessingContext.h>
#include <Util/References.h>

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <cstdint>
#include <string>
#include <utility>

namespace E_MinSG {
namespace SVS {

EScript::Type * E_PreprocessingContext::getTypeObject() {
	// E_PreprocessingContext ---|> E_Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

void E_PreprocessingContext::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_PreprocessingContext::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	using namespace MinSG::SVS;
	
	//! [ESF] new SVS.PreprocessingContext(SceneManager, FrameContext, GroupNode, Array, Number, Bool, Bool)
	ES_CONSTRUCTOR(typeObject, 7, 7, {
		MinSG::SceneManagement::SceneManager & sceneManager = parameter[0].to<MinSG::SceneManagement::SceneManager&>(rt);
		MinSG::FrameContext & frameContext = parameter[1].to<MinSG::FrameContext&>(rt);
		MinSG::GroupNode * rootNode = parameter[2].to<MinSG::GroupNode*>(rt);
		EScript::Array * array = parameter[3].to<EScript::Array*>(rt);
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
	ES_MFUN(typeObject, PreprocessingContext, "preprocessSingleNode", 0, 0,
				(thisObj->preprocessSingleNode(), EScript::create(nullptr)))

	//! [ESMF] Bool PreprocessingContext.isFinished()
	ES_MFUN(typeObject, const PreprocessingContext, "isFinished", 0, 0,thisObj->isFinished())

	//! [ESMF] Number PreprocessingContext.getNumRemainingNodes()
	ES_MFUN(typeObject, const PreprocessingContext, "getNumRemainingNodes", 0, 0, static_cast<uint32_t>(thisObj->getNumRemainingNodes()))
}

E_PreprocessingContext::~E_PreprocessingContext() = default;

}
}

#endif /* MINSG_EXT_SVS */
