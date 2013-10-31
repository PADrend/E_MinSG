/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_CAMERANODE_H
#define E_CAMERANODE_H

#include "E_AbstractCameraNode.h"
#include <MinSG/Core/Nodes/CameraNode.h>

namespace E_MinSG{

/**
 *  [E_CameraNode] ---|> [E_AbstractCameraNode] ---|> [E_Node]
 */
class E_CameraNode : public E_AbstractCameraNode {
	ES_PROVIDES_TYPE_NAME(CameraNode)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// ---
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_CameraNode(){}

		const MinSG::CameraNode * operator*()const	{	return static_cast<const MinSG::CameraNode*>(ref().get());	}
		MinSG::CameraNode * operator*()				{	return static_cast<MinSG::CameraNode*>(ref().get());	}

	protected:
		E_CameraNode(MinSG::CameraNode * c,EScript::Type* type=nullptr) : E_AbstractCameraNode(c,type?type:getTypeObject()) {}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_CameraNode,		MinSG::CameraNode*,		**eObj)	

#endif // E_CAMERANODE_H
