/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_MULTIALGORENDERING
#include <MinSG/Ext/MultiAlgoRendering/Dependencies.h>

#ifndef _E_MinSG_E_SampleContext_H_
#define _E_MinSG_E_SampleContext_H_

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/MultiAlgoRendering/SampleContext.h>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG{
	namespace E_MAR{

/*!	
	E_SampleContext ---|> EScript::ReferenceObject < Util::Reference < MinSG::MAR::SampleContext > > ---|> Object
		|
		--------------> MinSG::MAR::SampleContext		
*/
class E_SampleContext : public EScript::ReferenceObject<Util::Reference<MinSG::MAR::SampleContext> > {
		ES_PROVIDES_TYPE_NAME(SampleContext)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);
		
		const MinSG::MAR::SampleContext * operator*()const	{	return static_cast<const MinSG::MAR::SampleContext*>(ref().get());	}
		MinSG::MAR::SampleContext * operator*()				{	return static_cast<MinSG::MAR::SampleContext*>(ref().get());	}

		E_SampleContext(const Util::Reference<MinSG::MAR::SampleContext> & _obj) : ReferenceObject_t(_obj, E_SampleContext::getTypeObject()) {}
		virtual ~E_SampleContext() = default;
};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_MAR::E_SampleContext, MinSG::MAR::SampleContext *, **eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::MAR::SampleContext *, E_MinSG::E_MAR::E_SampleContext,  new E_MinSG::E_MAR::E_SampleContext(obj))

#endif // _E_MinSG_E_SampleContext_H_
#endif // MINSG_EXT_MULTIALGORENDERING
