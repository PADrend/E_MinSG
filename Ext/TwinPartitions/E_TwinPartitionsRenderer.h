/*
	This file is part of the E_MinSG library extension TwinPartitions.
	Copyright (C) 2010-2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_TWIN_PARTITIONS

#ifndef E_TWINPARTITIONSRENDERER_H
#define E_TWINPARTITIONSRENDERER_H

#include "../../Core/States/E_State.h"
#include <MinSG/Ext/TwinPartitions/TwinPartitionsRenderer.h>

namespace E_MinSG {

/**
 *   [E_TwinPartitionsRenderer] ---|> [E_State]
 */
class E_TwinPartitionsRenderer : public E_State {
	ES_PROVIDES_TYPE_NAME(TwinPartitionsRenderer)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		// ---
		static EScript::Type * typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_TwinPartitionsRenderer() {
		}

		const MinSG::TwinPartitions::TwinPartitionsRenderer * operator*() const {
			return static_cast<const MinSG::TwinPartitions::TwinPartitionsRenderer *>(ref().get());
		}
		MinSG::TwinPartitions::TwinPartitionsRenderer * operator*() {
			return static_cast<MinSG::TwinPartitions::TwinPartitionsRenderer *>(ref().get());
		}

	protected:
		E_TwinPartitionsRenderer(MinSG::TwinPartitions::TwinPartitionsRenderer * gNode, EScript::Type * type = nullptr) :
			E_State(gNode, type ? type : typeObject) {
		}
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_TwinPartitionsRenderer, MinSG::TwinPartitions::TwinPartitionsRenderer *, **eObj)

#endif /* E_TWINPARTITIONSRENDERER_H */
#endif /* MINSG_EXT_TWIN_PARTITIONS */
