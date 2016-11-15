/*
	This file is part of the MinSG library extension ThesisStanislaw.
	Copyright (C) 2016 Stanislaw Eppinger
	Copyright (C) 2016 Sascha Brandt

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_THESISSTANISLAW

#include "E_LightPatchRenderer.h"

#include <E_Rendering/Texture/E_Texture.h>
#include <E_MinSG/Core/Nodes/E_Node.h> 
#include <E_MinSG/Core/E_FrameContext.h>
#include <E_MinSG/Core/E_RenderParam.h>

#include <EScript/EScript.h>


using namespace EScript;
using namespace MinSG;

namespace E_MinSG {
namespace ThesisStanislaw{
  
EScript::Type * E_LightPatchRenderer::getTypeObject() {
	// E_LightPatchRenderer ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

/**
 * initMembers
 */
void E_LightPatchRenderer::init(EScript::Namespace & lib) {
  // E_LightPatchRenderer ---|> E_State ---|> Object
  EScript::Type * typeObject = E_LightPatchRenderer::getTypeObject();
  declareConstant(&lib,getClassName(),typeObject);
  
  using namespace MinSG::ThesisStanislaw;
  
  //! [ESMF] new MinSG.LightPatchRenderer()
  ES_CTOR(typeObject,0,0,new E_LightPatchRenderer)
  
  //! [ESMF] self LightPatchRenderer.setSamplingResolution(String, String)
  ES_MFUN(typeObject,LightPatchRenderer,"setShader",2,2, (thisObj->setShader( parameter[0].toString(), parameter[1].toString() ),thisEObj))
  
  //! [ESMF] self LightPatchRenderer.setApproximatedScene(Node*)
  ES_MFUN(typeObject,LightPatchRenderer,"setApproximatedScene",1,1, (thisObj->setApproximatedScene(parameter[0].to<MinSG::Node*>(rt)),thisEObj))
  
  //! [ESMF] self LightPatchRenderer.setSamplingResolution(Number, Number)
  ES_MFUN(typeObject,LightPatchRenderer,"setSamplingResolution",2,2, (thisObj->setSamplingResolution( parameter[0].to<uint32_t>(rt), parameter[1].to<uint32_t>(rt) ),thisEObj))
  
  //! [ESMF] self LightPatchRenderer.setSpotLights(Array)
  ES_MFUNCTION(typeObject, LightPatchRenderer, "setSpotLights", 1, 1, {
    Array * array = assertType<EScript::Array>(rt, parameter[0]);
    std::vector<MinSG::LightNode *> nodes;
    for(auto & element : *array){
      auto node = dynamic_cast<MinSG::LightNode*>(element.to<MinSG::Node*>(rt));
      if(node) nodes.push_back(node);
    }
    thisObj->setSpotLights(nodes);
    return thisEObj;
  })  

  //! [ESMF] self LightPatchRenderer.computeLightPatches(FrameContext, flags)
  ES_MFUN(typeObject, LightPatchRenderer, "computeLightPatches",1, 2, (thisObj->computeLightPatches(parameter[0].to<MinSG::FrameContext&>(rt), parameter[1].toUInt(0)), thisEObj))
    
  //! [ESMF] Texture|Void MinSG.TextureState.getTexture()
  ES_MFUNCTION(typeObject, LightPatchRenderer, "getPolygonIDTexture", 0,  0, {
      auto t = thisObj->getPolygonIDTexture();
      if(t.isNotNull())
        return new E_Rendering::E_Texture(t.get());
      else return EScript::create(nullptr);
  })
  //! [ESMF] Texture|Void MinSG.TextureState.getTexture()
  ES_MFUNCTION(typeObject, LightPatchRenderer, "getLightPatchTBO", 0,  0, {
      auto t = thisObj->getLightPatchTBO();
      if(t.isNotNull())
        return new E_Rendering::E_Texture(t.get());
      else return EScript::create(nullptr);
  })
  //! [ESMF] Texture|Void MinSG.TextureState.getTexture()
  ES_MFUNCTION(typeObject, LightPatchRenderer, "getNormalTexture", 0,  0, {
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
