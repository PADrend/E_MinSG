
#ifdef MINSG_EXT_THESISSTANISLAW
#ifndef MINSG_EXT_E_THESISSTANISLAW_POLYGONINDEXING_H
#define MINSG_EXT_E_THESISSTANISLAW_POLYGONINDEXING_H

#include <MinSG/Ext/ThesisStanislaw/PolygonIndexing.h>
#include "../../Core/States/E_NodeRendererState.h"

namespace EScript {
class Namespace;
class Runtime;
class Type;
}

namespace MinSG {
namespace ThesisStanislaw {
class PolygonIndexingState;
}
}

namespace E_MinSG {
namespace ThesisStanislaw{
/***
 **   E_PolygonIndexingState ---|> E_NodeRendererState ---|> E_State ---|> Object
 **/
class E_PolygonIndexingState : public E_NodeRendererState {
		ES_PROVIDES_TYPE_NAME(PolygonIndexingState)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_PolygonIndexingState();

		const MinSG::ThesisStanislaw::PolygonIndexingState * operator*()const	{	return static_cast<const MinSG::ThesisStanislaw::PolygonIndexingState*>(ref().get());	}
		MinSG::ThesisStanislaw::PolygonIndexingState * operator*()	{	return static_cast<MinSG::ThesisStanislaw::PolygonIndexingState*>(ref().get());	}

	protected:
		E_PolygonIndexingState(MinSG::ThesisStanislaw::PolygonIndexingState * obj, EScript::Type * type=nullptr);
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisStanislaw::E_PolygonIndexingState, MinSG::ThesisStanislaw::PolygonIndexingState*, **eObj)


#endif // MINSG_EXT_E_THESISSTANISLAW_POLYGONINDEXING_H
#endif // MINSG_EXT_THESISSTANISLAW
