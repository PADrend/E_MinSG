/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_Statistics_H
#define __E_Statistics_H

#include <EScript/Objects/ExtObject.h>
#include <EScript/Basics.h>
#include <MinSG/Core/Statistics.h>

namespace MinSG {
class Statistics;
}
namespace E_MinSG {

//! [E_Statistics] ---|> [ExtObject]
class E_Statistics : public EScript::ExtObject {
		ES_PROVIDES_TYPE_NAME(Statistics)
	public:
		EMINSGAPI static EScript::Type * getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		EMINSGAPI E_Statistics(MinSG::Statistics & stats, EScript::Type * type = nullptr);
		EMINSGAPI virtual ~E_Statistics();

		const MinSG::Statistics & operator*()const	{	return myStats;	}
		MinSG::Statistics & operator*()				{	return myStats;	}
	
	private:
		MinSG::Statistics & myStats;
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_Statistics,		MinSG::Statistics&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_Statistics,		MinSG::Statistics*,		&(**eObj))

#endif // __E_Statistics_H
