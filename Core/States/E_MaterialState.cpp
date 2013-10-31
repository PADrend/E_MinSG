/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_MaterialState.h"

#include "../../ELibMinSG.h"
#include <EScript/EScript.h>
#include <E_Rendering/Texture/E_Texture.h>
#include <E_Rendering/E_ParameterStructs.h>
#include <E_Util/Graphics/E_Color.h>

using namespace MinSG;
using namespace E_Rendering;

namespace E_MinSG {

EScript::Type* E_MaterialState::typeObject = nullptr;

/*!	(static)	*/
void E_MaterialState::init(EScript::Namespace & lib) {
	// MinSG.MaterialState ---|> MinSG.State ---|> [Object]
	typeObject = new EScript::Type(E_State::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::MaterialState,E_MaterialState>();

	//! new MinSG.MaterialState()
	ES_CTOR(typeObject, 0,0, new E_MaterialState(new MaterialState))

	//! [ESMF] Rendering.MaterialParameters MaterialState.getParameters()
	ES_MFUN(typeObject, const MaterialState, "getParameters", 0,  0,
				 EScript::create(thisObj->getParameters()))

	//! [ESMF] thisEObj MaterialState.setParameters(Rendering.MaterialParameters)
	ES_MFUN(typeObject, MaterialState, "setParameters", 1,  1,
				 (thisObj->setParameters(parameter[0].to<const Rendering::MaterialParameters&>(rt)), thisEObj))

	//! Util.Color4f materialState.getAmbient()
	ES_MFUN(typeObject, const MaterialState, "getAmbient", 0, 0, 
				EScript::create(thisObj->getParameters().getAmbient()))

	//! Util.Color4f materialState.getDiffuse()
	ES_MFUN(typeObject, const MaterialState, "getDiffuse", 0, 0, 
				EScript::create(thisObj->getParameters().getDiffuse()))

	//! Util.Color4f materialState.getSpecular()
	ES_MFUN(typeObject,const  MaterialState, "getSpecular", 0, 0, 
				EScript::create(thisObj->getParameters().getSpecular()))

	//! Number materialState.getShininess()
	ES_MFUN(typeObject, const MaterialState, "getShininess", 0, 0, 
				thisObj->getParameters().getShininess())

	//! thisEObj materialState.preMultiplyAlpha()
	ES_MFUN(typeObject, MaterialState, "preMultiplyAlpha", 0, 0, 
				(thisObj->preMultiplyAlpha(), thisEObj))

	//! thisEObj materialState.setAmbient(Util.Color4f)
	ES_MFUN(typeObject, MaterialState, "setAmbient", 1, 1, 
				(thisObj->changeParameters().setAmbient(parameter[0].to<Util::Color4f>(rt)),thisEObj))

	//! thisEObj materialState.setDiffuse(Util.Color4f)
	ES_MFUN(typeObject, MaterialState, "setDiffuse", 1, 1, 
				(thisObj->changeParameters().setDiffuse(parameter[0].to<Util::Color4f>(rt)),thisEObj))

	//! thisEObj materialState.setSpecular(Util.Color4f)
	ES_MFUN(typeObject, MaterialState, "setSpecular", 1, 1, 
				(thisObj->changeParameters().setSpecular(parameter[0].to<Util::Color4f>(rt)),thisEObj))

	//! thisEObj materialState.setShininess(Float)
	ES_MFUN(typeObject, MaterialState, "setShininess", 1, 1, 
				(thisObj->changeParameters().setShininess(parameter[0].toFloat()),thisEObj))


}
// ------------------------------------------------------------

/*!	(ctor)	*/
E_MaterialState::E_MaterialState(MaterialState * c, EScript::Type * type) :
	E_State(c, type ? type : typeObject) {
}

}
