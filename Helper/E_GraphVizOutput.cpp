/*
	This file is part of the E_MinSG library.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "E_GraphVizOutput.h"
#include "../Core/Nodes/E_Node.h"
#include "../SceneManagement/E_SceneManager.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <E_Util/E_FileName.h>
#include <MinSG/Helper/GraphVizOutput.h>

namespace E_MinSG {
namespace GraphVizOutput {

void init(EScript::Namespace * lib) {
	EScript::Namespace * ns = new EScript::Namespace;
	EScript::declareConstant(lib, "GraphVizOutput", ns);

	//! [ESF] Void GraphVizOutput.treeToFile(Node, SceneManager, FileName)
	ES_FUN(ns, "treeToFile", 3, 3, (
		MinSG::GraphVizOutput::treeToFile(parameter[0].to<MinSG::Node*>(rt),
										  **EScript::assertType<E_SceneManager>(rt, parameter[1]),
										  **EScript::assertType<E_Util::E_FileName>(rt, parameter[2])),
		EScript::create(nullptr)))
}

}
}
