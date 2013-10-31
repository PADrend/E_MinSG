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
#ifndef __E_KeyFrameAnimationNode_H
#define __E_KeyFrameAnimationNode_H

#include "../../Core/Nodes/E_GeometryNode.h"
#include <MinSG/Ext/KeyFrameAnimation/KeyFrameAnimationNode.h>
#include "../Behaviours/E_KeyFrameAnimationBehaviour.h"
#include <EScript/EScript.h>
#include "../../ELibMinSG.h"
#include <E_Rendering/Mesh/E_Mesh.h>

namespace E_MinSG{

/**
 *   [E_KeyFrameAnimationNode] ---|>  [E_GeometryNode] ---|>  [E_Node] ---|> [Object]
 */
class E_KeyFrameAnimationNode : public E_GeometryNode{
	ES_PROVIDES_TYPE_NAME(KeyFrameAnimationNode)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		// ---
		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_KeyFrameAnimationNode();

		const MinSG::KeyFrameAnimationNode * operator*()const	{	return static_cast<const MinSG::KeyFrameAnimationNode*>(ref().get());	}
		MinSG::KeyFrameAnimationNode * operator*()				{	return static_cast<MinSG::KeyFrameAnimationNode*>(ref().get());	}

		EScript::Map getAnimationData();

		EScript::String getActiveAnimationName();
		EScript::Bool setActiveAnimation(EScript::String name);

		EScript::Number getSpeedFactor();
		EScript::Bool setSpeedFactor(EScript::Number sf);

		EScript::Number getState();
		void setState(EScript::Number s);

		EScript::Number getAnimationposition();
		EScript::Bool setAnimationPosition(EScript::Number value);


	protected:
		E_KeyFrameAnimationNode(MinSG::KeyFrameAnimationNode * gNode,EScript::Type* type=nullptr);
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_KeyFrameAnimationNode, MinSG::KeyFrameAnimationNode *, **eObj)

#endif // __E_KeyFrameAnimationNode_H
