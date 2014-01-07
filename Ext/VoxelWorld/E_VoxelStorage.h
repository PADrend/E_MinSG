/*
	This file is part of the E_MinSG library extension VoxelWorld.
	Copyright (C) 2012-2013 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_VOXEL_WORLD

#ifndef E_MINSG_EXT_VOXELSTORAGE_H_
#define E_MINSG_EXT_VOXELSTORAGE_H_

#include <EScript/Objects/ReferenceObject.h>

#include <MinSG/Ext/VoxelWorld/VoxelWorld.h>
#include <Geometry/VoxelStorage.h>

namespace E_MinSG{
namespace VoxelWorld{

class E_VoxelStorage : public EScript::ReferenceObject<MinSG::VoxelWorld::simpleVoxelStorage_t, EScript::Policies::SameEObjects_ComparePolicy> {
		ES_PROVIDES_TYPE_NAME(VoxelStorage)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_VoxelStorage(uint32_t nullValue) : 
				ReferenceObject_t(getTypeObject(), nullValue) {}
        virtual ~E_VoxelStorage() = default;

};
}
}


ES_CONV_EOBJ_TO_OBJ(E_MinSG::VoxelWorld::E_VoxelStorage,		MinSG::VoxelWorld::simpleVoxelStorage_t&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_MinSG::VoxelWorld::E_VoxelStorage,		MinSG::VoxelWorld::simpleVoxelStorage_t*,		&(**eObj))

#endif // E_MINSG_EXT_VOXELSTORAGE_H_
#endif // MINSG_EXT_VOXEL_WORLD
