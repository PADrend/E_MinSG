/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_NODE_RENDERER_STATE_H_
#define E_NODE_RENDERER_STATE_H_
#include "../../Core/States/E_State.h"
#include <MinSG/Core/States/NodeRendererState.h>
#include <Util/References.h>
#include <cstddef>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG {

/**
 *   [E_NodeRendererState] ---|> [E_State]
 */
class E_NodeRendererState : public E_State {
		ES_PROVIDES_TYPE_NAME(NodeRendererState)

	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_NodeRendererState() 		{}
	
		const MinSG::NodeRendererState * operator*()const	{	return static_cast<const MinSG::NodeRendererState*>(ref().get());	}
		MinSG::NodeRendererState * operator*()				{	return static_cast<MinSG::NodeRendererState*>(ref().get());	}

	protected:
		E_NodeRendererState(MinSG::NodeRendererState * node, EScript::Type * type = nullptr) :
				E_State(node, type != nullptr ? type : getTypeObject()) {
		}
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_NodeRendererState,		MinSG::NodeRendererState*,		**eObj)	

#endif /* E_NODE_RENDERER_STATE_H_ */
