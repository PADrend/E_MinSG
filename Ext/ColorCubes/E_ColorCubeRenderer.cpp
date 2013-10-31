/*
	This file is part of the E_MinSG library extension ColorCubes.
	Copyright (C) 2010-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2010-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2010 Paul Justus <paul.justus@gmx.net>
	Copyright (C) 2010-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_COLORCUBES

#include "E_ColorCubeRenderer.h"
#include "../../Core/E_FrameContext.h"
#include "../../ELibMinSG.h"
#include "../ELibMinSGExt.h"

#include <MinSG/Core/FrameContext.h>
#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

Type* E_ColorCubeRenderer::typeObject=nullptr;


/**
 * initMembers
 */
void E_ColorCubeRenderer::init(EScript::Namespace & lib) {
	// E_ColorCubeRenderer ---|> E_NodeRendererState ---|> E_State ---|> Object
	typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::ColorCubeRenderer,E_ColorCubeRenderer>();

	//! [ESMF] new MinSG.ColorCubeRenderer()
	ES_CTOR(typeObject,0,0,EScript::create(new ColorCubeRenderer))

	//! [ESMF] self ColorCubeRenderer.setHighlightEnabled(bool)
	ES_MFUN(typeObject,ColorCubeRenderer,"setHighlightEnabled",1,1, (thisObj->setHighlightEnabled(parameter[0].toBool()),thisEObj))

	//! [ESMF] Bool ColorCubeRenderer.isHighlightEnabled()
	ES_MFUN(typeObject,ColorCubeRenderer,"isHighlightEnabled",0,0,	thisObj->isHighlightEnabled())

}
//---

E_ColorCubeRenderer::E_ColorCubeRenderer(ColorCubeRenderer * _obj, EScript::Type * type):E_NodeRendererState(_obj,type?type:typeObject){
}
E_ColorCubeRenderer::~E_ColorCubeRenderer() = default;

}

#endif // MINSG_EXT_COLORCUBES
