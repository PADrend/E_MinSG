/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifdef MINSG_EXT_IMAGECOMPARE

#include "E_AbstractImageComparator.h"
#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <MinSG/Ext/ImageCompare/AbstractImageComparator.h>
#include <MinSG/Ext/ImageCompare/SimilarPixelCounter.h>
#include <Util/References.h>
#include <Rendering/Texture/Texture.h>

#include <E_Rendering/E_RenderingContext.h>
#include <E_Rendering/Texture/E_Texture.h>

namespace E_MinSG {

using namespace EScript;

EScript::Type * E_AbstractImageComparator::getTypeObject() {
	// E_AbstractImageComparator ----|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

void E_AbstractImageComparator::init(EScript::Namespace & lib) {
	declareConstant(&lib, getClassName(), getTypeObject());

	//! [ESMF] [Number, void] ImageComparator.compare(RenderingContext, Texture inA, Texture inB, Texture out)
	ES_MFUNCTION_DECLARE( getTypeObject(),E_AbstractImageComparator, "compare", 3, 4, {
			Rendering::RenderingContext & context = parameter[0].to<Rendering::RenderingContext&>(runtime);
			Util::Reference<Rendering::Texture> inA = parameter[1].to<Rendering::Texture*>(runtime);
			Util::Reference<Rendering::Texture> inB = parameter[2].to<Rendering::Texture*>(runtime);
			Util::Reference<Rendering::Texture> out;
			if(parameter.count() == 4)
				out = parameter[3].to<Rendering::Texture*>(runtime);
			double quality = 0;
			if((**self)->compare(context, inA.get(), inB.get(), quality, out.get()))
				return Number::create(quality);
			else
				return EScript::create(nullptr); });

	// SimilarPixelCounter
	{
		// E_SimilarPixelCounter ---|> E_AbstractImageComparator ----|> Object
		static EScript::ERef<EScript::Type> comparatorTypeObject = new EScript::Type(E_AbstractImageComparator::getTypeObject());
		declareConstant(&lib, "SimilarPixelCounter", comparatorTypeObject.get());

		//! [ESF] ImageComparator new SimilarPixelCounter()
		ES_CTOR(comparatorTypeObject.get(), 0, 0,
				new E_AbstractImageComparator(new MinSG::ImageCompare::SimilarPixelCounter, comparatorTypeObject.get()))
	}
}

E_AbstractImageComparator::~E_AbstractImageComparator() {
}

}

#endif /* MINSG_EXT_IMAGECOMPARE */
