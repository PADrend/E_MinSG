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

#ifndef E_ABSTRACTONGPUCOMPARATOR_H
#define E_ABSTRACTONGPUCOMPARATOR_H

#include "E_AbstractImageComparator.h"
#include <MinSG/Ext/ImageCompare/AbstractOnGpuComparator.h>

namespace E_MinSG {

/*
 * E_ImageOnGpgComparator ---|> E_AbstractImageComparator ---|> ReferenceObject
 */
class E_AbstractOnGpuComparator : public E_AbstractImageComparator {
		ES_PROVIDES_TYPE_NAME(AbstractOnGpuComparator)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		const MinSG::ImageCompare::AbstractOnGpuComparator * operator*()const	{	return static_cast<const MinSG::ImageCompare::AbstractOnGpuComparator *>(ref().get());	}
		MinSG::ImageCompare::AbstractOnGpuComparator * operator*()				{	return static_cast<MinSG::ImageCompare::AbstractOnGpuComparator *>(ref().get());	}

	protected:
		E_AbstractOnGpuComparator(MinSG::ImageCompare::AbstractOnGpuComparator * comparator, EScript::Type * type) : E_AbstractImageComparator(comparator, type){}
	public:
		virtual ~E_AbstractOnGpuComparator(){}
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_AbstractOnGpuComparator,	MinSG::ImageCompare::AbstractOnGpuComparator*,	**eObj)

#endif /* E_ABSTRACTONGPUCOMPARATOR_H */

#endif /* MINSG_EXT_IMAGECOMPARE */
