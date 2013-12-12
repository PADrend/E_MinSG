/*
	This file is part of the E_MinSG library extension SVS.
	Copyright (C) 2013 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SVS

#ifndef E_MINSG_SVS_E_BUDGETRENDERER_H
#define E_MINSG_SVS_E_BUDGETRENDERER_H

#include "../../Core/States/E_NodeRendererState.h"
#include <MinSG/Ext/SVS/BudgetRenderer.h>
#include <string>

namespace EScript {
class Namespace;
class Runtime;
class Type;
}
namespace MinSG {
namespace SVS {
class BudgetRenderer;
}
}
namespace E_MinSG {
namespace SVS {

//!	EScript wrapper class for MinSG::SVS::BudgetRenderer
class E_BudgetRenderer : public E_NodeRendererState {
	protected:
		E_BudgetRenderer(MinSG::SVS::BudgetRenderer * renderer);
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_BudgetRenderer();

		const MinSG::SVS::BudgetRenderer * operator*() const {
			return static_cast<const MinSG::SVS::BudgetRenderer *>(ref().get());
		}
		MinSG::SVS::BudgetRenderer * operator*() {
			return static_cast<MinSG::SVS::BudgetRenderer *>(ref().get());
		}
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::SVS::E_BudgetRenderer, MinSG::SVS::BudgetRenderer *, **eObj)

#endif /* E_MINSG_SVS_E_BUDGETRENDERER_H */

#endif /* MINSG_EXT_SVS */
