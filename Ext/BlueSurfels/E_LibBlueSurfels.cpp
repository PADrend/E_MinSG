/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2014 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_LibBlueSurfels.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include "E_SurfelGenerator.h"
#include "E_SurfelRenderer.h"

namespace E_MinSG{

void BlueSurfels::init(EScript::Namespace & lib) {
	EScript::Namespace * nsBlueSurfels = new EScript::Namespace;
	declareConstant(&lib,"BlueSurfels",nsBlueSurfels);
	
	BlueSurfels::E_SurfelGenerator::init(*nsBlueSurfels);
	BlueSurfels::E_SurfelRenderer::init(lib); // namespace MinSG


}

}
#endif // MINSG_EXT_BLUE_SURFELS

