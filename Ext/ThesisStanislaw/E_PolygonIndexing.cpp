/*
	This file is part of the MinSG library.
	Copyright (C) 20016 Stanislaw Eppinger

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

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
  
EScript::Type * E_PolygonIndexingState::getTypeObject() {
	// E_PolygonIndexingState ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

/**
 * initMembers
 */
void E_PolygonIndexingState::init(EScript::Namespace & lib) {
  // E_PolygonIndexingState ---|> E_State ---|> Object
  EScript::Type * typeObject = E_PolygonIndexingState::getTypeObject();
  declareConstant(&lib,getClassName(),typeObject);
  addFactory<MinSG::ThesisStanislaw::PolygonIndexingState,E_PolygonIndexingState>();
  
  //! [ESMF] new MinSG.PolygonIndexingState()
  ES_CTOR(typeObject,0,0,EScript::create(new MinSG::ThesisStanislaw::PolygonIndexingState))

  //! [ESMF] self PolygonIndexingState.setDebugOutput(bool)
  ES_MFUN(typeObject,MinSG::ThesisStanislaw::PolygonIndexingState,"setDebugOutput",1,1, (thisObj->setDebugOutput(parameter[0].toBool()),thisObj))
  
  //! [ESMF] self PolygonIndexingState.reupdatePolygonIDs()
  ES_MFUN(typeObject,MinSG::ThesisStanislaw::PolygonIndexingState,"reupdatePolygonIDs",0,0, (thisObj->reupdatePolygonIDs(),thisObj))

}
//---

E_PolygonIndexingState::E_PolygonIndexingState(MinSG::ThesisStanislaw::PolygonIndexingState * _obj, EScript::Type * type):E_State(_obj,type?type:getTypeObject()){
}

E_PolygonIndexingState::~E_PolygonIndexingState() = default;

}
}

#endif // MINSG_EXT_THESISSTANISLAW
