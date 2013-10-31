/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_BillboardNode_H
#define __E_BillboardNode_H

#include "../../Core/Nodes/E_GeometryNode.h"
#include <MinSG/Ext/Nodes/BillboardNode.h>

namespace E_MinSG {

/**
 *   [E_BillboardNode] ---|> [E_GeometryNode] ---|> [E_Node] ---|> [Object]
 */
class E_BillboardNode : public E_GeometryNode {
	ES_PROVIDES_TYPE_NAME(BillboardNode)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// ---
		static EScript::Type * typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_BillboardNode();

		const MinSG::BillboardNode * operator*()const	{	return static_cast<const MinSG::BillboardNode*>(ref().get());	}
		MinSG::BillboardNode * operator*()				{	return static_cast<MinSG::BillboardNode*>(ref().get());	}

	protected:
		E_BillboardNode(MinSG::BillboardNode * gNode, EScript::Type * type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_BillboardNode, MinSG::BillboardNode *, **eObj)

#endif // __E_ListNode_H
