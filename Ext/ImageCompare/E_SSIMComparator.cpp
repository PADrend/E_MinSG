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

#include "E_SSIMComparator.h"
#include <EScript/Basics.h>

namespace E_MinSG{

//! (static)
EScript::Type * E_SSIMComparator::getTypeObject() {
	// E_ASSIMComparator ---|>E_AbstractOnGpuComparator ---|> E_AbstractImageComparator ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractOnGpuComparator::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_SSIMComparator::init(EScript::Namespace & lib) {

	EScript::Type * typeObject = E_SSIMComparator::getTypeObject();

	declareConstant(&lib,getClassName(),typeObject);

	//! [ESF] SSIMComparator new SSIMComparator()
	ES_CTOR(typeObject, 0, 0, new E_SSIMComparator(new MinSG::ImageCompare::SSIMComparator))
}

MinSG::ImageCompare::SSIMComparator * E_SSIMComparator::ref() {
	return static_cast<MinSG::ImageCompare::SSIMComparator *>(E_AbstractImageComparator::ref().get());
}
}
#endif // MINSG_EXT_IMAGECOMPARE
