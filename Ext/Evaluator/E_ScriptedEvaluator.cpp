/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_EVALUATORS

#include "E_ScriptedEvaluator.h"

#include "../../ELibMinSG.h"
#include "../../Core/Nodes/E_Node.h"
#include "../../Core/E_FrameContext.h"

#include <E_Util/E_Utils.h>
#include <E_Geometry/E_Rect.h>
#include <EScript/EScript.h>

using namespace MinSG::Evaluators;
using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

Type* E_ScriptedEvaluator::typeObject=nullptr;

/**
 * initMembers
 */
void E_ScriptedEvaluator::init(EScript::Namespace & lib) {
	// E_ScriptedEvaluator ----|> E_Evaluator ----|> Object
	typeObject = new EScript::Type(E_Evaluator::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	typeObject->allowUserInheritance(true);


	//!  Evaluator new ScriptedEvaluator([mode=SINGLE_VALUE])
	ES_CTOR(typeObject,0,1,
		new E_ScriptedEvaluator(rt,parameter.count()>0?static_cast<Evaluator::DirectionMode>(parameter[0].toInt()):Evaluator::SINGLE_VALUE,thisType))

	//! [ESMF] void Evaluator.beginMeasure()
	ES_FUN(typeObject,"beginMeasure",0,0,EScript::create(nullptr))
	
	//! [ESMF] void Evaluator.endMeasure()
	ES_FUN(typeObject,"endMeasure",0,0,EScript::create(nullptr))
	
	//! [ESMF] void Evaluator.getResults()
	ES_FUN(typeObject,"getResults",0,0,EScript::create(nullptr))
	
	//! [ESMF] void Evaluator.measure()
	ES_FUN(typeObject,"measure",0,0,EScript::create(nullptr))

}

//---

/*! ---|> Evaluator */
void ScriptedEvaluator::beginMeasure() {
	static const EScript::StringId fnId("beginMeasure");
	EScript::ObjRef result=EScript::callMemberFunction(runtime,eScriptedEvaluator,fnId,ParameterValues());
}

/*! ---|> Evaluator */
void ScriptedEvaluator::measure(FrameContext & context, Node & node, const Geometry::Rect & r) {
	static const EScript::StringId fnId("measure");
	EScript::ObjRef result=EScript::callMemberFunction(runtime,eScriptedEvaluator,fnId,
			ParameterValues( EScript::create(context),EScript::create(&node),EScript::create(r) ));
}

/*! ---|> Evaluator */
void ScriptedEvaluator::endMeasure(FrameContext & /*context*/) {
	static const EScript::StringId fnId("endMeasure");
	EScript::ObjRef result=EScript::callMemberFunction(runtime,eScriptedEvaluator,fnId,ParameterValues());
}

/*! ---|> Evaluator */
const Util::GenericAttributeList * ScriptedEvaluator::getResults() {
	static const EScript::StringId fnId("getResults");
	EScript::ObjRef result=EScript::callMemberFunction(runtime,eScriptedEvaluator,fnId,ParameterValues());
	return dynamic_cast<Util::GenericAttributeList *>(E_Util::E_Utils::convertEScriptObjectToGenericAttribute(result));
}

}

#endif /* MINSG_EXT_EVALUATORS */
