/*
	This file is part of the E_MinSG library extension TriangleTrees.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_TRIANGLETREES

#ifndef E_TREEVISUALIZATION_H_
#define E_TREEVISUALIZATION_H_

#include "../../Core/States/E_State.h"
#include <MinSG/Core/States/State.h>
#include <MinSG/Ext/TriangleTrees/TreeVisualization.h>
#include <Util/References.h>
#include <cstddef>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG {

/**
 *   [E_TreeVisualization] ---|> [E_State]
 */
class E_TreeVisualization : public E_State {
		ES_PROVIDES_TYPE_NAME(TreeVisualization)

	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_TreeVisualization() {
		}
		const MinSG::TriangleTrees::TreeVisualization * operator*()const		{	return static_cast<const MinSG::TriangleTrees::TreeVisualization*>(ref().get());	}
		MinSG::TriangleTrees::TreeVisualization * operator*()					{	return static_cast<MinSG::TriangleTrees::TreeVisualization*>(ref().get());	}
	protected:
		E_TreeVisualization(MinSG::TriangleTrees::TreeVisualization * node, EScript::Type * type = nullptr) :
				E_State(node, type != nullptr ? type : getTypeObject()) {
		}
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_TreeVisualization, MinSG::TriangleTrees::TreeVisualization *, **eObj)

#endif /* E_TREEVISUALIZATION_H_ */

#endif /* MINSG_EXT_TRIANGLETREES */
