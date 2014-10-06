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
#include <MinSG/Ext/BlueSurfels/SurfelAnalysis.h>
#include <E_Rendering/Mesh/E_Mesh.h>

#include "E_SurfelGenerator.h"
#include "E_SurfelRenderer.h"

namespace E_MinSG{

void BlueSurfels::init(EScript::Namespace & lib) {
	EScript::Namespace * nsBlueSurfels = new EScript::Namespace;
	declareConstant(&lib,"BlueSurfels",nsBlueSurfels);
	
	BlueSurfels::E_SurfelGenerator::init(*nsBlueSurfels);
	BlueSurfels::E_SurfelRenderer::init(lib); // namespace MinSG

	//! [Number*] MinSG.BlueSurfels.getProgressiveMinimalMinimalVertexDistances(Rendering.Mesh)
	ES_FUN(nsBlueSurfels,"getProgressiveMinimalMinimalVertexDistances",1,1,
			EScript::Array::create(MinSG::BlueSurfels::getProgressiveMinimalMinimalVertexDistances(*parameter[0].to<Rendering::Mesh*>(rt))))

	//! [Number*] MinSG.BlueSurfels.getMinimalVertexDistances(Rendering.Mesh,int)
	ES_FUN(nsBlueSurfels,"getMinimalVertexDistances",2,2,
			EScript::Array::create(MinSG::BlueSurfels::getMinimalVertexDistances(*parameter[0].to<Rendering::Mesh*>(rt),parameter[1].to<uint32_t>(rt))))


}

}
#endif // MINSG_EXT_BLUE_SURFELS

