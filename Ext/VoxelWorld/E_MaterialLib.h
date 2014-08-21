/*
	This file is part of the E_MinSG library extension VoxelWorld.
	Copyright (C) 2012-2013 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_VOXEL_WORLD

#ifndef E_MINSG_EXT_MATERIALLIB_H_
#define E_MINSG_EXT_MATERIALLIB_H_

#include <EScript/Objects/ReferenceObject.h>

#include <MinSG/Ext/VoxelWorld/MaterialLib.h>

namespace E_MinSG{
namespace VoxelWorld{

class E_MaterialLib : public EScript::ReferenceObject<MinSG::VoxelWorld::MaterialLib, EScript::Policies::SameEObjects_ComparePolicy> {
		ES_PROVIDES_TYPE_NAME(MaterialLib)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_MaterialLib() : 
				ReferenceObject_t(getTypeObject()) {}
		E_MaterialLib(MinSG::VoxelWorld::MaterialLib&&s) : 
				ReferenceObject_t(getTypeObject(), std::move(s)) {}
        virtual ~E_MaterialLib() = default;

};
}
}

ES_CONV_OBJ_TO_EOBJ(MinSG::VoxelWorld::MaterialLib&&,	E_MinSG::VoxelWorld::E_MaterialLib,			new E_MinSG::VoxelWorld::E_MaterialLib(std::move(obj)))
ES_CONV_EOBJ_TO_OBJ(E_MinSG::VoxelWorld::E_MaterialLib,		MinSG::VoxelWorld::MaterialLib&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_MinSG::VoxelWorld::E_MaterialLib,		MinSG::VoxelWorld::MaterialLib*,		&(**eObj))

#endif // E_MINSG_EXT_MATERIALLIB_H_
#endif // MINSG_EXT_VOXEL_WORLD
