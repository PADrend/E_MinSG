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

#ifndef E_ABSTRACTIMAGECOMPARATOR_H
#define E_ABSTRACTIMAGECOMPARATOR_H

#include <EScript/Objects/ReferenceObject.h>
#include <string>
#include <MinSG/Ext/ImageCompare/AbstractOnGpuComparator.h>

#include <Util/References.h>

namespace EScript {
class Namespace;
class Type;
}

namespace E_MinSG {

/*
 * E_AbstractImageComparator ---|> ReferenceObject
 */
class E_AbstractImageComparator : public EScript::ReferenceObject<Util::Reference<MinSG::ImageCompare::AbstractImageComparator> > {
		ES_PROVIDES_TYPE_NAME(AbstractImageComparator)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

	protected:
		E_AbstractImageComparator(MinSG::ImageCompare::AbstractImageComparator * comparator, EScript::Type * type) 
			: ReferenceObject_t(Util::Reference<MinSG::ImageCompare::AbstractImageComparator>(comparator), type) {
		}
	public:
		virtual ~E_AbstractImageComparator();
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_AbstractImageComparator,	MinSG::ImageCompare::AbstractImageComparator*,	(**eObj).get())


#endif /* E_ABSTRACTIMAGECOMPARATOR_H */

#endif /* MINSG_EXT_IMAGECOMPARE */
