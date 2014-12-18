/*
	This file is part of the MinSG library extension BlueSurfels.
	Copyright (C) 2012-2013 Claudius J�hn <claudius@uni-paderborn.de>
	Copyright (C) 2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_BLUE_SURFELS

#ifndef E_MINSG_BLUESURFELS_E_STREAMEDSURFELGENERATOR_H_
#define E_MINSG_BLUESURFELS_E_STREAMEDSURFELGENERATOR_H_

#include <EScript/Objects/ExtReferenceObject.h>
#include <MinSG/Ext/BlueSurfels/StreamedSurfelGenerator.h>

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG{
namespace BlueSurfels{


/*!	EScript wrapper class for MinSG::BlueSurfels::SurfelGenerator

		E_StreamedSurfelGenerator ---|> E_SurfelGenerator ---|> EScript::ExtReferenceObject<MinSG::BlueSurfels::StreamedSurfelGenerator>
			|
			--------------> MinSG::BlueSurfels::StreamedSurfelGenerator		*/
class E_StreamedSurfelGenerator : public EScript::ExtReferenceObject<MinSG::BlueSurfels::StreamedSurfelGenerator,EScript::Policies::SameEObjects_ComparePolicy> {
		ES_PROVIDES_TYPE_NAME(StreamedSurfelGenerator)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_StreamedSurfelGenerator(EScript::Type * type=nullptr) :
				ExtReferenceObject_t(MinSG::BlueSurfels::StreamedSurfelGenerator(), type ? type : E_StreamedSurfelGenerator::getTypeObject()) {}

		virtual ~E_StreamedSurfelGenerator() {}

};
}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::BlueSurfels::E_StreamedSurfelGenerator, MinSG::BlueSurfels::StreamedSurfelGenerator*, &(**eObj))

#endif // E_MINSG_BLUESURFELS_E_STREAMEDSURFELGENERATOR_H_
#endif // MINSG_EXT_BLUE_SURFELS

