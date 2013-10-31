/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_OccRenderer.h"
#include "../ELibMinSGExt.h"

#include <MinSG/Ext/OcclusionCulling/OccRenderer.h>
#include <EScript/EScript.h>

namespace E_MinSG {

EScript::Type* E_OccRenderer::typeObject=nullptr;

//! initMembers
void E_OccRenderer::init(EScript::Namespace & lib) {
	// E_OccRenderer ----|> E_State ----|> Object
	typeObject = new EScript::Type(E_State::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::OccRenderer,E_OccRenderer>();

	using namespace MinSG;

	//! [ESMF] new MinSG.OccRenderer
	ES_CTOR(typeObject,0,0, EScript::create(new OccRenderer))

	//! [ESMF] enum MinSG.getMode()	
	ES_MFUN(typeObject,OccRenderer,"getMode",0,0,static_cast<uint32_t>(thisObj->getMode()))

	//! [ESMF] self MinSG.setMode(mode)	
	ES_MFUN(typeObject,OccRenderer,"setMode",1,1,(thisObj->setMode(static_cast<OccRenderer::renderMode>(parameter[0].toInt())),thisEObj))

	declareConstant(typeObject,"MODE_CULLING", EScript::create(static_cast<uint32_t>(OccRenderer::MODE_CULLING)));
	declareConstant(typeObject,"MODE_SHOW_VISIBLE", EScript::create(static_cast<uint32_t>(OccRenderer::MODE_SHOW_VISIBLE)));
	declareConstant(typeObject,"MODE_SHOW_CULLED", EScript::create(static_cast<uint32_t>(OccRenderer::MODE_SHOW_CULLED)));
	declareConstant(typeObject,"MODE_OPT_CULLING", EScript::create(static_cast<uint32_t>(OccRenderer::MODE_OPT_CULLING)));
	declareConstant(typeObject,"MODE_UNCONDITIONED", EScript::create(static_cast<uint32_t>(OccRenderer::MODE_UNCONDITIONED)));

}
//---

//! [ctor]
E_OccRenderer::E_OccRenderer(MinSG::OccRenderer * _obj, EScript::Type * type):E_State(_obj,type?type:typeObject){
}
//! [dtor]
E_OccRenderer::~E_OccRenderer(){
}

}
