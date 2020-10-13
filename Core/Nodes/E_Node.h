/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_SG_NODE_H
#define E_SG_NODE_H
#include <EScript/Objects/ExtReferenceObject.h>
#include <E_Util/E_ObjectFactory.h>
#include <E_Util/E_Utils.h>
#include <MinSG/Core/Nodes/Node.h>
#include <Util/Factory/WrapperFactory.h>

namespace E_MinSG {

/**
 *   [E_Node] ---|> [EScript::Object]
 *     |
 *     ------> [MinSG::Node]
 */
class E_Node : public EScript::ExtReferenceObject< Util::Reference<MinSG::Node>,EScript::Policies::EqualContent_ComparePolicy,E_Util::Policies::StoreAttrsInAttributeProvider>{
		ES_PROVIDES_TYPE_NAME(Node)

		EMINSGAPI static E_Util::E_ObjectFactory<MinSG::Node, E_Node> factorySystem;
	protected:
		template<class NodeType, class E_NodeType>
		static void addFactory() {
			factorySystem.registerType(NodeType::getClassId(), Util::PolymorphicWrapperCreator<MinSG::Node, NodeType, E_NodeType>());
		}
	public:
		static E_Node * create(MinSG::Node * node) {
			if(node == nullptr) {
				return nullptr;
			}
			return factorySystem.create(node->getTypeId(), node);
		}
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		EMINSGAPI static EScript::Type * getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		EMINSGAPI virtual ~E_Node();
		
		const MinSG::Node * operator*()const	{	return static_cast<const MinSG::Node*>(ref().get());	}
		MinSG::Node * operator*()				{	return static_cast<MinSG::Node*>(ref().get());	}

		/// ---|> [EScript::Object]
		EMINSGAPI E_Node * clone()const override;
		EMINSGAPI std::string toString()const override;

	protected:
		EMINSGAPI E_Node(MinSG::Node * node,EScript::Type * type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_Node,						MinSG::Node*,		**eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::Node*, 							E_MinSG::E_Node,	obj ? E_MinSG::E_Node::create(obj) : nullptr)
ES_CONV_OBJ_TO_EOBJ(Util::Reference<MinSG::Node>,			E_MinSG::E_Node,	obj.isNotNull() ? E_MinSG::E_Node::create(obj.get()) : nullptr)

#endif // E_SG_NODE_H
