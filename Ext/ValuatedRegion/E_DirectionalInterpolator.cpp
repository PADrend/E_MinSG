/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_DirectionalInterpolator.h"

#include "E_ValuatedRegionNode.h"
#include "../../Core/Nodes/E_CameraNode.h"
#include <E_Rendering/E_RenderingContext.h>
#include <E_Util/E_Utils.h>
#include <EScript/EScript.h>
#include <memory>

using namespace EScript;
using namespace MinSG;

namespace E_MinSG {

Type* E_DirectionalInterpolator::typeObject=nullptr;

//! initMembers
void E_DirectionalInterpolator::init(EScript::Namespace & lib) {
	// E_DirectionalInterpolator ---|> [Object]
	typeObject = new EScript::Type(Object::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] DirectionalInterpolation new DirectionalInterpolation()
	ES_CTOR(typeObject,0,0,new E_DirectionalInterpolator )
	
	//! [ESMF] mixed new calculateValue(RenderingContext, ValuatedRegionNode,camera[,measurementApertureAngle_deg=90])
	ES_MFUNCTION(typeObject, DirectionalInterpolator,"calculateValue",3,4,{
		std::unique_ptr<Util::GenericAttribute> result(thisObj->calculateValue( 
															parameter[0].to<Rendering::RenderingContext&>(rt), 
															parameter[1].to<ValuatedRegionNode*>(rt),
															parameter[2].to<CameraNode*>(rt)->getFrustum(),	
															parameter[3].toFloat(90.0)));
		return E_Util::E_Utils::convertGenericAttributeToEScriptObject(result.get());
	})
	
}

//---

}
