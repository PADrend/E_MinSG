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

#ifndef _E_MinSG_E_PyramidComparator_H_
#define _E_MinSG_E_PyramidComparator_H_

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/ImageCompare/PyramidComparator.h>

#include "E_AbstractOnGpuComparator.h"

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG{

/*!	EScript wrapper class for MinSG::ImageCompare::PyramidComparator.

		E_PyramidComparator ---|> E_AbstractOnGpuComparator
			|
			--------------> MinSG::ImageCompare::PyramidComparator		*/
class E_PyramidComparator : public E_AbstractOnGpuComparator {

		ES_PROVIDES_TYPE_NAME(PyramidComparator)

	public:

		static EScript::Type * getTypeObject();

		static void init(EScript::Namespace & lib);

		MinSG::ImageCompare::PyramidComparator * operator*();

		E_PyramidComparator(MinSG::ImageCompare::PyramidComparator * _obj) :
				E_AbstractOnGpuComparator(_obj, E_PyramidComparator::getTypeObject()) {}

		virtual ~E_PyramidComparator() {}

};
}

#endif // _E_MinSG_E_PyramidComparator_H_
#endif // MINSG_EXT_IMAGECOMPARE
