/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_GeometryNode_H
#define __E_GeometryNode_H

#include "E_Node.h"
#include <MinSG/Core/Nodes/GeometryNode.h>

namespace E_MinSG{

/**
 *   [E_GeometryNode] ---|> [E_Node] ---|> [Object]
 */
class E_GeometryNode : public E_Node{
	ES_PROVIDES_TYPE_NAME(GeometryNode)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		// ---
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_GeometryNode(){}

		const MinSG::GeometryNode * operator*()const	{	return static_cast<const MinSG::GeometryNode*>(ref().get());	}
		MinSG::GeometryNode * operator*()				{	return static_cast<MinSG::GeometryNode*>(ref().get());	}

	protected:
		E_GeometryNode(MinSG::GeometryNode * gNode,EScript::Type* type=nullptr) : E_Node(gNode,type?type:getTypeObject()){}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_GeometryNode,		MinSG::GeometryNode*,		**eObj)	

#endif // __E_GeometryNode_H
