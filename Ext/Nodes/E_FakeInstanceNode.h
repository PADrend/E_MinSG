/*
	This file is part of the E_MinSG library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_MINSG_EXT_E_FAKEINSTANCENODE_H
#define E_MINSG_EXT_E_FAKEINSTANCENODE_H

#include "../../Core/Nodes/E_Node.h"
#include <MinSG/Ext/Nodes/FakeInstanceNode.h>

namespace E_MinSG {

class E_FakeInstanceNode : public E_Node {
	ES_PROVIDES_TYPE_NAME(FakeInstanceNode)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_FakeInstanceNode() {
		}

		const MinSG::FakeInstanceNode * operator*() const {
			return static_cast<const MinSG::FakeInstanceNode *>(ref().get());
		}
		MinSG::FakeInstanceNode * operator*() {
			return static_cast<MinSG::FakeInstanceNode *>(ref().get());
		}

	protected:
		E_FakeInstanceNode(MinSG::FakeInstanceNode * fiNode, EScript::Type * type = nullptr) :
			E_Node(fiNode, type ? type : getTypeObject()) {
		}
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_FakeInstanceNode, MinSG::FakeInstanceNode *, **eObj)

#endif /* E_MINSG_EXT_E_FAKEINSTANCENODE_H */
