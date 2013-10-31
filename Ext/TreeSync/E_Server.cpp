/*
	This file is part of the E_MinSG library extension TreeSync.
	Copyright (C) 2012-2013 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_TREE_SYNC

#include "E_Server.h"
#include "../../SceneManagement/E_SceneManager.h"
#include "../../Core/Nodes/E_Node.h"
#include <E_Util/Network/E_DataBroadcaster.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_MinSG{
namespace TreeSync{

//! (static)
EScript::Type * E_Server::getTypeObject() {
	// E_Server ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members 
void E_Server::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Server::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace MinSG;
	using namespace MinSG::TreeSync;

	//! [ESF] new Server(SceneManager,DataBroadcaster)
	ES_CTOR(typeObject,2,2,
				new E_Server( parameter[0].to<SceneManagement::SceneManager&>(rt),
								(**EScript::assertType<E_Util::Network::E_DataBroadcaster>(rt,parameter[1])).get()))

	//! [ESMF] self Server.initNodeObserver(Node)
	ES_MFUN(typeObject, Server,"initNodeObserver",1,1,	(thisObj->initNodeObserver(parameter[0].to<MinSG::Node*>(rt)),thisEObj))

}
}
}
#endif // MINSG_EXT_TREE_SYNC

