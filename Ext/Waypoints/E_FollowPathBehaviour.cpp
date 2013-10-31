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

#include "E_FollowPathBehaviour.h"

#include "E_PathNode.h"

#include "../../ELibMinSG.h"

#include <EScript/EScript.h>
#include <iostream>
#include <sstream>

namespace E_MinSG {

EScript::Type* E_FollowPathBehaviour::typeObject=nullptr;

// -----
//! [static]
void E_FollowPathBehaviour::init(EScript::Namespace & lib) {
	// MinSG.FollowPathBehaviour ---|> E_AbstractNodeBehaviour
	typeObject = new EScript::Type(E_AbstractNodeBehaviour::getTypeObject());

	declareConstant(&lib,getClassName(),typeObject);

	using namespace MinSG;

		//! [ESMF] new MinSG.FollowPathBehaviour( pathNode,Node[,speed )	
	ES_CTOR(typeObject,2,3,E_Behavior::create(
			 new FollowPathBehaviour(
				parameter[0].toBool() ? **EScript::assertType<E_PathNode>(rt,parameter[0]) : nullptr,
				parameter[1].to<MinSG::Node*>(rt),parameter[2].toFloat(1.0f))))


	//! [ESMF] self MinSG.FollowPathBehaviour.setPath(MinSG.PathNode | void)
	ES_MFUN(typeObject,FollowPathBehaviour,"setPath",1,1,(thisObj->setPath(
						parameter[0].toBool() ? **EScript::assertType<E_PathNode>(rt,parameter[0]) : nullptr),thisEObj))


	//! [ESMF] Number MinSG.FollowPathBehaviour.getSpeed()
	ES_MFUN(typeObject,FollowPathBehaviour,"getSpeed",0,0,thisObj->getSpeed())

	//! [ESMF] self MinSG.FollowPathBehaviour.setSpeed(Number)
	ES_MFUN(typeObject,FollowPathBehaviour,"setSpeed",1,1,(thisObj->setSpeed(parameter[0].toFloat()),thisEObj))

	//! [ESMF] Number MinSG.FollowPathBehaviour.getPosition()
	ES_MFUN(typeObject,FollowPathBehaviour,"getPosition",0,0,thisObj->getPosition())

	//! [ESMF] self MinSG.FollowPathBehaviour.setPosition(pos,now)
	ES_MFUN(typeObject,FollowPathBehaviour,"setPosition",2,2,(thisObj->setPosition(parameter[0].toFloat(),parameter[1].toFloat()),thisEObj))

	//! [ESMF] MinSG.PathNode MinSG.FollowPathBehaviour.getPath()	
	ES_MFUN(typeObject,FollowPathBehaviour,"getPath",0,0,EScript::create(thisObj->getPath()))

	addFactory<MinSG::FollowPathBehaviour,E_FollowPathBehaviour>();
}

// ------------------------------------------------------------
//! [ctor]
E_FollowPathBehaviour::E_FollowPathBehaviour(MinSG::FollowPathBehaviour * f):E_AbstractNodeBehaviour(f,typeObject) {
}

//! [dtor]
E_FollowPathBehaviour::~E_FollowPathBehaviour() {
	//dtor
}

}

#endif /* MINSG_EXT_WAYPOINTS */
