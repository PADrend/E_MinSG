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

#include "E_PathNode.h"

#include "../../ELibMinSG.h"
#include "../../Core/Behaviours/E_AbstractBehaviour.h"
#include "E_Waypoint.h"
#include <EScript/EScript.h>
#include <E_Geometry/E_SRT.h>

namespace E_MinSG {

EScript::Type* E_PathNode::typeObject=nullptr;

//! initMembers
void E_PathNode::init(EScript::Namespace & lib) {
	// MinSG.PathNode ----|> MinSG.GroupNode ----|> MinSG.Node ----|> Object
	typeObject = new EScript::Type(E_GroupNode::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::PathNode,E_PathNode>();

	using namespace MinSG;

	//! [ESMF] new MinSG.PathNode
	ES_CTOR(typeObject,0,0, EScript::create(new MinSG::PathNode))

	//! [ESMF] self MinSG.closeLoop(time)
	ES_MFUN(typeObject,PathNode,"closeLoop",1,1,(thisObj->closeLoop(parameter[0].toFloat()),thisEObj))

	//! [ESMF] self MinSG.createWaypoint(SRT,time)
	ES_MFUN(typeObject,PathNode,"createWaypoint",2,2,(thisObj->createWaypoint(
			parameter[0].to<const Geometry::SRT&>(rt),static_cast<float>(parameter[1].toDouble())),thisEObj))

	//! [ESMF] float MinSG.getMaxTime()
	ES_MFUN(typeObject,PathNode,"getMaxTime",0,0,thisObj->getMaxTime())

	//! [ESMF] Bool PathNode.getMetaDisplayTimes()
	ES_MFUN(typeObject,const PathNode, "getMetaDisplayTimes", 0, 0,thisObj->getMetaDisplayTimes())

	//! [ESMF] Bool PathNode.getMetaDisplayWaypoints()
	ES_MFUN(typeObject,const PathNode, "getMetaDisplayWaypoints", 0, 0,thisObj->getMetaDisplayWaypoints())

	//! [ESMF] Waypoint PathNode.getNextWaypoint(float time)
	ES_MFUN(typeObject,const PathNode, "getNextWaypoint", 1, 1,thisObj->getNextWaypoint(parameter[0].toFloat())->second.get())

	//! [ESMF] SRT MinSG.getPosition(float time)
	ES_MFUN(typeObject,PathNode,"getPosition",1,1,EScript::create(thisObj->getPosition(parameter[0].toFloat())))

	//! [ESMF] Waypoint|VOID PathNode.getWaypoint(time)
	ES_MFUNCTION(typeObject,PathNode,"getWaypoint",1,1,{
		MinSG::Waypoint * w=thisObj->getWaypoint(parameter[0].toFloat());
		return w==nullptr ? nullptr : EScript::create(w);
	})
	//! [ESMF] Array PathNode.getWaypoints()
	ES_MFUNCTION(typeObject,PathNode,"getWaypoints",0,0,{
		EScript::Array * a = EScript::Array::create();
		for (MinSG::PathNode::wayPointMap_t::const_iterator it=thisObj->begin();it!=thisObj->end();++it)
			a->pushBack( EScript::create((*it).second.get()) );
		return a;
	})

	//! [ESMF] SRT MinSG.getWorldPosition(float time)
	ES_MFUN(typeObject,PathNode,"getWorldPosition",1,1,EScript::create(thisObj->getWorldPosition(parameter[0].toFloat())))

	//! [ESMF] Bool MinSG.isLooping()
	ES_MFUN(typeObject,PathNode,"isLooping",0,0,thisObj->isLooping())

	//! [ESMF] self PathNode.removeLastWaypoint()
	ES_MFUN(typeObject,PathNode,"removeLastWaypoint",0,0,(thisObj->removeLastWaypoint(),thisEObj))

	//! [ESMF] self MinSG.setLooping(Bool)
	ES_MFUN(typeObject,PathNode,"setLooping",1,1,(thisObj->setLooping(parameter[0].toBool()),thisEObj))

	//! [ESMF] self PathNode.setMetaDisplayTimes(Bool)
	ES_MFUN(typeObject,PathNode, "setMetaDisplayTimes", 1, 1,	(thisObj->setMetaDisplayTimes(parameter[0].to<bool>(rt)), thisEObj))

	//! [ESMF] self PathNode.setMetaDisplayWaypoints(Bool)
	ES_MFUN(typeObject,PathNode, "setMetaDisplayWaypoints", 1, 1,	(thisObj->setMetaDisplayWaypoints(parameter[0].to<bool>(rt)), thisEObj))
}

// ------------------------------------------------------------

//! [ctor]
E_PathNode::E_PathNode(MinSG::PathNode * gNode,EScript::Type * type):
	E_GroupNode(gNode,type?type:typeObject){
}

//! [dtor]
E_PathNode::~E_PathNode(){
}

}

#endif /* MINSG_EXT_WAYPOINTS */
