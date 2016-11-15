/*
	This file is part of the MinSG library extension ThesisStanislaw.
	Copyright (C) 2016 Stanislaw Eppinger

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_THESISSTANISLAW

#ifndef MINSG_EXT_E_THESISSTANISLAW_LIGHTPATCHRENDERER_H
#define MINSG_EXT_E_THESISSTANISLAW_LIGHTPATCHRENDERER_H

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/ThesisStanislaw/LightPatchRenderer.h>

namespace EScript {
class Namespace;
class Runtime;
class Type;
}

namespace MinSG {
namespace ThesisStanislaw {
class LightPatchRenderer;
}
}

namespace E_MinSG {
namespace ThesisStanislaw{
	
/*!	EScript wrapper class for MinSG::ThesisStanislaw::LightPatchRenderer

		E_LightPatchRenderer ---|> EScript::ReferenceObject<MinSG::ThesisStanislaw::LightPatchRenderer>
			|
			--------------> MinSG::ThesisStanislaw::LightPatchRenderer		*/
class E_LightPatchRenderer : public EScript::ReferenceObject<MinSG::ThesisStanislaw::LightPatchRenderer, EScript::Policies::SameEObjects_ComparePolicy> {
		ES_PROVIDES_TYPE_NAME(LightPatchRenderer)
	public:
		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);		

		E_LightPatchRenderer() : ReferenceObject_t(E_LightPatchRenderer::getTypeObject()) {}
				
		virtual ~E_LightPatchRenderer() = default;
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisStanislaw::E_LightPatchRenderer, MinSG::ThesisStanislaw::LightPatchRenderer*, &(**eObj))

#endif // E_LIGHTPATCHRENDERER_H_INCLUDED
#endif // MINSG_EXT_THESISSTANISLAW
