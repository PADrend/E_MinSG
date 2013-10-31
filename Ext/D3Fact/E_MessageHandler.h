/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2010-2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT

#ifndef E_MESSAGEHANDLER_H_
#define E_MESSAGEHANDLER_H_

#include <EScript/EScript.h>
#include <EScript/Objects/ExtReferenceObject.h>
#include <E_Util/E_ObjectFactory.h>
#include <E_Util/E_Utils.h>
#include <Util/Factory/WrapperFactory.h>

#include <MinSG/Ext/D3Fact/MessageHandler.h>

namespace E_MinSG{

class E_MessageHandler : public EScript::ExtReferenceObject< Util::Reference<D3Fact::MessageHandler>, EScript::Policies::EqualContent_ComparePolicy,E_Util::Policies::StoreAttrsInAttributeProvider > {
	ES_PROVIDES_TYPE_NAME(MessageHandler)

	static E_Util::E_ObjectFactory<D3Fact::MessageHandler, E_MessageHandler> factorySystem;
protected:
		template<class MessageHandlerType, class E_MessageHandlerType>
		static void addFactory() {
			factorySystem.registerType(MessageHandlerType::getClassId(), Util::PolymorphicWrapperCreator<D3Fact::MessageHandler, MessageHandlerType, E_MessageHandlerType>());
		}
	public:
		static E_MessageHandler * create(D3Fact::MessageHandler * mh) {
			if(mh == nullptr) {
				return nullptr;
			}
			return factorySystem.create(mh->getTypeId(), mh);
		}
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;

	static EScript::Type * getTypeObject();
	static void init(EScript::Namespace & lib);

	virtual ~E_MessageHandler()	{}

	/// ---o
	virtual D3Fact::MessageHandler * getMessageHandler() const 		{ 	return ref().get();	}

	/// --- |> Object
	virtual E_MessageHandler * clone() const;

	/// --- |> Object
	virtual std::string toString() const;
protected:
	E_MessageHandler(D3Fact::MessageHandler * mh, EScript::Type * type=nullptr);
};

}
#endif /* E_MESSAGEHANDLER_H_ */
#endif /* MINSG_EXT_D3FACT */
