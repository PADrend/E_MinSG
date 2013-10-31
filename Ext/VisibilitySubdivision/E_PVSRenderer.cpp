/*
	This file is part of the E_MinSG library.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_VISIBILITY_SUBDIVISION

#include "E_PVSRenderer.h"
#include "../ValuatedRegion/E_ValuatedRegionNode.h"

#include <EScript/EScript.h>

namespace E_MinSG {

EScript::Type * E_PVSRenderer::getTypeObject() {
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

void E_PVSRenderer::init(EScript::Namespace & lib) {
	using namespace MinSG::VisibilitySubdivision;

	auto typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<PVSRenderer, E_PVSRenderer>();

	//! [ESMF] PVSRenderer new PVSRenderer()
	ES_CTOR(typeObject, 0, 0, EScript::create(new MinSG::VisibilitySubdivision::PVSRenderer()));

	//! [ESMF] self PVSRenderer.setViewCells(E_ValuatedRegionNode)
	ES_MFUN(typeObject, PVSRenderer, "setViewCells", 1, 1, 
			(thisObj->setViewCells((**EScript::assertType<E_ValuatedRegionNode>(rt, parameter[0]))), thisEObj))
}

E_PVSRenderer::E_PVSRenderer(MinSG::VisibilitySubdivision::PVSRenderer * renderer, EScript::Type * type) :
		E_State(renderer, type ? type : getTypeObject()) {
}

E_PVSRenderer::~E_PVSRenderer() = default;

}

#endif // MINSG_EXT_VISIBILITY_SUBDIVISION
