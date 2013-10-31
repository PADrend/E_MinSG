/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_TransparencyRenderer.h"
#include "../../ELibMinSG.h"
#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

//! (static)
EScript::Type * E_TransparencyRenderer::getTypeObject() {
	//  E_TransparencyRenderer ---|> E_NodeRendererState ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	return typeObject.get();
}

//! (static)
void E_TransparencyRenderer::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::TransparencyRenderer,E_TransparencyRenderer>();

	//! [ESF] new MinSG.TransparencyRenderer()
	ES_CTOR(typeObject, 0, 0, EScript::create(new TransparencyRenderer))

	//! [ESMF] thisEObj setUsePremultipliedAlpha(Bool)
	ES_MFUN(typeObject, TransparencyRenderer, "setUsePremultipliedAlpha", 1,  1,
				(thisObj->setUsePremultipliedAlpha(parameter[0].toBool()), thisEObj))

	//! [ESMF] Bool getUsePremultipliedAlpha()
	ES_MFUN(typeObject, const TransparencyRenderer, "getUsePremultipliedAlpha", 0,  0,
				thisObj->getUsePremultipliedAlpha())
}
//---

//! (ctor)
E_TransparencyRenderer::E_TransparencyRenderer(TransparencyRenderer * _obj, EScript::Type * type) :
		E_NodeRendererState(_obj,type?type:getTypeObject()){
}

}
