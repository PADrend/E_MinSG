/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Node.h"
#include <E_Geometry/E_Line3.h>
#include <E_Geometry/E_Matrix4x4.h>
#include <E_Geometry/E_SRT.h>
#include <E_Geometry/E_Vec3.h>
#include <E_Geometry/E_Box.h>

#include <MinSG/Core/Transformations.h>

#include "E_GroupNode.h"
#include "../E_FrameContext.h"
#include "../E_RenderParam.h"
#include "../States/E_State.h"
#include "../../ELibMinSG.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <E_Util/E_Utils.h>
#include <Util/Macros.h>

using namespace E_Geometry;
using namespace MinSG;

namespace E_MinSG {

//! (static)
E_Util::E_ObjectFactory<MinSG::Node,E_Node> E_Node::factorySystem;

// ----------------------------------------------------------------------

EScript::Type * E_Node::getTypeObject() {
	// E_Node ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

// ----------------------------------------------------------------------

//! [static] initMembers
void E_Node::init(EScript::Namespace & lib) {

	// converter for Util::ReferenceAttribute<MinSG::Node>>   < -- > E_MinSG::E_Node
	class Converter : public E_Util::E_Utils::AbstractGenericAttributeConverter {
	public:
		virtual ~Converter() {}

		typedef  Util::ReferenceAttribute<MinSG::Node> attr_t;
		
		Object * convertToEScript(const Util::GenericAttribute * const attribute) override {
			const auto * specificAttr = dynamic_cast<const attr_t*>(attribute);
			return specificAttr ? EScript::create(specificAttr->ref().get()) : nullptr;
		}

		Util::GenericAttribute * convertFromEScript(const EScript::ObjPtr & eObject) override {
			auto * eNode = eObject.toType<E_Node>();
			return eNode ? new attr_t(**eNode) : nullptr;
		}
	};
	E_Util::E_Utils::registerConverter(new Converter);
	
	// ---------------------------------
	
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::Node,E_Node>();

	// -----------------------------------
	// ---- Main

	//! [ESMF] self MinSG.Node.display(FrameContext[,Flags|RenderingParameter]);
	ES_MFUNCTION(typeObject,Node,"display",1,2,{
		E_RenderParam * eRp = parameter[1].toType<E_RenderParam>();
		if(eRp){
			thisObj->display(parameter[0].to<MinSG::FrameContext&>(rt),eRp->ref());
		}else{
			thisObj->display(parameter[0].to<MinSG::FrameContext&>(rt),
										static_cast<unsigned int>(parameter[1].toInt(0)));
		}
		return thisEObj;
	})

	//! [ESMF] self MinSG.Node.activate()
	ES_MFUN(typeObject,Node, "activate", 0, 0, (thisObj->activate(),thisEObj))

	//! [ESMF] self MinSG.Node.deactivate()
	ES_MFUN(typeObject,Node, "deactivate", 0, 0, (thisObj->deactivate(),thisEObj))

	//! [ESMF] bool MinSG.Node.isActive()
	ES_MFUN(typeObject,const Node,"isActive",0,0,thisObj->isActive())

	//! [ESMF] bool MinSG.Node.isDestroyed()
	ES_MFUN(typeObject,const Node,"isDestroyed",0,0,thisObj->isDestroyed())

	//! [ESMF] MinSG.GoupNode Node.getParent()
	ES_MFUN(typeObject,const Node,"getParent",0,0,thisObj->getParent())

	//! [ESMF] Bool MinSG.Node.hasParent()
	ES_MFUN(typeObject,const Node,"hasParent",0,0,thisObj->hasParent())

	//! [ESMF] String Node.getRuntimeId()
	ES_MFUNCTION(typeObject,const Node,"getRuntimeId",0,0,{
		const Node * node = thisObj;
		uintptr_t pointer = reinterpret_cast<uintptr_t>(node);
		std::ostringstream ostr;
		ostr << pointer;
		return ostr.str();
	})


	// -----------------------------------
	// ---- Attributes

	// -----------------------------------
	// ---- Bounding Boxes

	//! [ESMF] Box MinSG.Node.getWorldBB()
	ES_MFUN(typeObject,const Node,"getWorldBB",0,0,thisObj->getWorldBB())

	//! [ESMF] Box MinSG.Node.getBB()
	ES_MFUN(typeObject,const Node,"getBB",0,0,thisObj->getBB())

	//! [ESMF] Bool MinSG.Node.hasFixedBB()
	ES_MFUN(typeObject,const Node,"hasFixedBB",0,0,thisObj->hasFixedBB())

	//! [ESMF] self MinSG.Node.removeFixedBB(Box)
	ES_MFUN(typeObject,Node,"removeFixedBB",0,0,(thisObj->removeFixedBB(),thisEObj))

	//! [ESMF] self MinSG.Node.setFixedBB(Box)
	ES_MFUN(typeObject,Node,"setFixedBB",1,1,(thisObj->setFixedBB(parameter[0].to<const Geometry::Box&>(rt)),thisEObj))

	// -----------------------------------
	// ---- Instance

	//! [ESF] Node MinSG.Node.createInstance(Node prototype)
	ES_MFUN(typeObject,EScript::Type,"createInstance",1,1,(thisObj->getType(), // use Type as caller to assure static usage; use it to prevent warning.
														Node::createInstance(parameter[0].to<MinSG::Node*>(rt))))

	//! [ESMF] Bool MinSG.Node.isInstance()
	ES_MFUN(typeObject,const Node,"isInstance",0,0,thisObj->isInstance())

	//! [ESMF] Bool MinSG.Node.getPrototype()
	ES_MFUN(typeObject,const Node,"getPrototype",0,0,thisObj->getPrototype())

	//! [ESMF] self MinSG.Node._setPrototype( void||MinSG.Node )
	ES_MFUNCTION(typeObject,Node,"_setPrototype",1,1,{
		if(!parameter[0].toBool()){
			thisObj->_setPrototype(nullptr);
		}else{
			thisObj->_setPrototype(parameter[0].to<MinSG::Node*>(rt));
		}
		return thisEObj;
	})

	
	// -----------------------------------
	// ---- Matrix

	//! [ESMF] Bool MinSG.Node.hasMatrix()
	ES_MFUN(typeObject,const Node,"hasMatrix",0,0,thisObj->hasMatrix())

	//! [ESMF] Matrix4x4 MinSG.Node.getMatrix()
	ES_MFUNCTION(typeObject,const Node,"getMatrix",0,0,{
		const Geometry::Matrix4x4 * m=thisObj->getMatrixPtr();
		return EScript::create( m==nullptr ? Geometry::Matrix4x4() : Geometry::Matrix4x4(*m) );
	})

	//! [ESMF] Matrix4x4 MinSG.Node.getWorldMatrix()
	ES_MFUN(typeObject,const Node,"getWorldMatrix",0,0,thisObj->getWorldMatrix())

	//! [ESMF] self MinSG.Node.setMatrix(Matrix4x4)
	ES_MFUN(typeObject,Node,"setMatrix",1,1,(thisObj->setMatrix(parameter[0].to<const Geometry::Matrix4x4&>(rt)),thisEObj))

	

	// -----------------------------------
	// ---- Observer
	
	//! [ESMF] Bool MinSG.Node.isTransformationObserved(Vec3)
	ES_MFUN(typeObject,Node,"isTransformationObserved",0,0,	thisObj->isTransformationObserved())

	{
		struct ScriptedObserver{
			EScript::Runtime & rt;
			MinSG::Node * owningNode;
			ScriptedObserver(EScript::Runtime & _rt, MinSG::Node * _owningNode) : rt(_rt), owningNode(_owningNode){}
			void operator()(Node * transformedNode){
				static const EScript::StringId handlerId("onNodeTransformed");
				EScript::ObjRef result = EScript::callMemberFunction(rt,EScript::create(owningNode),handlerId,
															EScript::ParameterValues(EScript::create(transformedNode)));
			}
		};

		/*! [ESMF] self MinSG.Node._enableTransformationObserver()
			Adds a ScriptedObserver to the node. This observer calls the Node's script member function
			'onNodeTransformed' when a node in the subtree is transformed.
			\note Make sure that a member of that name exists before moving a node; an exception is thrown otherwise.
		*/
		ES_MFUN(typeObject,Node,"_enableTransformationObserver",0,0,
					(thisObj->addTransformationObserver(std::move(ScriptedObserver(rt,thisObj))),thisEObj))
	}
	{
		struct ScriptedObserver{
			EScript::Runtime & rt;
			MinSG::Node * owningNode;
			ScriptedObserver(EScript::Runtime & _rt, MinSG::Node * _owningNode) : rt(_rt), owningNode(_owningNode){}
			void operator()(Node * addedNode){
				static const EScript::StringId handlerId("onNodeAdded");
				EScript::ObjRef result = EScript::callMemberFunction(rt,EScript::create(owningNode),handlerId,
															EScript::ParameterValues(EScript::create(addedNode)));
			}
		};

		/*! [ESMF] self MinSG.Node._enableNodeAddedObserver()
			Adds a ScriptedObserver to the node. This observer calls the Node's script member function
			'onNodeAdded' when a node in the subtree is added.
			\note Make sure that a member of that name exists before moving a node; an exception is thrown otherwise.
		*/
		ES_MFUN(typeObject,Node,"_enableNodeAddedObserver",0,0,
					(thisObj->addNodeAddedObserver(std::move(ScriptedObserver(rt,thisObj))),thisEObj))
	}	
	{
		struct ScriptedObserver{
			EScript::Runtime & rt;
			MinSG::Node * owningNode;
			ScriptedObserver(EScript::Runtime & _rt, MinSG::Node * _owningNode) : rt(_rt), owningNode(_owningNode){}
			void operator()(GroupNode * parent, Node * removedNode){
				static const EScript::StringId handlerId("onNodeRemoved");
				EScript::ObjRef result = EScript::callMemberFunction(rt,EScript::create(owningNode),handlerId,
															EScript::ParameterValues(EScript::create(parent),EScript::create(removedNode)));
			}
		};

		/*! [ESMF] self MinSG.Node._enableNodeRemovedObserver()
			Adds a ScriptedObserver to the node. This observer calls the Node's script member function
			'onNodeRemoved' when a node in the subtree is added.
			\note Make sure that a member of that name exists before moving a node; an exception is thrown otherwise.
		*/
		ES_MFUN(typeObject,Node,"_enableNodeRemovedObserver",0,0,
					(thisObj->addNodeRemovedObserver(std::move(ScriptedObserver(rt,thisObj))),thisEObj))
	}

	// -----------------------------------
	// ---- SRT

	//! [ESMF] Bool MinSG.Node.hasSRT()
	ES_MFUN(typeObject,const Node,"hasSRT",0,0,thisObj->hasSRT())

	//! [ESMF] SRT MinSG.Node.getSRT()
	ES_MFUN(typeObject,const Node,"getSRT",0,0,thisObj->getSRT())

	//! [ESMF] self MinSG.Node.setSRT(SRT)
	ES_MFUN(typeObject,Node,"setSRT",1,1,(thisObj->setSRT(parameter[0].to<const Geometry::SRT&>(rt)),thisEObj))
	
	//! [ESMF] SRT MinSG.Node.getWorldSRT()
	ES_MFUN(typeObject,const Node,"getWorldSRT",0,0,Transformations::getWorldSRT(thisObj))
	
	//! [ESMF] slef MinSG.Node.setWorldSRT(SRT)
	ES_MFUN(typeObject,Node,"setWorldSRT",1,1,(thisObj->setSRT( Transformations::worldSRTToRelSRT(thisObj,parameter[0].to<const Geometry::SRT&>(rt))),thisEObj))


	// -----------------------------------
	// ---- States

	//! [ESMF] self MinSG.Node.removeStates()
	ES_MFUN(typeObject,Node,"removeStates",0,0,(thisObj->removeStates(),thisEObj))

	//! [ESMF] bool MinSG.Node.hasStates()
	ES_MFUN(typeObject,const Node,"hasStates",0,0,thisObj->hasStates())

	//! [ESMF] self MinSG.Node.addState(State)
	ES_MFUNCTION(typeObject,Node,"addState",1,1, {
		MinSG::State * state = parameter[0].to<MinSG::State*>(rt);
		if (state == nullptr) {
			WARN("addState(...): Given State is nullptr!");
		} else {
			thisObj->addState(state);
		}
		return thisEObj;
	})

	//! [ESMF] self MinSG.Node.removeState(State)
	ES_MFUNCTION(typeObject,Node,"removeState",1,1, {
		MinSG::State * state = parameter[0].to<MinSG::State*>(rt);
		if (state == nullptr) {
			WARN("removeState(...): Given State is nullptr!");
		} else {
			thisObj->removeState(state);
		}
		return thisEObj;
	})

	//! [ESMF] Array MinSG.Node.getStates()
	ES_MFUNCTION(typeObject,const Node,"getStates",0,0,{
		EScript::Array * a=EScript::Array::create();
		for(auto & state : thisObj->getStates())
			a->pushBack(EScript::create(state));
		return a;
	})

	// -----------------------------------
	// ---- Tranformations
	
	//! [ESMF] self MinSG.Node.moveRel(Vec3 | (x,y,z))
	ES_MFUNCTION(typeObject,Node,"moveRel",1,3,{
		Node * n=thisObj;
		if(parameter.count()<3){
			n->moveRel(parameter[0].to<Geometry::Vec3>(rt));
		}else{
			n->moveRel(Geometry::Vec3(parameter[0].toFloat(),parameter[1].toFloat(),parameter[2].toFloat()));
		}
		return thisEObj;
	})

	//! [ESMF] self MinSG.Node.moveLocal(Vec3 | (x,y,z))
	ES_MFUNCTION(typeObject,Node,"moveLocal",1,3,{
		Node * n=thisObj;
		n->moveLocal(parameter.count()<3 ? parameter[0].to<Geometry::Vec3>(rt) :
					 Geometry::Vec3(parameter[0].toFloat(),parameter[1].toFloat(),parameter[2].toFloat()) );
		return thisEObj;
	})
	
	//! [ESMF] self MinSG.Node.reset()
	ES_MFUN(typeObject,Node,"reset",0,0,(thisObj->reset(),thisEObj))

	//! [ESMF] self MinSG.Node.rotateRel_rad(float angle, (Vec3|x,y,z))
	ES_MFUN(typeObject,Node,"rotateRel_rad",2,4,(thisObj->
			rotateRel_rad(parameter[0].toFloat(),  parameter.count()<4 ?
						  parameter[1].to<Geometry::Vec3>(rt) :
						  Geometry::Vec3(parameter[1].toFloat(),parameter[2].toFloat(),parameter[3].toFloat())),thisEObj))

	//! [ESMF] self MinSG.Node.rotateRel_deg(float deg, (Vec3|x,y,z))
	ES_MFUN(typeObject,Node,"rotateRel_deg",2,4,(thisObj->
			rotateRel_deg(parameter[0].toFloat(),  parameter.count()<4 ?
						  parameter[1].to<Geometry::Vec3>(rt) :
						  Geometry::Vec3(parameter[1].toFloat(),parameter[2].toFloat(),parameter[3].toFloat())),thisEObj))

	//! [ESMF] self MinSG.Node.setRelRotation_rad(float angle, (Vec3|x,y,z))
	ES_MFUN(typeObject,Node,"setRelRotation_rad",2,4,(thisObj->
			setRelRotation_rad(parameter[0].toFloat(),  parameter.count()<4 ?
						  parameter[1].to<Geometry::Vec3>(rt) :
						  Geometry::Vec3(parameter[1].toFloat(),parameter[2].toFloat(),parameter[3].toFloat())),thisEObj))


	//! [ESMF] self MinSG.Node.setRelRotation_deg(float deg, (Vec3|x,y,z))
	ES_MFUN(typeObject,Node,"setRelRotation_deg",2,4,(thisObj->
			setRelRotation_deg(parameter[0].toFloat(),  parameter.count()<4 ?
						  parameter[1].to<Geometry::Vec3>(rt) :
						  Geometry::Vec3(parameter[1].toFloat(),parameter[2].toFloat(),parameter[3].toFloat())),thisEObj))


	//! [ESMF] self MinSG.Node.rotateLocal_rad(float angle, (Vec3|x,y,z))
	ES_MFUN(typeObject,Node,"rotateLocal_rad",2,4,(thisObj->
			rotateLocal_rad(parameter[0].toFloat(),  parameter.count()<4 ?
						  parameter[1].to<Geometry::Vec3>(rt) :
						  Geometry::Vec3(parameter[1].toFloat(),parameter[2].toFloat(),parameter[3].toFloat())),thisEObj))

	//! [ESMF] self MinSG.Node.rotateLocal_deg(float deg, (Vec3|x,y,z))
	ES_MFUN(typeObject,Node,"rotateLocal_deg",2,4,(thisObj->
			rotateLocal_deg(parameter[0].toFloat(),  parameter.count()<4 ?
						  parameter[1].to<Geometry::Vec3>(rt) :
						  Geometry::Vec3(parameter[1].toFloat(),parameter[2].toFloat(),parameter[3].toFloat())),thisEObj))

	//! [ESMF] Vec3 MinSG.Node.getWorldOrigin()
	ES_MFUN(typeObject,const Node,"getWorldOrigin",0,0,thisObj->getWorldOrigin())

	//! [ESMF] Vec3 MinSG.Node.getWorldPosition()
	ES_MFUN(typeObject,const Node,"getWorldPosition",0,0,thisObj->getWorldOrigin())

	//! [ESMF] self MinSG.Node.setWorldOrigin(Vec3)
	ES_MFUN(typeObject,Node,"setWorldOrigin",1,1,(thisObj->setWorldOrigin(parameter[0].to<Geometry::Vec3>(rt)),thisEObj))

	//! [ESMF] self MinSG.Node.setWorldPosition(Vec3)
	ES_MFUN(typeObject,Node,"setWorldPosition",1,1,(thisObj->setWorldOrigin(parameter[0].to<Geometry::Vec3>(rt)),thisEObj))

	//! [ESMF] Vec3 MinSG.Node.getRelOrigin()
	ES_MFUN(typeObject,const Node,"getRelOrigin",0,0,thisObj->getRelOrigin())

	//! [ESMF] Vec3 MinSG.Node.getRelPosition()
	ES_MFUN(typeObject,const Node,"getRelPosition",0,0,thisObj->getRelOrigin())

	//! [ESMF] self MinSG.Node.setRelOrigin(Vec3)
	ES_MFUN(typeObject,Node,"setRelOrigin",1,1,(thisObj->setRelOrigin(parameter[0].to<Geometry::Vec3>(rt)),thisEObj))

	//! [ESMF] self MinSG.Node.setRelPosition(Vec3)
	ES_MFUN(typeObject,Node,"setRelPosition",1,1,(thisObj->setRelOrigin(parameter[0].to<Geometry::Vec3>(rt)),thisEObj))

	//! [ESMF] self MinSG.Node.lookAtAbs(Vec3 worldPosition)
	ES_MFUNCTION(typeObject,Node,"lookAtAbs",1,1,{
		thisObj->lookAtAbs(parameter[0].to<Geometry::Vec3>(rt));
		return thisEObj;
	})

	//! [ESMF] self MinSG.Node.rotateToWorldDir(Vec3 dir)
	ES_MFUNCTION(typeObject,Node,"rotateToWorldDir",1,1,{
		thisObj->rotateToWorldDir(parameter[0].to<Geometry::Vec3>(rt));
		return thisEObj;
	})

	//! [ESMF] self MinSG.Node.setScale(number)
	ES_MFUN(typeObject,Node,"setScale",1,1,(thisObj->setScale(parameter[0].toDouble()),thisEObj))

	//! [ESMF] self MinSG.Node.scale(number)
	ES_MFUN(typeObject,Node,"scale",1,1,(thisObj->scale(parameter[0].toDouble()),thisEObj))

	//! [ESMF] number MinSG.Node.getScale()
	ES_MFUN(typeObject,const Node,"getScale",0,0,thisObj->getScale())

	// -----------------------------------
	// ---- Mixed Wrapper
	
	//! [ESMF] Object MinSG.Node.findNodeAttribute(string key)
	ES_MFUN(typeObject,const Node,"findNodeAttribute",1,1,
		 E_Util::E_Utils::convertGenericAttributeToEScriptObject(thisObj->findAttribute(parameter[0].toString())))

	//!	[ESMF] Map MinSG.Node.getNodeAttributes()
	ES_MFUN(typeObject,const Node,"getNodeAttributes",0,0,E_Util::E_Utils::convertGenericAttributeToEScriptObject(thisObj->getAttributes()))

	//! [ESMF] Object MinSG.Node.getNodeAttribute(string key)
	ES_MFUN(typeObject,const Node,"getNodeAttribute",1,1,
		 E_Util::E_Utils::convertGenericAttributeToEScriptObject(thisObj->getAttribute(parameter[0].toString())))

	//! [ESMF] Bool MinSG.Node.isClosed()
	ES_MFUN(typeObject,const Node,"isClosed",0,0,thisObj->isClosed())
	
	//! [ESMF] Bool MinSG.Node.isTempNode()
	ES_MFUN(typeObject,const Node,"isTempNode",0,0,thisObj->isTempNode())
	
	//! [ESMF] self MinSG.Node.isNodeAttributeSet(string key)
	ES_MFUN(typeObject,const Node,"isNodeAttributeSet",1,1,thisObj->isAttributeSet(parameter[0].toString()))
	
	//! [ESMF] self MinSG.Node.removeNodeAttributes()
	ES_MFUN(typeObject,Node,"removeNodeAttributes",0,0,(	thisObj->removeAttributes(),thisEObj))

	//! [ESMF] self MinSG.Node.setClosed(bool active)
	ES_MFUN(typeObject,Node,"setClosed",1,1,(thisObj->setClosed(parameter[0].toBool()),thisEObj))

	//! [ESMF] self MinSG.Node.setTempNode(bool)
	ES_MFUN(typeObject,Node,"setTempNode",1,1,(thisObj->setTempNode(parameter[0].toBool()),thisEObj))

	//! [ESMF] self MinSG.Node.setNodeAttribute(string key,value)
	ES_MFUN(typeObject,Node,"setNodeAttribute",2,2,(
		thisObj->setAttribute( parameter[0].toString(),
								E_Util::E_Utils::convertEScriptObjectToGenericAttribute(parameter[1])),thisEObj))

	//! [ESMF] bool MinSG.Node.unsetNodeAttribute(string key)
	ES_MFUN(typeObject,Node,"unsetNodeAttribute",1,1,thisObj->unsetAttribute(parameter[0].toString()))

	// ---------------------------------------------------------------------------------------------------------
	// external transformations
	
	
	//! [ESMF] Vec3 MinSG.Node.localDirToWorldDir(Vec3)
	ES_MFUN(typeObject,Node,"localDirToWorldDir",1,1,
				Transformations::localDirToWorldDir(thisObj,parameter[0].to<Geometry::Vec3>(rt)))
	
	//! [ESMF] Vec3 MinSG.Node.localDirToRelDir(Vec3)
	ES_MFUN(typeObject,Node,"localDirToRelDir",1,1,
				Transformations::localDirToRelDir(thisObj,parameter[0].to<Geometry::Vec3>(rt)))
	
	//! [ESMF] Vec3 MinSG.Node.localPosToWorldPos(Vec3)
	ES_MFUN(typeObject,Node,"localPosToWorldPos",1,1,
				Transformations::localPosToWorldPos(thisObj,parameter[0].to<Geometry::Vec3>(rt)))
	
	//! [ESMF] Vec3 MinSG.Node.localPosToRelPos(Vec3)
	ES_MFUN(typeObject,Node,"localPosToRelPos",1,1,
				Transformations::localPosToRelPos(thisObj,parameter[0].to<Geometry::Vec3>(rt)))
	
	//! [ESMF] Vec3 MinSG.Node.relDirToWorldDir(Vec3)
	ES_MFUN(typeObject,Node,"relDirToWorldDir",1,1,
				Transformations::relDirToWorldDir(thisObj,parameter[0].to<Geometry::Vec3>(rt)))
	
	//! [ESMF] Vec3 MinSG.Node.relDirToLocalDir(Vec3)
	ES_MFUN(typeObject,Node,"relDirToLocalDir",1,1,
				Transformations::relDirToLocalDir(thisObj,parameter[0].to<Geometry::Vec3>(rt)))
	
	//! [ESMF] Vec3 MinSG.Node.relPosToWorldPos(Vec3)
	ES_MFUN(typeObject,Node,"relPosToWorldPos",1,1,
				Transformations::relPosToWorldPos(thisObj,parameter[0].to<Geometry::Vec3>(rt)))
	
	//! [ESMF] Vec3 MinSG.Node.relPosToLocalPos(Vec3)
	ES_MFUN(typeObject,Node,"relPosToLocalPos",1,1,
				Transformations::relPosToLocalPos(thisObj,parameter[0].to<Geometry::Vec3>(rt)))
	
	//! [ESMF] Vec3 MinSG.Node.worldDirToLocalDir(Vec3)
	ES_MFUN(typeObject,Node,"worldDirToLocalDir",1,1,
				Transformations::worldDirToLocalDir(thisObj,parameter[0].to<Geometry::Vec3>(rt)))
	
	//! [ESMF] Vec3 MinSG.Node.worldDirToRelDir(Vec3)
	ES_MFUN(typeObject,Node,"worldDirToRelDir",1,1,
				Transformations::worldDirToRelDir(thisObj,parameter[0].to<Geometry::Vec3>(rt)))
	
	//! [ESMF] Vec3 MinSG.Node.worldPosToLocalPos(Vec3)
	ES_MFUN(typeObject,Node,"worldPosToLocalPos",1,1,
				Transformations::worldPosToLocalPos(thisObj,parameter[0].to<Geometry::Vec3>(rt)))
	
	//! [ESMF] Vec3 MinSG.Node.worldPosToRelPos(Vec3)
	ES_MFUN(typeObject,Node,"worldPosToRelPos",1,1,
				Transformations::worldPosToRelPos(thisObj,parameter[0].to<Geometry::Vec3>(rt)))

	//! [ESMF] self MinSG.Node.rotateAroundLocalAxis_deg(Number,Line3)
	ES_MFUN(typeObject,Node,"rotateAroundLocalAxis_deg",2,2,
				(Transformations::rotateAroundLocalAxis(thisObj,
															Geometry::Angle::deg(parameter[0].toFloat()),
															parameter[1].to<const Geometry::Line3&>(rt)),thisEObj))

	//! [ESMF] self MinSG.Node.rotateAroundLocalAxis_rad(Number,Line3)
	ES_MFUN(typeObject,Node,"rotateAroundLocalAxis_rad",2,2,
				(Transformations::rotateAroundLocalAxis(thisObj,
															Geometry::Angle::rad(parameter[0].toFloat()),
															parameter[1].to<const Geometry::Line3&>(rt)),thisEObj))

	//! [ESMF] self MinSG.Node.rotateAroundRelAxis_deg(Number,Line3)
	ES_MFUN(typeObject,Node,"rotateAroundRelAxis_deg",2,2,
				(Transformations::rotateAroundRelAxis(thisObj,
															Geometry::Angle::deg(parameter[0].toFloat()),
															parameter[1].to<const Geometry::Line3&>(rt)),thisEObj))

	//! [ESMF] self MinSG.Node.rotateAroundRelAxis_rad(Number,Line3)
	ES_MFUN(typeObject,Node,"rotateAroundRelAxis_rad",2,2,
				(Transformations::rotateAroundRelAxis(thisObj,
															Geometry::Angle::rad(parameter[0].toFloat()),
															parameter[1].to<const Geometry::Line3&>(rt)),thisEObj))

	//! [ESMF] self MinSG.Node.rotateAroundWorldAxis_deg(Number,Line3)
	ES_MFUN(typeObject,Node,"rotateAroundWorldAxis_deg",2,2,
				(Transformations::rotateAroundWorldAxis(thisObj,
															Geometry::Angle::deg(parameter[0].toFloat()),
															parameter[1].to<const Geometry::Line3&>(rt)),thisEObj))
															
	//! [ESMF] self MinSG.Node.rotateAroundWorldAxis_rad(Number,Line3)
	ES_MFUN(typeObject,Node,"rotateAroundWorldAxis_rad",2,2,
				(Transformations::rotateAroundWorldAxis(thisObj,
															Geometry::Angle::rad(parameter[0].toFloat()),
															parameter[1].to<const Geometry::Line3&>(rt)),thisEObj))

	// --------------------------------------------

	//! [ESMF] Number MinSG.Node.getMemoryUsage()
	ES_MFUN(typeObject, const Node, "getMemoryUsage", 0, 0, static_cast<double>(thisObj->getMemoryUsage()))

}


//---
//! (ctor)
E_Node::E_Node(Node * _node,EScript::Type * type):ExtReferenceObject_t(_node,type?type:getTypeObject()) {
}

//! (dtor)
E_Node::~E_Node() {
}

//! ---|> Object
E_Node * E_Node::clone()const {
	return EScript::create(ref()->clone());
}

//! ---|> Object
std::string E_Node::toString() const {
	std::ostringstream s;
	s << "[" << ref()->getTypeName() << ":" << reinterpret_cast<const void *> (ref().get()) << "]";
	return s.str();
}

}

