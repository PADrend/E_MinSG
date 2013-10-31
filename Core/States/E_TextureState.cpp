/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_TextureState.h"

#include <EScript/EScript.h>
#include "../../ELibMinSG.h"
#include <E_Rendering/Texture/E_Texture.h>

using namespace MinSG;
using namespace Rendering;
using namespace E_Rendering;

namespace E_MinSG {

//! (static)
EScript::Type * E_TextureState::getTypeObject() {
	//  E_TextureState ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

// -----

//! (static)
void E_TextureState::init(EScript::Namespace & lib) {

	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);
	addFactory<MinSG::TextureState,E_TextureState>();

	//! [ESF] new MinSG.TextureState( [Texture] )
	ES_CTOR(typeObject,0,1,EScript::create( parameter.count()==0 ?
			new TextureState() : new TextureState(parameter[0].to<Rendering::Texture*>(rt))))

	//! [ESMF] Texture|Void MinSG.TextureState.getTexture()
	ES_MFUNCTION(typeObject, TextureState, "getTexture", 0,  0, {
			Texture * t = thisObj->getTexture();
			if(t)
				return new E_Texture(t);
			else return EScript::create(nullptr);
	})

	//! [ESMF] int MinSG.TextureState.getTextureUnit()
	ES_MFUN(typeObject, const TextureState, "getTextureUnit", 0, 0,thisObj->getTextureUnit())

	//! [ESMF] Bool MinSG.TextureState.hasTexture()
	ES_MFUN(typeObject, const TextureState, "hasTexture", 0,  0, thisObj->hasTexture())

	//! [ESMF] thisEObj MinSG.TextureState.setTexture(Texture)
	//ES_MFUN(typeObject, TextureState, "setTexture", 1, 1,(
	//		thisObj->setTexture( parameter[0].to<Rendering::Texture*>(rt)) ),
	//		thisEObj))
	ES_MFUNCTION(typeObject, TextureState, "setTexture", 1,  1, {
			if(!parameter[0].toBool()){
				thisObj->setTexture(nullptr);
			} else {
				thisObj->setTexture(parameter[0].to<Rendering::Texture*>(rt));
			}
			return thisEObj;
	})


	//! [ESMF] thisEObj MinSG.TextureState.setTextureUnit(int)
	ES_MFUN(typeObject, TextureState, "setTextureUnit",1, 1, (
			thisObj->setTextureUnit( parameter[0].toInt()), thisEObj))

}

// ------------------------------------------------------------

//! (ctor)
E_TextureState::E_TextureState(TextureState * c,EScript::Type * type):E_State(c,type?type:getTypeObject()) {
}

}
