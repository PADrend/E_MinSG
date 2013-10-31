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

#include "E_AverageComparator.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_MinSG{

//! (static)
EScript::Type * E_AverageComparator::getTypeObject() {
	// E_AverageComparator ---|>E_AbstractOnGpuComparator ---|> E_AbstractImageComparator ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_AbstractOnGpuComparator::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_AverageComparator::init(EScript::Namespace & lib) {

	EScript::Type * typeObject = E_AverageComparator::getTypeObject();

	declareConstant(&lib,getClassName(),typeObject);

	//! [ESF] AverageComparator new AverageComparator()
	ES_CTOR(typeObject, 0, 0, new E_AverageComparator(new MinSG::ImageCompare::AverageComparator))
}

MinSG::ImageCompare::AverageComparator * E_AverageComparator::ref() {
	return static_cast<MinSG::ImageCompare::AverageComparator *>(E_AbstractImageComparator::ref().get());
}
}
#endif // MINSG_EXT_IMAGECOMPARE
