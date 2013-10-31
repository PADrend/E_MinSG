/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_IMPOSTORFACTORY_H
#define E_IMPOSTORFACTORY_H

// Forward declaration.
namespace EScript {
class Namespace;
}

namespace E_MinSG {
namespace E_ImpostorFactory {
void init(EScript::Namespace * lib);
}
}

#endif // E_IMPOSTORFACTORY_H
