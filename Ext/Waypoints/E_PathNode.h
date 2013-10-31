/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_WAYPOINTS

#ifndef __E_PathNode_H
#define __E_PathNode_H

#include "../../Core/Nodes/E_GroupNode.h"
#include <MinSG/Ext/Waypoints/PathNode.h>

namespace E_MinSG{
/***
 **   E_PathNode ---|> E_GroupNode ---|> Object
 **/
class E_PathNode : public E_GroupNode{
	ES_PROVIDES_TYPE_NAME(PathNode)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		// ---
		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_PathNode();

		const MinSG::PathNode * operator*()const	{	return static_cast<const MinSG::PathNode*>(ref().get());	}
		MinSG::PathNode * operator*()				{	return static_cast<MinSG::PathNode*>(ref().get());	}

	protected:
		E_PathNode(MinSG::PathNode * gNode,EScript::Type* type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_PathNode,		MinSG::PathNode*,		**eObj)	

#endif // __E_PathNode_H

#endif /* MINSG_EXT_WAYPOINTS */
