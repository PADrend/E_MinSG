/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_ABSTRACTCAMERANODE_H
#define E_ABSTRACTCAMERANODE_H

#include "E_Node.h"
#include <MinSG/Core/Nodes/AbstractCameraNode.h>

namespace E_MinSG{

/**
 *  [E_AbstractCameraNode] ---|> [E_Node]
 */
class E_AbstractCameraNode : public E_Node{
	ES_PROVIDES_TYPE_NAME(AbstractCameraNode)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// ---
		EMINSGAPI static EScript::Type * getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		virtual ~E_AbstractCameraNode(){}

		const MinSG::AbstractCameraNode * operator*()const	{	return static_cast<const MinSG::AbstractCameraNode*>(ref().get());	}
		MinSG::AbstractCameraNode * operator*()				{	return static_cast<MinSG::AbstractCameraNode*>(ref().get());	}

	protected:
		E_AbstractCameraNode(MinSG::AbstractCameraNode * c,EScript::Type* type=nullptr) : E_Node(c,type?type:getTypeObject()){}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_AbstractCameraNode,		MinSG::AbstractCameraNode*,		**eObj)	

#endif // E_ABSTRACTCAMERANODE_H
