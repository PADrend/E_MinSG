/*
	This file is part of the MinSG library extension ThesisStanislaw.
	Copyright (C) 2016 Stanislaw Eppinger

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_THESISSTANISLAW

#include "E_PhotonSampler.h"

#include <E_MinSG/Core/Nodes/E_Node.h> 
#include <E_MinSG/Core/E_FrameContext.h>
#include <E_MinSG/Core/E_RenderParam.h>
#include <E_MinSG/Core/Nodes/E_CameraNode.h>

#include <E_Rendering/Texture/E_Texture.h>
#include <E_Rendering/Mesh/E_Mesh.h>
#include <E_Rendering/Shader/E_Shader.h>
#include <E_Rendering/E_RenderingContext.h>
#include <E_Rendering/E_FBO.h>

#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {
namespace ThesisStanislaw{
  
EScript::Type * E_PhotonSampler::getTypeObject() {
	// E_PhotonSampler ---|>  Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

/**
 * initMembers
 */
void E_PhotonSampler::init(EScript::Namespace & lib) {
  // E_LightPatchRenderer ---|> E_State ---|> Object
  EScript::Type * typeObject = E_PhotonSampler::getTypeObject();
  declareConstant(&lib,getClassName(),typeObject);
  
  using namespace MinSG::ThesisStanislaw;
  
  declareConstant(typeObject, "POISSON", EScript::Number::create(static_cast<uint8_t>(PhotonSampler::Sampling::POISSON)));
  declareConstant(typeObject, "UNIFORM", EScript::Number::create(static_cast<uint8_t>(PhotonSampler::Sampling::UNIFORM)));
  
  //! [ESMF] new MinSG.PhotonSampler()
  ES_CTOR(typeObject,0,0,new E_PhotonSampler)
  
  //! [ESMF] self PhotonSampler.setShader(String, String)
  ES_MFUN(typeObject,PhotonSampler,"setShader",2,2, (thisObj->setShader( parameter[0].toString(), parameter[1].toString() ),thisEObj))
  
  //! [ESMF] self PhotonSampler.setApproximatedScene(Node*)
  ES_MFUN(typeObject,PhotonSampler,"setApproximatedScene",1,1, (thisObj->setApproximatedScene(parameter[0].to<MinSG::Node*>(rt)),thisEObj))
    
  //! [ESMF] self PhotonSampler.setPhotonNumber(Number)
  ES_MFUN(typeObject,PhotonSampler,"setPhotonNumber",1,1, (thisObj->setPhotonNumber( parameter[0].to<uint32_t>(rt) ),thisEObj))
  
  //! [ESMF] self PhotonSampler.setSamplingStrategy(Number)
  ES_MFUN(typeObject,PhotonSampler,"setSamplingStrategy",1,1, (thisObj->setSamplingStrategy( static_cast<uint8_t>(parameter[0].to<uint32_t>(rt)) ),thisEObj))
  
  //! [ESMF] self PhotonSampler.outputPhotonBuffer()
  ES_MFUN(typeObject,PhotonSampler,"outputPhotonBuffer",0,0, (thisObj->outputPhotonBuffer(),thisEObj))
  
  //! [ESMF] self PhotonSampler.bindSamplingTexture(RenderingContext, location)
  ES_MFUN(typeObject,PhotonSampler,"bindSamplingTexture",2,2, (thisObj->bindSamplingTexture(parameter[0].to<Rendering::RenderingContext&>(rt), parameter[1].toUInt()),thisEObj))
  
  //! [ESMF] self PhotonSampler.unbindSamplingTexture(RenderingContext, location)
  ES_MFUN(typeObject,PhotonSampler,"unbindSamplingTexture",2,2, (thisObj->unbindSamplingTexture(parameter[0].to<Rendering::RenderingContext&>(rt), parameter[1].toUInt()),thisEObj))

  //! [ESMF] self PhotonSampler.bindPhotonBuffer(location)
  ES_MFUN(typeObject,PhotonSampler,"bindPhotonBuffer",1,1, (thisObj->bindPhotonBuffer(parameter[0].toUInt()),thisEObj))
  
  //! [ESMF] self PhotonSampler.unbindPhotonBuffer(location)
  ES_MFUN(typeObject,PhotonSampler,"unbindPhotonBuffer",1,1, (thisObj->unbindPhotonBuffer(parameter[0].toUInt()),thisEObj))
  
  //! [ESMF] Number PhotonSampler.getSamplingTextureSize()
  ES_MFUN(typeObject,PhotonSampler,"getSamplingTextureSize",0,0, EScript::Number::create(thisObj->getSamplingTextureSize()))
  
  //! [ESMF] self PhotonSampler.computePhotonSamples(FrameContext, flags)
  ES_MFUN(typeObject, PhotonSampler, "computePhotonSamples",1, 2, (thisObj->computePhotonSamples(parameter[0].to<MinSG::FrameContext&>(rt), parameter[1].toUInt(0)), thisEObj))
  
	//! [ESMF] Texture|Void MinSG.TextureState.getTexture()
	ES_MFUNCTION(typeObject, PhotonSampler, "getPosTexture", 0,  0, {
			auto t = thisObj->getPosTexture();
			if(t.isNotNull())
				return new E_Rendering::E_Texture(t.get());
			else return EScript::create(nullptr);
	})
	//! [ESMF] Texture|Void MinSG.TextureState.getTexture()
	ES_MFUNCTION(typeObject, PhotonSampler, "getNormalTexture", 0,  0, {
			auto t = thisObj->getNormalTexture();
			if(t.isNotNull())
				return new E_Rendering::E_Texture(t.get());
			else return EScript::create(nullptr);
	})
	//! [ESMF] Texture|Void MinSG.TextureState.getTexture()
	ES_MFUNCTION(typeObject, PhotonSampler, "getSamplingTexture", 0,  0, {
			auto t = thisObj->getSamplingTexture();
			if(t.isNotNull())
				return new E_Rendering::E_Texture(t.get());
			else return EScript::create(nullptr);
	})
	//! [ESMF] Texture|Void MinSG.TextureState.getTexture()
	ES_MFUNCTION(typeObject, PhotonSampler, "getMatrixTexture", 0,  0, {
			auto t = thisObj->getMatrixTexture();
			if(t.isNotNull())
				return new E_Rendering::E_Texture(t.get());
			else return EScript::create(nullptr);
	})
  
}
//---
}
}


#endif // MINSG_EXT_THESISSTANISLAW
