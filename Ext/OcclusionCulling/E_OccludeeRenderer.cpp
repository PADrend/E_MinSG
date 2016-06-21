/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_OccludeeRenderer.h"
#include "../ELibMinSGExt.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_MinSG {

EScript::Type * E_OccludeeRenderer::getTypeObject() {
	// E_OccludeeRenderer ----|> E_State
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

void E_OccludeeRenderer::init(EScript::Namespace & lib) {
	declareConstant(&lib, getClassName(), getTypeObject());
	addFactory<MinSG::OccludeeRenderer,E_OccludeeRenderer>();

	using namespace MinSG;

	//! [ESF] OccludeeRenderer new OccludeeRenderer()
	ES_CTOR(getTypeObject(), 0, 0, new E_OccludeeRenderer(new MinSG::OccludeeRenderer))
	
	//! [ESMF] bool MinSG.getUseWireframe()	
	ES_MFUN(getTypeObject(),OccludeeRenderer,"getUseWireframe",0,0,thisObj->getUseWireframe())

	//! [ESMF] self MinSG.setUseWireframe(bool)	
	ES_MFUN(getTypeObject(),OccludeeRenderer,"setUseWireframe",1,1,(thisObj->setUseWireframe(parameter[0].toBool()),thisEObj))
	
	//! [ESMF] bool MinSG.getShowOriginal()	
	ES_MFUN(getTypeObject(),OccludeeRenderer,"getShowOriginal",0,0,thisObj->getShowOriginal())

	//! [ESMF] self MinSG.setShowOriginal(bool)	
	ES_MFUN(getTypeObject(),OccludeeRenderer,"setShowOriginal",1,1,(thisObj->setShowOriginal(parameter[0].toBool()),thisEObj))
}

}
