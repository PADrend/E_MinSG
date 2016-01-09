/*
	This file is part of the E_MinSG library extension Pipeline Statistics.
	Copyright (C) 2016 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_PIPELINESTATISTICS

#include "E_Collector.h"
#include "../../ELibMinSG.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <MinSG/Ext/PipelineStatistics/Collector.h>

namespace E_MinSG {
namespace PipelineStatistics {

EScript::Type * E_Collector::getTypeObject() {
	// E_Collector ---|> E_State
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

void E_Collector::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Collector::getTypeObject();
	declareConstant(&lib, "Collector", typeObject);
	addFactory<MinSG::PipelineStatistics::Collector, E_Collector>();

	using namespace MinSG::PipelineStatistics;

	//! [ESF] new MinSG.PipelineStatistics.Collector()
	ES_CTOR(typeObject, 0, 0, EScript::create(new MinSG::PipelineStatistics::Collector()))
}

E_Collector::E_Collector(MinSG::PipelineStatistics::Collector * collector) :
		E_State(collector, E_Collector::getTypeObject()) {
}

E_Collector::~E_Collector() = default;

}
}

#endif /* MINSG_EXT_PIPELINESTATISTICS */
