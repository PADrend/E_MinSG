#ifdef MINSG_EXT_THESISSTANISLAW

#include <E_MinSG/Ext/ThesisStanislaw/E_LightPatchRenderer.h>

#include <MinSG/Core/NodeRenderer.h>
#include <MinSG/Ext/ThesisStanislaw/LightPatchRenderer.h> 

#include <MinSG/Core/FrameContext.h>
#include <EScript/EScript.h>

#include <E_MinSG/Core/Nodes/E_Node.h> 

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {
namespace ThesisStanislaw{
  
EScript::Type * E_LightPatchRenderer::getTypeObject() {
	// E_LightPatchRenderer ---|> E_NodeRendererState ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	return typeObject.get();
}


/**
 * initMembers
 */
void E_LightPatchRenderer::init(EScript::Namespace & lib) {
  // E_LightPatchRenderer ---|> E_NodeRendererState ---|> E_State ---|> Object
  EScript::Type * typeObject = E_LightPatchRenderer::getTypeObject();
  declareConstant(&lib,getClassName(),typeObject);
  
  //! [ESMF] new MinSG.LightPatchRenderer()
  ES_CTOR(typeObject,0,0,EScript::create(new MinSG::ThesisStanislaw::LightPatchRenderer))
  
  //! [ESMF] self LightPatchRenderer.setApproximatedScene(Node*)
  ES_MFUN(typeObject,MinSG::ThesisStanislaw::LightPatchRenderer,"setApproximatedScene",1,1, (thisObj->setApproximatedScene(parameter[0].to<MinSG::Node*>(rt)),thisEObj))
  
  //! [ESMF] self LightPatchRenderer.setSamplingResolution(Number, Number)
  ES_MFUN(typeObject,MinSG::ThesisStanislaw::LightPatchRenderer,"setSamplingResolution",2,2, (thisObj->setSamplingResolution( parameter[0].to<uint32_t>(rt), parameter[1].to<uint32_t>(rt) ),thisObj))
  
  //! [ESMF] self LightPatchRenderer.setSpotLights(Array)
  ES_MFUNCTION(typeObject, MinSG::ThesisStanislaw::LightPatchRenderer, "setSpotLights", 1, 1, {
    Array * array = assertType<EScript::Array>(rt, parameter[0]);
    std::vector<MinSG::LightNode *> nodes;
    for(auto & element : *array){
      auto node = dynamic_cast<MinSG::LightNode*>(element.to<MinSG::Node*>(rt));
      if(node) nodes.push_back(node);
    }
    thisObj->setSpotLights(nodes);
  })

  addFactory<MinSG::ThesisStanislaw::LightPatchRenderer,E_LightPatchRenderer>();
}
//---

E_LightPatchRenderer::E_LightPatchRenderer(MinSG::ThesisStanislaw::LightPatchRenderer * _obj, EScript::Type * type):E_NodeRendererState(_obj,type?type:getTypeObject()){
}

E_LightPatchRenderer::~E_LightPatchRenderer() = default;

}
}


#endif // MINSG_EXT_THESISSTANISLAW
