/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_GroupNode.h"

#include <EScript/EScript.h>
#include "../../ELibMinSG.h"

namespace E_MinSG {

//! (static)
EScript::Type * E_GroupNode::getTypeObject() {
	// E_GroupNode ---|> E_Node ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_Node::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_GroupNode::init(EScript::Namespace & lib) {
	using namespace MinSG;
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::GroupNode,E_GroupNode>();

	//! [ESMF] new GroupNode([string name])
	ES_CONSTRUCTOR(typeObject,0,1,{
		EScript::throwRuntimeException("MinSG.GroupNode is abstract");
		return nullptr;
	})

	//! [ESMF] self GroupNode.addChild(MinSGNode child)
	ES_MFUN(typeObject,GroupNode,"addChild",1,1,
			(thisObj->addChild(parameter[0].to<MinSG::Node*>(rt)),thisEObj))

	//!	[ESMF] Number GroupNode.countChildren()
	ES_MFUN(typeObject,const GroupNode,"countChildren",0,0,
			static_cast<uint32_t>(thisObj->countChildren()))

	//! [ESMF] self GroupNode.removeChild(MinSGNode child)
	ES_MFUN(typeObject,GroupNode,"removeChild",1,1,
			(thisObj->removeChild(parameter[0].to<MinSG::Node*>(rt)),thisEObj))

}

}
