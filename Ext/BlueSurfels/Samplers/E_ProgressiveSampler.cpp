/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2014 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2016-2018 Sascha Brandt <sascha@brandt.graphics>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#include "E_ProgressiveSampler.h"

#include <E_Util/E_Utils.h>

#include <EScript/EScript.h>

namespace E_MinSG {
namespace BlueSurfels {
using namespace MinSG::BlueSurfels;

//! (static)
EScript::Type * E_ProgressiveSampler::getTypeObject() {
	// E_ProgressiveSampler ---|> E_AbstractSurfelSampler ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractSurfelSampler::getTypeObject());
	return typeObject.get();
}

//! ProgressiveSampler
void E_ProgressiveSampler::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	initPrintableName(typeObject,getClassName());
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<ProgressiveSampler,E_ProgressiveSampler>();

	//! [ESMF] new ProgressiveSampler
	ES_CTOR(typeObject, 0, 0, new ProgressiveSampler)
  
	ES_MGETSET(ProgressiveSampler, uint32_t, SamplesPerRound)
}

} /* BlueSurfels */
} /* MinSG */
#endif // MINSG_EXT_BLUE_SURFELS