/*
	This file is part of the MinSG library extension ThesisStanislaw.
	Copyright (C) 2016 Stanislaw Eppinger
	Copyright (C) 2016 Sascha Brandt

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_THESISSTANISLAW


#include "E_LibThesisStanislaw.h"

#include "E_LightPatchRenderer.h"
#include "E_PhotonRenderer.h"
#include "E_PhotonSampler.h"

#include "../../Core/Nodes/E_Node.h"

#include <MinSG/Ext/ThesisStanislaw/PolygonIndexing.h> 

#include <EScript/EScript.h>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {
namespace ThesisStanislaw{
  
void init(EScript::Namespace & lib) {
  E_LightPatchRenderer::init(lib);
  E_PhotonRenderer::init(lib);
  E_PhotonSampler::init(lib);
	
	//! void MinSG.ThesisStanislaw.indexPolygons(MinSG.Node,[bool debug])
	ES_FUN(&lib,"indexPolygons",1,2,
			(MinSG::ThesisStanislaw::indexPolygons(parameter[0].to<MinSG::Node*>(rt), parameter[1].toBool(false)), EScript::create(nullptr)))

}

}
}

#endif // MINSG_EXT_THESISSTANISLAW
