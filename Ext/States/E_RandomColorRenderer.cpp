/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_RandomColorRenderer.h"

#include <EScript/EScript.h>

namespace E_MinSG {

EScript::Type * E_RandomColorRenderer::typeObject = nullptr;

//! initMembers
void E_RandomColorRenderer::init(EScript::Namespace & lib) {
	/// [E_RandomColorRenderer] ---|> [E_State] ---|> [E_GroupNode] ---|> [E_Node]
	typeObject = new EScript::Type(E_State::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::RandomColorRenderer,E_RandomColorRenderer>();

	//! [ESMF] new MinSG.VisibilityEvaluator
	ES_CTOR(typeObject,0,0,EScript::create(new MinSG::RandomColorRenderer))
}

// ------------------------------------------------------------

//! [ctor]
E_RandomColorRenderer::E_RandomColorRenderer(MinSG::RandomColorRenderer * gNode,
												EScript::Type * type) :
	E_State(gNode, type ? type : typeObject) {
}

//! [dtor]
E_RandomColorRenderer::~E_RandomColorRenderer() {
}

}
