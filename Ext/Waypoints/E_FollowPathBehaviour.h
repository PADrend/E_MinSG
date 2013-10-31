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

#ifndef __E_FollowPathBehaviour_H
#define __E_FollowPathBehaviour_H

#include "../../Core/Behaviours/E_AbstractBehaviour.h"
#include <MinSG/Ext/Waypoints/FollowPathBehaviour.h>

namespace E_MinSG{

/***
 **   E_FollowPathBehaviour ---|> E_AbstractNodeBehaviour
 **/
class E_FollowPathBehaviour : public E_AbstractNodeBehaviour{
	ES_PROVIDES_TYPE_NAME(FollowPathBehaviour)

	public:
		// ---
		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		E_FollowPathBehaviour(MinSG::FollowPathBehaviour * behaviour);
		virtual ~E_FollowPathBehaviour();

		const MinSG::FollowPathBehaviour * operator*()const	{	return static_cast<const MinSG::FollowPathBehaviour*>(ref().get());	}
		MinSG::FollowPathBehaviour * operator*()			{	return static_cast<MinSG::FollowPathBehaviour*>(ref().get());	}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_FollowPathBehaviour,		MinSG::FollowPathBehaviour*,		**eObj)	

#endif // __E_FollowPathBehaviour_H

#endif /* MINSG_EXT_WAYPOINTS */
