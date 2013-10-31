/*
	This file is part of the MinSG library extension Behaviours.
	Copyright (C) 2011 Sascha Brandt
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_SimplePhysics2.h"

#include "../../ELibMinSG.h"

#include <EScript/Basics.h>

//#include <iostream>
//#include <sstream>

namespace E_MinSG {


using namespace MinSG;

//! (static)
EScript::Type * E_SimplePhysics2::getTypeObject() {
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_Behavior::getTypeObject());
	return typeObject.get();
}


//! [static] initMembers
void E_SimplePhysics2::init(EScript::Namespace & lib) {
	using namespace MinSG;
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::SimplePhysics2,E_SimplePhysics2>();

	//! [ESMF] new MinSG.E_SimplePhysics2()
	ES_CTOR(typeObject,0,0,	new SimplePhysics2)

//	//! [ESMF] MinSG.Node|void MinSG.SimplePhysics2.getChild(int index)
//	ES_MFUNCTION(typeObject,const SimplePhysics2,"getChild",1,1,{
//		MinSG::Node * child=thisObj->getChild(parameter[0].toUInt());
//		if(child != nullptr) {
//			return EScript::create(child);
//		} else {
//			return EScript::create(nullptr);
//		}
//	})
}

}
