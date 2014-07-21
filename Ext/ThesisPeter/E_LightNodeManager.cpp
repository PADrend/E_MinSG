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

using namespace MinSG::ThesisPeter;

namespace E_MinSG {
namespace ThesisPeter {

//! (static)
EScript::Type * E_LightNodeManager::getTypeObject() {
	// E_LightNodeManager ---|> [Object]
	static EScript::Type* typeObject = new EScript::Type(Object::getTypeObject());
	return typeObject;
}

//! initMembers
void E_LightNodeManager::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	//! [ESMF] self LightNodeManager.addAttribute(Mesh);
	ES_MFUN(typeObject, LightNodeManager, "addAttribute", 1, 1,
				 (thisObj->addAttribute(parameter[0].to<Rendering::Mesh*>(rt)), thisEObj))
}

//E_LightNodeManager::E_LightNodeManager(MinSG::ThesisPeter::LightNodeManager* renderer){
//
//}

E_LightNodeManager::~E_LightNodeManager() {

}

}
}

#endif /* MINSG_EXT_THESISPETER */
