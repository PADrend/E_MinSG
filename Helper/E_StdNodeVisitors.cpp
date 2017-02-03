/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_StdNodeVisitors.h"

// --
#include <MinSG/Helper/StdNodeVisitors.h>

#include "../ELibMinSG.h"

#include "../Core/Nodes/E_Node.h"
#include "../Core/Nodes/E_GroupNode.h"
#include "../Core/Nodes/E_ListNode.h"
#include "../Core/Nodes/E_GeometryNode.h"
#include "../Core/Nodes/E_LightNode.h"
#include "../Core/Nodes/E_CameraNode.h"
#include "../Core/States/E_State.h"
#include "../Core/E_FrameContext.h"


#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <E_Geometry/E_Matrix4x4.h>
#include <E_Geometry/E_Vec3.h>
#include <E_Geometry/E_Box.h>
#include <E_Geometry/E_Frustum.h>
#include <E_Geometry/E_Ray3.h>

using namespace EScript;
using namespace MinSG;
using namespace E_Geometry;

namespace E_MinSG {

//! init classes and Members
void init_stdNodeVisitors(EScript::Namespace * lib) {

	//! [ESF] Array collectClosedNodes(root)
	ES_FUNCTION(lib, "collectClosedNodes", 1, 1, {
		const auto nodes = collectClosedNodes((parameter[0].to<MinSG::Node*>(rt)));
		return getENodeArray(nodes.begin(), nodes.end());
	})

	//! [ESF] Array collectClosedNodesAtPosition(root,position)
	ES_FUNCTION(lib, "collectClosedNodesAtPosition", 2, 2, {
		const auto nodes = collectClosedNodesAtPosition((parameter[0].to<MinSG::Node*>(rt)),
														parameter[1].to<Geometry::Vec3>(rt));
		return getENodeArray(nodes.begin(), nodes.end());
	})

	//! [ESF] Array collectClosedNodesIntersectingBox(root,box)
	ES_FUNCTION(lib, "collectClosedNodesIntersectingBox", 2, 2, {
		const auto nodes = collectClosedNodesIntersectingBox((parameter[0].to<MinSG::Node*>(rt)),
															 parameter[1].to<const Geometry::Box&>(rt));
		return getENodeArray(nodes.begin(), nodes.end());
	})

	//! [ESF] Array collectGeoNodes(root)
	ES_FUNCTION(lib, "collectGeoNodes", 1, 1, {
		const auto nodes = collectNodes<GeometryNode>((parameter[0].to<MinSG::Node*>(rt)));
		return getENodeArray(nodes.begin(), nodes.end());
	})

	//! [ESF] Array collectGeoNodesAtPosition(root,position)
	ES_FUNCTION(lib, "collectGeoNodesAtPosition", 2, 2, {
		const auto nodes = collectGeoNodesAtPosition((parameter[0].to<MinSG::Node*>(rt)),
													 parameter[1].to<Geometry::Vec3>(rt));
		return getENodeArray(nodes.begin(), nodes.end());
	})

	//! [ESF] Array collectGeoNodesInFrustum(root,frustum, [bool includeIntersectingNodes])
	ES_FUNCTION(lib, "collectGeoNodesInFrustum", 2, 3, {
           const auto nodes = collectNodesInFrustum<GeometryNode>((parameter[0].to<MinSG::Node*>(rt)),
                                    parameter[1].to<const Geometry::Frustum&>(rt),parameter[2].toBool(true));
            return getENodeArray(nodes.begin(), nodes.end());


	})

	//! [ESF] Array collectGeoNodesIntersectingBox(root,box)
	ES_FUNCTION(lib, "collectGeoNodesIntersectingBox", 2, 2, {
		const auto nodes = collectGeoNodesIntersectingBox((parameter[0].to<MinSG::Node*>(rt)),
														  parameter[1].to<const Geometry::Box&>(rt));
		return getENodeArray(nodes.begin(), nodes.end());
	})
	
	//! [ESF] Array collectGeoNodesIntersectingBox(root,(pos,dir|ray))
	ES_FUNCTION(lib, "collectGeoNodesIntersectingRay", 2, 3, {
		Geometry::Ray3 ray;
		if(parameter.count() == 2) {
			ray = parameter[1].to<const Geometry::Ray3&>(rt);
		} else {
			ray.setOrigin(parameter[1].to<const Geometry::Vec3&>(rt));
			ray.setDirection(parameter[2].to<const Geometry::Vec3&>(rt));
		}
		const auto nodes = collectGeoNodesIntersectingRay((parameter[0].to<MinSG::Node*>(rt)),
														  ray.getOrigin(), ray.getDirection());
		return getENodeArray(nodes.begin(), nodes.end());
	})
	
	//! [ESF] Array collectInstances(Node root,Node prototype)
	ES_FUNCTION(lib, "collectInstances", 2, 2, {
		const auto nodes = collectInstances(	(parameter[0].to<MinSG::Node*>(rt)),
												(parameter[1].to<MinSG::Node*>(rt)));
		return getENodeArray(nodes.begin(), nodes.end());
	})

	//! [ESF] Array collectLightNodes(root)
	ES_FUNCTION(lib, "collectLightNodes", 1, 1, {
		const auto nodes = collectNodes<LightNode>((parameter[0].to<MinSG::Node*>(rt)));
		return getENodeArray(nodes.begin(), nodes.end());
	})

	//! [ESF] Array collectNodes(root[, type])
	ES_FUNCTION(lib, "collectNodes", 1, 2, {
		const auto nodes = collectNodes<Node>((parameter[0].to<MinSG::Node*>(rt)));
		Type * nodeType = parameter.count() > 1 ? EScript::assertType<Type>(rt, parameter[1]) : nullptr;

		EScript::Array * nodeArray = EScript::Array::create();
		for(const auto & node : nodes) {
			ObjRef en = EScript::create(node);
			if(en.isNotNull() && (parameter.count() < 2 || en->isA(nodeType))) {
				nodeArray->pushBack(en);
			}
		}
		return nodeArray;
	})

	//! [ESF] Array collectNextNodesReferencingAttribute(root, attrName)
	ES_FUNCTION(lib, "collectNextNodesReferencingAttribute", 2, 2, {
		const auto nodes = collectNextNodesReferencingAttribute((parameter[0].to<MinSG::Node*>(rt)),parameter[1].toString());
		return getENodeArray(nodes.begin(), nodes.end());
	})
	
	//! [ESF] Array collectNodesReferencingAttribute(root, attrName)
	ES_FUNCTION(lib, "collectNodesReferencingAttribute", 2, 2, {
		const auto nodes = collectNodesReferencingAttribute((parameter[0].to<MinSG::Node*>(rt)),parameter[1].toString());
		return getENodeArray(nodes.begin(), nodes.end());
	})
	
	//! [ESF] Array collectNodesWithAttribute(root, attrName)
	ES_FUNCTION(lib, "collectNodesWithAttribute", 2, 2, {
		const auto nodes = collectNodesWithAttribute((parameter[0].to<MinSG::Node*>(rt)),parameter[1].toString());
		return getENodeArray(nodes.begin(), nodes.end());
	})

	//! [ESF] Array collectVisibleNodes(root,FrameContext [[, Number or false maxDistance],bool fillDepthBuffer=false, Number renderingLayers])
	ES_FUNCTION(lib, "collectVisibleNodes", 2, 5, {
		const auto visNodes = collectVisibleNodes((parameter[0].to<MinSG::Node*>(rt)),
												parameter[1].to<MinSG::FrameContext&>(rt),
												parameter[2].toBool() ? parameter[2].toFloat() : -1.0,
												parameter[3].toBool(false),
												static_cast<renderingLayerMask_t>(parameter[4].toUInt(1)));
		return getENodeArray(visNodes.begin(),visNodes.end());
	})

	//! [ESF] Array collectStates(root[, type])
	ES_FUNCTION(lib, "collectStates", 1, 2, {
		const auto states = collectStates<State>((parameter[0].to<MinSG::Node*>(rt)));
		Type * stateType = parameter.count() > 1 ? EScript::assertType<Type>(rt, parameter[1]) : nullptr;

		EScript::Array * stateArray = EScript::Array::create();
		for(const auto & state : states) {
			ObjRef es = EScript::create(state);
			if(es.isNotNull() && (parameter.count() < 2 || es->isA(stateType))) {
				stateArray->pushBack(es);
			}
		}
		return stateArray;
	})

	//! [ESF] number countGeoNodes(root)
	ES_FUN(lib,"countGeoNodes",1,1,
			static_cast<uint32_t>(collectNodes<GeometryNode>((parameter[0].to<MinSG::Node*>(rt))).size()))
	
	//! [ESF] number countTriangles(root)
	ES_FUN(lib,"countTriangles",1,1,
				static_cast<uint32_t>(countTriangles(parameter[0].to<MinSG::Node*>(rt))))

	//! [ESF] number countTrianglesInFrustum(root, frustum)
	ES_FUN(lib,"countTrianglesInFrustum",2,2,
				static_cast<uint32_t>(countTrianglesInFrustum(
					parameter[0].to<MinSG::Node*>(rt),
					parameter[1].to<const Geometry::Frustum&>(rt)
				)))

	//! [ESF] number countGeoNodesInFrustum(root,camera)
	ES_FUNCTION(lib, "countGeoNodesInFrustum", 2, 2, {
		Node * root = parameter[0].to<MinSG::Node*>(rt);
		const CameraNode * camera = **EScript::assertType<E_CameraNode>(rt, parameter[1]);
		const Geometry::Frustum & frustum = camera->getFrustum();
		return static_cast<uint32_t>(collectNodesInFrustum<GeometryNode>(root, frustum).size());
	})

	//! [ESF] Array getChildNodes(root)
	ES_FUNCTION(lib, "getChildNodes", 1, 1, {
		const auto children = getChildNodes((parameter[0].to<MinSG::Node*>(rt)));
		return getENodeArray(children.begin(), children.end());
	})

	//! [ESF] Array countNodesInLevels(MinSG.Node)
	ES_FUNCTION(lib, "countNodesInLevels", 1, 1, {
		const auto levelCounts = countNodesInLevels(parameter[0].to<MinSG::Node*>(rt));

		Array * eLevelCounts = Array::create();
		eLevelCounts->reserve(levelCounts.size());
		for(const auto & levelCount : levelCounts) {
			eLevelCounts->pushBack(EScript::create(levelCount));
		}
		return eLevelCounts;
	})

	//! [ESF] void MinSG.moveTransformationsIntoClosedNodes(MinSG.Node)
	ES_FUN(lib, "moveTransformationsIntoClosedNodes", 1, 1, (
			MinSG::moveTransformationsIntoClosedNodes((parameter[0].to<MinSG::Node*>(rt))),
			EScript::create(nullptr)))

	//! [ESF] void MinSG.moveTransformationsIntoLeaves(MinSG.Node)
	ES_FUN(lib, "moveTransformationsIntoLeaves", 1, 1, (
				MinSG::moveTransformationsIntoLeaves((parameter[0].to<MinSG::Node*>(rt))),
				EScript::create(nullptr)))

	//! [ESF] void MinSG.moveStatesIntoClosedNodes(MinSG.Node)
	ES_FUN(lib, "moveStatesIntoClosedNodes", 1, 1, (
			MinSG::moveStatesIntoClosedNodes((parameter[0].to<MinSG::Node*>(rt))),
			EScript::create(nullptr)))

	//! [ESF] void MinSG.moveStatesIntoLeaves(MinSG.Node)
	ES_FUN(lib, "moveStatesIntoLeaves", 1, 1, (
				MinSG::moveStatesIntoLeaves((parameter[0].to<MinSG::Node*>(rt))),
				EScript::create(nullptr)))
}

}
