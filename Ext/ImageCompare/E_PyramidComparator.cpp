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

#include "E_PyramidComparator.h"
#include "E_SSIMComparator.h"
#include "E_AverageComparator.h"
#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <EScript/EScript.h>

#include <Util/Macros.h>

using namespace EScript;

namespace E_MinSG {

//! (static)
EScript::Type * E_PyramidComparator::getTypeObject() {
	// E_PyramidComparator ---|>E_AbstractOnGpuComparator ---|> E_AbstractImageComparator ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractOnGpuComparator::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_PyramidComparator::init(EScript::Namespace & lib) {

	EScript::Type * typeObject = E_PyramidComparator::getTypeObject();

	declareConstant(&lib, getClassName(), typeObject);

	//! [ESF] PyramidComparator new PyramidComparator()
	ES_CTOR(typeObject, 0, 0, new E_PyramidComparator(new MinSG::ImageCompare::PyramidComparator))

	ES_MFUNCTION_DECLARE(typeObject, E_PyramidComparator, "getInternalComparator", 0, 0, {
			MinSG::ImageCompare::AbstractOnGpuComparator * comp = (**self)->getInternalComparator();
			MinSG::ImageCompare::SSIMComparator *ssim = dynamic_cast<MinSG::ImageCompare::SSIMComparator*>(comp);
			if(ssim)
				return new E_SSIMComparator(ssim);
			MinSG::ImageCompare::AverageComparator *avg = dynamic_cast<MinSG::ImageCompare::AverageComparator*>(comp);
			if(avg)
				return new E_AverageComparator(avg);

			WARN("internal comparator of unknown type, please update escript binding");
			return EScript::create(nullptr);
	})

	//! [ESMF] void PyramidComparator.setInternalComparator(AbstractOnGpuComparator)
	ESMF_DECLARE(typeObject, E_PyramidComparator, "setInternalComparator", 1, 1,
			( (**self)->setInternalComparator(**EScript::assertType<E_AbstractOnGpuComparator>(runtime, parameter[0])), EScript::create(nullptr)))

	//! [ESMF] void PyramidComparator.setMinimalTestSize(Number sideLength)
	ESMF_DECLARE(typeObject, E_PyramidComparator, "setMinimalTestSize", 1, 1, ( (**self)->setMinimalTestSize(parameter[0].toUInt()), EScript::create(nullptr)))

	//! [ESMF] Number PyramidComparator.getMinimalTestSize()
	ESMF_DECLARE(typeObject, E_PyramidComparator, "getMinimalTestSize", 0, 0, Number::create((**self)->getMinimalTestSize()))
}

MinSG::ImageCompare::PyramidComparator * E_PyramidComparator::operator*() {
	return static_cast<MinSG::ImageCompare::PyramidComparator *>(E_AbstractImageComparator::ref().get());
}
}
#endif // MINSG_EXT_IMAGECOMPARE
