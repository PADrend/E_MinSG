/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef _E_MinSG_E_RenderParam_H_
#define _E_MinSG_E_RenderParam_H_

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Core/RenderParam.h>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG{

/*!	EScript wrapper class for MinSG::RenderParam.

		E_RenderParam ---|> EScript::ReferenceObject<MinSG::RenderParam>
			|
			--------------> MinSG::RenderParam		*/
class E_RenderParam : public EScript::ReferenceObject<MinSG::RenderParam,EScript::Policies::SameEObjects_ComparePolicy> {
		ES_PROVIDES_TYPE_NAME(RenderParam)
	public:
		EMINSGAPI static EScript::Type * getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		E_RenderParam() :
				ReferenceObject_t(MinSG::RenderParam(), E_RenderParam::getTypeObject()) {}
		E_RenderParam(const MinSG::RenderParam & _obj) :
				ReferenceObject_t(_obj, E_RenderParam::getTypeObject()) {}
		virtual ~E_RenderParam() {}

		const MinSG::RenderParam & operator*()const	{	return ref();	}
		MinSG::RenderParam & operator*()			{	return ref();	}
		
		/// ---|> [Object]
		virtual E_RenderParam * clone()const		{	return new E_RenderParam(ref());	}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_RenderParam,		MinSG::RenderParam&,		**eObj)	
ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_RenderParam,		MinSG::RenderParam*,		&(**eObj))

#endif // _E_MinSG_E_RenderParam_H_
