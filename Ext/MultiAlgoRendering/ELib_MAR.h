/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/


#ifdef MINSG_EXT_MULTIALGORENDERING
#include <MinSG/Ext/MultiAlgoRendering/Dependencies.h>

#ifndef ELIB_MAR_H_
#define ELIB_MAR_H_

// Forward declaration.
namespace EScript {
class Namespace;
}

namespace E_MinSG {
namespace E_MAR {

void init(EScript::Namespace * minsg);

}
}

#endif /* ELIB_MAR_H_ */
#endif // MINSG_EXT_MULTIALGORENDERING
