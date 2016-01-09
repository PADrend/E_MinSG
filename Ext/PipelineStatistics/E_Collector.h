/*
	This file is part of the E_MinSG library extension Pipeline Statistics.
	Copyright (C) 2016 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_PIPELINESTATISTICS

#ifndef E_MINSG_PIPELINESTATISTICS_E_COLLECTOR_H_
#define E_MINSG_PIPELINESTATISTICS_E_COLLECTOR_H_

#include "../../Core/States/E_State.h"
#include <MinSG/Ext/PipelineStatistics/Collector.h>
#include <string>

namespace EScript {
class Namespace;
class Runtime;
class Type;
}
namespace MinSG {
namespace PipelineStatistics {
class Collector;
}
}
namespace E_MinSG {
namespace PipelineStatistics {

//!	EScript wrapper class for MinSG::PipelineStatistics::Collector
class E_Collector : public E_State {
	protected:
		E_Collector(MinSG::PipelineStatistics::Collector * collector);
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_Collector();

		const MinSG::PipelineStatistics::Collector * operator*() const {
			return static_cast<const MinSG::PipelineStatistics::Collector*>(ref().get());
		}
		MinSG::PipelineStatistics::Collector * operator*() {
			return static_cast<MinSG::PipelineStatistics::Collector*>(ref().get());
		}
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::PipelineStatistics::E_Collector, MinSG::PipelineStatistics::Collector*, **eObj)

#endif /* E_MINSG_PIPELINESTATISTICS_E_COLLECTOR_H_ */

#endif /* MINSG_EXT_PIPELINESTATISTICS */
