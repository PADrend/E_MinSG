/*
	This file is part of the E_MinSG library extension TreeSync.
	Copyright (C) 2012-2013 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_TREE_SYNC

#ifndef E_MINSG_E_TREESYNCCLIENT_H_
#define E_MINSG_E_TREESYNCCLIENT_H_

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/TreeSync/Server.h>


namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG{
namespace TreeSync{

/*!	EScript wrapper class for MinSG::TreeSyncClient

		E_TreeSyncClient ---|> EScript::ReferenceObject<MinSG::TreeSyncClient*>
			|
			--------------> MinSG::TreeSyncClient		*/
class E_TreeSyncClient : public EScript::ReferenceObject<MinSG::TreeSync::TreeSyncClient, EScript::Policies::SameEObjects_ComparePolicy> {
		ES_PROVIDES_TYPE_NAME(TreeSyncClient)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_TreeSyncClient(Util::Network::DataConnection * dc,EScript::Type * type=nullptr) : 
				ReferenceObject_t(type ? type : getTypeObject(),dc) {}
		virtual ~E_TreeSyncClient() = default;

};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::TreeSync::E_TreeSyncClient,		MinSG::TreeSync::TreeSyncClient*,		&(**eObj))

#endif // E_MINSG_E_TREESYNCCLIENT_H_
#endif // MINSG_EXT_TREE_SYNC

