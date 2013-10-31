/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_MULTIALGORENDERING
#include <MinSG/Ext/MultiAlgoRendering/Dependencies.h>

#ifndef _E_MinSG_E_SampleStorage_H_
#define _E_MinSG_E_SampleStorage_H_

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/MultiAlgoRendering/SampleStorage.h>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG{
	namespace E_MAR{

/*!	
	E_SampleStorage ---|> EScript::ReferenceObject < Util::Reference < MinSG::MAR::SampleStorage > > ---|> Object
		|
		--------------> MinSG::MAR::SampleStorage		
*/
class E_SampleStorage : public EScript::ReferenceObject<Util::Reference<MinSG::MAR::SampleStorage> > {
		ES_PROVIDES_TYPE_NAME(SampleStorage)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);
		
		const MinSG::MAR::SampleStorage * operator*()const	{	return static_cast<const MinSG::MAR::SampleStorage*>(ref().get());	}
		MinSG::MAR::SampleStorage * operator*()				{	return static_cast<MinSG::MAR::SampleStorage*>(ref().get());	}

		E_SampleStorage(const Util::Reference<MinSG::MAR::SampleStorage> & _obj) : ReferenceObject_t(_obj, E_SampleStorage::getTypeObject()) {}
		virtual ~E_SampleStorage() = default;

};

/*!
	E_SampleResult ---|> EScript::ReferenceObject < Util::Reference < MinSG::MAR::SampleResult > > ---|> Object
		|
		--------------> MinSG::MAR::SampleResult
*/
class E_SampleResult : public EScript::ReferenceObject<Util::Reference<MinSG::MAR::SampleResult> > {
		ES_PROVIDES_TYPE_NAME(SampleResult)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);
		
		const MinSG::MAR::SampleResult * operator*()const	{	return static_cast<const MinSG::MAR::SampleResult*>(ref().get());	}
		MinSG::MAR::SampleResult * operator*()				{	return static_cast<MinSG::MAR::SampleResult*>(ref().get());	}

		E_SampleResult(const Util::Reference<MinSG::MAR::SampleResult> & _obj) : ReferenceObject_t(_obj, E_SampleResult::getTypeObject()) {}
		virtual ~E_SampleResult() = default;

};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_MAR::E_SampleStorage, MinSG::MAR::SampleStorage *, **eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::MAR::SampleStorage *, E_MinSG::E_MAR::E_SampleStorage,  new E_MinSG::E_MAR::E_SampleStorage(obj))

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_MAR::E_SampleResult, MinSG::MAR::SampleResult *, **eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::MAR::SampleResult *, E_MinSG::E_MAR::E_SampleResult,  new E_MinSG::E_MAR::E_SampleResult(obj))

#endif // _E_MinSG_E_SampleStorage_H_
#endif // MINSG_EXT_MULTIALGORENDERING
