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

#include "E_Waypoint.h"

#include <EScript/EScript.h>
#include <E_Util/E_Utils.h>
#include <E_Geometry/E_SRT.h>
#include "../../ELibMinSG.h"
#include "E_PathNode.h"

using namespace E_Geometry;
using namespace EScript;

namespace E_MinSG {
	
Type* E_Waypoint::typeObject=nullptr;

//! initMembers	
void E_Waypoint::init(EScript::Namespace & lib) {
	// MinSG.Waypoint ----|> Node ----|> Object
	typeObject = new EScript::Type(E_Node::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::Waypoint,E_Waypoint>();

	using namespace MinSG;

	//! [ESMF] PathNode Waypoint.getPath()
	ES_MFUN(typeObject,Waypoint,"getPath",0,0,EScript::create(thisObj->getPath()))

	//! [ESMF] SRT Waypoint.getSRT() 
	ES_MFUN(typeObject,Waypoint,"getSRT",0,0,EScript::create(thisObj->getSRT()))

	//! [ESMF] self Waypoint.setSRT(SRT) 
	ES_MFUN(typeObject,Waypoint,"setSRT",1,1,(thisObj->setSRT( parameter[0].to<const Geometry::SRT&>(rt) ), thisEObj))

	//! [ESMF] Number Waypoint.getTime() 
	ES_MFUN(typeObject,Waypoint,"getTime",0,0,thisObj->getTime())

	//! [ESMF] self Waypoint.setTime(Number) 
	ES_MFUN(typeObject,Waypoint,"setTime",1,1,(thisObj->setTime( parameter[0].toFloat() ), thisEObj))
}

// ------------------------------------------------------------

E_Waypoint::E_Waypoint(MinSG::Waypoint * t) :
	E_Node(t,typeObject){
}

}

#endif /* MINSG_EXT_WAYPOINTS */
