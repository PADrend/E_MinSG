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

#include "E_Delaunay2d.h"

#include "../../ELibMinSG.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <E_Geometry/E_Vec2.h>
#include <MinSG/Core/Nodes/ListNode.h>
#include <MinSG/Ext/Triangulation/Helper.h>

namespace E_MinSG {
namespace Triangulation {

static EScript::Object * convertToEScriptObject(const ObjRefPoint2 & point) {
	EScript::ERef<EScript::ExtObject> ePoint = EScript::ExtObject::create();

	static const EScript::StringId posId("pos");
	static const EScript::StringId dataId("data");

	ePoint->setAttribute(posId, new E_Geometry::E_Vec2(point.getPosition()));
	ePoint->setAttribute(dataId, point.data);
	EScript::initPrintableName(ePoint.get(),"Delaunay2d::Point");

	return ePoint.detachAndDecrease();
}

//! (static)
EScript::Type * E_Delaunay2d::getTypeObject() {
	// E_Delaunay2d ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_Delaunay2d::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Delaunay2d::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);


	using namespace MinSG::Triangulation;
	
	typedef Delaunay2d<E_MinSG::Triangulation::ObjRefPoint2> Delaunay2d_t;

	//! [ESF] new Delaunay2d()
	ES_CTOR(typeObject, 0, 0,		new E_Delaunay2d)

	//! [ESMF] self Delaunay2d.addPoint(Vec2 pos, Object data)
	ES_MFUN(typeObject, Delaunay2d_t, "addPoint", 2, 2,
				 (thisObj->addPoint(ObjRefPoint2(parameter[0].to<const Geometry::Vec2&>(rt), parameter[1])), thisEObj))

	//! [ESMF] Node Delaunay2d.createMinSGNodes()
	ES_MFUN(typeObject, const Delaunay2d_t, "createMinSGNodes", 0, 0,
				 EScript::create(MinSG::Triangulation::createMinSGNodes(*thisObj)))

	//! [ESMF] Array Delaunay2d.getTriangles()
	ES_MFUNCTION(typeObject, const Delaunay2d_t, "getTriangles", 0, 0, {
		struct Collector {
			EScript::Array * array;

			Collector() : array(EScript::Array::create()) {}

			void operator()(const ObjRefPoint2 & a, const ObjRefPoint2 & b, const ObjRefPoint2 & c) {
				EScript::Array * element = EScript::Array::create();
				element->pushBack(convertToEScriptObject(a));
				element->pushBack(convertToEScriptObject(b));
				element->pushBack(convertToEScriptObject(c));
				array->pushBack(element);
			}
		} collector;
		thisObj->generate(collector);
		return collector.array;
	})

	// Defined here because there are problems defining it inside the ES_MFUNCTION macro
	struct FunctionWrapper {
		EScript::Runtime & runtime;
		EScript::ObjPtr function;

		FunctionWrapper(EScript::Runtime & p_runtime, EScript::ObjPtr p_function) :
			runtime(p_runtime), function(p_function) {
		}

		void operator()(const ObjRefPoint2 & a, const ObjRefPoint2 & b, const ObjRefPoint2 & c) {
			EScript::ParameterValues parameters(3);
			parameters.set(0, convertToEScriptObject(a));
			parameters.set(1, convertToEScriptObject(b));
			parameters.set(2, convertToEScriptObject(c));
			EScript::callFunction(runtime, function.get(), parameters);
		}
	};

	//! [ESMF] void Delaunay2d.generate(Function)
	ES_MFUNCTION(typeObject, const Delaunay2d_t, "generate", 1, 1, {
		FunctionWrapper wrapper(rt, parameter[0]);
		thisObj->generate(wrapper);
		return EScript::create(nullptr);
	})
}

}
}
#endif // MINSG_EXT_TRIANGULATION
