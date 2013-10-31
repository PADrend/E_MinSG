/*
	This file is part of the E_MinSG library extension KeyFrameAnimation.
	Copyright (C) 2010-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2010-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2010 David Maicher
	Copyright (C) 2010-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_KeyFrameAnimationNode.h"

namespace E_MinSG {
using namespace EScript;

EScript::Type* E_KeyFrameAnimationNode::typeObject=nullptr;

//! initMembers	
void E_KeyFrameAnimationNode::init(EScript::Namespace & lib) {
	// MinSG.KeyFrameAnimationNode ----|> MinSG.GeometryNode  ----|> MinSG.Node ----|> Object
	typeObject = new EScript::Type(E_GeometryNode::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);

	using namespace MinSG;

	//! [ESF] Map MinSG.KeyFrameAnimationNode.getAnimationData() 	
	ES_MFUNCTION(typeObject,KeyFrameAnimationNode,"getAnimationData",0,0,{
		const auto animData = thisObj->getAnimationData();

		Map * animDataMap = Map::create();

		for(std::map<std::string, std::vector<int> >::const_iterator it = animData.begin(); it != animData.end(); ++it) {
			Array * animDataArray = Array::create();
			for(int i = 0; i < 3; i++) {
				animDataArray->pushBack(Number::create(it->second[i]));
			}
			animDataMap->setValue(String::create(it->first), animDataArray);
		}
		return animDataMap;
	})

	//! [ESF] String MinSG.KeyFrameAnimationNode.getActiveAnimation()	
	ES_MFUN(typeObject,KeyFrameAnimationNode,"getActiveAnimationName",0,0,thisObj->getActiveAnimationName())

	//! [ESF] Number MinSG.KeyFrameAnimationNode.getAnimationPosition()	
	ES_MFUN(typeObject,KeyFrameAnimationNode,"getAnimationPosition",0,0,EScript::Number::create(thisObj->getAnimationPosition()))

	//! [ESF] Number MinSG.KeyFrameAnimationNode.getSpeedFactor()	
	ES_MFUN(typeObject,KeyFrameAnimationNode,"getSpeedFactor",0,0,EScript::Number::create(thisObj->getSpeedFactor()))

	//! [ESF] Number MinSG.KeyFrameAnimationNode.getState()	
	ES_MFUN(typeObject,KeyFrameAnimationNode,"getState",0,0,EScript::Number::create(thisObj->getState()))

	//! [ESF] Bool MinSG.KeyFrameAnimationNode.hasBehaviour()	
	ES_MFUN(typeObject,KeyFrameAnimationNode,"hasBehaviour",0,0,thisObj->getBehaviour() != nullptr)

	//! [ESF] Bool MinSG.KeyFrameAnimationNode.setActiveAnimation(name)	
	ES_MFUN(typeObject,KeyFrameAnimationNode,"setActiveAnimation",1,1,thisObj->setActiveAnimation(parameter[0].toString()))

	//! [ESF] Bool MinSG.KeyFrameAnimationNode.setAnimationPosition(value)	
	ES_MFUN(typeObject,KeyFrameAnimationNode,"setAnimationPosition",1,1,thisObj->setAnimationPosition(parameter[0].toFloat()))

	//! [ESF] Bool MinSG.KeyFrameAnimationNode.setSpeedFactor(speedFactor)	
	ES_MFUN(typeObject,KeyFrameAnimationNode,"setSpeedFactor",1,1,thisObj->setSpeedFactor(parameter[0].toFloat()))

	//! [ESF] self MinSG.KeyFrameAnimationNode.setState(state)	
	ES_MFUN(typeObject,KeyFrameAnimationNode,"setState",1,1,(thisObj->setState(static_cast<short>(parameter[0].toFloat())),thisEObj))


	addFactory<MinSG::KeyFrameAnimationNode,E_KeyFrameAnimationNode>();
}

// ------------------------------------------------------------

//! (ctor)	
E_KeyFrameAnimationNode::E_KeyFrameAnimationNode(MinSG::KeyFrameAnimationNode * gNode,EScript::Type * type):
	E_GeometryNode(gNode,type?type:typeObject){
}

//! (dtor)	
E_KeyFrameAnimationNode::~E_KeyFrameAnimationNode(){
}

}
