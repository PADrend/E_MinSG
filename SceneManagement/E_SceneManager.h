/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __E_SceneManager_H
#define __E_SceneManager_H

#include <EScript/Objects/ExtReferenceObject.h>
#include <E_Util/E_Utils.h>
#include <MinSG/SceneManagement/SceneManager.h>
#include <memory>

namespace E_MinSG {

 /***
 **   E_SceneManager ---|> ExtReferenceObject
 **     |
 **     ------> MinSG::SceneManagement::SceneManager
 **
 ** \note the E_SceneManager owns the SceneManager object.
 **/
class E_SceneManager : public EScript::ExtReferenceObject<
									std::unique_ptr<MinSG::SceneManagement::SceneManager>,
									EScript::Policies::SameEObjects_ComparePolicy,
									E_Util::Policies::StoreAttrsInAttributeProvider>{
	ES_PROVIDES_TYPE_NAME(SceneManager)

	public:
		EMINSGAPI static EScript::Type* getTypeObject();
		EMINSGAPI static void init(EScript::Namespace & lib);

		EMINSGAPI E_SceneManager(EScript::Type * type = nullptr);
		EMINSGAPI virtual ~E_SceneManager();
		
		const MinSG::SceneManagement::SceneManager * operator*()const	{	return static_cast<const MinSG::SceneManagement::SceneManager*>(ref().get());	}
		MinSG::SceneManagement::SceneManager * operator*()				{	return static_cast<MinSG::SceneManagement::SceneManager*>(ref().get());	}
};
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_SceneManager,		MinSG::SceneManagement::SceneManager*,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_MinSG::E_SceneManager,		MinSG::SceneManagement::SceneManager&,		***eObj)

#endif // __E_SceneManager_H
