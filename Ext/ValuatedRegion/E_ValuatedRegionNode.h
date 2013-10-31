/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_ValuatedRegionNode_H
#define __E_ValuatedRegionNode_H

#include "../../Core/Nodes/E_ListNode.h"
#include "../../ELibMinSG.h"
#include <MinSG/Ext/ValuatedRegion/ValuatedRegionNode.h>

namespace E_MinSG {

/**
 *  [E_ValuatedRegionNode] ---|> [E_ListNode] ---|> [E_GroupNode] ---|> [E_Node]
 */
class E_ValuatedRegionNode : public E_ListNode{
	ES_PROVIDES_TYPE_NAME(ValuatedRegionNode)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		// ---
		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_ValuatedRegionNode();

		Object * getValue()const;
		void setValue(Object * attr);
		Object * getValueAtPosition(const Geometry::Vec3 & absPos);

		const MinSG::ValuatedRegionNode * operator*()const	{	return static_cast<const MinSG::ValuatedRegionNode*>(ref().get());	}
		MinSG::ValuatedRegionNode * operator*()				{	return static_cast<MinSG::ValuatedRegionNode*>(ref().get());	}

	protected:
		E_ValuatedRegionNode(MinSG::ValuatedRegionNode * gNode,EScript::Type* type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ValuatedRegionNode,		MinSG::ValuatedRegionNode*,		**eObj)	

#endif // __E_ValuatedRegionNode_H
