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

#include "E_AbstractOnGpuComparator.h"
#include <EScript/Utils/DeprecatedMacros.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <MinSG/Ext/ImageCompare/AbstractOnGpuComparator.h>
#include <MinSG/Ext/ImageCompare/SSIMComparator.h>
#include <MinSG/Ext/ImageCompare/AverageComparator.h>
#include <MinSG/Ext/ImageCompare/PyramidComparator.h>

#include <E_Rendering/E_FBO.h>

namespace E_MinSG {

using namespace EScript;

EScript::Type * E_AbstractOnGpuComparator::getTypeObject() {
	// E_AbstractOnGpuComparator ----|> E_AbstractImageComparator
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractImageComparator::getTypeObject());
	return typeObject.get();
}

void E_AbstractOnGpuComparator::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), getTypeObject());

	//! [ESMF] Number AbstractOnGpuComparator.getFilterSize()
	ESMF_DECLARE(typeObject, E_AbstractOnGpuComparator, "getFilterSize", 0, 0, EScript::Number::create((**self)->getFilterSize()));

	//! [ESMF] self AbstractOnGpuComparator.setFilterSize(Bool)
	ESMF_DECLARE(typeObject, E_AbstractOnGpuComparator, "setFilterSize", 1, 1, ((**self)->setFilterSize(parameter[0].toInt()), self));

	//! [ESMF] self AbstractOnGpuComparator.setFBO(FBO)
	ESMF_DECLARE(typeObject, E_AbstractOnGpuComparator, "setFBO", 1, 1,
			((**self)->setFBO(parameter[0].to<Rendering::FBO*>(runtime)), self));

	//! [ESMF] Number AbstractOnGpuComparator.getTextureDownloadSize()
	ESMF_DECLARE(typeObject, E_AbstractOnGpuComparator, "getTextureDownloadSize", 0, 0, EScript::Number::create((**self)->getTextureDownloadSize()));

	//! [ESMF] self AbstractOnGpuComparator.setTextureDownloadSize(sideLength)
	ESMF_DECLARE(typeObject, E_AbstractOnGpuComparator, "setTextureDownloadSize", 1, 1,
			((**self)->setTextureDownloadSize(parameter[0].toUInt()), self));

	ESMF_DECLARE(typeObject, E_AbstractOnGpuComparator, "setFilterType", 1, 1, ((**self)->setFilterType(static_cast<MinSG::ImageCompare::AbstractOnGpuComparator::FilterType>(parameter[0].toInt())), self))

	ESMF_DECLARE(typeObject, E_AbstractOnGpuComparator, "getFilterType", 0, 0, Number::create((**self)->getFilterType()))

	declareConstant(typeObject, "GAUSS", Number::create(MinSG::ImageCompare::AbstractOnGpuComparator::GAUSS));
	declareConstant(typeObject, "BOX", Number::create(MinSG::ImageCompare::AbstractOnGpuComparator::BOX));
}

E_AbstractOnGpuComparator::E_AbstractOnGpuComparator(MinSG::ImageCompare::AbstractOnGpuComparator * comparator, EScript::Type * type) :
		E_AbstractImageComparator(comparator, type) {
}

E_AbstractOnGpuComparator::~E_AbstractOnGpuComparator() {
}

MinSG::ImageCompare::AbstractOnGpuComparator * E_AbstractOnGpuComparator::operator*() {
	return static_cast<MinSG::ImageCompare::AbstractOnGpuComparator *>(E_AbstractImageComparator::ref().get());
}

}

#endif /* MINSG_EXT_IMAGECOMPARE */
