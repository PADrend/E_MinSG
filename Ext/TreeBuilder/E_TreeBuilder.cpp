/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "E_TreeBuilder.h"

#include "../../Core/Nodes/E_ListNode.h"
#include "../../Core/Nodes/E_GroupNode.h"



#include <E_Util/E_Utils.h>

#include <MinSG/Ext/TreeBuilder/TreeBuilder.h>

#include <Util/Macros.h>
#include <Util/GenericAttribute.h>

using namespace EScript;

namespace E_MinSG {

void E_TreeBuilder::init(EScript::Namespace & globals) {

	Namespace * lib=new Namespace();
	/** Provides functions for reorganizing the data structure of scene graphs.
	* Example:
	* ```js
	* MinSG.TreeBuilder.rebuildAsOcTree(scene, {
	* 	MinSG.TreeBuilder.MAX_TREE_DEPTH: 10,
	* 	MinSG.TreeBuilder.MAX_CHILD_COUNT: 8,
	* 	MinSG.TreeBuilder.LOOSE_FACTOR: 2,
	* 	MinSG.TreeBuilder.PREFERE_CUBES: true,
	* 	MinSG.TreeBuilder.USE_GEOMETRY_BB: false,
	* 	MinSG.TreeBuilder.EXACT_CUBES: true,
	* });
	* ```
	*/
	declareConstant(&globals,"TreeBuilder",lib);

	//! Boolean. If set, the bounding box is expanded to a cube/square before splitting (quadtree, octree). Don't forget to disable `use geometry bounding boxes´.
	declareConstant(lib, "EXACT_CUBES", String::create(MinSG::TreeBuilder::EXACT_CUBES));
	//! Number. The scale factor for boxes when inserting nodes. If you don't want a loose tree, set this value to one.
	declareConstant(lib, "LOOSE_FACTOR", String::create(MinSG::TreeBuilder::LOOSE_FACTOR));
	//! Number. The maximum number of nodes stored in leaves. Leaves with more nodes will be split up as long as the maximum depth is not reached.
	declareConstant(lib, "MAX_CHILD_COUNT", String::create(MinSG::TreeBuilder::MAX_CHILD_COUNT));
	//! Number. The maximum depth of the created tree. Leaves in depth >= maximum will not be split.
	declareConstant(lib, "MAX_TREE_DEPTH", String::create(MinSG::TreeBuilder::MAX_TREE_DEPTH));
	//! Boolean. If set, bounding boxes will not always split in all dimensions (quadtree, octree, kd-tree).
	//! If the ratio between maximum and minimum extent of the bounding box gets greater than squareroot of two, only the large dimensions are split.
	declareConstant(lib, "PREFERE_CUBES", String::create(MinSG::TreeBuilder::PREFERE_CUBES));
	//! Boolean. If set, bounding boxes of the geometry instead of those of the previous step are used for splitting (quadtree, octree, binary tree, kd-tree).
	declareConstant(lib, "USE_GEOMETRY_BB", String::create(MinSG::TreeBuilder::USE_GEOMETRY_BB));
	
	//! [ESF] void MinSG.rebuildAsBinaryTree(MinSG.GroupNode node, Map options)
	//! Builds a binary tree by splitting allways the largest dimension.
	ES_FUNCTION(lib, "rebuildAsBinaryTree", 2, 2, {
			MinSG::GroupNode * root = parameter[0].to<MinSG::GroupNode*>(rt);
			EScript::Map * emap = parameter[1].to<EScript::Map*>(rt);
			Util::GenericAttributeMap * map = dynamic_cast<Util::GenericAttributeMap *>(E_Util::E_Utils::convertEScriptObjectToGenericAttribute(emap));
			if(!map){
				WARN("rebuildAsBinaryTree: second parameter has to be a map");
				return EScript::create(nullptr);
			}
			MinSG::TreeBuilder::buildBinaryTree(root, *map);
			return EScript::create(nullptr);
	})
	
	//! [ESF] void MinSG.rebuildAsOcTree(MinSG.GroupNode node, Map options)
	//! Builds several variants of octrees.
	ES_FUNCTION(lib, "rebuildAsOcTree", 2, 2, {
			MinSG::GroupNode * root = parameter[0].to<MinSG::GroupNode*>(rt);
			EScript::Map * emap = parameter[1].to<EScript::Map*>(rt);
			Util::GenericAttributeMap * map = dynamic_cast<Util::GenericAttributeMap *>(E_Util::E_Utils::convertEScriptObjectToGenericAttribute(emap));
			if(!map){
				WARN("rebuildAsOcTree: second parameter has to be a map");
				return EScript::create(nullptr);
			}
			MinSG::TreeBuilder::buildOcTree(root, *map);
			return EScript::create(nullptr);
	})
	
	//! [ESF] void MinSG.rebuildAsKDTree(MinSG.GroupNode node, Map options)
	//! Builds several variants of kd-trees.
	ES_FUNCTION(lib, "rebuildAsKDTree", 2, 2, {
			MinSG::GroupNode * root = parameter[0].to<MinSG::GroupNode*>(rt);
			EScript::Map * emap = parameter[1].to<EScript::Map*>(rt);
			Util::GenericAttributeMap * map = dynamic_cast<Util::GenericAttributeMap *>(E_Util::E_Utils::convertEScriptObjectToGenericAttribute(emap));
			if(!map){
				WARN("rebuildAsKDTree: second parameter has to be a map");
				return EScript::create(nullptr);
			}
			MinSG::TreeBuilder::buildKDTree(root, *map);
			return EScript::create(nullptr);
	})
	
	//! [ESF] void MinSG.rebuildAsQuadTree(MinSG.GroupNode node, Map options)
	//! Builds several variants of quadtrees.
	ES_FUNCTION(lib, "rebuildAsQuadTree", 2, 2, {
			MinSG::GroupNode * root = parameter[0].to<MinSG::GroupNode*>(rt);
			EScript::Map * emap = parameter[1].to<EScript::Map*>(rt);
			Util::GenericAttributeMap * map = dynamic_cast<Util::GenericAttributeMap *>(E_Util::E_Utils::convertEScriptObjectToGenericAttribute(emap));
			if(!map){
				WARN("rebuildAsQuadTree: second parameter has to be a map");
				return EScript::create(nullptr);
			}
			MinSG::TreeBuilder::buildQuadTree(root, *map);
			return EScript::create(nullptr);
	})
	
	//! [ESF] void MinSG.rebuildAsList(MinSG.GroupNode node, Map options)
	//! Builds a simple list.
	ES_FUNCTION(lib, "rebuildAsList", 2, 2, {
			MinSG::GroupNode * root = parameter[0].to<MinSG::GroupNode*>(rt);
			EScript::Map * emap = parameter[1].to<EScript::Map*>(rt);
			Util::GenericAttributeMap * map = dynamic_cast<Util::GenericAttributeMap *>(E_Util::E_Utils::convertEScriptObjectToGenericAttribute(emap));
			if(!map){
				WARN("rebuildAsList: second parameter has to be a map");
				return EScript::create(nullptr);
			}
			MinSG::TreeBuilder::buildList(root, *map);
			return EScript::create(nullptr);
	})
}

}
