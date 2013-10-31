/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_MIRRORSTATE_H_
#define E_MIRRORSTATE_H_

#include "../../Core/States/E_State.h"
#include <MinSG/Ext/States/MirrorState.h>
#include <MinSG/Core/States/State.h>
#include <Util/References.h>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG {

//! [E_MirrorState] ---|> [E_State]
class E_MirrorState : public E_State {
	ES_PROVIDES_TYPE_NAME(MirrorState)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		virtual ~E_MirrorState() {
		}

		const MinSG::MirrorState * operator*()const		{	return static_cast<const MinSG::MirrorState*>(ref().get());	}
		MinSG::MirrorState * operator*()				{	return static_cast<MinSG::MirrorState*>(ref().get());	}

	protected:
		E_MirrorState(MinSG::MirrorState * gNode, EScript::Type * type=nullptr)  : E_State(gNode, type ? type : getTypeObject()) {
		}
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_MirrorState, MinSG::MirrorState *, **eObj)

#endif /* E_MIRRORSTATE_H_ */
