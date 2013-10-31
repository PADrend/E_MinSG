/*
	This file is part of the MinSG library extension ThesisJonas.
	Copyright (C) 2013 Jonas Knoll

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_THESISJONAS

#ifndef E_MINSG_THESISJONAS_E_PREPROCESSOR_H_
#define E_MINSG_THESISJONAS_E_PREPROCESSOR_H_

namespace EScript {
class Namespace;
}
namespace E_MinSG {
namespace ThesisJonas {

//!	EScript wrapper class for MinSG::ThesisJonas preprocessor functions
namespace E_Preprocessor {
void init(EScript::Namespace & lib);
}

}
}

#endif /* E_MINSG_THESISJONAS_E_PREPROCESSOR_H_ */

#endif /* MINSG_EXT_THESISJONAS */
