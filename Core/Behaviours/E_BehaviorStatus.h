/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_BehaviorStatus_H
#define __E_BehaviorStatus_H

#include <EScript/Objects/ExtReferenceObject.h>
#include <E_Util/E_Utils.h>
#include <E_Util/E_ObjectFactory.h>
#include <MinSG/Core/Behaviours/BehaviorStatus.h>

namespace E_MinSG{

/***
 **   E_BehaviorStatus ---|> EScript::ExtReferenceObject
 **     |
 **     ------> MinSG::BehaviorStatus
 **/
class E_BehaviorStatus : public EScript::ExtReferenceObject< Util::Reference<MinSG::BehaviorStatus>,EScript::Policies::EqualContent_ComparePolicy,E_Util::Policies::StoreAttrsInAttributeProvider>{
	ES_PROVIDES_TYPE_NAME(BehaviorStatus)

	public:
		// ---
		EMINSGAPI static EScript::Type* getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		E_BehaviorStatus(MinSG::BehaviorStatus * behavior) : ExtReferenceObject_t(behavior,getTypeObject()) {}
		virtual ~E_BehaviorStatus()	{}

		MinSG::BehaviorStatus * operator*()const	{	return ref().get();	}
		MinSG::BehaviorStatus * get()const			{	return ref().get();	}
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_BehaviorStatus,		MinSG::BehaviorStatus*,		**eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::BehaviorStatus*, 		E_MinSG::E_BehaviorStatus,	new E_MinSG::E_BehaviorStatus(obj))

#endif // __E_BehaviorStatus_H
