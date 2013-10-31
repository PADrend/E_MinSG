/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_StrangeExampleRenderer.h"
#include "../../ELibMinSG.h"
#include "../ELibMinSGExt.h"
#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

Type* E_StrangeExampleRenderer::typeObject=nullptr;

//! initMembers
void E_StrangeExampleRenderer::init(EScript::Namespace & lib) {
	// E_StrangeExampleRenderer ----|> E_State ----|> Object
	typeObject = new EScript::Type(E_State::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::StrangeExampleRenderer,E_StrangeExampleRenderer>();

	//! [ESMF] new MinSG.StrangeExampleRenderer()   
	ES_CTOR(typeObject,0,0,EScript::create(new StrangeExampleRenderer))
}
//---

//! [ctor]
E_StrangeExampleRenderer::E_StrangeExampleRenderer(StrangeExampleRenderer * _obj, EScript::Type * type):E_State(_obj,type?type:typeObject){
}
//! [dtor]
E_StrangeExampleRenderer::~E_StrangeExampleRenderer(){
}

}
