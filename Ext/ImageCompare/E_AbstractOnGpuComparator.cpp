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
#include <MinSG/Ext/ImageCompare/AbstractOnGpuComparator.h>
#include <MinSG/Ext/ImageCompare/SSIMComparator.h>
#include <MinSG/Ext/ImageCompare/AverageComparator.h>
#include <MinSG/Ext/ImageCompare/PyramidComparator.h>

#include <E_Rendering/E_FBO.h>
#include <E_Util/IO/E_FileLocator.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_MinSG {

using namespace EScript;

EScript::Type * E_AbstractOnGpuComparator::getTypeObject() {
	// E_AbstractOnGpuComparator ----|> E_AbstractImageComparator
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractImageComparator::getTypeObject());
	return typeObject.get();
}

void E_AbstractOnGpuComparator::init(EScript::Namespace & lib) {
	using namespace MinSG::ImageCompare;
	
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), getTypeObject());

	//! [ESMF] Number AbstractOnGpuComparator.getFilterSize()
	ES_MFUN(typeObject, const AbstractOnGpuComparator, "getFilterSize", 0, 0, EScript::create(thisObj->getFilterSize()))

	//! [ESMF] self AbstractOnGpuComparator.setFilterSize(Bool)
	ES_MFUN(typeObject, AbstractOnGpuComparator, "setFilterSize", 1, 1, (thisObj->setFilterSize(parameter[0].toInt()), thisEObj))

	//! [ESMF] self AbstractOnGpuComparator.setFBO(FBO)
	ES_MFUN(typeObject, AbstractOnGpuComparator, "setFBO", 1, 1,
			(thisObj->setFBO(parameter[0].to<Rendering::FBO*>(rt)), thisEObj))

	//! [ESMF] Number AbstractOnGpuComparator.getTextureDownloadSize()
	ES_MFUN(typeObject, AbstractOnGpuComparator, "getTextureDownloadSize", 0, 0, EScript::create(thisObj->getTextureDownloadSize()))

	//! [ESMF] self AbstractOnGpuComparator.setTextureDownloadSize(sideLength)
	ES_MFUN(typeObject, AbstractOnGpuComparator, "setTextureDownloadSize", 1, 1,
			(thisObj->setTextureDownloadSize(parameter[0].toUInt()), thisEObj))

	ES_MFUN(typeObject, AbstractOnGpuComparator, "setFilterType", 1, 1, (thisObj->setFilterType(static_cast<MinSG::ImageCompare::AbstractOnGpuComparator::FilterType>(parameter[0].toInt())), thisEObj))

	ES_MFUN(typeObject, const AbstractOnGpuComparator, "getFilterType", 0, 0, EScript::create(static_cast<uint32_t>(thisObj->getFilterType())))
	
	
	//! void AbstractOnGpuComparator.initShaderFileLocator(Util.FileLocator)
	ES_FUN(typeObject,  "initShaderFileLocator", 1, 1, (AbstractOnGpuComparator::initShaderFileLocator(*parameter[0].to<Util::FileLocator*>(rt)),EScript::create(nullptr)))

	declareConstant(typeObject, "GAUSS", EScript::create(static_cast<uint32_t>(MinSG::ImageCompare::AbstractOnGpuComparator::GAUSS)));
	declareConstant(typeObject, "BOX", EScript::create(static_cast<uint32_t>(MinSG::ImageCompare::AbstractOnGpuComparator::BOX)));
}


}

#endif /* MINSG_EXT_IMAGECOMPARE */
