/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_RTREE

#ifndef E_RTREE_H_
#define E_RTREE_H_

#include "../../Core/Nodes/E_ListNode.h"
#include <MinSG/Ext/RTree/RTree.h>

namespace E_MinSG {

class E_RTree : public E_ListNode {
	ES_PROVIDES_TYPE_NAME(RTree)

	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_RTree();

		const MinSG::RTree * operator*()const	{	return static_cast<const MinSG::RTree*>(ref().get());	}
		MinSG::RTree * operator*()				{	return static_cast<MinSG::RTree*>(ref().get());	}

	protected:
		E_RTree(MinSG::RTree * treeNode, EScript::Type * type=nullptr);
};

}

#endif /* E_RTREE_H_ */

#endif /* MINSG_EXT_RTREE */
