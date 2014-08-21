/*
	This file is part of the MinSG library extension ThesisJonas.
	Copyright (C) 2013 Jonas Knoll

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_THESISJONAS

#include "E_Renderer.h"

#include "../../ELibMinSG.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_MinSG {
namespace ThesisJonas {

EScript::Type * E_Renderer::getTypeObject() {
	// E_Renderer ---|> E_NodeRendererState ---|> E_State
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	return typeObject.get();
}

void E_Renderer::init(EScript::Namespace & lib) {
	using MinSG::ThesisJonas::Renderer;
	EScript::Type * typeObject = E_Renderer::getTypeObject();
	declareConstant(&lib, "Renderer", typeObject);
	addFactory<MinSG::ThesisJonas::Renderer, E_Renderer>();

	declareConstant(typeObject, "NO_TRAVERSAL", EScript::Number::create(Renderer::NO_TRAVERSAL));
	declareConstant(typeObject, "INSIDE_BB", EScript::Number::create(Renderer::INSIDE_BB));
	declareConstant(typeObject, "FIXED_PROJECTED_SIZE", EScript::Number::create(Renderer::FIXED_PROJECTED_SIZE));
	declareConstant(typeObject, "FIXED_PROJECTED_SIZE_PREPROCESSED_DPC", EScript::Number::create(Renderer::FIXED_PROJECTED_SIZE_PREPROCESSED_DPC));

	//! [ESF] Void Renderer.addRendererToNode(Node)
	ES_FUN(typeObject, "addRendererToNode", 1, 1,
				 (Renderer::addRendererToNode( parameter[0].to<MinSG::Node*>(rt) ),EScript::create(nullptr)))

	 //! [ESMF] Number Renderer.getRenderTriangles()
	ES_MFUN(typeObject, const Renderer, "getRenderTriangles", 0, 0,
				 (thisObj->getRenderTriangles()))

	//! [ESMF] Void Renderer.setRenderTriangles(Bool)
	ES_MFUN(typeObject, Renderer, "setRenderTriangles", 1, 1,
				 (thisObj->setRenderTriangles(parameter[0].toBool()),EScript::create(nullptr)))

	//! [ESMF] Number Renderer.getRenderPoints()
	ES_MFUN(typeObject, const Renderer, "getRenderPoints", 0, 0,
				 (thisObj->getRenderPoints()))

	//! [ESMF] Void Renderer.setRenderPoints(Bool)
	ES_MFUN(typeObject, Renderer, "setRenderPoints", 1, 1,
				 (thisObj->setRenderPoints(parameter[0].toBool()),EScript::create(nullptr)))

	//! [ESMF] Number Renderer.getRenderOriginal()
	ES_MFUN(typeObject, const Renderer, "getRenderOriginal", 0, 0,
				 (thisObj->getRenderOriginal()))

	//! [ESMF] Void Renderer.setRenderOriginal(Bool)
	ES_MFUN(typeObject, Renderer, "setRenderOriginal", 1, 1,
				 (thisObj->setRenderOriginal(parameter[0].toBool()),EScript::create(nullptr)))

	//! [ESMF] Number Renderer.getTraverseAlgorithm()
	ES_MFUN(typeObject, const Renderer, "getTraverseAlgorithm", 0, 0,
				 EScript::Number::create(thisObj->getTraverseAlgorithm()))

	//! [ESMF] Void Renderer.setTraverseAlgorithm(Number)
	ES_MFUNCTION(typeObject, Renderer, "setTraverseAlgorithm", 1, 1, {
		switch(parameter[0].to<uint32_t>(rt)) {
			case Renderer::NO_TRAVERSAL:
				thisObj->setTraverseAlgorithm(Renderer::NO_TRAVERSAL);
				break;
			case Renderer::FIXED_PROJECTED_SIZE:
				thisObj->setTraverseAlgorithm(Renderer::FIXED_PROJECTED_SIZE);
				break;
			case Renderer::FIXED_PROJECTED_SIZE_PREPROCESSED_DPC:
				thisObj->setTraverseAlgorithm(Renderer::FIXED_PROJECTED_SIZE_PREPROCESSED_DPC);
				break;

			case Renderer::INSIDE_BB:
			default:
				thisObj->setTraverseAlgorithm(Renderer::INSIDE_BB);
				break;
		}
		return EScript::create(nullptr);
	})

	//! [ESMF] Number Renderer.getProjectedSize()
	ES_MFUN(typeObject, const Renderer, "getProjectedSize", 0, 0,
				 EScript::Number::create(thisObj->getProjectedSize()))

	//! [ESMF] Void Renderer.setProjectedSize(Number)
	ES_MFUN(typeObject, Renderer, "setProjectedSize", 1, 1,
				 (thisObj->setProjectedSize(parameter[0].to<float>(rt)),EScript::create(nullptr)))

	//! [ESMF] Void Renderer.setDynamicPrimitiveCount(Bool)
	ES_MFUN(typeObject, Renderer, "setDynamicPrimitiveCount", 1, 1,
				 (thisObj->setDynamicPrimitiveCount(parameter[0].toBool()),EScript::create(nullptr)))

	//! [ESMF] Number Renderer.getDynamicPrimitiveCount()
	ES_MFUN(typeObject, const Renderer, "getDynamicPrimitiveCount", 0, 0,
				 (thisObj->getDynamicPrimitiveCount()))

	//! [ESMF] Void Renderer.setFrustumCulling(Bool)
	ES_MFUN(typeObject, Renderer, "setFrustumCulling", 1, 1,
				 (thisObj->setFrustumCulling(parameter[0].toBool()),EScript::create(nullptr)))

	//! [ESMF] Number Renderer.getFrustumCulling()
	ES_MFUN(typeObject, const Renderer, "getFrustumCulling", 0, 0,
				 (thisObj->getFrustumCulling()))

	//! [ESMF] Void Renderer.setUseTotalBudget(Bool)
	ES_MFUN(typeObject, Renderer, "setUseTotalBudget", 1, 1,
				 (thisObj->setUseTotalBudget(parameter[0].toBool()),EScript::create(nullptr)))

	//! [ESMF] Number Renderer.getUseTotalBudget()
	ES_MFUN(typeObject, const Renderer, "getUseTotalBudget", 0, 0,
				 (thisObj->getUseTotalBudget()))

	//! [ESMF] Void Renderer.setRenderSMwhenTBtooLow(Bool)
	ES_MFUN(typeObject, Renderer, "setRenderSMwhenTBtooLow", 1, 1,
				 (thisObj->setRenderSMwhenTBtooLow(parameter[0].toBool()),EScript::create(nullptr)))

	//! [ESMF] Number Renderer.getRenderSMwhenTBtooLow()
	ES_MFUN(typeObject, const Renderer, "getRenderSMwhenTBtooLow", 0, 0,
				 (thisObj->getRenderSMwhenTBtooLow()))

	//! [ESMF] Number Renderer.getTriangleBudget()
	ES_MFUN(typeObject, const Renderer, "getTriangleBudget", 0, 0,
				 EScript::Number::create(thisObj->getTriangleBudget()))

	//! [ESMF] Void Renderer.setTriangleBudget(Number)
	ES_MFUN(typeObject, Renderer, "setTriangleBudget", 1, 1,
				 (thisObj->setTriangleBudget(parameter[0].to<double>(rt)),EScript::create(nullptr)))

	 //! [ESMF] Number Renderer.getTriangleBudgetDistributionType()
	ES_MFUN(typeObject, const Renderer, "getTriangleBudgetDistributionType", 0, 0,
				 EScript::Number::create(thisObj->getTriangleBudgetDistributionType()))

	//! [ESMF] Void Renderer.setTriangleBudgetDistributionType(Number)
	ES_MFUNCTION(typeObject, Renderer, "setTriangleBudgetDistributionType", 1, 1, {
		switch(parameter[0].to<uint32_t>(rt)) {
			case MinSG::BudgetAnnotationState::DISTRIBUTE_EVEN:
				thisObj->setTriangleBudgetDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_EVEN);
				break;
			case MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE:
				thisObj->setTriangleBudgetDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE);
				break;
			case MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT:
				thisObj->setTriangleBudgetDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT);
				break;
			case MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT_ITERATIVE:
				thisObj->setTriangleBudgetDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT_ITERATIVE);
				break;
			default:
				thisObj->setTriangleBudgetDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_EVEN);
				break;
		}
		return EScript::create(nullptr);
	})
}

E_Renderer::E_Renderer(MinSG::ThesisJonas::Renderer * renderer) :
		E_NodeRendererState(renderer, E_Renderer::getTypeObject())
//		E_BudgetAnnotationState(renderer)
{
}

E_Renderer::~E_Renderer() {
}

}
}

#endif /* MINSG_EXT_THESISJONAS */
