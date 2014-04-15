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
	EScript::Type * typeObject = E_Renderer::getTypeObject();
	declareConstant(&lib, "Renderer", typeObject);
	addFactory<MinSG::ThesisJonas::Renderer, E_Renderer>();

	declareConstant(typeObject, "NO_TRAVERSAL", EScript::Number::create(MinSG::ThesisJonas::Renderer::NO_TRAVERSAL));
	declareConstant(typeObject, "INSIDE_BB", EScript::Number::create(MinSG::ThesisJonas::Renderer::INSIDE_BB));
	declareConstant(typeObject, "FIXED_PROJECTED_SIZE", EScript::Number::create(MinSG::ThesisJonas::Renderer::FIXED_PROJECTED_SIZE));
	declareConstant(typeObject, "FIXED_PROJECTED_SIZE_PREPROCESSED_DPC", EScript::Number::create(MinSG::ThesisJonas::Renderer::FIXED_PROJECTED_SIZE_PREPROCESSED_DPC));

	//! [ESF] Void Renderer.addRendererToNode(Node)
	ES_FUN(typeObject, "addRendererToNode", 1, 1,
				 (MinSG::ThesisJonas::Renderer::addRendererToNode(EScript::assertType<E_Node>(rt, parameter[0])->ref().get()), EScript::Void::get()))

	 //! [ESMF] Number Renderer.getRenderTriangles()
	ESMF_DECLARE(typeObject, const E_Renderer, "getRenderTriangles", 0, 0,
				 EScript::Bool::create((**self)->getRenderTriangles()))

	//! [ESMF] Void Renderer.setRenderTriangles(Bool)
	ESMF_DECLARE(typeObject, E_Renderer, "setRenderTriangles", 1, 1,
				 ((**self)->setRenderTriangles(EScript::assertType<EScript::Bool>(runtime, parameter[0])->toBool()), EScript::Void::get()))

	//! [ESMF] Number Renderer.getRenderPoints()
	ESMF_DECLARE(typeObject, const E_Renderer, "getRenderPoints", 0, 0,
				 EScript::Bool::create((**self)->getRenderPoints()))

	//! [ESMF] Void Renderer.setRenderPoints(Bool)
	ESMF_DECLARE(typeObject, E_Renderer, "setRenderPoints", 1, 1,
				 ((**self)->setRenderPoints(EScript::assertType<EScript::Bool>(runtime, parameter[0])->toBool()), EScript::Void::get()))

	//! [ESMF] Number Renderer.getRenderOriginal()
	ESMF_DECLARE(typeObject, const E_Renderer, "getRenderOriginal", 0, 0,
				 EScript::Bool::create((**self)->getRenderOriginal()))

	//! [ESMF] Void Renderer.setRenderOriginal(Bool)
	ESMF_DECLARE(typeObject, E_Renderer, "setRenderOriginal", 1, 1,
				 ((**self)->setRenderOriginal(EScript::assertType<EScript::Bool>(runtime, parameter[0])->toBool()), EScript::Void::get()))

	//! [ESMF] Number Renderer.getTraverseAlgorithm()
	ESMF_DECLARE(typeObject, const E_Renderer, "getTraverseAlgorithm", 0, 0,
				 EScript::Number::create((**self)->getTraverseAlgorithm()))

	//! [ESMF] Void Renderer.setTraverseAlgorithm(Number)
	ES_MFUNCTION_DECLARE(typeObject, E_Renderer, "setTraverseAlgorithm", 1, 1, {
		switch(parameter[0].to<uint32_t>(runtime)) {
			case MinSG::ThesisJonas::Renderer::NO_TRAVERSAL:
				(**self)->setTraverseAlgorithm(MinSG::ThesisJonas::Renderer::NO_TRAVERSAL);
				break;
			case MinSG::ThesisJonas::Renderer::FIXED_PROJECTED_SIZE:
				(**self)->setTraverseAlgorithm(MinSG::ThesisJonas::Renderer::FIXED_PROJECTED_SIZE);
				break;
			case MinSG::ThesisJonas::Renderer::FIXED_PROJECTED_SIZE_PREPROCESSED_DPC:
				(**self)->setTraverseAlgorithm(MinSG::ThesisJonas::Renderer::FIXED_PROJECTED_SIZE_PREPROCESSED_DPC);
				break;

			case MinSG::ThesisJonas::Renderer::INSIDE_BB:
			default:
				(**self)->setTraverseAlgorithm(MinSG::ThesisJonas::Renderer::INSIDE_BB);
				break;
		}
		return EScript::Void::get();
	})

	//! [ESMF] Number Renderer.getProjectedSize()
	ESMF_DECLARE(typeObject, const E_Renderer, "getProjectedSize", 0, 0,
				 EScript::Number::create((**self)->getProjectedSize()))

	//! [ESMF] Void Renderer.setProjectedSize(Number)
	ESMF_DECLARE(typeObject, E_Renderer, "setProjectedSize", 1, 1,
				 ((**self)->setProjectedSize(parameter[0].to<float>(runtime)), EScript::Void::get()))

	//! [ESMF] Void Renderer.setDynamicPrimitiveCount(Bool)
	ESMF_DECLARE(typeObject, E_Renderer, "setDynamicPrimitiveCount", 1, 1,
				 ((**self)->setDynamicPrimitiveCount(EScript::assertType<EScript::Bool>(runtime, parameter[0])->toBool()), EScript::Void::get()))

	//! [ESMF] Number Renderer.getDynamicPrimitiveCount()
	ESMF_DECLARE(typeObject, const E_Renderer, "getDynamicPrimitiveCount", 0, 0,
				 EScript::Bool::create((**self)->getDynamicPrimitiveCount()))

	//! [ESMF] Void Renderer.setFrustumCulling(Bool)
	ESMF_DECLARE(typeObject, E_Renderer, "setFrustumCulling", 1, 1,
				 ((**self)->setFrustumCulling(EScript::assertType<EScript::Bool>(runtime, parameter[0])->toBool()), EScript::Void::get()))

	//! [ESMF] Number Renderer.getFrustumCulling()
	ESMF_DECLARE(typeObject, const E_Renderer, "getFrustumCulling", 0, 0,
				 EScript::Bool::create((**self)->getFrustumCulling()))

	//! [ESMF] Void Renderer.setUseTotalBudget(Bool)
	ESMF_DECLARE(typeObject, E_Renderer, "setUseTotalBudget", 1, 1,
				 ((**self)->setUseTotalBudget(EScript::assertType<EScript::Bool>(runtime, parameter[0])->toBool()), EScript::Void::get()))

	//! [ESMF] Number Renderer.getUseTotalBudget()
	ESMF_DECLARE(typeObject, const E_Renderer, "getUseTotalBudget", 0, 0,
				 EScript::Bool::create((**self)->getUseTotalBudget()))

	//! [ESMF] Void Renderer.setRenderSMwhenTBtooLow(Bool)
	ESMF_DECLARE(typeObject, E_Renderer, "setRenderSMwhenTBtooLow", 1, 1,
				 ((**self)->setRenderSMwhenTBtooLow(EScript::assertType<EScript::Bool>(runtime, parameter[0])->toBool()), EScript::Void::get()))

	//! [ESMF] Number Renderer.getRenderSMwhenTBtooLow()
	ESMF_DECLARE(typeObject, const E_Renderer, "getRenderSMwhenTBtooLow", 0, 0,
				 EScript::Bool::create((**self)->getRenderSMwhenTBtooLow()))

	//! [ESMF] Number Renderer.getTriangleBudget()
	ESMF_DECLARE(typeObject, const E_Renderer, "getTriangleBudget", 0, 0,
				 EScript::Number::create((**self)->getTriangleBudget()))

	//! [ESMF] Void Renderer.setTriangleBudget(Number)
	ESMF_DECLARE(typeObject, E_Renderer, "setTriangleBudget", 1, 1,
				 ((**self)->setTriangleBudget(parameter[0].to<double>(runtime)), EScript::Void::get()))

	 //! [ESMF] Number Renderer.getTriangleBudgetDistributionType()
	ESMF_DECLARE(typeObject, const E_Renderer, "getTriangleBudgetDistributionType", 0, 0,
				 EScript::Number::create((**self)->getTriangleBudgetDistributionType()))

	//! [ESMF] Void Renderer.setTriangleBudgetDistributionType(Number)
	ES_MFUNCTION_DECLARE(typeObject, E_Renderer, "setTriangleBudgetDistributionType", 1, 1, {
		switch(parameter[0].to<uint32_t>(runtime)) {
			case MinSG::BudgetAnnotationState::DISTRIBUTE_EVEN:
				(**self)->setTriangleBudgetDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_EVEN);
				break;
			case MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE:
				(**self)->setTriangleBudgetDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE);
				break;
			case MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT:
				(**self)->setTriangleBudgetDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT);
				break;
			case MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT_ITERATIVE:
				(**self)->setTriangleBudgetDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_PROJECTED_SIZE_AND_PRIMITIVE_COUNT_ITERATIVE);
				break;
			default:
				(**self)->setTriangleBudgetDistributionType(MinSG::BudgetAnnotationState::DISTRIBUTE_EVEN);
				break;
		}
		return EScript::Void::get();
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
