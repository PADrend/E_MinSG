/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Behavior.h"

#include "../../ELibMinSG.h"

#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

//! (static)
E_Util::E_ObjectFactory<Behavior,E_Behavior> E_Behavior::factorySystem;

//! (static)
EScript::Type * E_Behavior::getTypeObject() {
	// E_Behavior ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

// -----

//! [static]
void E_Behavior::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());	
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::Behavior,E_Behavior>();


	declareConstant(typeObject,"CONTINUE", EScript::create(static_cast<uint32_t>(Behavior::CONTINUE)));
	declareConstant(typeObject,"FINISHED", EScript::create(static_cast<uint32_t>(Behavior::FINISHED)));

}

}
