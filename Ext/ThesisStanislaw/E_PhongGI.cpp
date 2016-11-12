/*
	This file is part of the MinSG library.
	Copyright (C) 20016 Stanislaw Eppinger

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_THESISSTANISLAW

#include <MinSG/Ext/ThesisStanislaw/PhotonSampler.h>
#include <MinSG/Ext/ThesisStanislaw/PhotonRenderer.h>

#include <E_MinSG/Ext/ThesisStanislaw/E_PhongGI.h>

#include <MinSG/Core/NodeRenderer.h>
#include <MinSG/Ext/ThesisStanislaw/PhongGI.h>

#include <MinSG/Core/FrameContext.h>
#include <EScript/EScript.h>

#include <E_MinSG/Core/Nodes/E_Node.h>
#include <E_MinSG/Core/States/E_State.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {
namespace ThesisStanislaw{
  
EScript::Type * E_PhongGI::getTypeObject() {
	// E_PhongGI ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}


/**
 * initMembers
 */
void E_PhongGI::init(EScript::Namespace & lib) {
  // E_PhongGI ---|> E_State ---|> Object
  EScript::Type * typeObject = E_PhongGI::getTypeObject();
  declareConstant(&lib,getClassName(),typeObject);
  
  //! [ESMF] new MinSG.PhongGI()
  ES_CTOR(typeObject,0,0,EScript::create(new MinSG::ThesisStanislaw::PhongGI))

  //! [ESMF] self PhongGI.setPhotonSampler(PhotonSampler*)
  ES_MFUN(typeObject,MinSG::ThesisStanislaw::PhongGI,"setPhotonSampler",1,1, (thisObj->setPhotonSampler(dynamic_cast<MinSG::ThesisStanislaw::PhotonSampler*>(parameter[0].to<MinSG::State*>(rt))),thisObj))
  
  addFactory<MinSG::ThesisStanislaw::PhongGI,E_PhongGI>();
}
//---

E_PhongGI::E_PhongGI(MinSG::ThesisStanislaw::PhongGI * _obj, EScript::Type * type):E_State(_obj,type?type:getTypeObject()){
}

E_PhongGI::~E_PhongGI() = default;

}
}


#endif // MINSG_EXT_THESISSTANISLAW
