/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/


#ifdef MINSG_EXT_MULTIALGORENDERING
#include <MinSG/Ext/MultiAlgoRendering/Dependencies.h>

#ifndef E_REGIONEVALUATOR_H
#define E_REGIONEVALUATOR_H

#include <MinSG/Ext/MultiAlgoRendering/RegionEvaluator.h>
#include <EScript/Objects/ReferenceObject.h>

namespace E_MinSG{
	namespace E_MAR{

/**
	E_RegionEvaluator ---|> ReferenceObject < Util::Reference < MinSG::MAR::RegionEvaluator > > ---|> Object
		|
		------> MinSG::MAR::RegionEvaluator
 */
class E_RegionEvaluator : public EScript::ReferenceObject<Util::Reference<MinSG::MAR::RegionEvaluator>> {
	ES_PROVIDES_TYPE_NAME(RegionEvaluator)
	public:
		
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);
		
		const MinSG::MAR::RegionEvaluator * operator*()const	{	return static_cast<const MinSG::MAR::RegionEvaluator*>(ref().get());	}
		MinSG::MAR::RegionEvaluator * operator*()				{	return static_cast<MinSG::MAR::RegionEvaluator*>(ref().get());	}

		E_RegionEvaluator(MinSG::MAR::RegionEvaluator * _region, EScript::Type * type=nullptr) : ReferenceObject_t(_region,type?type:getTypeObject()) {}
		virtual ~E_RegionEvaluator() = default;
};

/**
	E_PolygonDensityEvaluator ---|> E_RegionEvaluator ---|> ReferenceObject < Util::Reference < MinSG::MAR::RegionEvaluator > > ---|> Object
		|
		------> MinSG::MAR::PolygonDensityEvaluator ---|> MinSG::MAR::RegionEvaluator
 */
class E_PolygonDensityEvaluator : public E_RegionEvaluator {
	ES_PROVIDES_TYPE_NAME(PolygonDensityEvaluator)
public:
	static EScript::Type * getTypeObject();
	static void init(EScript::Namespace & lib);
	
	const MinSG::MAR::PolygonDensityEvaluator * operator*()const	{	return static_cast<const MinSG::MAR::PolygonDensityEvaluator*>(ref().get());	}
	MinSG::MAR::PolygonDensityEvaluator * operator*()				{	return static_cast<MinSG::MAR::PolygonDensityEvaluator*>(ref().get());	}
	
	E_PolygonDensityEvaluator(MinSG::MAR::PolygonDensityEvaluator * p, EScript::Type* type=nullptr) : E_RegionEvaluator(p,type?type:getTypeObject()) {}
	virtual ~E_PolygonDensityEvaluator() = default;
};

/**
	E_PolygonCountEvaluator ---|> E_RegionEvaluator ---|> ReferenceObject < Util::Reference < MinSG::MAR::RegionEvaluator > > ---|> Object
		|
		------> MinSG::MAR::PolygonCountEvaluator ---|> MinSG::MAR::RegionEvaluator
 */
class E_PolygonCountEvaluator : public E_RegionEvaluator {
	ES_PROVIDES_TYPE_NAME(PolygonCountEvaluator)
public:
	static EScript::Type * getTypeObject();
	static void init(EScript::Namespace & lib);
	
	const MinSG::MAR::PolygonCountEvaluator * operator*()const	{	return static_cast<const MinSG::MAR::PolygonCountEvaluator*>(ref().get());	}
	MinSG::MAR::PolygonCountEvaluator * operator*()				{	return static_cast<MinSG::MAR::PolygonCountEvaluator*>(ref().get());	}
	
	E_PolygonCountEvaluator(MinSG::MAR::PolygonCountEvaluator * p, EScript::Type* type=nullptr) : E_RegionEvaluator(p,type?type:getTypeObject()) {}
	virtual ~E_PolygonCountEvaluator() = default;
};

/**
	E_RegionSizeEvaluator ---|> E_RegionEvaluator ---|> ReferenceObject < Util::Reference < MinSG::MAR::RegionEvaluator > > ---|> Object
		|
		------> MinSG::MAR::RegionSizeEvaluator ---|> MinSG::MAR::RegionEvaluator
 */
class E_RegionSizeEvaluator : public E_RegionEvaluator {
	ES_PROVIDES_TYPE_NAME(RegionSizeEvaluator)
public:
	static EScript::Type * getTypeObject();
	static void init(EScript::Namespace & lib);
	
	const MinSG::MAR::RegionSizeEvaluator * operator*()const	{	return static_cast<const MinSG::MAR::RegionSizeEvaluator*>(ref().get());	}
	MinSG::MAR::RegionSizeEvaluator * operator*()				{	return static_cast<MinSG::MAR::RegionSizeEvaluator*>(ref().get());	}
	
	E_RegionSizeEvaluator(MinSG::MAR::RegionSizeEvaluator * p, EScript::Type* type=nullptr) : E_RegionEvaluator(p,type?type:getTypeObject()) {}
	virtual ~E_RegionSizeEvaluator() = default;
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_MAR::E_RegionEvaluator, MinSG::MAR::RegionEvaluator *, **eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::MAR::RegionEvaluator *, E_MinSG::E_MAR::E_RegionEvaluator,  new E_MinSG::E_MAR::E_RegionEvaluator(obj))

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_MAR::E_PolygonDensityEvaluator, MinSG::MAR::PolygonDensityEvaluator *, **eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::MAR::PolygonDensityEvaluator *, E_MinSG::E_MAR::E_PolygonDensityEvaluator,  new E_MinSG::E_MAR::E_PolygonDensityEvaluator(obj))

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_MAR::E_PolygonCountEvaluator, MinSG::MAR::PolygonCountEvaluator *, **eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::MAR::PolygonCountEvaluator *, E_MinSG::E_MAR::E_PolygonCountEvaluator,  new E_MinSG::E_MAR::E_PolygonCountEvaluator(obj))

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_MAR::E_RegionSizeEvaluator, MinSG::MAR::RegionSizeEvaluator *, **eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::MAR::RegionSizeEvaluator *, E_MinSG::E_MAR::E_RegionSizeEvaluator,  new E_MinSG::E_MAR::E_RegionSizeEvaluator(obj))

#endif // E_REGIONEVALUATOR_H
#endif // MINSG_EXT_MULTIALGORENDERING
