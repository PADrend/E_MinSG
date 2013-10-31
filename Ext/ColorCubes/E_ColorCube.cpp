/*
	This file is part of the E_MinSG library extension ColorCubes.
	Copyright (C) 2010-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2010-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2010 Paul Justus <paul.justus@gmx.net>
	Copyright (C) 2010-2012 Ralf Petring <ralf@petring.net>

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_COLORCUBES

#include "E_ColorCube.h"
#include "../../Core/Nodes/E_Node.h"
#include "../../Core/E_FrameContext.h"
#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <MinSG/Ext/ColorCubes/ColorCube.h>

namespace E_MinSG {
namespace E_ColorCube {

void init(EScript::Namespace & lib) {
	EScript::Namespace * ns = new EScript::Namespace;
	declareConstant(&lib, "ColorCube", ns);


	//! [ESF] Void ColorCube.buildColorCubes(FrameContext, Node [, nodeCount=100 [, triangleCount=10000] ] )
	ES_FUNCTION2(ns, "buildColorCubes", 2, 4, {
		MinSG::FrameContext & context = parameter[0].to<MinSG::FrameContext&>(rt);
		MinSG::Node * node = parameter[1].to<MinSG::Node*>(rt);

		uint32_t nodeCount = 100;
		uint32_t triangleCount = 10000;

		if (parameter.count() >= 3)
			nodeCount = parameter[2].toInt();
		if (parameter.count() == 4)
			triangleCount = parameter[3].toInt();

		MinSG::ColorCube::buildColorCubes(context, node, nodeCount, triangleCount);
		return EScript::create(nullptr);
	})

	//! [ESF] Bool ColorCube.hasColorCube(Node)
	ES_FUN(ns, "hasColorCube", 1, 1,
		MinSG::ColorCube::hasColorCube(parameter[0].to<MinSG::Node*>(rt))
	)

	//! [ESF] void ColorCube.removeColorCube(Node node, Bool recursive)
	ES_FUN(ns, "removeColorCube", 2, 2, (
		MinSG::ColorCube::removeColorCube(parameter[0].to<MinSG::Node*>(rt), parameter[1].to<bool>(rt))
	, EScript::create(nullptr)))
}

}
}

#endif // MINSG_EXT_COLORCUBES
