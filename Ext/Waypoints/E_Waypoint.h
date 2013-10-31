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

#ifndef E_WAYPOINT_H
#define E_WAYPOINT_H

#include "../../Core/Nodes/E_Node.h"
#include <MinSG/Ext/Waypoints/Waypoint.h>

namespace E_MinSG{

/**
 **   [E_Waypoint] ---|> [E_Node] ---|> [Object]
 **/
class E_Waypoint : public E_Node {
		ES_PROVIDES_TYPE_NAME(Waypoint)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		const MinSG::Waypoint * operator*()const	{	return static_cast<const MinSG::Waypoint*>(ref().get());	}
		MinSG::Waypoint * operator*()				{	return static_cast<MinSG::Waypoint*>(ref().get());	}

	protected:
		E_Waypoint(MinSG::Waypoint * t);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_Waypoint,		MinSG::Waypoint*,		**eObj)	

#endif // E_WAYPOINT_H

#endif /* MINSG_EXT_WAYPOINTS */
