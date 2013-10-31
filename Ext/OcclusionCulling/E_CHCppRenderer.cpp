/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_CHCppRenderer.h"
#include "../ELibMinSGExt.h"

#include <EScript/EScript.h>
#include <MinSG/Ext/OcclusionCulling/CHCppRenderer.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

Type* E_CHCppRenderer::typeObject=nullptr;

//! initMembers
void E_CHCppRenderer::init(EScript::Namespace & lib) {
	// E_CHCppRenderer ----|> E_State ----|> Object
	typeObject = new EScript::Type(E_State::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::CHCppRenderer,E_CHCppRenderer>();

	//! [ESMF] new MinSG.CHCppRenderer
	ES_CTOR(typeObject,0,0,EScript::create(new CHCppRenderer))

	//! [ESMF] enum MinSG.getMode()	
	ES_MFUN(typeObject,CHCppRenderer,"getMode",0,0,static_cast<uint32_t>(thisObj->getMode()))

	//! [ESMF] void MinSG.setMode(mode)	
	ES_MFUN(typeObject,CHCppRenderer,"setMode",1,1,(thisObj->setMode(static_cast<CHCppRenderer::renderMode>(parameter[0].toInt())),thisEObj))

	//! [ESMF] int MinSG.getVisibilityThreshold()	
	ES_MFUN(typeObject,CHCppRenderer,"getVisibilityThreshold",0,0,thisObj->getVisibilityThreshold())

	//! [ESMF] void MinSG.setMode(int)	
	ES_MFUN(typeObject,CHCppRenderer,"setVisibilityThreshold",1,1,(thisObj->setVisibilityThreshold(parameter[0].toInt()),thisEObj))

	//! [ESMF] int MinSG.getMaxPrevInvisNodesBatchSize()	
	ES_MFUN(typeObject,CHCppRenderer,"getMaxPrevInvisNodesBatchSize",0,0,thisObj->getMaxPrevInvisNodesBatchSize())

	//! [ESMF] void MinSG.setMaxPrevInvisNodesBatchSize(int)	
	ES_MFUN(typeObject,CHCppRenderer,"setMaxPrevInvisNodesBatchSize",1,1,(thisObj->setMaxPrevInvisNodesBatchSize(parameter[0].toInt()),thisEObj))

	//! [ESMF] int MinSG.getSkippedFramesTillQuery()	
	ES_MFUN(typeObject,CHCppRenderer,"getSkippedFramesTillQuery",0,0,thisObj->getSkippedFramesTillQuery())

	//! [ESMF] void MinSG.setSkippedFramesTillQuery(int)	
	ES_MFUN(typeObject,CHCppRenderer,"setSkippedFramesTillQuery",1,1,(thisObj->setSkippedFramesTillQuery(parameter[0].toInt()),thisEObj))

	//! [ESMF] int MinSG.getMaxDepthForTightBoundingVolumes()	
	ES_MFUN(typeObject,CHCppRenderer,"getMaxDepthForTightBoundingVolumes",0,0,thisObj->getMaxDepthForTightBoundingVolumes())

	//! [ESMF] void MinSG.setMaxDepthForTightBoundingVolumes(int)	
	ES_MFUN(typeObject,CHCppRenderer,"setMaxDepthForTightBoundingVolumes",1,1,(thisObj->setMaxDepthForTightBoundingVolumes(parameter[0].toInt()),thisEObj))

	//! [ESMF] float MinSG.getMaxAreaDerivationForTightBoundingVolumes()	
	ES_MFUN(typeObject,CHCppRenderer,"getMaxAreaDerivationForTightBoundingVolumes",0,0,thisObj->getMaxAreaDerivationForTightBoundingVolumes())

	//! [ESMF] void MinSG.setMaxAreaDerivationForTightBoundingVolumes(float)	
	ES_MFUN(typeObject,CHCppRenderer,"setMaxAreaDerivationForTightBoundingVolumes",1,1,(thisObj->setMaxAreaDerivationForTightBoundingVolumes(parameter[0].toFloat()),thisEObj))

	declareConstant(typeObject,"MODE_CULLING", EScript::create(static_cast<uint32_t>(CHCppRenderer::MODE_CULLING)));
	declareConstant(typeObject,"MODE_SHOW_VISIBLE", EScript::create(static_cast<uint32_t>(CHCppRenderer::MODE_SHOW_VISIBLE)));
	declareConstant(typeObject,"MODE_SHOW_CULLED", EScript::create(static_cast<uint32_t>(CHCppRenderer::MODE_SHOW_CULLED)));
	declareConstant(typeObject,"MODE_UNCONDITIONED", EScript::create(static_cast<uint32_t>(CHCppRenderer::MODE_UNCONDITIONED)));

}
//---

//! [ctor]
E_CHCppRenderer::E_CHCppRenderer(CHCppRenderer * _obj, EScript::Type * type):E_State(_obj,type?type:typeObject){
}
//! [dtor]
E_CHCppRenderer::~E_CHCppRenderer(){
}

}
