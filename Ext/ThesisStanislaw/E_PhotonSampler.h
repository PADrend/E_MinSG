/*
	This file is part of the MinSG library extension ThesisJonas.
	Copyright (C) 2016 Stanislaw Eppinger

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_THESISSTANISLAW

#ifndef MINSG_EXT_E_THESISSTANISLAW_PHOTONSAMPLER_H
#define MINSG_EXT_E_THESISSTANISLAW_PHOTONSAMPLER_H

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/ThesisStanislaw/PhotonSampler.h>

namespace EScript {
class Namespace;
class Runtime;
class Type;
}

namespace E_MinSG {
namespace ThesisStanislaw{
	
/*!	EScript wrapper class for MinSG::ThesisStanislaw::PhotonSampler

		E_PhotonSampler ---|> EScript::ReferenceObject<MinSG::ThesisStanislaw::PhotonSampler>
			|
			--------------> MinSG::ThesisStanislaw::PhotonSampler		*/
class E_PhotonSampler : public EScript::ReferenceObject<MinSG::ThesisStanislaw::PhotonSampler, EScript::Policies::SameEObjects_ComparePolicy> {
		ES_PROVIDES_TYPE_NAME(PhotonSampler)
	public:
		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);		

		E_PhotonSampler() : ReferenceObject_t(E_PhotonSampler::getTypeObject()) {}
				
		virtual ~E_PhotonSampler() = default;
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisStanislaw::E_PhotonSampler, MinSG::ThesisStanislaw::PhotonSampler*, &(**eObj))


#endif // E_PHOTONSAMPLER_H_INCLUDED
#endif // MINSG_EXT_THESISSTANISLAW
