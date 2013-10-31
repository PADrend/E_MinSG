/*
	This file is part of the E_MinSG library extension D3Fact.
	Copyright (C) 2010-2012 Sascha Brandt <myeti@mail.upb.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_D3FACT

#ifndef ESYNCHANDLER_H_
#define ESYNCHANDLER_H_

#include "E_MessageHandler.h"
#include <MinSG/Ext/D3Fact/SyncHandler.h>

namespace E_MinSG{

class E_SyncHandler : public E_MessageHandler {
	ES_PROVIDES_TYPE_NAME(SyncHandler)

public:
	template<class, class, class> friend class Util::PolymorphicWrapperCreator;

	static EScript::Type* getTypeObject();
	static void init(EScript::Namespace & lib);

	virtual ~E_SyncHandler();

	/// ---|> E_MessageHandler
	virtual D3Fact::SyncHandler * getMessageHandler() const {
		return dynamic_cast<D3Fact::SyncHandler *>(E_MessageHandler::getMessageHandler());
	}
protected:
	E_SyncHandler(D3Fact::SyncHandler * h,EScript::Type* type=nullptr);
};

} /* namespace E_MinSG */
#endif /* ESYNCHANDLER_H_ */
#endif
