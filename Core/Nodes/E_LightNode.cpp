/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_LightNode.h"

#include "../../ELibMinSG.h"
#include "../E_FrameContext.h"
#include <E_Util/Graphics/E_Color.h>
#include <EScript/EScript.h>

using namespace MinSG;

namespace E_MinSG {

//! (static)
EScript::Type * E_LightNode::getTypeObject() {
	// E_LightNode ---|> E_Node ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_Node::getTypeObject());
	return typeObject.get();
}

// -----

//! (static)
void E_LightNode::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::LightNode,E_LightNode>();

	declareConstant(typeObject, "SPOT", 		static_cast<uint32_t>(Rendering::LightParameters::SPOT));
	declareConstant(typeObject, "POINT", 		static_cast<uint32_t>(Rendering::LightParameters::POINT));
	declareConstant(typeObject, "DIRECTIONAL", 	static_cast<uint32_t>(Rendering::LightParameters::DIRECTIONAL));

	//! [ESMF] new LightNode( [type] )
	ES_CONSTRUCTOR(typeObject,0,1,{
		if(parameter.count()==0)
			return EScript::create(new LightNode);
		else
            return EScript::create(new LightNode(static_cast<Rendering::LightParameters::lightType_t>(parameter[0].to<int>(rt))));
	})

    //! [ESMF] self AbstractLightNode.switchOn(FrameContext)
    ES_MFUN(typeObject,LightNode, "switchOn", 1,1, 	(thisObj->switchOn(parameter[0].to<MinSG::FrameContext&>(rt)),thisEObj))

    //! [ESMF] self AbstractLightNode.switchOff(FrameContext)
    ES_MFUN(typeObject,LightNode, "switchOff", 1,1,	(thisObj->switchOff(parameter[0].to<MinSG::FrameContext&>(rt)),thisEObj))

	//! [ESMF] Util.Color4f LightNode.getAmbientLightColor()
	ES_MFUN(typeObject,const LightNode,"getAmbientLightColor",0,0,		EScript::create(thisObj->getAmbientLightColor()))

	//! [ESMF] Number LightNode.getConstantAttenuation()
	ES_MFUN(typeObject,const LightNode,"getConstantAttenuation", 0, 0,	thisObj->getConstantAttenuation())

	//!	[ESMF] Number MinSG.LightNode.getCutoff()
	ES_MFUN(typeObject,const LightNode,"getCutoff", 0, 0,				thisObj->getCutoff())

	//! [ESMF] Util.Color4f LightNode.getDiffuseLightColor()
	ES_MFUN(typeObject,const LightNode,"getDiffuseLightColor",0,0,		EScript::create(thisObj->getDiffuseLightColor()))

	//!	[ESMF] Number MinSG.LightNode.getExponent()
	ES_MFUN(typeObject,const LightNode,"getExponent", 0, 0,				thisObj->getExponent())

	//! [ESMF] Number AbstractLightNode.getLightType()
	ES_MFUN(typeObject,const LightNode, "getLightType", 0, 0,			thisObj->getType())

	//! [ESMF] Number LightNode.getLinearAttenuation()
	ES_MFUN(typeObject,const LightNode,"getLinearAttenuation", 0, 0,	thisObj->getLinearAttenuation())

	//! [ESMF] Number LightNode.getQuadraticAttenuation()
	ES_MFUN(typeObject,const LightNode,"getQuadraticAttenuation", 0, 0,	thisObj->getQuadraticAttenuation())

	//! [ESMF] Util.Color4f LightNode.getSpecularLightColor()
	ES_MFUN(typeObject,const LightNode,"getSpecularLightColor",0,0,		EScript::create(thisObj->getSpecularLightColor()))

	//! [ESMF] Bool LightNode.isSwitchedOn()
	ES_MFUN(typeObject,const LightNode,"isSwitchedOn",0,0,				thisObj->isSwitchedOn())

	//! [ESMF] self LightNode.setAmbientLightColor(Util.Color4)
	ES_MFUN(typeObject,LightNode,"setAmbientLightColor",1,1,			(thisObj->setAmbientLightColor(parameter[0].to<Util::Color4f>(rt)),thisEObj))

	//! [ESMF] self LightNode.setConstantAttenuation(Number value)
	ES_MFUN(typeObject,LightNode,"setConstantAttenuation", 1, 1,		(thisObj->setConstantAttenuation(parameter[0].toFloat()),thisEObj))

	//! [ESMF] self AbstractLightNode.setCutoff( float co )
	ES_MFUN(typeObject,LightNode,"setCutoff",1,1,						(thisObj->setCutoff(parameter[0].toFloat()),thisEObj))

	//! [ESMF] self LightNode.setDiffuseLightColor(Util.Color4)
	ES_MFUN(typeObject,LightNode,"setDiffuseLightColor",1,1,			(thisObj->setDiffuseLightColor(parameter[0].to<Util::Color4f>(rt)),thisEObj))

	//! [ESMF] self AbstractLightNode.setExponent( float ex )
	ES_MFUN(typeObject,LightNode,"setExponent",1,1,						(thisObj->setExponent(parameter[0].toFloat()),thisEObj))

	//! [ESMF] self AbstractLightNode.setLightType(Number type)
	ES_MFUN(typeObject,LightNode, "setLightType", 1, 1,					(thisObj->setLightType(static_cast<Rendering::LightParameters::lightType_t>(parameter[0].toInt())),thisEObj))

	//! [ESMF] self LightNode.setLinearAttenuation(Number value)
	ES_MFUN(typeObject,LightNode,"setLinearAttenuation", 1, 1,			(thisObj->setLinearAttenuation(parameter[0].toFloat()),thisEObj))

	//! [ESMF] self LightNode.setQuadraticAttenuation(Number value)
	ES_MFUN(typeObject,LightNode,"setQuadraticAttenuation",1,1,			(thisObj->setQuadraticAttenuation(parameter[0].toFloat()),thisEObj))

	//! [ESMF] self LightNode.setSpecularLightColor(Util.Color4)
	ES_MFUN(typeObject,LightNode,"setSpecularLightColor",1,1,			(thisObj->setSpecularLightColor(parameter[0].to<Util::Color4f>(rt)),thisEObj))

}

}
