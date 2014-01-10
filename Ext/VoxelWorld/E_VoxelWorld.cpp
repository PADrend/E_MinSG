/*
	This file is part of the E_MinSG library extension VoxelWorld.
	Copyright (C) 2012-2013 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_VOXEL_WORLD

#include "E_VoxelWorld.h"
#include "E_VoxelStorage.h"

#include <E_Geometry/E_Box.h>
#include <E_Rendering/Mesh/E_Mesh.h>
#include <E_Util/E_FileName.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>


#include <Geometry/VoxelStorage.h>
#include <MinSG/Ext/VoxelWorld/VoxelWorld.h>
#include <MinSG/Ext/VoxelWorld/StreamerVOX.h>

namespace E_MinSG{
namespace VoxelWorld{

//! (static)
void init(EScript::Namespace & lib) {
	EScript::Namespace * ns = new EScript::Namespace;
	declareConstant(&lib,"VoxelWorld",ns);

	E_VoxelStorage::init(*ns);
	
	using namespace MinSG;
	using namespace MinSG::VoxelWorld;

	//! [ESF] generateMesh( const simpleVoxelStorage_t&, const Geometry::_Box<int32_t>& boundary)
	ES_FUN(ns, "generateMesh",2,2,	generateMesh( parameter[0].to<const simpleVoxelStorage_t&>(rt),parameter[1].to<Geometry::_Box<int32_t>>(rt) ))


	//! [ESF] loadVoxels( String Filename)
	ES_FUNCTION(ns, "loadVoxels",1,1,{
		simpleVoxelStorage_t storage(0);
		storage.deserialize(loadVoxels( parameter[0].to<Util::FileName>(rt)));
		return EScript::create(std::move(storage));
	})


	//! [ESF] loadVoxels( String Filename, VoxelStorage)
	ES_FUNCTION(ns, "saveVoxels",2,2,{
		const auto& voxels = parameter[1].to<const simpleVoxelStorage_t&>(rt);
		saveVoxels(parameter[0].to<Util::FileName>(rt),voxels.serialize(voxels.getBlockBounds()));
		return nullptr;
	})
}
}
}
#endif // MINSG_EXT_VOXEL_WORLD

