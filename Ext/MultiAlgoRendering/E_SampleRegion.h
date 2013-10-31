/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_MULTIALGORENDERING
#include <MinSG/Ext/MultiAlgoRendering/Dependencies.h>

#ifndef _E_MinSG_E_SampleRegion_H_
#define _E_MinSG_E_SampleRegion_H_

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/MultiAlgoRendering/SampleRegion.h>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG{
	namespace E_MAR{

/*!
	E_SampleRegion ---|> EScript::ReferenceObject < Util::Reference < MinSG::MAR::SampleRegion> > ---|> Object
		|
		--------------> MinSG::MAR::SampleRegion
*/
class E_SampleRegion : public EScript::ReferenceObject<Util::Reference<MinSG::MAR::SampleRegion> > {
		ES_PROVIDES_TYPE_NAME(SampleRegion)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);
		
		const MinSG::MAR::SampleRegion * operator*()const	{	return static_cast<const MinSG::MAR::SampleRegion*>(ref().get());	}
		MinSG::MAR::SampleRegion * operator*()				{	return static_cast<MinSG::MAR::SampleRegion*>(ref().get());	}

		E_SampleRegion(const Util::Reference<MinSG::MAR::SampleRegion> & _obj) : ReferenceObject_t(_obj, E_SampleRegion::getTypeObject()) {}
		virtual ~E_SampleRegion() = default;

};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_MAR::E_SampleRegion, MinSG::MAR::SampleRegion *, **eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::MAR::SampleRegion *, E_MinSG::E_MAR::E_SampleRegion,  new E_MinSG::E_MAR::E_SampleRegion(obj))
ES_CONV_OBJ_TO_EOBJ(const Util::Reference<MinSG::MAR::SampleRegion>, E_MinSG::E_MAR::E_SampleRegion,  new E_MinSG::E_MAR::E_SampleRegion(obj.get()))

#endif // _E_MinSG_E_SampleRegion_H_
#endif // MINSG_EXT_MULTIALGORENDERING
