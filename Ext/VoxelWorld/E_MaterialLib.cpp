/*
	This file is part of the E_MinSG library extension VoxelWorld.
	Copyright (C) 2012-2013 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_VOXEL_WORLD

#include "E_MaterialLib.h"

#include <EScript/Basics.h>
//#include <EScript/StdObjects.h>

namespace E_MinSG{
namespace VoxelWorld{
//
//! (static)
EScript::Type * E_MaterialLib::getTypeObject() {
	// E_MaterialLib ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members 
void E_MaterialLib::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_MaterialLib::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace MinSG;
	using namespace MinSG::VoxelWorld;

	//! [ESF] new MaterialLib
	ES_CTOR(typeObject,0,0, new E_MaterialLib)

//	//! [ESMF] Number MaterialLib.get(Vec3)
//	ES_MFUN(typeObject, const simpleMaterialLib_t,"get",1,1,	thisObj->get(parameter[0].to<Geometry::_Vec3<int32_t>>(rt)))
//	
//	//! [ESMF] Box MaterialLib.getBlockBounds()
//	ES_MFUN(typeObject, const simpleMaterialLib_t,"getBlockBounds",0,0,	thisObj->getBlockBounds())
//	
//	//! [ESMF] self MaterialLib.fill(Box, int)
//	ES_MFUN(typeObject, simpleMaterialLib_t,"fill",2,2,	(thisObj->fill(parameter[0].to<Geometry::_Box<int32_t>>(rt),parameter[1].to<uint32_t>(rt)),thisEObj))
//
//	//! [ESMF] self MaterialLib.set(Vec3, int)
//	ES_MFUN(typeObject, simpleMaterialLib_t,"set",2,2,	(thisObj->set(parameter[0].to<Geometry::_Vec3<int32_t>>(rt),parameter[1].to<uint32_t>(rt)),thisEObj))

}
}
}
#endif // MINSG_EXT_VOXEL_WORLD

