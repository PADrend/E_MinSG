/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "E_ListNode.h"
#include <EScript/EScript.h>

#include "../../ELibMinSG.h"

namespace E_MinSG {

//! (static)
EScript::Type * E_ListNode::getTypeObject() {
	// E_ListNode ---|> E_GroupNode ---|> E_Node ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_GroupNode::getTypeObject());
	return typeObject.get();
}


//! [static] initMembers
void E_ListNode::init(EScript::Namespace & lib) {
	using namespace MinSG;
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::ListNode,E_ListNode>();

	//! [ESMF] new MinSG.E_ListNode()
	ES_CTOR(typeObject,0,0,	new ListNode)

	//! [ESMF] MinSG.Node|void MinSG.ListNode.getChild(int index)
	ES_MFUNCTION(typeObject,const ListNode,"getChild",1,1,{
		MinSG::Node * child=thisObj->getChild(parameter[0].toUInt());
		if(child != nullptr) {
			return EScript::create(child);
		} else {
			return EScript::create(nullptr);
		}
	})
}

}
