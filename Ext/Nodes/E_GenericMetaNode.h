/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_GenericMetaNode_H
#define __E_GenericMetaNode_H

#include "../../Core/Nodes/E_Node.h"
#include <MinSG/Ext/Nodes/GenericMetaNode.h>

namespace E_MinSG{

/***
 **   E_GenericMetaNode ---|> E_Node ---|> Object
 **/
class E_GenericMetaNode : public E_Node{
	ES_PROVIDES_TYPE_NAME(GenericMetaNode)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		// ---
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_GenericMetaNode(){}

		const MinSG::GenericMetaNode * operator*()const	{	return static_cast<const MinSG::GenericMetaNode*>(ref().get());	}
		MinSG::GenericMetaNode * operator*()			{	return static_cast<MinSG::GenericMetaNode*>(ref().get());	}

	protected:
		E_GenericMetaNode(MinSG::GenericMetaNode * gNode,EScript::Type* type=nullptr) :
			E_Node(gNode,type?type:getTypeObject()){}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_GenericMetaNode, MinSG::GenericMetaNode *, **eObj)

#endif // __E_GenericMetaNode_H
