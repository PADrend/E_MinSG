/*
	This file is part of the E_MinSG library extension SVS.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SVS

#ifndef E_MINSG_SVS_E_GEOMETRYNODECOLLECTOR_H
#define E_MINSG_SVS_E_GEOMETRYNODECOLLECTOR_H

#include "../../Core/States/E_NodeRendererState.h"
#include <MinSG/Ext/SVS/GeometryNodeCollector.h>
#include <string>

namespace EScript {
class Namespace;
class Runtime;
class Type;
}
namespace MinSG {
namespace SVS {
class GeometryNodeCollector;
}
}
namespace E_MinSG {
namespace SVS {

//!	EScript wrapper class for MinSG::SVS::GeometryNodeCollector
class E_GeometryNodeCollector : public E_NodeRendererState {
	protected:
		E_GeometryNodeCollector(MinSG::SVS::GeometryNodeCollector * collector);
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_GeometryNodeCollector();

		const MinSG::SVS::GeometryNodeCollector * operator*() const {
			return static_cast<const MinSG::SVS::GeometryNodeCollector *>(ref().get());
		}
		MinSG::SVS::GeometryNodeCollector * operator*() {
			return static_cast<MinSG::SVS::GeometryNodeCollector *>(ref().get());
		}
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::SVS::E_GeometryNodeCollector,	MinSG::SVS::GeometryNodeCollector*,	**eObj)

#endif /* E_MINSG_SVS_E_GEOMETRYNODECOLLECTOR_H */

#endif /* MINSG_EXT_SVS */
