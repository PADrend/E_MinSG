/*
	This file is part of the E_MinSG library extension TreeSync.
	Copyright (C) 2012-2013 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_TREE_SYNC

#include "E_TreeSyncClient.h"
#include "../../SceneManagement/E_SceneManager.h"
#include <E_Util/Network/E_DataConnection.h>
#include <EScript/Basics.h>

namespace E_MinSG{
namespace TreeSync{

//! (static)
EScript::Type * E_TreeSyncClient::getTypeObject() {
	// E_TreeSyncClient ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members 
void E_TreeSyncClient::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_TreeSyncClient::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace MinSG;
	using namespace MinSG::TreeSync;

	//! [ESF] new TreeSyncClient(Util::Network::DataConnection)
	ES_CTOR(typeObject,1,1,								new E_TreeSyncClient( (**EScript::assertType<E_Util::Network::E_DataConnection>(rt,parameter[0])).get(),thisType))

	//! [ESMF] self TreeSyncClient.execute(SceneManager)
	ES_MFUN(typeObject, TreeSyncClient,"execute",1,1,	(thisObj->execute( parameter[0].to<SceneManagement::SceneManager&>(rt) ),thisEObj))


}
}

}
#endif // MINSG_EXT_TREE_SYNC

