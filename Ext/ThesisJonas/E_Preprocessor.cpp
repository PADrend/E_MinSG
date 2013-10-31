/*
	This file is part of the MinSG library extension ThesisJonas.
	Copyright (C) 2013 Jonas Knoll

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_THESISJONAS

#include "E_Preprocessor.h"
#include <MinSG/Ext/ThesisJonas/Preprocessor.h>

#include "../../Core/Nodes/E_GeometryNode.h"
#include "../../Core/Nodes/E_Node.h"
#include "../../Core/E_FrameContext.h"
#include "../../SceneManagement/E_SceneManager.h"
#include "../../../E_Rendering/Mesh/E_Mesh.h"
#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <E_Util/Graphics/E_PixelAccessor.h>

using namespace MinSG::ThesisJonas;

namespace E_MinSG {
namespace ThesisJonas {
namespace E_Preprocessor {

void init(EScript::Namespace & lib) {
	declareConstant(&lib, "PREPROCESSING_NODE_ID", EScript::String::create(MinSG::ThesisJonas::PREPROCESSING_NODE_ID.toString()));
	declareConstant(&lib, "SAMPLING_MESH_ID", EScript::String::create(MinSG::ThesisJonas::SAMPLING_MESH_ID.toString()));

	declareConstant(&lib, "ALG_MID_POINT_DIST", EScript::Number::create(MinSG::ThesisJonas::ALG_MID_POINT_DIST));
	declareConstant(&lib, "ALG_MID_POINT_DIST_SIZE_WEIGHT", EScript::Number::create(MinSG::ThesisJonas::ALG_MID_POINT_DIST_SIZE_WEIGHT));
	declareConstant(&lib, "ALG_THESIS_FACTORS", EScript::Number::create(MinSG::ThesisJonas::ALG_THESIS_FACTORS));
	declareConstant(&lib, "ALG_THESIS_WEIGHTS", EScript::Number::create(MinSG::ThesisJonas::ALG_THESIS_WEIGHTS));
	declareConstant(&lib, "ALG_SIZE", EScript::Number::create(MinSG::ThesisJonas::ALG_SIZE));
	declareConstant(&lib, "ALG_RANDOM", EScript::Number::create(MinSG::ThesisJonas::ALG_RANDOM));

	//! [ESF] Void ThesisJonas.approximateNodeFromImage(Node, PixelAccessor, parameters)
	ES_FUNCTION2(&lib, "approximateNodeFromImage", 3, 3, {
		MinSG::Node * node = **EScript::assertType<E_Node>(rt, parameter[0]);
//		Util::PixelAccessor * pix = (*EScript::assertType<E_Util::E_PixelAccessor>(rt,parameter[1])).ref().get();

		// copy textures
		EScript::Array *a = EScript::assertType<EScript::Array>(rt, parameter[1]);
		std::vector<Util::PixelAccessor *> pix;
		for(unsigned int i=0; i<a->size(); ++i) {
			pix.emplace_back((*EScript::assertType<E_Util::E_PixelAccessor>(rt,a->at(i))).ref().get());
		}

		// copy parameter values
		EScript::Array *b = EScript::assertType<EScript::Array>(rt, parameter[2]);
		std::vector<double> parameters;
		for(unsigned int i=0; i<b->size(); ++i) {
			parameters.emplace_back(b->at(i)->toDouble());
		}

		approximateNodeFromImage(node, pix, parameters);
		return EScript::Void::get();
	})

	//! [ESF] Void ThesisJonas.randomizeTriangleOrder(GeoNode)
	ES_FUNCTION2(&lib, "randomizeTriangleOrder", 1, 1, {
		MinSG::GeometryNode * geoNode = **EScript::assertType<E_GeometryNode>(rt, parameter[0]);

		randomizeTriangleOrder(geoNode);
		return EScript::Void::get();
	})

	//! [ESF] Void ThesisJonas.printHistoHistogramOfNode(Node)
	ES_FUNCTION2(&lib, "printHistoHistogramOfNode", 1, 1, {
		MinSG::Node * n = **EScript::assertType<E_Node>(rt, parameter[0]);

		printHistoHistogramOfNode(n);
		return EScript::Void::get();
	})

	//! [ESF] Void ThesisJonas.printAndResetTimers()
	ES_FUN(&lib, "printAndResetTimers", 0, 0,
				 (MinSG::ThesisJonas::printAndResetTimers(), EScript::Void::get()))


	//! [ESF] Void ThesisJonas.initPreprocessing(Node, parameters)
	ES_FUNCTION2(&lib, "initPreprocessing", 2, 2, {
		MinSG::Node * node = **EScript::assertType<E_Node>(rt, parameter[0]);

		// copy parameter values
		EScript::Array *b = EScript::assertType<EScript::Array>(rt, parameter[1]);
		std::vector<double> parameters;
		for(unsigned int i=0; i<b->size(); ++i) {
			parameters.emplace_back(b->at(i)->toDouble());
		}

		initPreprocessing(node, parameters);
		return EScript::Void::get();
	})

	 //! [ESF] Void ThesisJonas.extractTrianglesFromNewDirection(Image)
	ES_FUNCTION2(&lib, "extractTrianglesFromNewDirection", 1, 1, {
		Util::PixelAccessor * img = (*EScript::assertType<E_Util::E_PixelAccessor>(rt,parameter[0])).ref().get();

		MinSG::ThesisJonas::extractTrianglesFromNewDirection(img);
		return EScript::Void::get();
	})

	//! [ESF] Void ThesisJonas.finishPreprocessing()
	ES_FUN(&lib, "finishPreprocessing", 0, 0,
				 (MinSG::ThesisJonas::finishPreprocessing(), EScript::Void::get()))

}

}
}
}

#endif /* MINSG_EXT_THESISJONAS */
