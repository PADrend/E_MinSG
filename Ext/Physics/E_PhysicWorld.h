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
#ifndef E_PHYSICWORLD_H
#define E_PHYSICWORLD_H

#include<MinSG/Ext/Physics/PhysicWorld.h>
#include <EScript/Objects/ExtReferenceObject.h>
#include <EScript/Objects/ReferenceObject.h>
namespace EScript {
class Namespace;
}
namespace E_MinSG {
namespace  Physics {
    /*!	EScript wrapper class for MinSG::Physics::PhysicWorld

		E_PhysicWorld ---|> EScript::ExtReferenceObject<MinSG::Physics::PhysicWorld>
			|
			--------------> MinSG::Physics::PhysicWorld	*/
class E_PhysicWorld : public EScript::ReferenceObject<Util::Reference<MinSG::Physics::PhysicWorld>> {
		ES_PROVIDES_TYPE_NAME(PhysicWorld)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

//		E_PhysicWorld(PhysicWorld *w, EScript::Type * type=nullptr) :
//				ExtReferenceObject_t(w), type ? type : E_PhysicWorld::getTypeObject()) {}
        template<typename...args> explicit E_PhysicWorld(args&&... params) :
			ReferenceObject_t(E_PhysicWorld::getTypeObject(),std::forward<args>(params)...) {}

		virtual ~E_PhysicWorld() {}

};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::Physics::E_PhysicWorld,    MinSG::Physics::PhysicWorld*,		(**eObj).get())
ES_CONV_OBJ_TO_EOBJ(MinSG::Physics::PhysicWorld*,       E_MinSG::Physics::E_PhysicWorld,	obj ? new E_MinSG::Physics::E_PhysicWorld(obj) : nullptr)

#endif // E_PHYSICWORLD_H
#endif // MINSG_EXT_PHYSICS
