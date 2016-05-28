#ifdef MINSG_EXT_THESISSTANISLAW

#include <E_MinSG/Ext/ThesisStanislaw/E_PhotonRenderer.h>

#include <MinSG/Ext/ThesisStanislaw/PhotonRenderer.h>
#include <MinSG/Ext/ThesisStanislaw/PhotonSampler.h>
#include <MinSG/Ext/ThesisStanislaw/LightPatchRenderer.h>

#include <MinSG/Core/NodeRenderer.h>

#include <MinSG/Core/FrameContext.h>
#include <EScript/EScript.h>

#include <E_MinSG/Core/Nodes/E_Node.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {
namespace ThesisStanislaw{
  
EScript::Type * E_PhotonRenderer::getTypeObject() {
	// E_LightPatchRenderer ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}


/**
 * initMembers
 */
void E_PhotonRenderer::init(EScript::Namespace & lib) {
  // E_LightPatchRenderer ---|> E_State ---|> Object
  EScript::Type * typeObject = E_PhotonRenderer::getTypeObject();
  declareConstant(&lib,getClassName(),typeObject);
  
  
  //! [ESMF] new MinSG.PhotonRenderer()
  ES_CTOR(typeObject,0,0,EScript::create(new MinSG::ThesisStanislaw::PhotonRenderer))
  
  //! [ESMF] self PhotonRenderer.setApproximatedScene(Node*)
  ES_MFUN(typeObject,MinSG::ThesisStanislaw::PhotonRenderer,"setApproximatedScene",1,1, (thisObj->setApproximatedScene(parameter[0].to<MinSG::Node*>(rt)),thisObj))
  
  //! [ESMF] self PhotonRenderer.setLightPatchRenderer(LightPatchRenderer*)
  ES_MFUN(typeObject,MinSG::ThesisStanislaw::PhotonRenderer,"setLightPatchRenderer",1,1, (thisObj->setLightPatchRenderer(dynamic_cast<MinSG::ThesisStanislaw::LightPatchRenderer*>(parameter[0].to<MinSG::State*>(rt))),thisObj))
  
  //! [ESMF] self PhotonRenderer.setPhotonSampler(PhotonSampler*)
  ES_MFUN(typeObject,MinSG::ThesisStanislaw::PhotonRenderer,"setPhotonSampler",1,1, (thisObj->setPhotonSampler(dynamic_cast<MinSG::ThesisStanislaw::PhotonSampler*>(parameter[0].to<MinSG::State*>(rt))),thisObj))
  
  //! [ESMF] self PhotonRenderer.setSamplingResolution(Number, Number)
  ES_MFUN(typeObject,MinSG::ThesisStanislaw::PhotonRenderer,"setSamplingResolution",2,2, (thisObj->setSamplingResolution( parameter[0].to<uint32_t>(rt), parameter[1].to<uint32_t>(rt) ),thisObj))
  
  addFactory<MinSG::ThesisStanislaw::PhotonRenderer,E_PhotonRenderer>();
}
//---

E_PhotonRenderer::E_PhotonRenderer(MinSG::ThesisStanislaw::PhotonRenderer * _obj, EScript::Type * type):E_State(_obj,type?type:getTypeObject()){
}

E_PhotonRenderer::~E_PhotonRenderer() = default;

}
}


#endif // MINSG_EXT_THESISSTANISLAW
