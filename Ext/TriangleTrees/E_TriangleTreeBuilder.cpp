/*
	This file is part of the E_MinSG library extension TriangleTrees.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_TRIANGLETREES

#include "E_TriangleTreeBuilder.h"
#include "../../Core/Nodes/E_GeometryNode.h"
#include "../../Core/Nodes/E_Node.h"
#include "../../ELibMinSG.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <E_Rendering/Mesh/E_Mesh.h>
#include <MinSG/Ext/TriangleTrees/ABTreeBuilder.h>
#include <MinSG/Ext/TriangleTrees/kDTreeBuilder.h>
#include <MinSG/Ext/TriangleTrees/OctreeBuilder.h>
#include <MinSG/Ext/TriangleTrees/RandomizedSampleTreeBuilder.h>
#include <MinSG/Ext/TriangleTrees/TriangleTreeBuilder.h>
#include <cstddef>
#include <vector>

namespace MinSG {
class GeometryNode;
class Node;
}
namespace Rendering {
class Mesh;
}
namespace E_MinSG {
namespace E_TriangleTreeBuilder {

void init(EScript::Namespace & lib) {
	//! [ESF] Mesh mergeGeometry(Array)
	ES_FUNCTION(&lib, "mergeGeometry", 1, 1, {
		EScript::Array * eGeoNodes = parameter[0].to<EScript::Array*>(rt);
		std::vector<MinSG::GeometryNode *> geoNodes;
		geoNodes.reserve(eGeoNodes->size());
		for(EScript::Array::iterator it = eGeoNodes->begin(); it != eGeoNodes->end(); ++it) {
			MinSG::GeometryNode * geoNode = (**EScript::assertType<E_GeometryNode>(rt, *it));
			geoNodes.push_back(geoNode);
		}
		Rendering::Mesh * mesh = MinSG::TriangleTrees::Builder::mergeGeometry(geoNodes);
		if(mesh == nullptr) {
			return EScript::create(nullptr);
		}
		return EScript::create(mesh);
	})
	//! createABTree(Mesh, Number, Number)
	ES_FUNCTION(&lib, "createABTree", 3, 3, {
		Rendering::Mesh * mesh = parameter[0].to<Rendering::Mesh*>(rt);
		MinSG::TriangleTrees::ABTreeBuilder builder(static_cast<std::size_t>(parameter[1].toInt()), parameter[2].toFloat());
		MinSG::Node * node = MinSG::TriangleTrees::Builder::buildMinSGTree(mesh, builder);
		return EScript::create(node);
	})
	//! createkDTree(Mesh, Number, Number)
	ES_FUNCTION(&lib, "createkDTree", 3, 3, {
		Rendering::Mesh * mesh = parameter[0].to<Rendering::Mesh*>(rt);
		MinSG::TriangleTrees::kDTreeBuilder builder(static_cast<std::size_t>(parameter[1].toInt()), parameter[2].toFloat());
		MinSG::Node * node = MinSG::TriangleTrees::Builder::buildMinSGTree(mesh, builder);
		return EScript::create(node);
	})
	//! createOctree(Mesh, Number, Number)
	ES_FUNCTION(&lib, "createOctree", 3, 3, {
		Rendering::Mesh * mesh = parameter[0].to<Rendering::Mesh*>(rt);
		MinSG::TriangleTrees::OctreeBuilder builder(static_cast<std::size_t>(parameter[1].toInt()), parameter[2].toFloat());
		MinSG::Node * node = MinSG::TriangleTrees::Builder::buildMinSGTree(mesh, builder);
		return EScript::create(node);
	})
	//! createRandomizedSampleTree(Mesh)
	ES_FUNCTION(&lib, "createRandomizedSampleTree", 1, 1, {
		Rendering::Mesh * mesh = parameter[0].to<Rendering::Mesh*>(rt);
		MinSG::TriangleTrees::RandomizedSampleTreeBuilder builder;
		MinSG::Node * node = MinSG::TriangleTrees::Builder::buildMinSGTree(mesh, builder);
		return EScript::create(node);
	})
}

}
}

#endif /* MINSG_EXT_TRIANGLETREES */
