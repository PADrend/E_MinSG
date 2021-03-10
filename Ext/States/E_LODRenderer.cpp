/*
	This file is part of the E_MinSG library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_LODRenderer.h"
#include "../../Core/Nodes/E_Node.h"
#include <MinSG/Ext/States/LODRenderer.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_MinSG {

EScript::Type * E_LODRenderer::getTypeObject() {
	// E_LODRenderer ---|> E_State
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	return typeObject.get();
}

void E_LODRenderer::init(EScript::Namespace & lib) {
	
	using namespace MinSG;
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, E_LODRenderer::getClassName(), typeObject);
	addFactory<MinSG::LODRenderer,E_LODRenderer>();
	
	ES_CTOR(typeObject, 0, 0, new LODRenderer())
	
	ES_MFUN(typeObject, LODRenderer, "getMinComplexity", 0, 0, thisObj->getMinComplexity())
	ES_MFUN(typeObject, LODRenderer, "getMaxComplexity", 0, 0, thisObj->getMaxComplexity())
	ES_MFUN(typeObject, LODRenderer, "getRelComplexity", 0, 0, thisObj->getRelComplexity())
	
	ES_MFUN(typeObject, LODRenderer, "setMinComplexity", 1, 1, (thisObj->setMinComplexity(parameter[0].to<uint32_t>(rt)), thisEObj))
	ES_MFUN(typeObject, LODRenderer, "setMaxComplexity", 1, 1, (thisObj->setMaxComplexity(parameter[0].to<uint32_t>(rt)), thisEObj))
	ES_MFUN(typeObject, LODRenderer, "setRelComplexity", 1, 1, (thisObj->setRelComplexity(parameter[0].to<float>(rt)), thisEObj))
	
	ES_MFUN(typeObject, LODRenderer, "generateLODsRecursiv", 1, 1, (thisObj->generateLODsRecursiv(parameter[0].to<MinSG::Node*>(rt)), thisEObj)) 
	
}

E_LODRenderer::E_LODRenderer(MinSG::LODRenderer * state) :
	E_NodeRendererState(state, E_LODRenderer::getTypeObject()) {
}

E_LODRenderer::~E_LODRenderer() = default;

const MinSG::LODRenderer * E_LODRenderer::operator*() const {
	return static_cast<const MinSG::LODRenderer *>(ref().get());
}
MinSG::LODRenderer * E_LODRenderer::operator*() {
	return static_cast<MinSG::LODRenderer *>(ref().get());
}

}
