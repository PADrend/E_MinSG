/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_IMPORTCONTEXT_H
#define E_IMPORTCONTEXT_H

#include <MinSG/SceneManagement/Importer/ImportContext.h>
#include <EScript/Objects/ReferenceObject.h>
#include <Util/References.h>

namespace E_MinSG {

/***
 **   E_ImportContext ---|> ReferenceObject
 **     |
 **     ------> MinSG::SceneManagement::ImportContext
 **/
class E_ImportContext : public EScript::ReferenceObject<MinSG::SceneManagement::ImportContext,
														EScript::Policies::SameEObjects_ComparePolicy> {
		ES_PROVIDES_TYPE_NAME(ImportContext)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_ImportContext(MinSG::SceneManagement::ImportContext && context) : ReferenceObject_t(getTypeObject(), context) {}
		virtual ~E_ImportContext()	{}
};

}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ImportContext,		MinSG::SceneManagement::ImportContext*,		&**eObj)
ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_ImportContext,		MinSG::SceneManagement::ImportContext&,		**eObj)

#endif // E_IMPORTCONTEXT_H
