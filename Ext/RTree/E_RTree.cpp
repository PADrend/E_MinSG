/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_RTREE

#include "../../ELibMinSG.h"
#include "E_RTree.h"
#include <EScript/EScript.h>

namespace E_MinSG {

EScript::Type * E_RTree::typeObject = nullptr;

//! [static] initMembers
void E_RTree::init(EScript::Namespace & lib) {
	typeObject = new EScript::Type(E_ListNode::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	
	//! [ESMF] new MinSG.RTree(minEntries, maxEntries)	
	ES_CTOR(typeObject,2,2,EScript::create(new MinSG::RTree(parameter[0].toInt(), parameter[1].toInt())))

	addFactory<MinSG::RTree,E_RTree>();
}

// ------------------------------------------------------------

E_RTree::E_RTree(MinSG::RTree * treeNode, EScript::Type * type) :
	E_ListNode(treeNode, type ? type : typeObject) {
}

E_RTree::~E_RTree() {
}

}

#endif /* MINSG_EXT_RTREE */
