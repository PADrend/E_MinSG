/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_TRIANGULATION

#include "E_Delaunay3d.h"

#include "../../ELibMinSG.h"

#include <MinSG/Core/Nodes/ListNode.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <E_Geometry/E_Vec3.h>
#include <E_Geometry/E_Tetrahedron.h>
#include <MinSG/Ext/Triangulation/Helper.h>

namespace E_MinSG{
namespace Triangulation{

static EScript::Object * convertToEScriptObject(const ObjRefPoint3 * point) {
	EScript::ERef<EScript::ExtObject> ePoint = EScript::ExtObject::create();

	static const EScript::StringId posId("pos");
	static const EScript::StringId dataId("data");

	ePoint->setAttribute(posId, EScript::create(point->getPosition()));
	ePoint->setAttribute(dataId, point->data);
	EScript::initPrintableName(ePoint.get(),"Delaunay3d::Point");

	return ePoint.detachAndDecrease();
}

//! (static)
EScript::Type * E_Delaunay3d::getTypeObject() {
	// E_Delaunay3d ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_Delaunay3d::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Delaunay3d::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace MinSG::Triangulation;
	
	typedef Delaunay3d<E_MinSG::Triangulation::ObjRefPoint3> Delaunay3d_t;

	//! [ESF] new Delaunay3d()
	ES_CTOR(typeObject,0,0,		new E_Delaunay3d())

	//! [ESMF] self Delaunay3d.addPoint(Vec3 pos, Object data)
	ES_MFUN(typeObject, Delaunay3d_t, "addPoint", 2, 2,
				 (thisObj->addPoint(ObjRefPoint3(parameter[0].to<const Geometry::Vec3&>(rt), parameter[1])), thisEObj))

	//! [ESMF] Node Delaunay3d.createMinSGNodes(Bool)
	ES_MFUN(typeObject, Delaunay3d_t, "createMinSGNodes", 1, 1,
				EScript::create(MinSG::Triangulation::createMinSGNodes(*thisObj, parameter[0].toBool())))

	//! [ESMF] Array|Void Delaunay3d.findTetrahedron(Vec3, Number)
	ES_MFUNCTION(typeObject, Delaunay3d_t, "findTetrahedron", 2, 2, {
		const Geometry::Vec3 & pos = parameter[0].to<const Geometry::Vec3&>(rt);
		const auto * tetrahedron = thisObj->findTetrahedron(pos, parameter[1].toFloat());
		if(tetrahedron == nullptr) {
			return EScript::create(nullptr);
		}
		EScript::Array * points = EScript::Array::create();
		points->pushBack(convertToEScriptObject(tetrahedron->getA()));
		points->pushBack(convertToEScriptObject(tetrahedron->getB()));
		points->pushBack(convertToEScriptObject(tetrahedron->getC()));
		points->pushBack(convertToEScriptObject(tetrahedron->getD()));
		return points;
	})

	//! [ESMF] Array Delaunay3d.findNearestTetrahedron(Vec3)
	ES_MFUNCTION(typeObject, Delaunay3d_t, "findNearestTetrahedron", 1, 1, {
		const Geometry::Vec3 & pos = parameter[0].to<const Geometry::Vec3&>(rt);
		const auto * tetrahedron = thisObj->findNearestTetrahedron(pos);
		EScript::Array * points = EScript::Array::create();
		points->pushBack(convertToEScriptObject(tetrahedron->getA()));
		points->pushBack(convertToEScriptObject(tetrahedron->getB()));
		points->pushBack(convertToEScriptObject(tetrahedron->getC()));
		points->pushBack(convertToEScriptObject(tetrahedron->getD()));
		return points;
	})

	//! [ESMF] Bool Delaunay3d.isValid()
	ES_MFUN(typeObject,const Delaunay3d_t,"isValid",0,0,
				EScript::Bool::create(thisObj->isValid()))

	//! [ESMF] self Delaunay3d.updateTetrahedra()
	ES_MFUN(typeObject,Delaunay3d_t,"updateTetrahedra",0,0,
				(thisObj->updateTetrahedra(),thisEObj))

	//! [ESMF] self Delaunay3d.validate()
	ES_MFUN(typeObject,Delaunay3d_t,"validate",0,0,
				(thisObj->validate(),thisEObj))

	// Defined here because there are problems defining it inside the ES_MFUNCTION macro
	struct FunctionWrapper {
		EScript::Runtime & runtime;
		EScript::ObjPtr function;

		FunctionWrapper(EScript::Runtime & p_runtime, EScript::ObjPtr p_function) :
			runtime(p_runtime), function(p_function) {
		}

		void operator()(const MinSG::Triangulation::TetrahedronWrapper<ObjRefPoint3> & tetrahedron) {
			EScript::ParameterValues parameters(5);
			parameters.set(0, new E_Geometry::E_Tetrahedron(tetrahedron.getTetrahedron()));
			parameters.set(1, convertToEScriptObject(tetrahedron.getA()));
			parameters.set(2, convertToEScriptObject(tetrahedron.getB()));
			parameters.set(3, convertToEScriptObject(tetrahedron.getC()));
			parameters.set(4, convertToEScriptObject(tetrahedron.getD()));
			EScript::callFunction(runtime, function.get(), parameters);
		}
	};

	//! [ESMF] void Delaunay3d.generate(Function)
	ES_MFUNCTION(typeObject, Delaunay3d_t, "generate", 1, 1, {
		FunctionWrapper wrapper(rt, parameter[0]);
		thisObj->generate(wrapper);
		return EScript::create(nullptr);
	})
}
}
}
#endif // MINSG_EXT_TRIANGULATION
