/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_ShaderStrategy.h"

#include <E_Util/E_Utils.h>
#include <E_Util/IO/E_FileLocator.h>

#include <EScript/EScript.h>

namespace E_MinSG {
namespace BlueSurfels {
using namespace MinSG::BlueSurfels;

//! (static)
EScript::Type * E_ShaderStrategy::getTypeObject() {
	// E_ShaderStrategy ---|> E_AbstractSurfelStrategy ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractSurfelStrategy::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_ShaderStrategy::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<ShaderStrategy,E_ShaderStrategy>();

	//! [ESMF] new ShaderStrategy
	ES_CTOR(typeObject, 0, 0, new ShaderStrategy)
  
	ES_MFUN(typeObject, ShaderStrategy, "refreshShader", 0, 0, (thisObj->refreshShader(), thisEObj))
  ES_MGETSET(ShaderStrategy, std::string, ShaderVS)
  ES_MGETSET(ShaderStrategy, std::string, ShaderFS)
  ES_MGETSET(ShaderStrategy, std::string, ShaderGS)
	
	ES_MFUN(typeObject, ShaderStrategy, "addSearchPath", 1, 1, (thisObj->getFileLocator().addSearchPath(parameter[0].toString()), thisEObj))
}

} /* BlueSurfels */
} /* MinSG */
#endif // MINSG_EXT_BLUE_SURFELS