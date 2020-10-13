/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_FrameContext_H
#define __E_FrameContext_H

#include <EScript/Objects/ReferenceObject.h>
#include <EScript/Basics.h>
#include <MinSG/Core/FrameContext.h>

namespace E_MinSG{

/**
 *   [E_FrameContext] ---|> [Object]
 */
class E_FrameContext : public EScript::ReferenceObject<Util::Reference<MinSG::FrameContext>>{
	ES_PROVIDES_TYPE_NAME(FrameContext)
	public:
		EMINSGAPI static EScript::Type* getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		EMINSGAPI E_FrameContext(MinSG::FrameContext * fctxt);
		EMINSGAPI virtual ~E_FrameContext();

};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_FrameContext,		MinSG::FrameContext&,		*((**eObj).get()))
ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_FrameContext,		MinSG::FrameContext*,		(**eObj).get())	
ES_CONV_OBJ_TO_EOBJ(MinSG::FrameContext&,			E_MinSG::E_FrameContext,	new E_MinSG::E_FrameContext(&obj))
ES_CONV_OBJ_TO_EOBJ(MinSG::FrameContext*,			E_MinSG::E_FrameContext,	new E_MinSG::E_FrameContext(obj))

#endif // __E_FrameContext_H
