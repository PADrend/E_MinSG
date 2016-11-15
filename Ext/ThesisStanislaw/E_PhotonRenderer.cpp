/*
	This file is part of the MinSG library extension ThesisStanislaw.
	Copyright (C) 2016 Stanislaw Eppinger

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_THESISSTANISLAW

#include "E_PhotonRenderer.h"

#include <E_MinSG/Ext/ThesisStanislaw/E_PhotonSampler.h>
#include <E_MinSG/Ext/ThesisStanislaw/E_LightPatchRenderer.h>

#include <E_MinSG/Core/Nodes/E_Node.h> 
#include <E_MinSG/Core/E_FrameContext.h>
#include <E_MinSG/Core/E_RenderParam.h>

#include <E_Rendering/Texture/E_Texture.h>

#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {
namespace ThesisStanislaw{
  
EScript::Type * E_PhotonRenderer::getTypeObject() {
	// E_PhotonRenderer ---|>  Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}


/**
 * initMembers
 */
void E_PhotonRenderer::init(EScript::Namespace & lib) {
  // E_LightPatchRenderer ---|> E_State ---|> Object
  EScript::Type * typeObject = E_PhotonRenderer::getTypeObject();
  declareConstant(&lib,getClassName(),typeObject);
  
  using namespace MinSG::ThesisStanislaw;  
  
  //! [ESMF] new MinSG.PhotonRenderer()
  ES_CTOR(typeObject,0,0,new E_PhotonRenderer)
  
  //! [ESMF] self PhotonRenderer.setShader(String, String)
  ES_MFUN(typeObject,PhotonRenderer,"setShader",2,2, (thisObj->setShader( parameter[0].toString(), parameter[1].toString() ),thisEObj))
  
  //! [ESMF] self PhotonRenderer.setApproximatedScene(Node*)
  ES_MFUN(typeObject,PhotonRenderer,"setApproximatedScene",1,1, (thisObj->setApproximatedScene(parameter[0].to<MinSG::Node*>(rt)),thisEObj))
  
  //! [ESMF] self PhotonRenderer.setLightPatchRenderer(LightPatchRenderer*)
  ES_MFUN(typeObject,PhotonRenderer,"setLightPatchRenderer",1,1, (thisObj->setLightPatchRenderer(parameter[0].to<LightPatchRenderer*>(rt)),thisEObj))
  
  //! [ESMF] self PhotonRenderer.setPhotonSampler(PhotonSampler*)
  ES_MFUN(typeObject,PhotonRenderer,"setPhotonSampler",1,1, (thisObj->setPhotonSampler(parameter[0].to<PhotonSampler*>(rt)),thisEObj))
  
  //! [ESMF] self PhotonRenderer.setSamplingResolution(Number, Number)
  ES_MFUN(typeObject,PhotonRenderer,"setSamplingResolution",2,2, (thisObj->setSamplingResolution( parameter[0].to<uint32_t>(rt), parameter[1].to<uint32_t>(rt) ),thisEObj))
    
  //! [ESMF] self PhotonRenderer.gatherLight(FrameContext, flags)
  ES_MFUN(typeObject, PhotonRenderer, "gatherLight",1, 2, (thisObj->gatherLight(parameter[0].to<MinSG::FrameContext&>(rt), parameter[1].toUInt(0)), thisEObj))
      
	//! [ESMF] Texture|Void MinSG.TextureState.getTexture()
	ES_MFUNCTION(typeObject, PhotonRenderer, "getLightTexture", 0,  0, {
			auto t = thisObj->getLightTexture();
			if(t.isNotNull())
				return new E_Rendering::E_Texture(t.get());
			else return EScript::create(nullptr);
	})
	//! [ESMF] Texture|Void MinSG.TextureState.getTexture()
	ES_MFUNCTION(typeObject, PhotonRenderer, "getNormalTexture", 0,  0, {
			auto t = thisObj->getNormalTexture();
			if(t.isNotNull())
				return new E_Rendering::E_Texture(t.get());
			else return EScript::create(nullptr);
	})
}
//---

}
}


#endif // MINSG_EXT_THESISSTANISLAW
