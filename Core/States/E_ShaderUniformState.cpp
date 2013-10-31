/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_ShaderUniformState.h"

#include <EScript/EScript.h>
#include "../../ELibMinSG.h"
#include <E_Rendering/Shader/E_Shader.h>
#include <E_Rendering/Shader/E_Uniform.h>

using namespace MinSG;
using namespace E_Rendering;

namespace E_MinSG {

//! (static)
EScript::Type * E_ShaderUniformState::getTypeObject() {
	// MinSG.ShaderUniformState ---|> MinSG.State ---|> [Object]
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

// -----

//! (static)
void E_ShaderUniformState::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::ShaderUniformState,E_ShaderUniformState>();

	//! [ESMF] new MinSG.ShaderUniformState()
	ES_CTOR(typeObject,0,0,EScript::create( new ShaderUniformState))

	//! [ESMF] new MinSG.ShaderUniformState.setUniform(Uniform u)
	ES_MFUN(typeObject, ShaderUniformState, "setUniform", 1, 1,(
			thisObj->setUniform(parameter[0].to<const Rendering::Uniform&>(rt)),thisEObj))

	//! [ESMF] new MinSG.ShaderUniformState.hasUniform(String u)
	ES_MFUN(typeObject, const ShaderUniformState, "hasUniform",1, 1, thisObj->hasUniform(parameter[0].toString()))

	//! [ESMF]Uniform MinSG.ShaderUniformState.getUniform(String u)
	ES_MFUN(typeObject, const ShaderUniformState, "getUniform",1, 1, EScript::create(thisObj->getUniform(parameter[0].toString())))

	//! [ESMF] thisEObj MinSG.ShaderUniformState.removeUniform(String u | Uniform)
	ES_MFUNCTION(typeObject, ShaderUniformState, "removeUniform", 1, 1,{
		E_Uniform * eu=parameter[0].toType<E_Uniform>();
		if(eu){
			thisObj->removeUniform(**eu);
		}else{
			thisObj->removeUniform(parameter[0].toString());
		}
		return thisEObj;
	})

	//! [ESMF] thisEObj MinSG.ShaderUniformState.removeUniforms()
	ES_MFUN(typeObject, ShaderUniformState, "removeUniforms",0, 0, (thisObj->removeUniforms(),thisEObj))


	//! [ESMF] Array MinSG.ShaderUniformState.getUniforms()
	ES_MFUNCTION(typeObject, ShaderUniformState, "getUniforms",0, 0, {
		const ShaderUniformState::uniformMap_t & uniforms=thisObj->getUniforms();
		EScript::Array *a = EScript::Array::create();
		for(ShaderUniformState::uniformMap_t::const_iterator it=uniforms.begin();it!=uniforms.end();++it)
			a->pushBack( EScript::create( (*it).second ));
		return a;
	})

}

// ------------------------------------------------------------

//! (ctor)
E_ShaderUniformState::E_ShaderUniformState(ShaderUniformState * c,EScript::Type * type):E_State(c,type?type:getTypeObject()) {
}

}
