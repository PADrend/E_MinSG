/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_GroupNode_H
#define __E_GroupNode_H

#include "E_Node.h"
#include <MinSG/Core/Nodes/GroupNode.h>

namespace E_MinSG{

/**
 *   [E_GroupNode] ---|> [E_Node] ---|> [Object]
 */
class E_GroupNode : public E_Node{
	ES_PROVIDES_TYPE_NAME(GroupNode)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		// ---
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_GroupNode(){}

		const MinSG::GroupNode * operator*()const	{	return static_cast<const MinSG::GroupNode*>(ref().get());	}
		MinSG::GroupNode * operator*()				{	return static_cast<MinSG::GroupNode*>(ref().get());	}

	protected:
		E_GroupNode(MinSG::GroupNode * gNode,EScript::Type* type=nullptr) : E_Node( gNode,type?type:getTypeObject()){}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_GroupNode,		MinSG::GroupNode*,		**eObj)	

#endif // __E_GroupNode_H
