/*
	This file is part of the E_MinSG library extension SphericalSampling.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SPHERICALSAMPLING

#ifndef E_MINSG_SPHERICALSAMPLING_E_GEOMETRYNODECOLLECTOR_H
#define E_MINSG_SPHERICALSAMPLING_E_GEOMETRYNODECOLLECTOR_H

#include "../../Core/States/E_NodeRendererState.h"
#include <MinSG/Ext/SphericalSampling/GeometryNodeCollector.h>
#include <string>

namespace EScript {
class Namespace;
class Runtime;
class Type;
}
namespace MinSG {
namespace SphericalSampling {
class GeometryNodeCollector;
}
}
namespace E_MinSG {
namespace SphericalSampling {

//!	EScript wrapper class for MinSG::SphericalSampling::GeometryNodeCollector
class E_GeometryNodeCollector : public E_NodeRendererState {
	protected:
		E_GeometryNodeCollector(MinSG::SphericalSampling::GeometryNodeCollector * collector);
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_GeometryNodeCollector();

		const MinSG::SphericalSampling::GeometryNodeCollector * operator*() const {
			return static_cast<const MinSG::SphericalSampling::GeometryNodeCollector *>(ref().get());
		}
		MinSG::SphericalSampling::GeometryNodeCollector * operator*() {
			return static_cast<MinSG::SphericalSampling::GeometryNodeCollector *>(ref().get());
		}
};

}
}

#endif /* E_MINSG_SPHERICALSAMPLING_E_GEOMETRYNODECOLLECTOR_H */

#endif /* MINSG_EXT_SPHERICALSAMPLING */
