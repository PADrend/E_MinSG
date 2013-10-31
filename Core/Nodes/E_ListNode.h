/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_ListNode_H
#define __E_ListNode_H
#include "E_GroupNode.h"
#include <MinSG/Core/Nodes/ListNode.h>

namespace E_MinSG{

/**
 *   [E_ListNode] ---|> [E_GroupNode] ---|> [E_Node] ---|> [Object]
 */
class E_ListNode : public E_GroupNode{
	ES_PROVIDES_TYPE_NAME(ListNode)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// ---
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_ListNode(){}

		const MinSG::ListNode * operator*()const	{	return static_cast<const MinSG::ListNode*>(ref().get());	}
		MinSG::ListNode * operator*()				{	return static_cast<MinSG::ListNode*>(ref().get());	}

	protected:
		E_ListNode(MinSG::ListNode * gNode,EScript::Type* type=nullptr) : E_GroupNode( gNode,type?type:getTypeObject()){}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ListNode,		MinSG::ListNode*,		**eObj)	

#endif // __E_ListNode_H
