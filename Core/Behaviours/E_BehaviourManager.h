/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_BehaviourManager_H
#define __E_BehaviourManager_H

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Core/Behaviours/BehaviourManager.h>

namespace E_MinSG {

/***
 **   E_BehaviourManager ---|> Object
 **/
class E_BehaviourManager : public EScript::ReferenceObject<Util::Reference<MinSG::BehaviourManager> >{
	ES_PROVIDES_TYPE_NAME(BehaviourManager)

	public:
		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);

		E_BehaviourManager(MinSG::BehaviourManager * manager) : ReferenceObject_t(manager,getTypeObject()){}
		virtual ~E_BehaviourManager(){}

		MinSG::BehaviourManager * operator*()const		{	return ref().get();	}
		MinSG::BehaviourManager * get()const			{	return ref().get();	}

};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_BehaviourManager,		MinSG::BehaviourManager*,		**eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::BehaviourManager*, 			E_MinSG::E_BehaviourManager,	new E_MinSG::E_BehaviourManager(obj))

#endif // __E_BehaviourManager_H
