/*
	This file is part of the E_MinSG library extension SamplingAnalysis.
	Copyright (C) 2011-2012 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_SAMPLING_ANALYSIS

#include "E_SamplingAnalysis.h"
#include "../../ELibMinSG.h"
#include <EScript/Utils/DeprecatedMacros.h>
#include <E_Geometry/E_Vec3.h>
#include <E_Util/Graphics/E_Bitmap.h>
#include <MinSG/Ext/SamplingAnalysis/SamplingAnalysis.h>

namespace E_MinSG {
namespace E_SamplingAnalysis{

using namespace EScript;
using namespace MinSG;
using namespace E_Geometry;
using namespace SamplingAnalysis;

static Object * createEHistogram(SamplingAnalysis::Histogram1D * hist){
	Array * buckets(Array::create());
		for(std::vector<uint32_t>::iterator it=hist->buckets.begin();it!=hist->buckets.end();++it)
		buckets->pushBack(Number::create(*it));

	ObjRef eHist( ExtObject::create() );

	eHist->setAttribute("buckets",buckets);
	eHist->setAttribute("sum",Number::create(hist->sum));
	eHist->setAttribute("maxValue",Number::create(hist->maxValue));
	eHist->setAttribute("overflow",Number::create(hist->overflow));
	return eHist.detachAndDecrease();
}

//! (static)
void init(EScript::Namespace & lib) {

	Namespace * ns = new Namespace();
	declareConstant(&lib,"SamplingAnalysis",ns);


	//! result createDistanceHistogram(Array Vec3, numberOfBuckets)
	ES_FUNCTION2( ns, "createDistanceHistogram",2,2,{
		std::vector<Geometry::Vec3> positions;
		for(auto & entry : *parameter[0].to<EScript::Array*>(rt))
			positions.emplace_back( entry.to<Geometry::Vec3>(rt) );
		return createEHistogram(createDistanceHistogram(positions,parameter[1].toInt()));
	})

	//! result create2dDistanceHistogram(Array Vec3, numberOfBuckets)
	ES_FUNCTION2( ns, "create2dDistanceHistogram",2,2,{
		std::vector<Geometry::Vec3> positions;
		for(auto & entry : *parameter[0].to<EScript::Array*>(rt))
			positions.emplace_back( entry.to<Geometry::Vec3>(rt) );
		return EScript::create(create2dDistanceHistogram(positions,parameter[1].toInt()));
	})

	//! result createAngleHistogram(Array Vec3, numberOfBuckets)
	ES_FUNCTION2( ns, "createAngleHistogram",2,2,{
		std::vector<Geometry::Vec3> positions;
		for(auto & entry : *parameter[0].to<EScript::Array*>(rt))
			positions.emplace_back( entry.to<Geometry::Vec3>(rt) );
		return createEHistogram(createAngleHistogram(positions,parameter[1].toInt()));
	})

	//! result createClosestPointDistanceHistogram(Array Vec3, numberOfBuckets)
	ES_FUNCTION2( ns, "createClosestPointDistanceHistogram",2,2,{
		std::vector<Geometry::Vec3> positions;
		for(auto & entry : *parameter[0].to<EScript::Array*>(rt))
			positions.emplace_back( entry.to<Geometry::Vec3>(rt) );
		return createEHistogram(createClosestPointDistanceHistogram(positions,parameter[1].toInt()));
	})

}

}
}


#endif // MINSG_EXT_SAMPLING_ANALYSIS
