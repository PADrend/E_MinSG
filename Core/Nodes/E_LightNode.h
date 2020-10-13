/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_LIGHTNODE_H
#define E_LIGHTNODE_H

#include "../Nodes/E_Node.h"
#include <MinSG/Core/Nodes/LightNode.h>

namespace E_MinSG{

/**
 *  [E_LightNode] ---|> [E_Node]
 */
class E_LightNode : public E_Node{
	ES_PROVIDES_TYPE_NAME(LightNode)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		// ---
		EMINSGAPI static EScript::Type * getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		virtual ~E_LightNode(){}

		const MinSG::LightNode * operator*()const	{	return static_cast<const MinSG::LightNode*>(ref().get());	}
		MinSG::LightNode * operator*()				{	return static_cast<MinSG::LightNode*>(ref().get());	}

	protected:
		E_LightNode(MinSG::LightNode * c,EScript::Type* type=nullptr) : E_Node(c,type?type:getTypeObject()){}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_LightNode,		MinSG::LightNode*,		**eObj)	

#endif // E_LIGHTNODE_H
