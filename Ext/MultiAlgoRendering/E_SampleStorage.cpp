/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_MULTIALGORENDERING

#include "E_SampleStorage.h"

#include "E_SampleRegion.h"
#include "E_SampleContext.h"
#include "E_MultiAlgoGroupNode.h"

#include <E_Geometry/E_Box.h>

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_MinSG{
	namespace E_MAR{
		
		using namespace MinSG::MAR;

//! SampleStorage ---------------------------------------------------------------------------------------

//! (static)
EScript::Type * E_SampleStorage::getTypeObject() {
	// E_SampleStorage ---|> [ReferenceObject]
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_SampleStorage::init(EScript::Namespace & lib) {
	
	declareConstant(&lib,getClassName(),getTypeObject());

	ES_MFUN( getTypeObject(), SampleStorage, "addNode", 1, 1, (thisObj->addNode(parameter[0].to<MultiAlgoGroupNode*>(rt)), EScript::create(nullptr) ))

	ES_MFUN( getTypeObject(), SampleStorage, "addAlgorithm", 1, 1, (thisObj->addAlgorithm(parameter[0].to<MultiAlgoGroupNode::AlgoId>(rt)), EScript::create(nullptr) ))

	ES_MFUN( getTypeObject(), const SampleStorage, "getBounds", 0, 0, EScript::create(thisObj->getBounds()))
	
	ES_MFUN( getTypeObject(), const SampleStorage, "getNodes", 0, 0, EScript::Array::create(thisObj->getNodes()))
	
	ES_MFUN( getTypeObject(), const SampleStorage, "getAlgorithms", 0, 0, EScript::Array::create(thisObj->getAlgorithms()))
}

//! SampleResult ----------------------------------------------------------------------------------------

//! (static)
EScript::Type * E_SampleResult::getTypeObject() { 
	// E_SampleResult ---|> [ReferenceObject]
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_SampleResult::init(EScript::Namespace & lib) {
	
	declareConstant(&lib,getClassName(),getTypeObject());

	//! [ESF] new SampleResult(MultiAlgoGroupNode, MultiAlgoGroupNode.AlgoId, pixel, time, error)
	ES_CTOR(getTypeObject(),5,5,
		EScript::create(new SampleResult(
			parameter[0].to<MultiAlgoGroupNode*>(rt),
			parameter[1].to<MultiAlgoGroupNode::AlgoId>(rt),
			parameter[2].to<float>(rt), // pixel
			parameter[3].to<float>(rt), // time
			parameter[4].to<float>(rt)  // error
		))
	)
}

}}
#endif // MINSG_EXT_MULTIALGORENDERING
