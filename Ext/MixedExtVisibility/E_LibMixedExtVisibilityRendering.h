/*
	This file is part of the MinSG library extension MixedExtVisibility.
	Copyright (C) 2015 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_MIXED_EXTERN_VISIBILITY

#ifndef E_LIB_MINSG_EXT_VIS_H_
#define E_LIB_MINSG_EXT_VIS_H_


namespace EScript {
class Namespace;
}
namespace E_MinSG{
namespace MixedExtVisibility{
void init(EScript::Namespace & lib);
}
}

#endif // E_LIB_MINSG_EXT_VIS_H_
#endif // MINSG_EXT_MIXED_EXTERN_VISIBILITY

