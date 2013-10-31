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

#ifndef _E_MinSG_Triangulation_E_Delaunay3d_H_
#define _E_MinSG_Triangulation_E_Delaunay3d_H_

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Point.h>
#include <Geometry/Vec3.h>
#include <MinSG/Ext/Triangulation/Delaunay3d.h>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG{
namespace Triangulation{

struct ObjRefPoint3 : public Geometry::Point<Geometry::Vec3f> {
	EScript::ObjRef data;

	ObjRefPoint3(const Geometry::Vec3f & pos, const EScript::ObjRef & object) :
			Geometry::Point<Geometry::Vec3f>(pos), data(object) {
	}
};

/*!	EScript wrapper class for MinSG::Delaunay3d::Delaunay3d.

		E_Delaunay3d ---|> EScript::ReferenceObject<MinSG::Delaunay3d::Delaunay3d>
			|
			--------------> MinSG::Delaunay3d::Delaunay3d		*/
class E_Delaunay3d : public EScript::ReferenceObject<MinSG::Triangulation::Delaunay3d<ObjRefPoint3>, EScript::Policies::SameEObjects_ComparePolicy> {
		ES_PROVIDES_TYPE_NAME(Delaunay3d)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_Delaunay3d() : ReferenceObject_t(E_Delaunay3d::getTypeObject()) {}
		virtual ~E_Delaunay3d() = default;

};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::Triangulation::E_Delaunay3d, MinSG::Triangulation::Delaunay3d<E_MinSG::Triangulation::ObjRefPoint3>*, &(**eObj))

#endif // _E_MinSG_Triangulation_E_Delaunay3d_H_
#endif // MINSG_EXT_TRIANGULATION
