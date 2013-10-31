/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_ValuatedRegionNode.h"

#include "../../SceneManagement/E_SceneManager.h"
#include <EScript/EScript.h>
#include <E_Geometry/E_Box.h>
#include <E_Geometry/E_Vec3.h>
#include <E_Util/E_Utils.h>

namespace E_MinSG {

EScript::Type* E_ValuatedRegionNode::typeObject=nullptr;


//! initMembers
void E_ValuatedRegionNode::init(EScript::Namespace & lib) {
	// [E_ValuatedRegionNode] ---|> [E_ListNode] ---|> [E_GroupNode] ---|> [E_Node]
	typeObject = new EScript::Type(E_ListNode::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::ValuatedRegionNode,E_ValuatedRegionNode>();

	using namespace MinSG;

	//! [ESMF] new MinSG.ValuatedRegionNode(Box,resX,resY,resZ)	
	ES_CTOR(typeObject,4,4,EScript::create(
				new MinSG::ValuatedRegionNode(parameter[0].to<const Geometry::Box&>(rt),
							Geometry::Vec3i(parameter[1].toUInt(),parameter[2].toUInt(),parameter[3].toUInt()))))

	//! [ESMF] self ValuatedRegionNode.addColor(r, g, b, a)
	ES_MFUN(typeObject,ValuatedRegionNode,"addColor",4,4,
				(thisObj->addColor(parameter[0].toFloat(), parameter[1].toFloat(), parameter[2].toFloat(), parameter[3].toFloat()),thisEObj))

	//! [ESMF] self ValuatedRegionNode.clearColors()
	ES_MFUN(typeObject,ValuatedRegionNode,"clearColors",0,0,(thisObj->clearColors(),thisEObj))

	//! [ESMF] Number ValuatedRegionNode.getHeightScale()
	ES_MFUN(typeObject,ValuatedRegionNode,"getHeightScale",0,0,thisObj->getHeightScale())

	//! [ESMF] Object ValuatedRegionNode.getNodeAtPosition(Vec3)
	ES_MFUN(typeObject,ValuatedRegionNode,"getNodeAtPosition",1,1,
					EScript::create(thisObj->getNodeAtPosition(parameter[0].to<const Geometry::Vec3&>(rt))))

	//! [ESMF] Vec3 ValuatedRegionNode.getPosition(cellX,cellY,cellZ)
	ES_MFUN(typeObject,ValuatedRegionNode,"getPosition",3,3,new E_Geometry::E_Vec3( thisObj->
			getPosition(parameter[0].toFloat(),parameter[1].toFloat(),parameter[2].toFloat())))

	//! [ESMF] Object ValuatedRegionNode.getValueAtPosition(Vec3)
	ES_MFUN(typeObject,ValuatedRegionNode,"getValueAtPosition",1,1,
					E_Util::E_Utils::convertGenericAttributeToEScriptObject(thisObj->getValueAtPosition(parameter[0].to<const Geometry::Vec3&>(rt))))

	//! [ESMF] number ValuatedRegionNode.getValueAsNumber()
	ES_MFUN(typeObject,ValuatedRegionNode,"getValueAsNumber",0,0,thisObj->getValueAsNumber())
	
	//! [ESMF] Number ValuatedRegionNode.getXResolution()
	ES_MFUN(typeObject,ValuatedRegionNode,"getXResolution",0,0,static_cast<uint32_t>(thisObj->getXResolution()))
	
	//! [ESMF] self ValuatedRegionNode.getYResolution()
	ES_MFUN(typeObject,ValuatedRegionNode,"getYResolution",0,0,static_cast<uint32_t>(thisObj->getYResolution()))

	//! [ESMF] Number ValuatedRegionNode.getZResolution()
	ES_MFUN(typeObject,ValuatedRegionNode,"getZResolution",0,0,static_cast<uint32_t>(thisObj->getZResolution()))

	//! [ESMF] Int ValuatedRegionNode.getSize()
	ES_MFUN(typeObject,ValuatedRegionNode,"getSize",0,0,static_cast<uint32_t>(thisObj->getSize()))

	//! [ESMF] Int ValuatedRegionNode.getDiameter()
	ES_MFUN(typeObject,ValuatedRegionNode,"getDiameter",0,0,
		sqrt(static_cast<double>(thisObj->getXResolution()*thisObj->getXResolution() +
								 thisObj->getYResolution()*thisObj->getYResolution() + 
								 thisObj->getZResolution()*thisObj->getZResolution())))

	//! [ESMF] Object ValuatedRegionNode.getValue()
	ES_MFUN(typeObject,ValuatedRegionNode,"getValue",0,0,
				E_Util::E_Utils::convertGenericAttributeToEScriptObject(thisObj->getValue()))

	//! [ESMF] bool ValuatedRegionNode.isLeaf()
	ES_MFUN(typeObject,ValuatedRegionNode,"isLeaf",0,0,thisObj->isLeaf())

	//! [ESMF] self ValuatedRegionNode.setValue(Object Value)
	ES_MFUN(typeObject,E_ValuatedRegionNode,"setValue",1,1,(thisObj->setValue(parameter[0].get()),thisEObj))

	//! [ESMF] [Number*] ValuatedRegionNode.getValueAsNumbers()
	ES_MFUNCTION(typeObject,ValuatedRegionNode,"getValueAsNumbers",0,0,{
		EScript::Array * a = EScript::Array::create();
		std::list<float> numbers;
		thisObj->getValueAsNumbers(numbers);
		for(std::list<float>::const_iterator it=numbers.begin();it!=numbers.end();++it)
			a->pushBack(EScript::create(*it));
		return a;
	})

	//! [ESMF] self ValuatedRegionNode.setHeightScale(Number Value)
	ES_MFUN(typeObject,ValuatedRegionNode,"setHeightScale",1,1,(thisObj->setHeightScale(parameter[0].toFloat()),thisEObj))

	//! [ESMF] self ValuatedRegionNode.splitUp(Number regionsX, Number regionsY, Number regionsZ)
	ES_MFUN(typeObject,ValuatedRegionNode, "splitUp", 3, 3,
				 (thisObj->splitUp(parameter[0].toUInt(), parameter[1].toUInt(), parameter[2].toUInt()), thisEObj));

	declareConstant(typeObject, "NO_BLENDING", static_cast<uint32_t>(MinSG::ValuatedRegionNode::NO_BLENDING));
}

// ------------------------------------------------------------

//! [ctor]
E_ValuatedRegionNode::E_ValuatedRegionNode(MinSG::ValuatedRegionNode * gNode,EScript::Type * type):
	E_ListNode(gNode,type?type:typeObject){
}

//! [dtor]
E_ValuatedRegionNode::~E_ValuatedRegionNode(){
}

EScript::Object * E_ValuatedRegionNode::getValue()const{
	return E_Util::E_Utils::convertGenericAttributeToEScriptObject((**this)->getValue());
}

void E_ValuatedRegionNode::setValue(Object * attr){
	(**this)->setValue(E_Util::E_Utils::convertEScriptObjectToGenericAttribute(attr));
}

EScript::Object * E_ValuatedRegionNode::getValueAtPosition(const Geometry::Vec3 & absPos){
	return E_Util::E_Utils::convertGenericAttributeToEScriptObject((**this)->getValueAtPosition(absPos));
}

}
