/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_NodeRendererState.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include "../../ELibMinSG.h"


namespace E_MinSG {

EScript::Type * E_NodeRendererState::getTypeObject() {
	// E_NodeRendererState ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

void E_NodeRendererState::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<MinSG::NodeRendererState,E_NodeRendererState>();
	
	using namespace MinSG;
	
	//! [ESF] String E_NodeRendererState.getSourceChannel()
	ES_MFUN(typeObject, const NodeRendererState, "getSourceChannel", 0, 0, 
				thisObj->getSourceChannel().toString())
	
	//! [ESF] thisEObj E_NodeRendererState.setSourceChannel(String)
	ES_MFUN(typeObject, NodeRendererState, "setSourceChannel",1, 1,  
				( thisObj->setSourceChannel( parameter[0].toString()),thisEObj))
}

}
