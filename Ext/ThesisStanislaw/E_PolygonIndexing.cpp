#ifdef MINSG_EXT_THESISSTANISLAW

#include <E_MinSG/Ext/ThesisStanislaw/E_PolygonIndexing.h>

#include <MinSG/Core/NodeRenderer.h>
#include <MinSG/Ext/ThesisStanislaw/PolygonIndexing.h> 

#include <MinSG/Core/FrameContext.h>
#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {
namespace ThesisStanislaw{
  
Type* E_PolygonIndexingState::typeObject=nullptr;


/**
 * initMembers
 */
void E_PolygonIndexingState::init(EScript::Namespace & lib) {
  // E_PolygonIndexingState ---|> E_NodeRendererState ---|> E_State ---|> Object
  typeObject = E_PolygonIndexingState::getTypeObject();
  declareConstant(&lib,getClassName(),typeObject);
  addFactory<MinSG::ThesisStanislaw::PolygonIndexingState,E_PolygonIndexingState>();
  
  //! [ESMF] new MinSG.PolygonIndexingState()
  ES_CTOR(typeObject,0,0,EScript::create(new MinSG::ThesisStanislaw::PolygonIndexingState))

  //! [ESMF] self PolygonIndexingState.setDebugOutput(bool)
  ES_MFUN(typeObject,MinSG::ThesisStanislaw::PolygonIndexingState,"setDebugOutput",1,1, (thisObj->setDebugOutput(parameter[0].toBool()),thisEObj))

  //! [ESMF] Bool ColorCubeRenderer.isHighlightEnabled()
  //ES_MFUN(typeObject,ColorCubeRenderer,"isHighlightEnabled",0,0,	thisObj->isHighlightEnabled())

}
//---

E_PolygonIndexingState::E_PolygonIndexingState(MinSG::ThesisStanislaw::PolygonIndexingState * _obj, EScript::Type * type):E_NodeRendererState(_obj,type?type:typeObject){
}

E_PolygonIndexingState::~E_PolygonIndexingState() = default;

}
}

#endif // MINSG_EXT_THESISSTANISLAW
