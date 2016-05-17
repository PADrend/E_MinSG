#ifdef MINSG_EXT_THESISSTANISLAW

#include <E_MinSG/Ext/ThesisStanislaw/E_PhotonSampler.h>

#include <MinSG/Core/NodeRenderer.h>
#include <MinSG/Ext/ThesisStanislaw/PhotonSampler.h> 

#include <MinSG/Core/FrameContext.h>
#include <EScript/EScript.h>

#include <E_MinSG/Core/Nodes/E_Node.h>
#include <E_MinSG/Core/Nodes/E_CameraNode.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {
namespace ThesisStanislaw{
  
EScript::Type * E_PhotonSampler::getTypeObject() {
	// E_LightPatchRenderer ---|> E_NodeRendererState ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	return typeObject.get();
}


/**
 * initMembers
 */
void E_PhotonSampler::init(EScript::Namespace & lib) {
  // E_LightPatchRenderer ---|> E_NodeRendererState ---|> E_State ---|> Object
  EScript::Type * typeObject = E_PhotonSampler::getTypeObject();
  declareConstant(&lib,getClassName(),typeObject);
  
  declareConstant(typeObject, "POISSON", EScript::Number::create(static_cast<uint8_t>(MinSG::ThesisStanislaw::PhotonSampler::Sampling::POISSON)));
  
  //! [ESMF] new MinSG.PhotonSampler()
  ES_CTOR(typeObject,0,0,EScript::create(new MinSG::ThesisStanislaw::PhotonSampler))
  
  //! [ESMF] self PhotonSampler.setApproximatedScene(Node*)
  ES_MFUN(typeObject,MinSG::ThesisStanislaw::PhotonSampler,"setApproximatedScene",1,1, (thisObj->setApproximatedScene(parameter[0].to<MinSG::Node*>(rt)),thisEObj))
  
  //! [ESMF] self PhotonSampler.setCamera(CameraNode*)
  ES_MFUN(typeObject,MinSG::ThesisStanislaw::PhotonSampler,"setCamera",1,1, (thisObj->setCamera(parameter[0].to<MinSG::CameraNode*>(rt)),thisEObj))
  
  //! [ESMF] self PhotonSampler.setPhotonNumber(Number)
  ES_MFUN(typeObject,MinSG::ThesisStanislaw::PhotonSampler,"setPhotonNumber",1,1, (thisObj->setPhotonNumber( parameter[0].to<uint32_t>(rt) ),thisObj))
  
  //! [ESMF] self PhotonSampler.setSamplingStrategy(Number)
  ES_MFUN(typeObject,MinSG::ThesisStanislaw::PhotonSampler,"setSamplingStrategy",1,1, (thisObj->setSamplingStrategy( static_cast<uint8_t>(parameter[0].to<uint32_t>(rt)) ),thisObj))
  
  //! [ESMF] self PhotonSampler.resample()
  ES_MFUN(typeObject,MinSG::ThesisStanislaw::PhotonSampler,"resample",0,0, (thisObj->resample(),thisObj))

  addFactory<MinSG::ThesisStanislaw::PhotonSampler,E_PhotonSampler>();
}
//---

E_PhotonSampler::E_PhotonSampler(MinSG::ThesisStanislaw::PhotonSampler * _obj, EScript::Type * type):E_NodeRendererState(_obj,type?type:getTypeObject()){
}

E_PhotonSampler::~E_PhotonSampler() = default;

}
}


#endif // MINSG_EXT_THESISSTANISLAW
