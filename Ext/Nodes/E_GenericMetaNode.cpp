/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_GenericMetaNode.h"

#include "../../ELibMinSG.h"
#include <E_Geometry/E_Box.h>
#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

//! (static)
EScript::Type * E_GenericMetaNode::getTypeObject() {
	// E_GenericMetaNode ---|> E_Node ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_Node::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_GenericMetaNode::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::GenericMetaNode,E_GenericMetaNode>();

	//! [ESF] new MinSG.GenericMetaNode()
	ES_CTOR(typeObject,0,0,EScript::create(new GenericMetaNode))

	//! [ESMF] self genericMetaNode.setBB( Geometry.Box )
	ES_MFUN(typeObject,GenericMetaNode,"setBB",1,1,	(thisObj->setBB(parameter[0].to<const Geometry::Box&>(rt)),thisEObj))

}

}
