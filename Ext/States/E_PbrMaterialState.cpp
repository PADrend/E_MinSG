/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	Copyright (C) 2021 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_PbrMaterialState.h"
#include "../../ELibMinSG.h"
#include "../ELibMinSGExt.h"
#include "../../Core/E_FrameContext.h"
#include <E_Rendering/Texture/E_Texture.h>
#include <E_Util/E_FileName.h>
#include <E_Util/IO/E_FileLocator.h>
#include <E_Util/E_Utils.h>
#include <E_Util/Graphics/E_Color.h>
#include <E_Geometry/E_Vec3.h>
#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

Type* E_PbrMaterialState::typeObject=nullptr;

//! initMembers
void E_PbrMaterialState::init(EScript::Namespace & lib) {
	// E_PbrMaterialState ----|> E_State ----|> Object
	typeObject = new EScript::Type(E_State::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::PbrMaterialState,E_PbrMaterialState>();

	//! [ESMF] new MinSG.PbrMaterialState()   
	ES_CTOR(typeObject,0,0,EScript::create( new PbrMaterialState))
	
	//! [ESMF] Number MinSG.PbrMaterialState.getBaseColorFactor()
	ES_MFUN(typeObject, const PbrMaterialState, "getBaseColorFactor", 0, 0, new E_Util::E_Color4f(thisObj->getBaseColorFactor()))

	//! [ESMF] thisEObj MinSG.PbrMaterialState.setBaseColorFactor(Number)
	ES_MFUN(typeObject, PbrMaterialState, "setBaseColorFactor", 1, 1, (thisObj->setBaseColorFactor(*parameter[0].to<Util::Color4f*>(rt)), thisEObj))

	//! [ESMF] Texture|Void MinSG.PbrMaterialState.getBaseColorTexture()
	ES_MFUN(typeObject, const PbrMaterialState, "getBaseColorTexture", 0, 0, thisObj->getBaseColorTexture() ? new E_Rendering::E_Texture(thisObj->getBaseColorTexture()) : nullptr)

	//! [ESMF] thisEObj MinSG.PbrMaterialState.setBaseColorTexture(Texture)
	ES_MFUN(typeObject, PbrMaterialState, "setBaseColorTexture", 1, 1, (thisObj->setBaseColorTexture(!parameter[0].toBool() ? nullptr : parameter[0].to<Rendering::Texture*>(rt)), thisEObj))

	//! [ESMF] Texture|Void MinSG.PbrMaterialState.getMetallicRoughnessTexture()
	ES_MFUN(typeObject, const PbrMaterialState, "getMetallicRoughnessTexture", 0, 0, thisObj->getMetallicRoughnessTexture() ? new E_Rendering::E_Texture(thisObj->getMetallicRoughnessTexture()) : nullptr)

	//! [ESMF] thisEObj MinSG.PbrMaterialState.setMetallicRoughnessTexture(Texture)
	ES_MFUN(typeObject, PbrMaterialState, "setMetallicRoughnessTexture", 1, 1, (thisObj->setMetallicRoughnessTexture(!parameter[0].toBool() ? nullptr : parameter[0].to<Rendering::Texture*>(rt)), thisEObj))
	
	//! [ESMF] Texture|Void MinSG.PbrMaterialState.getNormalTexture()
	ES_MFUN(typeObject, const PbrMaterialState, "getNormalTexture", 0, 0, thisObj->getNormalTexture() ? new E_Rendering::E_Texture(thisObj->getNormalTexture()) : nullptr)

	//! [ESMF] thisEObj MinSG.PbrMaterialState.setNormalTexture(Texture)
	ES_MFUN(typeObject, PbrMaterialState, "setNormalTexture", 1, 1, (thisObj->setNormalTexture(!parameter[0].toBool() ? nullptr : parameter[0].to<Rendering::Texture*>(rt)), thisEObj))
	
	//! [ESMF] Texture|Void MinSG.PbrMaterialState.getOcclusionTexture()
	ES_MFUN(typeObject, const PbrMaterialState, "getOcclusionTexture", 0, 0, thisObj->getOcclusionTexture() ? new E_Rendering::E_Texture(thisObj->getOcclusionTexture()) : nullptr)

	//! [ESMF] thisEObj MinSG.PbrMaterialState.setOcclusionTexture(Texture)
	ES_MFUN(typeObject, PbrMaterialState, "setOcclusionTexture", 1, 1, (thisObj->setOcclusionTexture(!parameter[0].toBool() ? nullptr : parameter[0].to<Rendering::Texture*>(rt)), thisEObj))
	
	//! [ESMF] Number MinSG.PbrMaterialState.getEmissiveFactor()
	ES_MFUN(typeObject, const PbrMaterialState, "getEmissiveFactor", 0, 0, new E_Geometry::E_Vec3(thisObj->getEmissiveFactor()))

	//! [ESMF] thisEObj MinSG.PbrMaterialState.setEmissiveFactor(Number)
	ES_MFUN(typeObject, PbrMaterialState, "setEmissiveFactor", 1, 1, (thisObj->setEmissiveFactor(parameter[0].to<const Geometry::Vec3&>(rt)), thisEObj))
	
	//! [ESMF] Texture|Void MinSG.PbrMaterialState.getEmissiveTexture()
	ES_MFUN(typeObject, const PbrMaterialState, "getEmissiveTexture", 0, 0, thisObj->getEmissiveTexture() ? new E_Rendering::E_Texture(thisObj->getEmissiveTexture()) : nullptr)

	//! [ESMF] thisEObj MinSG.PbrMaterialState.setEmissiveTexture(Texture)
	ES_MFUN(typeObject, PbrMaterialState, "setEmissiveTexture", 1, 1, (thisObj->setEmissiveTexture(!parameter[0].toBool() ? nullptr : parameter[0].to<Rendering::Texture*>(rt)), thisEObj))

	//! [ESMF] Number MinSG.PbrMaterialState.getAlphaMode()
	ES_MFUN(typeObject, const PbrMaterialState, "getAlphaMode", 0, 0, static_cast<uint32_t>(thisObj->getAlphaMode()))

	//! [ESMF] thisEObj MinSG.PbrMaterialState.setAlphaMode(Number)
	ES_MFUN(typeObject, PbrMaterialState, "setAlphaMode", 1, 1, (thisObj->setAlphaMode(static_cast<PbrAlphaMode>(parameter[0].toUInt())), thisEObj))
	
	//! [ESMF] Number MinSG.PbrMaterialState.getShadingModel()
	ES_MFUN(typeObject, const PbrMaterialState, "getShadingModel", 0, 0, static_cast<uint32_t>(thisObj->getShadingModel()))

	//! [ESMF] thisEObj MinSG.PbrMaterialState.setShadingModel(Number)
	ES_MFUN(typeObject, PbrMaterialState, "setShadingModel", 1, 1, (thisObj->setShadingModel(static_cast<PbrShadingModel>(parameter[0].toUInt())), thisEObj))

	//! [ESMF] thisEObj MinSG.PbrMaterialState.setSearchPaths(FileLocator | Array)
	ES_MFUNCTION(typeObject, PbrMaterialState, "setSearchPaths", 1, 1, {
		auto* a = parameter[0].toType<EScript::Array>();
		if(a) {
			std::vector<std::string> paths;
			for(const auto& o : *a) {
				paths.emplace_back(o.toString());
			}
			thisObj->setSearchPaths(paths);
		} else {
			auto& locator = parameter[0].to<Util::FileLocator&>(rt);
			thisObj->setSearchPaths(locator.getSearchPaths());
		}
		return thisEObj;
	})
	
	ES_MGETSET(PbrMaterialState, uint32_t, BaseColorTexCoord)
	ES_MGETSET(PbrMaterialState, uint32_t, BaseColorTexUnit)
	ES_MGETSET(PbrMaterialState, float, MetallicFactor)
	ES_MGETSET(PbrMaterialState, float, RoughnessFactor)
	ES_MGETSET(PbrMaterialState, uint32_t, MetallicRoughnessTexCoord)
	ES_MGETSET(PbrMaterialState, uint32_t, MetallicRoughnessTexUnit)
	ES_MGETSET(PbrMaterialState, float, NormalScale)
	ES_MGETSET(PbrMaterialState, uint32_t, NormalTexCoord)
	ES_MGETSET(PbrMaterialState, uint32_t, NormalTexUnit)
	ES_MGETSET(PbrMaterialState, float, OcclusionStrength)
	ES_MGETSET(PbrMaterialState, uint32_t, OcclusionTexCoord)
	ES_MGETSET(PbrMaterialState, uint32_t, OcclusionTexUnit)
	ES_MGETSET(PbrMaterialState, uint32_t, EmissiveTexCoord)
	ES_MGETSET(PbrMaterialState, uint32_t, EmissiveTexUnit)
	ES_MGETSET(PbrMaterialState, float, AlphaCutoff)
	ES_MGETSET(PbrMaterialState, bool, DoubleSided)
	ES_MGETSET(PbrMaterialState, bool, UseSkinning)
	ES_MGETSET(PbrMaterialState, bool, UseIBL)
	ES_MGETSET(PbrMaterialState, bool, ReceiveShadow)
}
//---

//! [ctor]
E_PbrMaterialState::E_PbrMaterialState(PbrMaterialState * _obj, EScript::Type * type):
		E_State(_obj,type?type:typeObject){
}
//! [dtor]
E_PbrMaterialState::~E_PbrMaterialState(){
}

}
