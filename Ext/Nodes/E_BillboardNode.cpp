/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_BillboardNode.h"
#include <MinSG/Ext/Nodes/BillboardNode.h>
#include "../../Core/Nodes/E_GeometryNode.h"
#include "../../ELibMinSG.h"
#include <E_Geometry/E_Rect.h>
#include <EScript/EScript.h>

using namespace E_Geometry;

namespace E_MinSG {

EScript::Type* E_BillboardNode::typeObject = nullptr;

//!	[static] initMembers
void E_BillboardNode::init(EScript::Namespace & lib) {
	// MinSG.BillboardNode ---|> MinSG.GeometryNode ---|> MinSG.Node ---|> Object
	typeObject = new EScript::Type(E_GeometryNode::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::BillboardNode,E_BillboardNode>();
	//!	[ESMF] new MinSG.E_BillboardNode(Rect,Bool rotateUpAxis[,rotateRightAxis=false)
	ES_CTOR(typeObject,2,3, EScript::create(
			new MinSG::BillboardNode (EScript::assertType<E_Rect>(rt,parameter[0])->ref(),parameter[1].toBool(),parameter[2].toBool(false))))


	//! [ESMF] self BillboardNode.setRect(Geometry::Rect)
	ES_MFUN(typeObject,MinSG::BillboardNode, "setRect", 1, 1,	 (thisObj->setRect(parameter[0].to<Geometry::Rect>(rt)), thisEObj))

}
// ------------------------------------------------------------

E_BillboardNode::E_BillboardNode(MinSG::BillboardNode * gNode, EScript::Type * type) :
	E_GeometryNode(gNode, type ? type : typeObject) {
}

E_BillboardNode::~E_BillboardNode() {
}

}
