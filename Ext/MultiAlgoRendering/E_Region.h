/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/


#ifdef MINSG_EXT_MULTIALGORENDERING
#include <MinSG/Ext/MultiAlgoRendering/Dependencies.h>

#ifndef E_REGION_H
#define E_REGION_H

#include <MinSG/Ext/MultiAlgoRendering/Region.h>
#include <EScript/Objects/ReferenceObject.h>

namespace E_MinSG{
	namespace E_MAR{

/**
	E_Region ---|> ReferenceObject < Util::Reference < MinSG::MAR::Region > > ---|> Object
		|
		------> MinSG::MAR::Region
 */
class E_Region : public EScript::ReferenceObject<Util::Reference<MinSG::MAR::Region> > {
	ES_PROVIDES_TYPE_NAME(Region)
	public:
		virtual ~E_Region() = default;
		
		static void init(EScript::Namespace & lib);
		static EScript::Type * getTypeObject();
		
		const MinSG::MAR::Region * operator*()const	{	return static_cast<const MinSG::MAR::Region*>(ref().get());	}
		MinSG::MAR::Region * operator*()				{	return static_cast<MinSG::MAR::Region*>(ref().get());	}

		E_Region(MinSG::MAR::Region * _region, EScript::Type* type=nullptr):EScript::ReferenceObject<Util::Reference<MinSG::MAR::Region> >(_region, type?type:getTypeObject()){}
};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_MAR::E_Region, MinSG::MAR::Region *, **eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::MAR::Region *, E_MinSG::E_MAR::E_Region,  new E_MinSG::E_MAR::E_Region(obj))
ES_CONV_OBJ_TO_EOBJ(const Util::Reference<MinSG::MAR::Region> &, E_MinSG::E_MAR::E_Region,  new E_MinSG::E_MAR::E_Region(obj.get()))

#endif // E_REGION_H
#endif // MINSG_EXT_MULTIALGORENDERING
