/*
	This file is part of the E_MinSG library extension SphericalSampling.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SPHERICALSAMPLING

#ifndef E_MINSG_SPHERICALSAMPLING_E_BUDGETRENDERER_H
#define E_MINSG_SPHERICALSAMPLING_E_BUDGETRENDERER_H

#include "../../Core/States/E_NodeRendererState.h"
#include <MinSG/Ext/SphericalSampling/BudgetRenderer.h>
#include <string>

namespace EScript {
class Namespace;
class Runtime;
class Type;
}
namespace MinSG {
namespace SphericalSampling {
class BudgetRenderer;
}
}
namespace E_MinSG {
namespace SphericalSampling {

//!	EScript wrapper class for MinSG::SphericalSampling::BudgetRenderer
class E_BudgetRenderer : public E_NodeRendererState {
	protected:
		E_BudgetRenderer(MinSG::SphericalSampling::BudgetRenderer * renderer);
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_BudgetRenderer();

		const MinSG::SphericalSampling::BudgetRenderer * operator*() const {
			return static_cast<const MinSG::SphericalSampling::BudgetRenderer *>(ref().get());
		}
		MinSG::SphericalSampling::BudgetRenderer * operator*() {
			return static_cast<MinSG::SphericalSampling::BudgetRenderer *>(ref().get());
		}
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::SphericalSampling::E_BudgetRenderer, MinSG::SphericalSampling::BudgetRenderer *, **eObj)

#endif /* E_MINSG_SPHERICALSAMPLING_E_BUDGETRENDERER_H */

#endif /* MINSG_EXT_SPHERICALSAMPLING */
