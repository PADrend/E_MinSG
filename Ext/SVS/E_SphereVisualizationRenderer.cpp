/*
	This file is part of the E_MinSG library extension SVS.
	Copyright (C) 2012-2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SVS

#include "E_SphereVisualizationRenderer.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <MinSG/Ext/SVS/SphereVisualizationRenderer.h>

namespace E_MinSG {
namespace SVS {

using MinSG::SVS::SphereVisualizationRenderer;

EScript::Type * E_SphereVisualizationRenderer::getTypeObject() {
	// E_SphereVisualizationRenderer ---|> E_NodeRendererState ---|> E_State
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	return typeObject.get();
}

void E_SphereVisualizationRenderer::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_SphereVisualizationRenderer::getTypeObject();
	declareConstant(&lib, "SphereVisualizationRenderer", typeObject);
	addFactory<SphereVisualizationRenderer, E_SphereVisualizationRenderer>();

	//! [ESF] new MinSG.SVS.SphereVisualizationRenderer()
	ES_CTOR(typeObject, 0, 0, EScript::create(new SphereVisualizationRenderer()))
}

E_SphereVisualizationRenderer::E_SphereVisualizationRenderer(SphereVisualizationRenderer * renderer) :
		E_NodeRendererState(renderer, E_SphereVisualizationRenderer::getTypeObject()) {
}

E_SphereVisualizationRenderer::~E_SphereVisualizationRenderer() = default;

const SphereVisualizationRenderer * E_SphereVisualizationRenderer::operator*() const {
	return static_cast<const SphereVisualizationRenderer *>(ref().get());
}
SphereVisualizationRenderer * E_SphereVisualizationRenderer::operator*() {
	return static_cast<SphereVisualizationRenderer *>(ref().get());
}

}
}

#endif /* MINSG_EXT_SVS */
