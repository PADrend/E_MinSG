/*
	This file is part of the E_MinSG library extension Physics.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2013 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2013 Mouns Almarrani

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_PHYSICS

#include "E_PhysicWorld.h"
#include "../../Core/Nodes/E_Node.h"
#include <E_Geometry/E_Plane.h>
#include <E_Geometry/E_Vec3.h>
#include <MinSG/Ext/Physics/PhysicWorld.h>
#include <E_Rendering/E_RenderingContext.h>
#include <Util/References.h>
#include <E_Util/E_Utils.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_MinSG {
namespace Physics{
	//! (static)
EScript::Type * E_PhysicWorld::getTypeObject() {
	// E_PhysicWorld ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_PhysicWorld::init(EScript::Namespace & lib) {
	EScript::Namespace * ns = new EScript::Namespace;
	declareConstant(&lib,"Physics",ns);

	EScript::Type * typeObject = E_PhysicWorld::getTypeObject();
	declareConstant(ns,getClassName(),typeObject);

	using namespace MinSG::Physics;

	declareConstant(ns,"SHAPE_TYPE",EScript::create(PhysicWorld::SHAPE_TYPE.toString()));
	declareConstant(ns,"SHAPE_TYPE_BOX",EScript::create(PhysicWorld::SHAPE_TYPE_BOX));
	declareConstant(ns,"SHAPE_TYPE_SPHERE",EScript::create(PhysicWorld::SHAPE_TYPE_SPHERE));
	declareConstant(ns,"SHAPE_TYPE_CONVEX_HULL",EScript::create(PhysicWorld::SHAPE_TYPE_CONVEX_HULL));
	declareConstant(ns,"SHAPE_TYPE_STATIC_TRIANGLE_MESH",EScript::create(PhysicWorld::SHAPE_TYPE_STATIC_TRIANGLE_MESH));

	//! [ESF] Bool MinSG.Physics.hasPhysicsProperties(Node)
	ES_FUN(ns, "hasPhysicsProperties", 1, 1,	(PhysicWorld::hasPhysicsProperties(parameter[0].to<MinSG::Node*>(rt))))

	// ---------------------------

	//!	[ESMF] PhysicWorld MinSG.Physics.createBulletWorld()
	ES_FUN(ns,"createBulletWorld",0,0,								EScript::create(PhysicWorld::createBulletWorld()))

	//! [ESMF] thisEObj PhysicWorld.addNodeToPhyiscWorld(Node)
	ES_MFUN(typeObject, PhysicWorld, "addNodeToPhyiscWorld", 1, 1,	(thisObj->addNodeToPhyiscWorld(parameter[0].to<MinSG::Node*>(rt)),thisEObj))

    //! [ESMF] thisEObj PhysicWorld.applyHingeConstraint(Node, Node, Geometry::Vec3, Geometry::Vec3)
	ES_MFUN(typeObject, PhysicWorld, "applyHingeConstraint", 4, 4, (thisObj->applyHingeConstraint(parameter[0].to<MinSG::Node*>(rt), parameter[1].to<MinSG::Node*>(rt), parameter[2].to<Geometry::Vec3>(rt), parameter[3].to<Geometry::Vec3>(rt)),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.applyP2PConstraint(Node, Node, Geometry::Vec3)
	ES_MFUN(typeObject, PhysicWorld, "applyP2PConstraint", 3, 3, (thisObj->applyP2PConstraint(parameter[0].to<MinSG::Node*>(rt), parameter[1].to<MinSG::Node*>(rt), parameter[2].to<Geometry::Vec3>(rt)),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.cleanupWorld()
	ES_MFUN(typeObject, PhysicWorld, "cleanupWorld", 0, 0,			(thisObj->cleanupWorld(),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.createGroundPlane(Geometry::Plane)
	ES_MFUN(typeObject, PhysicWorld, "createGroundPlane", 1, 1,		(thisObj->createGroundPlane(parameter[0].to<const Geometry::Plane&>(rt)),thisEObj))

	//! [ESMF] String PhysicWorld.getConstraintPivot(Node)
	ES_MFUN(typeObject, PhysicWorld, "getConstraintPivot", 1, 1,	(thisObj->getConstraintPivot(parameter[0].to<MinSG::Node*>(rt))))

	//! [ESMF] Number PhysicWorld.getFriction(Node)
	ES_MFUN(typeObject, PhysicWorld, "getFriction", 1, 1,			(thisObj->getFriction(parameter[0].to<MinSG::Node*>(rt))))

	//! [ESMF] Geometry.Vec3 PhysicWorld.getGravity()
	ES_MFUN(typeObject, PhysicWorld, "getGravity", 0, 0,			EScript::create((thisObj->getGravity())))

	//! [ESMF] Number PhysicWorld.getLocalSurfaceVelocity(Node)
	ES_MFUN(typeObject, PhysicWorld, "getLocalSurfaceVelocity", 1, 1,	(thisObj->getLocalSurfaceVelocity(parameter[0].to<MinSG::Node*>(rt))))

	//! [ESMF] Number PhysicWorld.getMass(Node)
	ES_MFUN(typeObject, PhysicWorld, "getMass", 1, 1,				(thisObj->getMass(parameter[0].to<MinSG::Node*>(rt))))

	//! [ESMF] Number PhysicWorld.getRollingFriction(Node)
	ES_MFUN(typeObject, PhysicWorld, "getRollingFriction", 1, 1,	(thisObj->getRollingFriction(parameter[0].to<MinSG::Node*>(rt))))

	//! [ESMF] Number PhysicWorld.getShapeDescription(Node)
	ES_MFUN(typeObject, PhysicWorld, "getShapeDescription", 1, 1,	(E_Util::E_Utils::convertGenericAttributeToEScriptObject((thisObj->getShapeDescription(parameter[0].to<MinSG::Node*>(rt))))))

	 //! [ESMF] thisEObj PhysicWorld.initNodeObserver(Node)
	ES_MFUN(typeObject, PhysicWorld, "initNodeObserver", 1, 1,		(thisObj->initNodeObserver(parameter[0].to<MinSG::Node*>(rt)),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.removeConstraints(Node)
	ES_MFUN(typeObject, PhysicWorld, "removeConstraints", 1, 1,	(thisObj->removeConstraints(parameter[0].to<MinSG::Node*>(rt)),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.removeConstraintBetweenNodes(Node, Node)
	ES_MFUN(typeObject, PhysicWorld, "removeConstraintBetweenNodes", 2, 2,	(thisObj->removeConstraintBetweenNodes(parameter[0].to<MinSG::Node*>(rt), parameter[1].to<MinSG::Node*>(rt)),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.removeNode(Node)
	ES_MFUN(typeObject, PhysicWorld, "removeNode", 1, 1,			(thisObj->removeNode(parameter[0].to<MinSG::Node*>(rt)),thisEObj))

	 //! [ESMF] thisEObj PhysicWorld.renderPhysicWorld(RenderingContext)
	ES_MFUN(typeObject, PhysicWorld, "renderPhysicWorld", 1, 1,		(thisObj->renderPhysicWorld(*parameter[0].to<Rendering::RenderingContext*>(rt)),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.setGravity(Geometry.Vec3)
	ES_MFUN(typeObject, PhysicWorld, "setGravity", 1, 1,			(thisObj->setGravity(parameter[0].to<Geometry::Vec3>(rt)),thisEObj))

   //! [ESMF] thisEObj PhysicWorld.stepSimulation(float)
	ES_MFUN(typeObject, PhysicWorld, "stepSimulation", 1, 1,		(thisObj->stepSimulation(parameter[0].toFloat()),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.updateConstraintPivot(Node, string)
	ES_MFUN(typeObject, PhysicWorld, "updateConstraintPivot", 2, 2,(thisObj->updateConstraintPivot(parameter[0].to<MinSG::Node*>(rt), parameter[1].toString()),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.updateFriction(Node, float)
	ES_MFUN(typeObject, PhysicWorld, "updateFriction", 2, 2,		(thisObj->updateFriction(parameter[0].to<MinSG::Node*>(rt), parameter[1].toFloat() ),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.updateLocalSurfaceVelocity(Node, Vec3)
	ES_MFUN(typeObject, PhysicWorld, "updateLocalSurfaceVelocity", 2, 2,(thisObj->updateLocalSurfaceVelocity(parameter[0].to<MinSG::Node*>(rt), parameter[1].to<Geometry::Vec3>(rt)),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.updateMass(Node, float)
	ES_MFUN(typeObject, PhysicWorld, "updateMass", 2, 2,			(thisObj->updateMass(parameter[0].to<MinSG::Node*>(rt), parameter[1].toFloat() ),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.updateRollingFriction(Node, float)
	ES_MFUN(typeObject, PhysicWorld, "updateRollingFriction", 2, 2,	(thisObj->updateRollingFriction(parameter[0].to<MinSG::Node*>(rt), parameter[1].toFloat() ),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.updateShape(Node, Map)
	ES_MFUN(typeObject, PhysicWorld, "updateShape", 2, 2,			(thisObj->updateShape(parameter[0].to<MinSG::Node*>(rt),
								  dynamic_cast< Util::GenericAttributeMap*>( E_Util::E_Utils::convertEScriptObjectToGenericAttribute( parameter[1].to<EScript::Map*>(rt) ))),thisEObj))



}

}

}

#endif //MINSG_EXT_PHYSICS

