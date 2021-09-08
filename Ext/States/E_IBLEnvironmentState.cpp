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
#include "E_IBLEnvironmentState.h"
#include "../../ELibMinSG.h"
#include "../ELibMinSGExt.h"
#include "../../Core/E_FrameContext.h"
#include <E_Rendering/Texture/E_Texture.h>
#include <E_Util/E_FileName.h>
#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

Type* E_IBLEnvironmentState::typeObject=nullptr;

//! initMembers
void E_IBLEnvironmentState::init(EScript::Namespace & lib) {
	// E_IBLEnvironmentState ----|> E_State ----|> Object
	typeObject = new EScript::Type(E_State::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::IBLEnvironmentState,E_IBLEnvironmentState>();

	//! [ESMF] new MinSG.IBLEnvironmentState()   
	ES_CTOR(typeObject,0,0,EScript::create( new IBLEnvironmentState))

	//! [ESMF] Texture|Void MinSG.IBLEnvironmentState.getEnvironmentMap()
	ES_MFUNCTION(typeObject, IBLEnvironmentState, "getEnvironmentMap", 0, 0, {
			Rendering::Texture * t = thisObj->getEnvironmentMap();
			if(t)
				return new E_Rendering::E_Texture(t);
			else return EScript::create(nullptr);
	})

	//! [ESMF] Bool MinSG.IBLEnvironmentState.hasEnvironmentMap()
	ES_MFUN(typeObject, const IBLEnvironmentState, "hasEnvironmentMap", 0, 0, thisObj->getEnvironmentMap() != nullptr)

	//! [ESMF] thisEObj MinSG.IBLEnvironmentState.setEnvironmentMap(Texture)
	ES_MFUNCTION(typeObject, IBLEnvironmentState, "setEnvironmentMap", 1, 1, {
			if(!parameter[0].toBool()){
				thisObj->setEnvironmentMap(nullptr);
			} else {
				thisObj->setEnvironmentMap(parameter[0].to<Rendering::Texture*>(rt));
			}
			return thisEObj;
	})

	//! [ESMF] thisEObj MinSG.IBLEnvironmentState.loadEnvironmentMapFromHDR(FileName)
	ES_MFUN(typeObject, IBLEnvironmentState, "loadEnvironmentMapFromHDR", 1, 1, (thisObj->loadEnvironmentMapFromHDR(Util::FileName(parameter[0].toString())), thisEObj))

	//! [ESMF] String MinSG.IBLEnvironmentState.getHdrFile()
	ES_MFUN(typeObject, const IBLEnvironmentState, "getHdrFile", 0, 0, new E_Util::E_FileName(thisObj->getHdrFile()))

	//! [ESMF] String MinSG.IBLEnvironmentState.getLOD()
	ES_MFUN(typeObject, const IBLEnvironmentState, "getLOD", 0, 0, thisObj->getLOD())

	//! [ESMF] thisEObj MinSG.IBLEnvironmentState.setLOD(Number)
	ES_MFUN(typeObject, IBLEnvironmentState, "setLOD", 1, 1, (thisObj->setLOD(parameter[0].toFloat()), thisEObj))

	//! [ESMF] String MinSG.IBLEnvironmentState.isDrawEnvironmentEnabled()
	ES_MFUN(typeObject, const IBLEnvironmentState, "isDrawEnvironmentEnabled", 0, 0, thisObj->isDrawEnvironmentEnabled())

	//! [ESMF] thisEObj MinSG.IBLEnvironmentState.setDrawEnvironment(Bool)
	ES_MFUN(typeObject, IBLEnvironmentState, "setDrawEnvironment", 1, 1, (thisObj->setDrawEnvironment(parameter[0].toBool()), thisEObj))

	//! [ESMF] Texture|Void MinSG.IBLEnvironmentState.getIrradianceMap()
	ES_MFUNCTION(typeObject, IBLEnvironmentState, "getIrradianceMap", 0, 0, {
			Rendering::Texture * t = thisObj->getIrradianceMap();
			if(t)
				return new E_Rendering::E_Texture(t);
			else return EScript::create(nullptr);
	})

	//! [ESMF] Texture|Void MinSG.IBLEnvironmentState.getPrefilteredEnvMap()
	ES_MFUNCTION(typeObject, IBLEnvironmentState, "getPrefilteredEnvMap", 0, 0, {
			Rendering::Texture * t = thisObj->getPrefilteredEnvMap();
			if(t)
				return new E_Rendering::E_Texture(t);
			else return EScript::create(nullptr);
	})

	//! [ESMF] Texture|Void MinSG.IBLEnvironmentState.getBrdfLUT()
	ES_MFUNCTION(typeObject, IBLEnvironmentState, "getBrdfLUT", 0, 0, {
			Rendering::Texture * t = thisObj->getBrdfLUT();
			if(t)
				return new E_Rendering::E_Texture(t);
			else return EScript::create(nullptr);
	})

	//! [ESMF] thisEObj MinSG.IBLEnvironmentState.generateFromScene(FrameContext, Node, flags)
	ES_MFUNCTION(typeObject, IBLEnvironmentState, "generateFromScene",2, 3, {
		FrameContext & context = parameter[0].to<MinSG::FrameContext&>(rt);
		Node * node = parameter[1].to<MinSG::Node*>(rt);
		if (parameter.count() == 2) {
			thisObj->generateFromScene(context, node,RenderParam());
		} else {
			thisObj->generateFromScene(context, node, parameter[2].toUInt());
		}
		return thisEObj;
	})

	ES_MGETSET(IBLEnvironmentState, float, Rotation);
	ES_MGETSET(IBLEnvironmentState, float, RotationDeg);
}
//---

//! [ctor]
E_IBLEnvironmentState::E_IBLEnvironmentState(IBLEnvironmentState * _obj, EScript::Type * type):
		E_State(_obj,type?type:typeObject){
}
//! [dtor]
E_IBLEnvironmentState::~E_IBLEnvironmentState(){
}

}
