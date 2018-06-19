/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2017-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#ifndef E_MINSG_EXT_BLUESURFELS_SURFEL_SAMPLER_H_
#define E_MINSG_EXT_BLUESURFELS_SURFEL_SAMPLER_H_

#include <MinSG/Ext/BlueSurfels/Samplers/AbstractSurfelSampler.h>

#include <E_Util/E_ObjectFactory.h>

#include <EScript/Objects/ExtReferenceObject.h>
#include <EScript/Objects/Type.h>

namespace E_MinSG {
namespace BlueSurfels {

class E_AbstractSurfelSampler : public EScript::ExtReferenceObject<Util::Reference<MinSG::BlueSurfels::AbstractSurfelSampler>> {
		ES_PROVIDES_TYPE_NAME(AbstractSurfelSampler)  
		static E_Util::E_ObjectFactory<MinSG::BlueSurfels::AbstractSurfelSampler, E_AbstractSurfelSampler> factorySystem;
	protected:
		template<class Type, class E_Type>
		static void addFactory() {
			factorySystem.registerType(Type::getClassId(), Util::PolymorphicWrapperCreator<MinSG::BlueSurfels::AbstractSurfelSampler, Type, E_Type>());
		}
	public:
		static E_AbstractSurfelSampler * create(MinSG::BlueSurfels::AbstractSurfelSampler * obj) {
			return obj ? factorySystem.create(obj->getTypeId(), obj) : nullptr;
		}
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
	public:  
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);
	  
	  const MinSG::BlueSurfels::AbstractSurfelSampler * operator*() const { return static_cast<const MinSG::BlueSurfels::AbstractSurfelSampler*>(ref().get()); }
	  MinSG::BlueSurfels::AbstractSurfelSampler * operator*() { return static_cast<MinSG::BlueSurfels::AbstractSurfelSampler*>(ref().get()); }
	protected:
		E_AbstractSurfelSampler(MinSG::BlueSurfels::AbstractSurfelSampler * obj, EScript::Type * type = nullptr) 
			: ExtReferenceObject_t(Util::Reference<MinSG::BlueSurfels::AbstractSurfelSampler>(obj), type ? type : getTypeObject()) { }
	public:
		virtual ~E_AbstractSurfelSampler() = default;
};

} /* BlueSurfels */
} /* E_MinSG */

ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_AbstractSurfelSampler, MinSG::BlueSurfels::AbstractSurfelSampler*, **eObj)
ES_CONV_OBJ_TO_EOBJ(MinSG::BlueSurfels::AbstractSurfelSampler*, E_MinSG::BlueSurfels::E_AbstractSurfelSampler, E_MinSG::BlueSurfels::E_AbstractSurfelSampler::create(obj))
ES_CONV_OBJ_TO_EOBJ(Util::Reference<MinSG::BlueSurfels::AbstractSurfelSampler>, E_MinSG::BlueSurfels::E_AbstractSurfelSampler, E_MinSG::BlueSurfels::E_AbstractSurfelSampler::create(obj.get()))

#endif /* end of include guard: E_MINSG_EXT_BLUESURFELS_SURFEL_SAMPLER_H_ */

#endif // MINSG_EXT_BLUE_SURFELS