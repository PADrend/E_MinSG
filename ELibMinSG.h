/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef ELIB_MINSG_H
#define ELIB_MINSG_H

#include "Core/Nodes/E_Node.h"
#include <EScript/Objects/Collections/Array.h>

namespace EScript {
class Namespace;
}
namespace E_MinSG {

EMINSGAPI void init(EScript::Namespace * globals);

/*! Create an EScript Array of ENodes from a sequence container
	(array,list,vector, ..., NOT map or set) of Nodes.	*/
template<typename listIt_t>
EScript::Array * getENodeArray(const listIt_t & begin, const listIt_t & end) {
	EScript::Array * array = EScript::Array::create();
	for(listIt_t it = begin; it != end; ++it) {
		E_Node * en = EScript::create(*it);
		if(en != nullptr) {
			array->pushBack(en);
		}
	}
	return array;
}

}

#endif // ELIB_MINSG_H
