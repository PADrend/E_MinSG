/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_GeometryNode.h"

#include <EScript/EScript.h>
#include "../../ELibMinSG.h"
#include <E_Rendering/Mesh/E_Mesh.h>

namespace E_MinSG {

//! (static)
EScript::Type * E_GeometryNode::getTypeObject() {
	// E_GeometryNode ---|> E_Node ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_Node::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_GeometryNode::init(EScript::Namespace & lib) {
	using namespace MinSG;
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::GeometryNode,E_GeometryNode>();

	//! [ESMF] GeometryNode new MinSG.GeometryNode([Mesh])
	ES_CTOR(typeObject, 0, 1, EScript::create(parameter.count() == 0?
			new GeometryNode :
			new GeometryNode(parameter[0].to<Rendering::Mesh*>(rt))))

	//! [ESMF] Number MinSG.GeometryNode.getGraphicsMemoryUsage()
	ES_MFUN(typeObject,const GeometryNode,"getGraphicsMemoryUsage",0,0, 
				 static_cast<uint32_t>(thisObj->getMesh()->getGraphicsMemoryUsage()))

	//! [ESMF] Number MinSG.GeometryNode.getMainMemoryUsage()
	ES_MFUN(typeObject,const GeometryNode,"getMainMemoryUsage",0,0, 
				 static_cast<uint32_t>(thisObj->getMesh()->getMainMemoryUsage()))

	//! [ESMF] Mesh MinSG.GeometryNode.getMesh()
	ES_MFUNCTION(typeObject,const GeometryNode,"getMesh",0,0,{
		Rendering::Mesh * m=thisObj->getMesh();
		if(m==nullptr)
			return  EScript::create(nullptr);
		return EScript::create(m);
	})

	//! [ESMF] Number MinSG.GeometryNode.getTriangleCount()
	ES_MFUN(typeObject,const GeometryNode,"getTriangleCount", 0, 0, thisObj->getTriangleCount())

	//! [ESMF] Number MinSG.GeometryNode.getVertexCount()
	ES_MFUN(typeObject,const GeometryNode,"getVertexCount", 0, 0, thisObj->getVertexCount())

	//! [ESMF] Bool MinSG.GeometryNode.hasMesh()
	ES_MFUN(typeObject,GeometryNode, "hasMesh", 0, 0, thisObj->hasMesh())

	//! [ESMF] self MinSG.GeometryNode.setMesh(mesh)
	ES_MFUNCTION(typeObject,GeometryNode,"setMesh",1,1,{
			if(!parameter[0].toBool()){
				thisObj->setMesh(nullptr);
			}else{
				thisObj->setMesh(parameter[0].to<Rendering::Mesh*>(rt));
			}
			return thisEObj;
	})

}

}
