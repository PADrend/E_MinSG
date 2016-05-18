#ifdef MINSG_EXT_THESISSTANISLAW

#ifndef MINSG_EXT_E_THESISSTANISLAW_APPROXSCENEDEBUG_H
#define MINSG_EXT_E_THESISSTANISLAW_APPROXSCENEDEBUG_H

#include <MinSG/Ext/ThesisStanislaw/ApproxSceneDebug.h>
#include "../../Core/States/E_NodeRendererState.h"

namespace EScript {
class Namespace;
class Runtime;
class Type;
}

namespace MinSG {
namespace ThesisStanislaw {
class ApproxSceneDebug;
}
}

namespace E_MinSG {
namespace ThesisStanislaw{
/***
 **   E_ApproxSceneDebug ---|> E_NodeRendererState ---|> E_State ---|> Object
 **/
class E_ApproxSceneDebug : public E_NodeRendererState {
		ES_PROVIDES_TYPE_NAME(ApproxSceneDebug)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_ApproxSceneDebug();

		const MinSG::ThesisStanislaw::ApproxSceneDebug * operator*()const	{	return static_cast<const MinSG::ThesisStanislaw::ApproxSceneDebug*>(ref().get());	}
		MinSG::ThesisStanislaw::ApproxSceneDebug * operator*()	{	return static_cast<MinSG::ThesisStanislaw::ApproxSceneDebug*>(ref().get());	}

	protected:
		E_ApproxSceneDebug(MinSG::ThesisStanislaw::ApproxSceneDebug * obj, EScript::Type * type=nullptr);
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisStanislaw::E_ApproxSceneDebug, MinSG::ThesisStanislaw::ApproxSceneDebug*, **eObj)


#endif // MINSG_EXT_E_THESISSTANISLAW_APPROXSCENEDEBUG_H
#endif // MINSG_EXT_THESISSTANISLAW
