/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_BlendingState.h"

#include "../../ELibMinSG.h"
#include <EScript/EScript.h>
#include <E_Rendering/E_ParameterStructs.h>
#include <E_Util/Graphics/E_Color.h>

using namespace MinSG;
namespace E_MinSG {

EScript::Type* E_BlendingState::typeObject = nullptr;

// -----

//! (static)
void E_BlendingState::init(EScript::Namespace & lib) {
	// MinSG.BlendingState ---|> MinSG.State ---|> [Object]
	typeObject = new EScript::Type(E_State::getTypeObject());
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::BlendingState,E_BlendingState>();

	//! [ESF] BlendingState new BlendingState()
	ES_CONSTRUCTOR(typeObject, 0, 1, {
		if(parameter.count() == 1) {
			return EScript::create(new MinSG::BlendingState(
				EScript::assertType<E_Rendering::E_ParameterStructs::E_BlendingParameters>(rt, parameter[0])->ref()
			));
		} else {
			return EScript::create(new MinSG::BlendingState());
		}
	})

	//! [ESMF] Rendering.BlendingParameters BlendingState.getParameters()
	ES_MFUN(typeObject, const BlendingState, "getParameters", 0,  0,
				 new E_Rendering::E_ParameterStructs::E_BlendingParameters(thisObj->getParameters()))

	//! [ESMF] thisEObj BlendingState.setParameters(Rendering.BlendingParameters)
	ES_MFUN(typeObject, BlendingState, "setParameters", 1,  1,
				 (thisObj->setParameters(EScript::assertType<E_Rendering::E_ParameterStructs::E_BlendingParameters>(rt, parameter[0])->ref()), thisEObj))

	//! [ESMF] number new BlendingState.getBlendEquation()
	ES_MFUN(typeObject, const BlendingState, "getBlendEquation", 0, 0, 
				static_cast<uint32_t>(thisObj->getParameters().getBlendEquationRGB()))

	//! [ESMF] thisEObj BlendingState.setBlendEquation(Number)
	ES_MFUN(typeObject, BlendingState, "setBlendEquation", 1, 1, 
				(thisObj->changeParameters().setBlendEquation(static_cast<Rendering::BlendingParameters::equation_t>(parameter[0].toUInt())), thisEObj))

	//! [ESMF] number new BlendingState.getBlendFuncSrc()
	ES_MFUN(typeObject,const  BlendingState, "getBlendFuncSrc", 0, 0, 
				static_cast<uint32_t>(thisObj->getParameters().getBlendFuncSrcRGB()))

	//! [ESMF] thisEObj BlendingState.setBlendFuncSrc(Number)
	ES_MFUN(typeObject, BlendingState, "setBlendFuncSrc", 1, 1, 
				(thisObj->changeParameters().setBlendFuncSrcRGB(static_cast<Rendering::BlendingParameters::function_t>(parameter[0].toUInt())), thisEObj))

	//! [ESMF] number new BlendingState.getBlendFuncDst()
	ES_MFUN(typeObject, const BlendingState, "getBlendFuncDst", 0, 0, 
				static_cast<uint32_t>(thisObj->getParameters().getBlendFuncDstRGB()))

	//! [ESMF] thisEObj BlendingState.setBlendFuncDst(Number)
	ES_MFUN(typeObject, BlendingState, "setBlendFuncDst", 1, 1, 
				(thisObj->changeParameters().setBlendFuncDstRGB(static_cast<Rendering::BlendingParameters::function_t>(parameter[0].toUInt())), thisEObj))

	//! [ESMF] number new BlendingState.getBlendConstAlpha()
	ES_MFUN(typeObject, const BlendingState, "getBlendConstAlpha", 0, 0, 
				thisObj->getParameters().getBlendColor().getA())

	//! [ESMF] thisEObj BlendingState.setBlendConstAlpha(Number)
	ES_MFUN(typeObject, BlendingState, "setBlendConstAlpha", 1, 1, 
				(thisObj->changeParameters().setBlendColor(Util::Color4f(0.0f, 0.0f, 0.0f, parameter[0].toFloat())), thisEObj))

	//! [ESMF] Bool new BlendingState.getBlendDepthMask()
	ES_MFUN(typeObject, const BlendingState, "getBlendDepthMask", 0, 0, 
				thisObj->getBlendDepthMask())

	//! [ESMF] thisEObj BlendingState.setBlendDepthMask(Bool)
	ES_MFUN(typeObject, BlendingState, "setBlendDepthMask", 1, 1, 
				(thisObj->setBlendDepthMask(parameter[0].toBool()), thisEObj))

}
// ------------------------------------------------------------
// ------------------------------------------------------------

//! (ctor)
E_BlendingState::E_BlendingState(BlendingState * c, EScript::Type * type) :
	E_State(c, type ? type : typeObject) {
}


}
