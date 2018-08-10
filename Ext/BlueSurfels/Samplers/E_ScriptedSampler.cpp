/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_ScriptedSampler.h"

#include <E_Rendering/Mesh/E_Mesh.h>

#include <E_Util/E_Utils.h>
#include <Util/Macros.h>

#include <EScript/EScript.h>

namespace E_MinSG {
namespace BlueSurfels {
using namespace MinSG::BlueSurfels;

Rendering::Mesh* ScriptedSampler::sampleSurfels(Rendering::Mesh* sourceMesh) {
	if(!sourceMesh) return nullptr;
		
	EScript::ObjRef eThis = EScript::create(this); // create a temporary E_ScriptedState
	if(eThis.isNull()){
		WARN("ScriptedSampler::sampleSurfels");
		return nullptr;
	}
	EScript::ObjRef eMesh = EScript::create(sourceMesh);

	// call obj.doEnableState(Node,RenderParam)
	// \note the 'context'-parameter is ignored, as the E_FrameContext can not be reconstructed from an existing FrameContext-object.
	static const EScript::StringId attrName("doSampleSurfels");
	EScript::ObjRef result = EScript::callMemberFunction(runtime, eThis.get(), attrName,
												EScript::ParameterValues(eMesh));
	return result.to<Rendering::Mesh*>(runtime);
}

//! (static)
EScript::Type * E_ScriptedSampler::getTypeObject() {
	// E_ScriptedSampler ---|> E_AbstractSurfelSampler ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractSurfelSampler::getTypeObject());
	return typeObject.get();
}

//! ScriptedSampler
void E_ScriptedSampler::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<ScriptedSampler,E_ScriptedSampler>();
	typeObject->allowUserInheritance(true);

	//! [ESMF] new ScriptedSampler
	ES_CTOR(typeObject, 0, 0, new ScriptedSampler(thisType, rt))
	
	//!	[ESMF] void ScriptedSampler.doSampleSurfels(Mesh) \note ObjectAttribute
	ES_FUN(typeObject,"doSampleSurfels",1,1,(EScript::create(nullptr)))
	EScript::markAttributeAsObjectAttribute(typeObject,"doSampleSurfels");
}

} /* BlueSurfels */
} /* MinSG */
#endif // MINSG_EXT_BLUE_SURFELS