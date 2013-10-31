/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/


#ifdef MINSG_EXT_MULTIALGORENDERING

#include "E_MultiAlgoGroupNode.h"

#include "../../Core/States/E_GroupState.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

using MinSG::MAR::MultiAlgoGroupNode;

namespace E_MinSG {
namespace E_MAR {

EScript::Type * E_MultiAlgoGroupNode::getTypeObject() {
	// E_MAR::E_MultiAlgoGroupNode ---|> E_GroupNode ---|> E_Node ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_GroupNode::getTypeObject());
	return typeObject.get();
}

void E_MultiAlgoGroupNode::init(EScript::Namespace & lib) {
	
	using MinSG::MAR::MultiAlgoGroupNode;

	declareConstant(&lib,getClassName(),getTypeObject());
	
	addFactory<MultiAlgoGroupNode,E_MultiAlgoGroupNode>();

	declareConstant(getTypeObject(),"CHCpp",EScript::create(MultiAlgoGroupNode::CHCpp));
	declareConstant(getTypeObject(),"CHCppAggressive",EScript::create(MultiAlgoGroupNode::CHCppAggressive));
	declareConstant(getTypeObject(),"ColorCubes",EScript::create(MultiAlgoGroupNode::ColorCubes));
	declareConstant(getTypeObject(),"SkipRendering",EScript::create(MultiAlgoGroupNode::SkipRendering));
	declareConstant(getTypeObject(),"Auto",EScript::create(MultiAlgoGroupNode::Auto));
	declareConstant(getTypeObject(),"BruteForce",EScript::create(MultiAlgoGroupNode::BruteForce));
	declareConstant(getTypeObject(),"BlueSurfels",EScript::create(MultiAlgoGroupNode::BlueSurfels));
	declareConstant(getTypeObject(),"ForceSurfels",EScript::create(MultiAlgoGroupNode::ForceSurfels));
	declareConstant(getTypeObject(),"SphericalSampling",EScript::create(MultiAlgoGroupNode::SphericalSampling));
	declareConstant(getTypeObject(),"ClassicLOD",EScript::create(MultiAlgoGroupNode::ClassicLOD));

	ES_CTOR(getTypeObject(), 0, 0, EScript::create(new MultiAlgoGroupNode()))

	ES_FUN(getTypeObject(), "setHighlightIntensity", 1, 1, (MultiAlgoGroupNode::setHighlightIntensity(parameter[0].to<float>(rt)), EScript::create(nullptr)))
	
	ES_FUN(getTypeObject(), "getHighlightIntensity", 0, 0, MultiAlgoGroupNode::getHighlightIntensity())

	ES_FUN(getTypeObject(), "algoIdToString", 1, 1, MultiAlgoGroupNode::algoIdToString(parameter[0].to<MultiAlgoGroupNode::AlgoId>(rt)))

	ES_FUN(getTypeObject(),  "initAlgorithm", 1, 1, (MultiAlgoGroupNode::initAlgorithm(parameter[0].to<MultiAlgoGroupNode::AlgoId>(rt)),EScript::create(nullptr)))

	ES_MFUN(getTypeObject(), MultiAlgoGroupNode, "setAlgorithm", 1, 1, (thisObj->setAlgorithm(parameter[0].to<MultiAlgoGroupNode::AlgoId>(rt)), thisEObj))

	ES_MFUN(getTypeObject(), const MultiAlgoGroupNode, "getAlgorithm", 0, 0, EScript::create(thisObj->getAlgorithm()))

	ES_MFUN(getTypeObject(), MultiAlgoGroupNode, "initNode", 0, 0, (thisObj->initNode(), thisEObj))
}

}
}
namespace EScript{
Object * create(MultiAlgoGroupNode::AlgoId obj) {
        return EScript::create(static_cast<MultiAlgoGroupNode::AlgoId_t>(obj));
}
}

#endif // MINSG_EXT_MULTIALGORENDERING
