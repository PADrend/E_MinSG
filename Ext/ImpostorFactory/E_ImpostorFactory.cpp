/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_ImpostorFactory.h"
#include "../../Core/Nodes/E_Node.h"
#include "../../Core/E_FrameContext.h"
#include "../../ELibMinSG.h"

#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/Basics.h>

#include <MinSG/Core/Nodes/GeometryNode.h>
#include <MinSG/Core/Nodes/Node.h>
#include <MinSG/Ext/ImpostorFactory/ImpostorFactory.h>

namespace E_MinSG {
namespace E_ImpostorFactory {

void init(EScript::Namespace * lib) {
	//! [ESF] GeometryNode MinSG.createReliefBoardForNode(FrameContext, Node)
	ES_FUNCTION2(lib, "createReliefBoardForNode", 2, 2, {
		MinSG::FrameContext & frameContext = parameter[0].to<MinSG::FrameContext&>(rt);
		MinSG::Node * node = parameter[1].to<MinSG::Node*>(rt);
		return EScript::create(MinSG::ImpostorFactory::createReliefBoardForNode(frameContext, node));
	})

	//! [ESF] GeometryNode MinSG.createTexturedDepthMeshForNode(FrameContext, Node)
	ES_FUNCTION2(lib, "createTexturedDepthMeshForNode", 2, 2, {
		MinSG::FrameContext & frameContext = parameter[0].to<MinSG::FrameContext&>(rt);
		MinSG::Node * node = parameter[1].to<MinSG::Node*>(rt);
		return EScript::create(MinSG::ImpostorFactory::createTexturedDepthMeshForNode(frameContext, node));
	})
}

}
}
