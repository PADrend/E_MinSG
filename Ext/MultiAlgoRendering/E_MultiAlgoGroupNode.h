/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/


#ifdef MINSG_EXT_MULTIALGORENDERING
#include <MinSG/Ext/MultiAlgoRendering/Dependencies.h>

#ifndef E_MultiAlgoGroupNode_H
#define E_MultiAlgoGroupNode_H

#include "../../Core/Nodes/E_GroupNode.h"
#include <MinSG/Ext/MultiAlgoRendering/MultiAlgoGroupNode.h>

namespace E_MinSG{
	namespace E_MAR{

/*!	EScript wrapper class for MinSG::MAR::SurfelRenderer
	[E_MultiAlgoGroupNode] ---|> [E_GroupNode] ---|> [E_Node] ---|> [Object]
		|
		--------------> MinSG::MAR::MultiAlgoGroupNode ---|> MinSG::GroupNode ---|> MinSG::Node
*/
class E_MultiAlgoGroupNode : public E_GroupNode{
	ES_PROVIDES_TYPE_NAME(MultiAlgoGroupNode)

	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static void init(EScript::Namespace & lib);

		virtual ~E_MultiAlgoGroupNode() = default;

		static EScript::Type * getTypeObject();

		const MinSG::MAR::MultiAlgoGroupNode * operator*() const 	{ return static_cast<const MinSG::MAR::MultiAlgoGroupNode *>(ref().get()); }
		MinSG::MAR::MultiAlgoGroupNode * operator*() 				{ return static_cast<MinSG::MAR::MultiAlgoGroupNode*>(ref().get()); }

	protected:
		E_MultiAlgoGroupNode(MinSG::MAR::MultiAlgoGroupNode * gNode,EScript::Type * type=nullptr):E_GroupNode( gNode,type?type:getTypeObject()){}
};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_MAR::E_MultiAlgoGroupNode, MinSG::MAR::MultiAlgoGroupNode *, **eObj)
namespace EScript {
// ES_CONV_EOBJ_TO_OBJ and ES_CONV_OBJ_TO_EOBJ can not be used for AlgoID's
template<> inline MinSG::MAR::MultiAlgoGroupNode::AlgoId
convertTo<MinSG::MAR::MultiAlgoGroupNode::AlgoId>(Runtime & runtime,ObjPtr obj){
        return static_cast<MinSG::MAR::MultiAlgoGroupNode::AlgoId>(obj.to<MinSG::MAR::MultiAlgoGroupNode::AlgoId_t>(runtime));
}

Object * create(MinSG::MAR::MultiAlgoGroupNode::AlgoId obj);
}

#endif // E_MultiAlgoGroupNode_H
#endif // MINSG_EXT_MULTIALGORENDERING
