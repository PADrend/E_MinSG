/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_ShaderState.h"

#include "../../ELibMinSG.h"
#include <MinSG/SceneManagement/SceneDescription.h>
#include <E_Rendering/Shader/E_Shader.h>
#include <E_Rendering/Shader/E_Uniform.h>
#include <EScript/EScript.h>

using namespace MinSG;
using namespace E_Rendering;

namespace E_MinSG {

//! (static)
EScript::Type * E_ShaderState::getTypeObject() {
	// MinSG.ShaderState ---|> MinSG.State ---|> [Object]
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

// -----

//! (static)
void E_ShaderState::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::ShaderState,E_ShaderState>();

	//! [ESMF] new MinSG.ShaderState(Shader s = nullptr)
	ES_CTOR(typeObject,0,1,(
			EScript::create( parameter.count()==0 ? new ShaderState() :
								new ShaderState(parameter[0].to<Rendering::Shader*>(rt)))))


	//! [ESMF] new MinSG.ShaderState.setUniform(Uniform u)
	ES_MFUN(typeObject, ShaderState, "setUniform", 1, 1,(
			thisObj->setUniform(parameter[0].to<const Rendering::Uniform&>(rt)),thisEObj))

	//! [ESMF] new MinSG.ShaderState.hasUniform(String u)
	ES_MFUN(typeObject, const ShaderState, "hasUniform",1, 1, thisObj->hasUniform(parameter[0].toString()))

	//! [ESMF]Uniform MinSG.ShaderState.getUniform(String u)
	ES_MFUN(typeObject, const ShaderState, "getUniform",1, 1, EScript::create(thisObj->getUniform(parameter[0].toString())))

	//! [ESMF]Shader|void MinSG.ShaderState.getShader()
	ES_MFUNCTION(typeObject, ShaderState, "getShader", 0, 0,{
		Rendering::Shader * s=thisObj->getShader();
		if(s)
			return EScript::create(s);
		return EScript::create(nullptr);
	})

	//! [ESMF] thisEObj MinSG.ShaderState.setShader(Shader s)
	ES_MFUN(typeObject, ShaderState, "setShader",1, 1, (
			thisObj->setShader(parameter[0].to<Rendering::Shader*>(rt)),thisEObj))

	//! [ESMF] thisEObj MinSG.ShaderState.removeUniform(String u | Uniform)
	ES_MFUNCTION(typeObject, ShaderState, "removeUniform",1, 1, {
		E_Uniform * eu=parameter[0].toType<E_Uniform>();
		if(eu){
			thisObj->removeUniform(**eu);
		}else{
			thisObj->removeUniform(parameter[0].toString());
		}
		return thisEObj;
	})

	//! [ESMF] thisEObj MinSG.ShaderState.removeUniforms()
	ES_MFUN(typeObject, ShaderState, "removeUniforms",0, 0, (thisObj->removeUniforms(),thisEObj))


	//! [ESMF] Array MinSG.ShaderState.getUniforms()
	ES_MFUNCTION(typeObject, ShaderState, "getUniforms",0, 0, {
		const ShaderState::uniformMap_t & uniforms=thisObj->getUniforms();
		EScript::Array *a = EScript::Array::create();
		for(ShaderState::uniformMap_t::const_iterator it=uniforms.begin();it!=uniforms.end();++it)
			a->pushBack( EScript::create( (*it).second ));
		return a;
	})
		
	typeObject->setAttribute("STATE_ATTR_SHADER_FILES",
					EScript::Attribute(EScript::create(MinSG::SceneManagement::Consts::STATE_ATTR_SHADER_FILES.toString()),EScript::Attribute::TYPE_ATTR_BIT|EScript::Attribute::CONST_BIT));

	typeObject->setAttribute("STATE_ATTR_SHADER_NAME",
					EScript::Attribute(EScript::create(MinSG::SceneManagement::Consts::STATE_ATTR_SHADER_NAME.toString()),EScript::Attribute::TYPE_ATTR_BIT|EScript::Attribute::CONST_BIT));
}

// ------------------------------------------------------------

//! (ctor)
E_ShaderState::E_ShaderState(ShaderState * c,EScript::Type * type):E_State(c,type?type:getTypeObject()) {
}

}
