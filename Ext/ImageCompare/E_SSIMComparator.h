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

#ifndef _E_MinSG_E_SSIMComparator_H_
#define _E_MinSG_E_SSIMComparator_H_

#include <EScript/Objects/ReferenceObject.h>
#include <MinSG/Ext/ImageCompare/SSIMComparator.h>

#include "E_AbstractOnGpuComparator.h"

namespace EScript {
class Namespace;
class Type;
}
namespace E_MinSG{

/*!	EScript wrapper class for MinSG::ImageCompare::SSIMComparator.

		E_SSIMComparator ---|> E_AbstractOnGpuComparator
			|
			--------------> MinSG::ImageCompare::SSIMComparator		*/
class E_SSIMComparator : public E_AbstractOnGpuComparator {

		ES_PROVIDES_TYPE_NAME(SSIMComparator)

	public:

		static EScript::Type * getTypeObject();

		static void init(EScript::Namespace & lib);

		MinSG::ImageCompare::SSIMComparator * ref();

		E_SSIMComparator(MinSG::ImageCompare::SSIMComparator * _obj) :
				E_AbstractOnGpuComparator(_obj, E_SSIMComparator::getTypeObject()) {}

		virtual ~E_SSIMComparator() {}

};
}

#endif // _E_MinSG_E_SSIMComparator_H_
#endif // MINSG_EXT_IMAGECOMPARE
