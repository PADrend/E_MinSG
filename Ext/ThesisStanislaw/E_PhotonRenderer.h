/*
	This file is part of the MinSG library extension ThesisStanislaw.
	Copyright (C) 2016 Stanislaw Eppinger

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_THESISSTANISLAW

#ifndef MINSG_EXT_E_THESISSTANISLAW_PHOTONRENDERER_H
#define MINSG_EXT_E_THESISSTANISLAW_PHOTONRENDERER_H

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/ThesisStanislaw/PhotonRenderer.h>

namespace EScript {
class Namespace;
class Type;
}

namespace E_MinSG {
namespace ThesisStanislaw{
	
/*!	EScript wrapper class for MinSG::ThesisStanislaw::PhotonRenderer

		E_PhotonRenderer ---|> EScript::ReferenceObject<MinSG::ThesisStanislaw::PhotonRenderer>
			|
			--------------> MinSG::ThesisStanislaw::PhotonRenderer		*/
class E_PhotonRenderer : public EScript::ReferenceObject<MinSG::ThesisStanislaw::PhotonRenderer, EScript::Policies::SameEObjects_ComparePolicy> {
		ES_PROVIDES_TYPE_NAME(PhotonRenderer)
	public:
		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);		

		E_PhotonRenderer() : ReferenceObject_t(E_PhotonRenderer::getTypeObject()) {}
				
		virtual ~E_PhotonRenderer() = default;
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisStanislaw::E_PhotonRenderer, MinSG::ThesisStanislaw::PhotonRenderer*, &(**eObj))


#endif // MINSG_EXT_E_THESISSTANISLAW_PHOTONRENDERER_H
#endif // MINSG_EXT_THESISSTANISLAW
