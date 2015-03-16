/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012,2015 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_CHCRenderer.h"
#include "../ELibMinSGExt.h"

#include <MinSG/Ext/OcclusionCulling/CHCRenderer.h>
#include <EScript/EScript.h>

namespace E_MinSG {

EScript::Type * E_CHCRenderer::getTypeObject() {
	// E_CHCRenderer ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_CHCRenderer::init(EScript::Namespace & lib) {
	EScript::Type* typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::CHCRenderer,E_CHCRenderer>();

	using namespace MinSG;

	//! [ESMF] new MinSG.CHCRenderer
	ES_CTOR(typeObject,0,0, EScript::create(new CHCRenderer))

	//! [ESMF] enum MinSG.getMode()	
	ES_MFUN(typeObject,CHCRenderer,"getDebugShowVisible",0,0,thisObj->getDebugShowVisible())

	//! [ESMF] self MinSG.setDebugShowVisible(bool)	
	ES_MFUN(typeObject,CHCRenderer,"setDebugShowVisible",1,1,(thisObj->setDebugShowVisible(parameter[0].toBool()),thisEObj))
}

}
