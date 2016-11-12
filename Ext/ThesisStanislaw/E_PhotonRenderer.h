/*
	This file is part of the MinSG library.
	Copyright (C) 20016 Stanislaw Eppinger

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_THESISSTANISLAW

#ifndef MINSG_EXT_E_THESISSTANISLAW_PHOTONRENDERER_H
#define MINSG_EXT_E_THESISSTANISLAW_PHOTONRENDERER_H

#include <MinSG/Ext/ThesisStanislaw/PhotonRenderer.h>

#include "../../Core/States/E_State.h"

namespace EScript {
class Namespace;
class Runtime;
class Type;
}

namespace MinSG {
namespace ThesisStanislaw {
class PhotonRenderer;
}
}

namespace E_MinSG {
namespace ThesisStanislaw{
/***
 **   E_PhotonRenderer ---|> E_State ---|> Object
 **/
class E_PhotonRenderer : public E_State {
		ES_PROVIDES_TYPE_NAME(PhotonRenderer)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_PhotonRenderer();

		const MinSG::ThesisStanislaw::PhotonRenderer * operator*()const	{	return static_cast<const MinSG::ThesisStanislaw::PhotonRenderer*>(ref().get());	}
		MinSG::ThesisStanislaw::PhotonRenderer * operator*()	{	return static_cast<MinSG::ThesisStanislaw::PhotonRenderer*>(ref().get());	}

	protected:
		E_PhotonRenderer(MinSG::ThesisStanislaw::PhotonRenderer * obj, EScript::Type * type=nullptr);
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisStanislaw::E_PhotonRenderer, MinSG::ThesisStanislaw::PhotonRenderer*, **eObj)


#endif // MINSG_EXT_E_THESISSTANISLAW_PHOTONRENDERER_H
#endif // MINSG_EXT_THESISSTANISLAW
