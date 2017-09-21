/*
	This file is part of the MinSG library extension PathTracing.
	Copyright (C) 2017 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_PATHTRACING

#ifndef E_MINSG_E_PATHTRACER_H_
#define E_MINSG_E_PATHTRACER_H_

#include <EScript/Objects/ExtReferenceObject.h>
#include <MinSG/Ext/PathTracing/PathTracer.h>
#include <MinSG/Ext/PathTracing/Light.h>


namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG{


/*!	EScript wrapper class for MinSG::PathTracer

		E_PathTracer ---|> EScript::ExtReferenceObject<MinSG::PathTracer>
			|
			--------------> MinSG::PathTracer		*/
class E_PathTracer : public EScript::ExtReferenceObject<std::unique_ptr<MinSG::PathTracing::PathTracer>, EScript::Policies::SameEObjects_ComparePolicy> {
		ES_PROVIDES_TYPE_NAME(PathTracer)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_PathTracer(MinSG::PathTracing::PathTracer* pathtracer, EScript::Type * type=nullptr) : 
				ExtReferenceObject(type ? type : E_PathTracer::getTypeObject(), pathtracer) {}
				
		virtual ~E_PathTracer() {}
		
		const MinSG::PathTracing::PathTracer * operator*()const	{	return ref().get();	}
		MinSG::PathTracing::PathTracer * operator*()				{	return ref().get();	}
};
}


ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_PathTracer,	MinSG::PathTracing::PathTracer*, **eObj)

#endif // E_MINSG_E_PATHTRACER_H_
#endif // MINSG_EXT_PATHTRACING

