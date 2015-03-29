/*
	This file is part of the MinSG library extension ThesisPeter.
	Copyright (C) 2014 Peter Stilow

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_THESISPETER

#ifndef E_MINSG_THESISPETER_E_LIGHTNODEMANAGER_H_
#define E_MINSG_THESISPETER_E_LIGHTNODEMANAGER_H_

#include <MinSG/Ext/ThesisPeter/LightNodeManager.h>

#include <EScript/Objects/ReferenceObject.h>
#include <Util/References.h>

namespace E_MinSG {
namespace ThesisPeter {

//!	EScript wrapper class for MinSG::ThesisPeter::LightNodeManager
class E_LightNodeManager : public EScript::ReferenceObject<MinSG::ThesisPeter::LightNodeManager,
														EScript::Policies::SameEObjects_ComparePolicy> {
	ES_PROVIDES_TYPE_NAME(LightNodeManager)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_LightNodeManager() : ReferenceObject_t(getTypeObject()) {}
		virtual ~E_LightNodeManager();
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisPeter::E_LightNodeManager,	MinSG::ThesisPeter::LightNodeManager*,	&**eObj)
ES_CONV_EOBJ_TO_OBJ(E_MinSG::ThesisPeter::E_LightNodeManager,	MinSG::ThesisPeter::LightNodeManager,	**eObj)

#endif /* E_MINSG_THESISPETER_E_LIGHTNODEMANAGER_H_ */

#endif /* MINSG_EXT_THESISPETER */
