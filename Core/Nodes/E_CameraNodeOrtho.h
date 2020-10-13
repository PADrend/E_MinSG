/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_CAMERANODEORTHO_H
#define E_CAMERANODEORTHO_H

#include "E_AbstractCameraNode.h"
#include <MinSG/Core/Nodes/CameraNodeOrtho.h>

namespace E_MinSG{

/**
 *  [E_CameraNodeOrtho] ---|> [E_AbstractCameraNode] ---|> [E_Node]
 */
class E_CameraNodeOrtho : public E_AbstractCameraNode {
	ES_PROVIDES_TYPE_NAME(CameraNodeOrtho)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// ---
		EMINSGAPI static EScript::Type * getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		virtual ~E_CameraNodeOrtho() {}

		const MinSG::CameraNodeOrtho * operator*()const		{	return static_cast<const MinSG::CameraNodeOrtho*>(ref().get());	}
		MinSG::CameraNodeOrtho * operator*()				{	return static_cast<MinSG::CameraNodeOrtho*>(ref().get());	}

	protected:
		E_CameraNodeOrtho(MinSG::CameraNodeOrtho * c,EScript::Type* type=nullptr) : E_AbstractCameraNode(c,type?type:getTypeObject()){}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_CameraNodeOrtho,		MinSG::CameraNodeOrtho*,		**eObj)	

#endif // E_CAMERANODEORTHO_H
