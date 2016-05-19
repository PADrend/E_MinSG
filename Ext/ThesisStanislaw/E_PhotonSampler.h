#ifdef MINSG_EXT_THESISSTANISLAW

#ifndef MINSG_EXT_E_THESISSTANISLAW_PHOTONSAMPLER_H
#define MINSG_EXT_E_THESISSTANISLAW_PHOTONSAMPLER_H

#include <MinSG/Ext/ThesisStanislaw/PhotonSampler.h>
#include "../../Core/States/E_State.h"

namespace EScript {
class Namespace;
class Runtime;
class Type;
}

namespace MinSG {
namespace ThesisStanislaw {
class PhotonSampler;
}
}

namespace E_MinSG {
namespace ThesisStanislaw{
/***
 **   E_PhotonSampler ---|> E_State ---|> Object
 **/
class E_PhotonSampler : public E_State {
		ES_PROVIDES_TYPE_NAME(PhotonSampler)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_PhotonSampler();

		const MinSG::ThesisStanislaw::PhotonSampler * operator*()const	{	return static_cast<const MinSG::ThesisStanislaw::PhotonSampler*>(ref().get());	}
		MinSG::ThesisStanislaw::PhotonSampler * operator*()	{	return static_cast<MinSG::ThesisStanislaw::PhotonSampler*>(ref().get());	}

	protected:
		E_PhotonSampler(MinSG::ThesisStanislaw::PhotonSampler * obj, EScript::Type * type=nullptr);
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisStanislaw::E_PhotonSampler, MinSG::ThesisStanislaw::PhotonSampler*, **eObj)


#endif // E_PHOTONSAMPLER_H_INCLUDED
#endif // MINSG_EXT_THESISSTANISLAW
