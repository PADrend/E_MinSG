/*
	This file is part of the E_MinSG library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_FakeInstanceNode.h"
#include <EScript/Basics.h>

namespace E_MinSG {

EScript::Type * E_FakeInstanceNode::getTypeObject() {
	// E_FakeInstanceNode ---|> E_Node ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_Node::getTypeObject());
	return typeObject.get();
}

void E_FakeInstanceNode::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	EScript::declareConstant(&lib, getClassName(), typeObject);
	addFactory<MinSG::FakeInstanceNode, E_FakeInstanceNode>();
	
	using namespace MinSG;

	//! [ESF] new MinSG.FakeInstanceNode()
	ES_CTOR(typeObject, 0, 0, EScript::create(new MinSG::FakeInstanceNode))

	//! [ESMF] Node FakeInstanceNode.getFakePrototype()
	ES_MFUN(typeObject,FakeInstanceNode, "getFakePrototype", 0, 0,	 EScript::create(thisObj->getFakePrototype()))

	//! [ESMF] self FakeInstanceNode.setFakePrototype(Node)
	ES_MFUN(typeObject,FakeInstanceNode, "setFakePrototype", 1, 1,	 (thisObj->setFakePrototype(parameter[0].to<MinSG::Node*>(rt)), thisEObj))

}

}
