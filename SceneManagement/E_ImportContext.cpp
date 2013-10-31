/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_ImportContext.h"
#include <EScript/EScript.h>

using namespace MinSG::SceneManagement;
using namespace EScript;

namespace E_MinSG {

//! (static)
Type * E_ImportContext::getTypeObject(){
	// [E_ImportContext] ---|> [Object]
	static EScript::Type * typeObject = new EScript::Type(Object::getTypeObject());
	return typeObject;
}

//! initMembers
void E_ImportContext::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
}

}
