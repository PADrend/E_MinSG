/*
	This file is part of the MinSG library extension ThesisPeter.
	Copyright (C) 2014 Peter Stilow

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_THESISPETER

#include "E_LightNodeManager.h"
#include <MinSG/Ext/ThesisPeter/LightNodeManager.h>

#include "../../ELibMinSG.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <E_Rendering/E_RenderingContext.h>
#include <E_MinSG/Core/E_FrameContext.h>

using namespace MinSG::ThesisPeter;

namespace E_MinSG {
namespace ThesisPeter {

//! (static)
EScript::Type * E_LightNodeManager::getTypeObject() {
	// E_LightNodeManager ---|> [Object]
//	static EScript::Type* typeObject = new EScript::Type(Object::getTypeObject());
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(Object::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_LightNodeManager::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject, getClassName());
	declareConstant(&lib, getClassName(), typeObject);
//	addFactory<MinSG::ThesisPeter::LightNodeManager, E_LightNodeManager>();

	//! [ESMF] new MinSG.ThesisPeter.LightNodeManager()
	ES_CTOR(typeObject, 0, 0, new E_LightNodeManager)

	//! [ESMF] self LightNodeManager.test(Node);
	ES_MFUN(typeObject, LightNodeManager, "test", 2, 2,
				 (thisObj->test(parameter[0].to<MinSG::FrameContext&>(rt), parameter[1].to<MinSG::Node*>(rt)), thisEObj))

	//! [ESMF] self LightNodeManager.setSceneRootNode(Node);
	ES_MFUN(typeObject, LightNodeManager, "setSceneRootNode", 1, 1,
				 (thisObj->setSceneRootNode(parameter[0].to<MinSG::Node*>(rt)), thisEObj))

	//! [ESMF] self LightNodeManager.setRenderingContext(RenderingContext);
	ES_MFUN(typeObject, LightNodeManager, "setRenderingContext", 1, 1,
				 (thisObj->setRenderingContext(parameter[0].to<Rendering::RenderingContext&>(rt)), thisEObj))

    //! [ESMF] self LightNodeManager.setFrameContext(FrameContext);
    ES_MFUN(typeObject, LightNodeManager, "setFrameContext", 1,1,
				 (thisObj->setFrameContext(parameter[0].to<MinSG::FrameContext&>(rt)), thisEObj))

	//! [ESMF] self LightNodeManager.createLightNodes();
	ES_MFUN(typeObject, LightNodeManager, "createLightNodes", 0, 0,
				 (thisObj->createLightNodes(), thisEObj))

	//! [ESMF] self LightNodeManager.cleanUpDebug();
	ES_MFUN(typeObject, LightNodeManager, "cleanUpDebug", 0, 0,
				 (thisObj->cleanUpDebug(), thisEObj))

	//! [ESMF] self LightNodeManager.cleanUp();
	ES_MFUN(typeObject, LightNodeManager, "cleanUp", 0, 0,
				 (thisObj->cleanUp(), thisEObj))

	//! [ESMF] self LightNodeManager.activateLighting(SceneRootNode, LightRootNode, RenderingContext, FrameContext);
	ES_MFUN(typeObject, LightNodeManager, "activateLighting", 4, 4,
				 (thisObj->activateLighting(parameter[0].to<MinSG::Node*>(rt), parameter[1].to<MinSG::Node*>(rt),
												parameter[2].to<Rendering::RenderingContext&>(rt), parameter[3].to<MinSG::FrameContext&>(rt)), thisEObj))

}

//E_LightNodeManager::E_LightNodeManager(MinSG::ThesisPeter::LightNodeManager* renderer){
//
//}

E_LightNodeManager::~E_LightNodeManager() {

}

}
}

#endif /* MINSG_EXT_THESISPETER */
