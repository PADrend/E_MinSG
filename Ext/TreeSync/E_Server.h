/*
	This file is part of the E_MinSG library extension TreeSync.
	Copyright (C) 2012-2013 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_TREE_SYNC

#ifndef _E_MinSG_TreeSync_E_Server_H_
#define _E_MinSG_TreeSync_E_Server_H_

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/TreeSync/Server.h>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG{
namespace TreeSync{

/*!	EScript wrapper class for MinSG::TreeSync::Server.	

		E_Server ---|> EScript::ReferenceObject<MinSG::TreeSync::Server>
			|
			--------------> MinSG::TreeSync::Server		*/
class E_Server : public EScript::ReferenceObject<MinSG::TreeSync::Server, EScript::Policies::SameEObjects_ComparePolicy> {
		ES_PROVIDES_TYPE_NAME(Server)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_Server(MinSG::SceneManagement::SceneManager & sm,Util::Network::DataBroadcaster * db) : 
				ReferenceObject_t(getTypeObject() , sm,db) {}
        virtual ~E_Server() = default;

};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::TreeSync::E_Server,		MinSG::TreeSync::Server*,		&(**eObj))

#endif // _E_MinSG_TreeSync_E_Server_H_
#endif // MINSG_EXT_TREE_SYNC
