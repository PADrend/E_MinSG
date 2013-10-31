/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/


#ifdef MINSG_EXT_MULTIALGORENDERING
#include <MinSG/Ext/MultiAlgoRendering/Dependencies.h>

#ifndef E_ALGOSELECTOR_H
#define E_ALGOSELECTOR_H

#include "../../Core/States/E_State.h"
#include <MinSG/Ext/MultiAlgoRendering/AlgoSelector.h>

namespace E_MinSG{
	namespace E_MAR{

/**
	E_AlgoSelector ---|> E_State ---|> ReferenceObject < Util::Reference < MinSG::State > >
		|
		------> MinSG::MAR::AlgoSelector ---|> MinSG::State
 */
class E_AlgoSelector : public E_State{
	ES_PROVIDES_TYPE_NAME(AlgoSelector)

	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

		static EScript::Type* typeObject;
		static void init(EScript::Namespace & lib);

		virtual ~E_AlgoSelector() = default;
		
		static EScript::Type * getTypeObject();

		const MinSG::MAR::AlgoSelector * operator*()const	{	return static_cast<const MinSG::MAR::AlgoSelector*>(ref().get());	}
		MinSG::MAR::AlgoSelector * operator*()				{	return static_cast<MinSG::MAR::AlgoSelector*>(ref().get());	}

	protected:
		E_AlgoSelector(MinSG::MAR::AlgoSelector * c, EScript::Type * type=nullptr):E_State(c,type?type:getTypeObject()){}
};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_MAR::E_AlgoSelector, MinSG::MAR::AlgoSelector *, **eObj)

namespace EScript {// ES_CONV_EOBJ_TO_OBJ and ES_CONV_OBJ_TO_EOBJ can not be used for this stuff
template<> inline MinSG::MAR::AlgoSelector::INTERPOLATION_MODE
convertTo<MinSG::MAR::AlgoSelector::INTERPOLATION_MODE>(Runtime & runtime,ObjPtr obj){
        return static_cast<MinSG::MAR::AlgoSelector::INTERPOLATION_MODE>(obj.to<MinSG::MAR::AlgoSelector::INTERPOLATION_MODE_t>(runtime));
}
Object * create(MinSG::MAR::AlgoSelector::INTERPOLATION_MODE obj);

template<> inline MinSG::MAR::AlgoSelector::REGULATION_MODE
convertTo<MinSG::MAR::AlgoSelector::REGULATION_MODE>(Runtime & runtime,ObjPtr obj){
        return static_cast<MinSG::MAR::AlgoSelector::REGULATION_MODE>(obj.to<MinSG::MAR::AlgoSelector::REGULATION_MODE_t>(runtime));
}
Object * create(MinSG::MAR::AlgoSelector::REGULATION_MODE obj);
}
#endif // E_ALGOSELECTOR_H
#endif // MINSG_EXT_MULTIALGORENDERING
