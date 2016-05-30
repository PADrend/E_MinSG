#ifdef MINSG_EXT_THESISSTANISLAW

#ifndef MINSG_EXT_E_THESISSTANISLAW_PHONGGI_H
#define MINSG_EXT_E_THESISSTANISLAW_PHONGGI_H

#include <MinSG/Ext/ThesisStanislaw/PhongGI.h>
#include "../../Core/States/E_State.h"

namespace EScript {
class Namespace;
class Runtime;
class Type;
}

namespace MinSG {
namespace ThesisStanislaw {
class PhongGI;
}
}

namespace E_MinSG {
namespace ThesisStanislaw{
/***
 **   E_PhongGI ---|> E_State ---|> Object
 **/
class E_PhongGI : public E_State {
		ES_PROVIDES_TYPE_NAME(PhongGI)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_PhongGI();

		const MinSG::ThesisStanislaw::PhongGI * operator*()const	{	return static_cast<const MinSG::ThesisStanislaw::PhongGI*>(ref().get());	}
		MinSG::ThesisStanislaw::PhongGI * operator*()	{	return static_cast<MinSG::ThesisStanislaw::PhongGI*>(ref().get());	}

	protected:
		E_PhongGI(MinSG::ThesisStanislaw::PhongGI * obj, EScript::Type * type=nullptr);
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisStanislaw::E_PhongGI, MinSG::ThesisStanislaw::PhongGI*, **eObj)


#endif // MINSG_EXT_E_THESISSTANISLAW_APPROXSCENEDEBUG_H
#endif // MINSG_EXT_THESISSTANISLAW
