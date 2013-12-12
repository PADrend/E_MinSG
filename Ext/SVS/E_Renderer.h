/*
	This file is part of the E_MinSG library extension SVS.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_SVS

#ifndef E_MINSG_SVS_E_RENDERER_H_
#define E_MINSG_SVS_E_RENDERER_H_

#include "../../Core/States/E_NodeRendererState.h"
#include <MinSG/Ext/SVS/Renderer.h>
#include <string>

namespace EScript {
class Namespace;
class Runtime;
class Type;
}
namespace MinSG {
namespace SVS {
class Renderer;
}
}
namespace E_MinSG {
namespace SVS {

//!	EScript wrapper class for MinSG::SVS::Renderer
class E_Renderer : public E_NodeRendererState {
	protected:
		E_Renderer(MinSG::SVS::Renderer * renderer);
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_Renderer();
		
		const MinSG::SVS::Renderer * operator*()const	{	return static_cast<const MinSG::SVS::Renderer*>(ref().get());	}
		MinSG::SVS::Renderer * operator*()				{	return static_cast<MinSG::SVS::Renderer*>(ref().get());	}
};

}
}

#endif /* E_MINSG_SVS_E_RENDERER_H_ */

#endif /* MINSG_EXT_SVS */
