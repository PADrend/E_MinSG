/*
	This file is part of the E_MinSG library extension Physics.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2013,2015 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2013 Mouns Almarrani

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_PHYSICS

#include "E_PhysicWorld.h"
#include "../../Core/Nodes/E_Node.h"
#include <E_Geometry/E_Box.h>
#include <E_Geometry/E_Plane.h>
#include <E_Geometry/E_Sphere.h>
#include <E_Geometry/E_SRT.h>
#include <E_Geometry/E_Vec3.h>
#include <MinSG/Ext/Physics/PhysicWorld.h>
#include <MinSG/Ext/Physics/CollisionShape.h>
#include <E_Rendering/E_RenderingContext.h>
#include <Util/References.h>
#include <E_Util/E_Utils.h>


namespace E_MinSG {
namespace Physics{
class E_CollisionShape : public EScript::ReferenceObject<Util::Reference<MinSG::Physics::CollisionShape>> {
		ES_PROVIDES_TYPE_NAME(CollisionShape)
	public:
		static EScript::Type * getTypeObject() {
			// E_CollisionShape ---|> Object
			static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
			return typeObject.get();
		}
        template<typename...args> explicit E_CollisionShape(args&&... params) :
			ReferenceObject_t(E_CollisionShape::getTypeObject(),std::forward<args>(params)...) {}

		virtual ~E_CollisionShape() {}
};
}
}
ES_CONV_EOBJ_TO_OBJ(E_MinSG::Physics::E_CollisionShape,   					MinSG::Physics::CollisionShape*,		(**eObj).get())
ES_CONV_OBJ_TO_EOBJ(MinSG::Physics::CollisionShape*,      					E_MinSG::Physics::E_CollisionShape,	obj ? new E_MinSG::Physics::E_CollisionShape(obj) : nullptr)
ES_CONV_OBJ_TO_EOBJ(Util::Reference<MinSG::Physics::CollisionShape>,      	E_MinSG::Physics::E_CollisionShape,	obj ? new E_MinSG::Physics::E_CollisionShape(obj) : nullptr)

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

	declareConstant(ns,E_CollisionShape::getClassName(),E_CollisionShape::getTypeObject());

	using namespace MinSG::Physics;

	// ---------------------------

	//!	[ESMF] PhysicWorld MinSG.Physics.createBulletWorld()
	ES_FUN(ns,"createBulletWorld",0,0,								EScript::create(PhysicWorld::createBulletWorld()))

	//! [ESMF] thisEObj PhysicWorld.applyProperties(Node)
	ES_MFUN(typeObject, PhysicWorld, "applyProperties", 1, 1,	(thisObj->applyProperties(*parameter[0].to<MinSG::Node*>(rt)),thisEObj))

    //! [ESMF] thisEObj PhysicWorld.applyHingeConstraint(Node, Node, Geometry::Vec3, Geometry::Vec3)
	ES_MFUN(typeObject, PhysicWorld, "applyHingeConstraint", 4, 4, (thisObj->applyHingeConstraint(parameter[0].to<MinSG::Node*>(rt), parameter[1].to<MinSG::Node*>(rt), parameter[2].to<Geometry::Vec3>(rt), parameter[3].to<Geometry::Vec3>(rt)),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.applyP2PConstraint(Node, Node, Geometry::Vec3)
	ES_MFUN(typeObject, PhysicWorld, "applyP2PConstraint", 3, 3, (thisObj->applyP2PConstraint(parameter[0].to<MinSG::Node*>(rt), parameter[1].to<MinSG::Node*>(rt), parameter[2].to<Geometry::Vec3>(rt)),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.cleanupWorld()
	ES_MFUN(typeObject, PhysicWorld, "cleanupWorld", 0, 0,			(thisObj->cleanupWorld(),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.createGroundPlane(Geometry::Plane)
	ES_MFUN(typeObject, PhysicWorld, "createGroundPlane", 1, 1,		(thisObj->createGroundPlane(parameter[0].to<const Geometry::Plane&>(rt)),thisEObj))

	//! [ESMF] CollisionShape PhysicWorld.createShape_AABB(Geometry::Box)
	ES_MFUN(typeObject, PhysicWorld, "createShape_AABB", 1, 1,		thisObj->createShape_AABB(parameter[0].to<const Geometry::Box&>(rt)))

	typedef std::vector<std::pair<Util::Reference<CollisionShape>,Geometry::SRT>> shapeArr_t;
	//! [ESMF] CollisionShape PhysicWorld.createShape_Composed( [ [Shape,SRT] ])
	ES_MFUNCTION(typeObject, PhysicWorld, "createShape_Composed", 1, 1,{
		shapeArr_t shapes;
		for(auto& entry : *parameter[0].to<EScript::Array*>(rt) ){
			EScript::Array& entryArr = *entry.to<EScript::Array*>(rt);
			shapes.emplace_back( std::make_pair(
						entryArr.at(0).to<MinSG::Physics::CollisionShape*>(rt),
						entryArr.at(1).to<Geometry::SRT>(rt)));
		}
		return EScript::create(thisObj->createShape_Composed(shapes));
	})

	//! [ESMF] CollisionShape PhysicWorld.createShape_Sphere(Geometry::Sphere)
	ES_MFUN(typeObject, PhysicWorld, "createShape_Sphere", 1, 1,	thisObj->createShape_Sphere(parameter[0].to<const Geometry::Sphere&>(rt)))

	//! [ESMF] Geometry.Vec3 PhysicWorld.getGravity()
	ES_MFUN(typeObject, PhysicWorld, "getGravity", 0, 0,			EScript::create((thisObj->getGravity())))

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

	//! [ESMF] thisEObj PhysicWorld.setFriction(Node, float)
	ES_MFUN(typeObject, PhysicWorld, "setFriction", 2, 2,			(thisObj->setFriction(*parameter[0].to<MinSG::Node*>(rt), parameter[1].toFloat() ),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.updateLocalSurfaceVelocity(Node, Vec3)
	ES_MFUN(typeObject, PhysicWorld, "updateLocalSurfaceVelocity", 2, 2,(thisObj->updateLocalSurfaceVelocity(parameter[0].to<MinSG::Node*>(rt), parameter[1].to<Geometry::Vec3>(rt)),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.setMass(Node, float)
	ES_MFUN(typeObject, PhysicWorld, "setMass", 2, 2,				(thisObj->setMass(*parameter[0].to<MinSG::Node*>(rt), parameter[1].toFloat() ),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.setRollingFriction(Node, float)
	ES_MFUN(typeObject, PhysicWorld, "setRollingFriction", 2, 2,	(thisObj->setRollingFriction(*parameter[0].to<MinSG::Node*>(rt), parameter[1].toFloat() ),thisEObj))

	//! [ESMF] thisEObj PhysicWorld.setShape(Node, CollisionShape)
	ES_MFUN(typeObject, PhysicWorld, "setShape", 2, 2,				(thisObj->setShape(*parameter[0].to<MinSG::Node*>(rt),
								  parameter[1].to<MinSG::Physics::CollisionShape*>(rt)) ,thisEObj))

}

}

}

#endif //MINSG_EXT_PHYSICS

