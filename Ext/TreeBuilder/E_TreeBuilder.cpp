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

#include <EScript/Utils/DeprecatedMacros.h>

#include <E_Util/E_Utils.h>

#include <MinSG/Ext/TreeBuilder/TreeBuilder.h>

#include <Util/Macros.h>
#include <Util/GenericAttribute.h>

using namespace EScript;

namespace E_MinSG {

void E_TreeBuilder::init(EScript::Namespace & globals) {

	Namespace * lib=new Namespace();
	declareConstant(&globals,"TreeBuilder",lib);

	declareConstant(lib, "EXACT_CUBES", String::create(MinSG::TreeBuilder::EXACT_CUBES));
	declareConstant(lib, "LOOSE_FACTOR", String::create(MinSG::TreeBuilder::LOOSE_FACTOR));
	declareConstant(lib, "MAX_CHILD_COUNT", String::create(MinSG::TreeBuilder::MAX_CHILD_COUNT));
	declareConstant(lib, "MAX_TREE_DEPTH", String::create(MinSG::TreeBuilder::MAX_TREE_DEPTH));
	declareConstant(lib, "PREFERE_CUBES", String::create(MinSG::TreeBuilder::PREFERE_CUBES));
	declareConstant(lib, "USE_GEOMETRY_BB", String::create(MinSG::TreeBuilder::USE_GEOMETRY_BB));

	ES_FUNCTION2(lib, "rebuildAsBinaryTree", 2, 2, {
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

	ES_FUNCTION2(lib, "rebuildAsOcTree", 2, 2, {
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

	ES_FUNCTION2(lib, "rebuildAsKDTree", 2, 2, {
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

	ES_FUNCTION2(lib, "rebuildAsQuadTree", 2, 2, {
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

	ES_FUNCTION2(lib, "rebuildAsList", 2, 2, {
			MinSG::GroupNode * root = parameter[0].to<MinSG::GroupNode*>(rt);
			EScript::Map * emap = parameter[1].to<EScript::Map*>(rt);
			Util::GenericAttributeMap * map = dynamic_cast<Util::GenericAttributeMap *>(E_Util::E_Utils::convertEScriptObjectToGenericAttribute(emap));
			if(!map){
				WARN("rebuildAsQuadTree: second parameter has to be a map");
				return EScript::create(nullptr);
			}
			MinSG::TreeBuilder::buildList(root, *map);
			return EScript::create(nullptr);
	})
}

}
