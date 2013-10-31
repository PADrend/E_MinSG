/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_StatChart_H
#define __E_StatChart_H

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/Tools/StatChart.h>

namespace E_MinSG{

/**
 *   [E_StatChart] ---|> [ReferenceObject]
 */
class E_StatChart : public EScript::ReferenceObject<MinSG::StatChart,EScript::Policies::SameEObjects_ComparePolicy>{
	ES_PROVIDES_TYPE_NAME(StatChart)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_StatChart(int width,int height,float timeScale,EScript::Type* type=nullptr);
		virtual ~E_StatChart();
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_StatChart,		MinSG::StatChart*,		&(**eObj))

#endif // __E_StatChart_H
