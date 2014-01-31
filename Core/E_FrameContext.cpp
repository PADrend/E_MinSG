/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_FrameContext.h"
#include "Nodes/E_AbstractCameraNode.h"
#include "E_RenderParam.h"
#include "E_Statistics.h"
#include "../ELibMinSG.h"
#include <EScript/EScript.h>
#include <E_Geometry/E_Box.h>
#include <E_Geometry/E_Vec3.h>
#include <E_Geometry/E_Vec4.h>
#include <E_Geometry/E_Matrix4x4.h>
#include <E_Geometry/E_Rect.h>
#include <E_Util/Graphics/E_Color.h>
#include <E_Rendering/E_RenderingContext.h>
#include <E_Rendering/Mesh/E_Mesh.h>
#include <E_Rendering/E_TextRenderer.h>

using namespace EScript;
using namespace E_Geometry;
using namespace MinSG;

namespace E_MinSG {

//! (static)
EScript::Type * E_FrameContext::getTypeObject() {
	// E_FrameContext ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_FrameContext::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	declareConstant(typeObject,"DEFAULT_CHANNEL",String::create(FrameContext::DEFAULT_CHANNEL.toString()));
	declareConstant(typeObject,"APPROXIMATION_CHANNEL",String::create(FrameContext::APPROXIMATION_CHANNEL.toString()));
	
	declareConstant(typeObject,"PASS_ON",Bool::create(static_cast<bool>(NodeRendererResult::PASS_ON)));
	declareConstant(typeObject,"NODE_HANDLED",Bool::create(static_cast<bool>(NodeRendererResult::NODE_HANDLED)));

	//! [ESMF] new MinSG.FrameContext()
	ES_CTOR(typeObject,0,0,EScript::create( new FrameContext ))

	//! [ESMF] Statistics MinSG.FrameContext.getStatistics( )
	ES_MFUN(typeObject, FrameContext, "getStatistics", 0, 0, new E_Statistics(thisObj->getStatistics()));

	//!	[ESMF] Vec3 MinSG.FrameContext.convertScreenPosToWorldPos(Vec3)
	ES_MFUNCTION(typeObject, FrameContext,"convertScreenPosToWorldPos",1,1,{
		Geometry::Vec3 v = parameter[0].to<Geometry::Vec3>(rt);
		return new E_Geometry::E_Vec3(thisObj->convertScreenPosToWorldPos(v));
	})

	//!	[ESMF] Vec3 MinSG.FrameContext.convertWorldPosToScreenPos(Vec3)
	ES_MFUNCTION(typeObject, FrameContext,"convertWorldPosToScreenPos",1,1,{
		Geometry::Vec3 v = parameter[0].to<Geometry::Vec3>(rt);
		return new E_Geometry::E_Vec3(thisObj->convertWorldPosToScreenPos(v));
	})

	//!	[ESMF] Rect MinSG.FrameContext.getProjectedRect(Node)
	ES_MFUNCTION(typeObject, FrameContext,"getProjectedRect",1,1,{
		Node * n = (parameter[0].to<MinSG::Node*>(rt));
		return EScript::create(thisObj->getProjectedRect(n));
	})

	//! [ESMF] thisEObj MinSG.FrameContext.displayMesh(Mesh)
	ES_MFUNCTION(typeObject, FrameContext,"displayMesh", 1, 3,{
				if(parameter.count() == 1)
					thisObj->displayMesh(
							parameter[0].to<Rendering::Mesh*>(rt));
				else{
					assertParamCount(rt,parameter,3,3);
					thisObj->displayMesh(
							parameter[0].to<Rendering::Mesh*>(rt),parameter[1].toUInt(),parameter[2].toUInt());
				}
				return thisEObj;
	})
	
	//!	[ESMF] bool MinSG.FrameContext.displayNode(Node[,RenderingParameters|flags])
	ES_MFUNCTION(typeObject, FrameContext,"displayNode",1,2,{
		E_RenderParam * eRp = parameter[1].toType<E_RenderParam>();
		if(eRp){
			return EScript::create(thisObj->displayNode((parameter[0].to<MinSG::Node*>(rt)),eRp->ref()));
		}else{
			return EScript::create(thisObj->displayNode((parameter[0].to<MinSG::Node*>(rt)),
										static_cast<MinSG::renderFlag_t>(parameter[1].toUInt(0))));
		}
	})

	//! [ESMF] thisEObj MinSG.FrameContext.beginFrame( [_frameNumber] )
	ES_MFUN(typeObject, FrameContext,"beginFrame",0,0,
				(thisObj->beginFrame(parameter[0].toInt(-1)),thisEObj))

	//! [ESMF] thisEObj MinSG.FrameContext.endFrame(bool waitForGlFinish=false)
	ES_MFUN(typeObject, FrameContext,"endFrame",0,1,
				(thisObj->endFrame(parameter[0].toBool(false)),thisEObj))

	//!	[ESF] Camera Context.getCamera()
	ES_MFUN(typeObject, FrameContext, "getCamera", 0, 0,
				 EScript::create(thisObj->getCamera()))

	//!	[ESF] Void Context.setCamera(AbstractCameraNode)
	ES_MFUN(typeObject, FrameContext, "setCamera", 1, 1,
                 (thisObj->setCamera(parameter[0].to<AbstractCameraNode*>(rt)), thisEObj))

	//!	[ESF] Void Context.pushCamera()
	ES_MFUN(typeObject, FrameContext, "pushCamera", 0, 0,
				 (thisObj->pushCamera(), thisEObj))

	//!	[ESF] Void Context.popCamera()
	ES_MFUN(typeObject, FrameContext, "popCamera", 0, 0,
				 (thisObj->popCamera(), thisEObj))

	//!	[ESF] Void Context.pushAndSetCamera(AbstractCameraNode)
	ES_MFUN(typeObject, FrameContext, "pushAndSetCamera", 1, 1,
                 (thisObj->pushAndSetCamera(parameter[0].to<AbstractCameraNode*>(rt)), thisEObj))

	//! [ESMF] Map FrameContext.getRenderingChannels()
	ES_MFUNCTION(typeObject, FrameContext, "getRenderingChannels", 0, 0, {
		const auto & channels = thisObj->getRenderingChannels();
		EScript::Map * channelMap = EScript::Map::create();
		for(const auto & keyValuePair : channels) {
			channelMap->setValue(EScript::String::create(keyValuePair.first.toString()), 
								 EScript::Number::create(keyValuePair.second.getElements().size()));
		}
		return channelMap;
	})

	//! RenderingContext FrameContext.getRenderingContext()
	ES_MFUN(typeObject, FrameContext, "getRenderingContext", 0, 0,
				new E_Rendering::E_RenderingContext(&(thisObj->getRenderingContext())))

	//! [ESMF] thisEObj FrameContext.showAnnotation(Node,text,[int yPosOffset,[Bool showRectangle, [Util.Color textColor,Util.Color bgColor] ]])
	ES_MFUNCTION(typeObject, FrameContext,"showAnnotation",2,6,{
		if(parameter.count()<5){
			thisObj->showAnnotation(parameter[0].to<MinSG::Node*>(rt),parameter[1].toString(),parameter[2].to<uint32_t>(rt,0),parameter[3].to<bool>(rt,true));
		}else{
			thisObj->showAnnotation(parameter[0].to<MinSG::Node*>(rt),parameter[1].toString(),parameter[2].to<uint32_t>(rt,0),parameter[3].to<bool>(rt,true),
									parameter[4].to<Util::Color4f>(rt),parameter[5].to<Util::Color4f>(rt));
		}
		return thisEObj;
	})

	//! [ESMF] Rendering.TextRenderer FrameContext.getTextRenderer()
	ES_MFUN(typeObject, FrameContext, "getTextRenderer", 0, 0,
				new E_Rendering::E_TextRenderer(thisObj->getTextRenderer()))

	//! [ESMF] thisEObj FrameContext.setTextRenderer(Rendering.TextRenderer)
	ES_MFUN(typeObject, FrameContext, "setTextRenderer", 1, 1,
                (thisObj->setTextRenderer(parameter[0].to<Rendering::TextRenderer&>(rt)), thisEObj))

	//! [ESMF] void FrameContext.setWorld...Vector(Vec3)
	ES_MFUN(typeObject, FrameContext, "setWorldUpVector", 1, 1, ( thisObj->setWorldUpVector(parameter[0].to<Geometry::Vec3>(rt)) , thisEObj ) )
	ES_MFUN(typeObject, FrameContext, "setWorldFrontVector", 1, 1, ( thisObj->setWorldFrontVector(parameter[0].to<Geometry::Vec3>(rt)) , thisEObj ) )
	ES_MFUN(typeObject, FrameContext, "setWorldRightVector", 1, 1, ( thisObj->setWorldRightVector(parameter[0].to<Geometry::Vec3>(rt)) , thisEObj ) )

	//! [ESMF] Vec3 FrameContext.getWorld...Vector()
	ES_MFUN(typeObject, FrameContext, "getWorldUpVector", 0, 0, EScript::create(thisObj->getWorldUpVector()) )
	ES_MFUN(typeObject, FrameContext, "getWorldFrontVector", 0, 0, EScript::create(thisObj->getWorldFrontVector()) )
	ES_MFUN(typeObject, FrameContext, "getWorldRightVector", 0, 0, EScript::create(thisObj->getWorldRightVector()) )
}

//---

//! (ctor)
E_FrameContext::E_FrameContext(MinSG::FrameContext * fctxt) : EScript::ReferenceObject<Util::Reference<MinSG::FrameContext>>(fctxt,getTypeObject()) {
}

//! (dtor)
E_FrameContext::~E_FrameContext() {
}

}
