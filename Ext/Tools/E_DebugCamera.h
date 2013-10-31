/*
	This file is part of the E_MinSG library.
	Copyright (C) 2013 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef _E_MinSG_E_DebugCamera_H_
#define _E_MinSG_E_DebugCamera_H_

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/Tools/DebugCamera.h>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG{

/*!	EScript wrapper class for MinSG::DebugCamera.	

		E_DebugCamera ---|> EScript::ReferenceObject<Util::Reference<MinSG::DebugCamera> >
			|
			--------------> MinSG::DebugCamera		*/
class E_DebugCamera : public EScript::ReferenceObject<Util::Reference<MinSG::DebugCamera> > {
		ES_PROVIDES_TYPE_NAME(DebugCamera)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_DebugCamera(Util::Reference<MinSG::DebugCamera> _obj) : 
				ReferenceObject_t(_obj, E_DebugCamera::getTypeObject()) {}
        virtual ~E_DebugCamera() {}

};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_DebugCamera, MinSG::DebugCamera *, 	(**eObj).get())
ES_CONV_OBJ_TO_EOBJ(MinSG::DebugCamera*,	E_MinSG::E_DebugCamera, obj ? new E_MinSG::E_DebugCamera(obj) : nullptr)

#endif // _E_MinSG_E_DebugCamera_H_
