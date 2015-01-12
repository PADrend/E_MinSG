/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_NaiveOccRenderer.h"
#include "../ELibMinSGExt.h"

#include <MinSG/Ext/OcclusionCulling/NaiveOccRenderer.h>
#include <EScript/EScript.h>

namespace E_MinSG {

EScript::Type * E_NaiveOccRenderer::getTypeObject() {
	// E_NaiveOccRenderer ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_NaiveOccRenderer::init(EScript::Namespace & lib) {
	EScript::Type* typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::NaiveOccRenderer,E_NaiveOccRenderer>();

	using namespace MinSG;

	//! [ESMF] new MinSG.NaiveOccRenderer
	ES_CTOR(typeObject,0,0, EScript::create(new NaiveOccRenderer))

	//! [ESMF] enum MinSG.getMode()	
	ES_MFUN(typeObject,NaiveOccRenderer,"getDebugShowVisible",0,0,thisObj->getDebugShowVisible())

	//! [ESMF] self MinSG.setDebugShowVisible(bool)	
	ES_MFUN(typeObject,NaiveOccRenderer,"setDebugShowVisible",1,1,(thisObj->setDebugShowVisible(parameter[0].toBool()),thisEObj))
}

}
