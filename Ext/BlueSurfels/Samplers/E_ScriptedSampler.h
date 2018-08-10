/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#ifndef E_MINSG_EXT_SCRIPTED_SAMPLER_H_
#define E_MINSG_EXT_SCRIPTED_SAMPLER_H_

#include "E_AbstractSurfelSampler.h"

namespace E_MinSG {
namespace BlueSurfels {

class ScriptedSampler : public MinSG::BlueSurfels::AbstractSurfelSampler {
	PROVIDES_TYPE_NAME(ScriptedSampler)
public:
  ScriptedSampler(EScript::EPtr<EScript::Type> type, EScript::Runtime & _runtime) :
  		MinSG::BlueSurfels::AbstractSurfelSampler(), eType(type), runtime(_runtime) { }
  virtual Rendering::Mesh* sampleSurfels(Rendering::Mesh* sourceMesh);
	EScript::EPtr<EScript::Type> getEType() { return eType; }
private:
  EScript::ERef<EScript::Type> eType;
  EScript::Runtime & runtime;
};

class E_ScriptedSampler : public E_AbstractSurfelSampler {
  ES_PROVIDES_TYPE_NAME(ScriptedSampler)
	public:
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
		
	  static EScript::Type * getTypeObject();
	  static void init(EScript::Namespace & lib);

	  E_ScriptedSampler(ScriptedSampler* obj) : E_AbstractSurfelSampler(obj, obj->getEType().get()) {}
	  virtual ~E_ScriptedSampler() = default;
	
		const ScriptedSampler * operator*() const { return static_cast<const ScriptedSampler*>(ref().get()); }
		ScriptedSampler * operator*() { return static_cast<ScriptedSampler*>(ref().get()); }
};	

} /* BlueSurfels */
} /* MinSG */

ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_ScriptedSampler, E_MinSG::BlueSurfels::ScriptedSampler*, **eObj)

#endif /* end of include guard: E_MINSG_EXT_SCRIPTED_SAMPLER_H_ */
#endif // MINSG_EXT_BLUE_SURFELS