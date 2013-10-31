/*
	This file is part of the E_MinSG library extension MultiAlgoRendering.
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/


#ifdef MINSG_EXT_MULTIALGORENDERING

#include "E_Region.h"

#include "../../Core/E_FrameContext.h"
#include "../../ELibMinSG.h"

#include <E_Geometry/E_Box.h>

#include <E_Util/E_Utils.h>

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

using namespace EScript;

namespace E_MinSG {
namespace E_MAR {
	
	using namespace MinSG::MAR;

EScript::Type * E_Region::getTypeObject() {
	// E_MAR::E_Region ---|> [ReferenceObject<Util::Reference<MinSG::MAR::Region>>
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(Object::getTypeObject());
	return typeObject.get();
}

void E_Region::init(EScript::Namespace & lib) {

	declareConstant(&lib,getClassName(),getTypeObject());

	ES_CTOR(getTypeObject(), 1, 1,
		EScript::create(new Region(parameter[0].to<const Geometry::Box&>(rt), nullptr)));

	ES_MFUN(getTypeObject(), Region, "setColor", 1, 1, (thisObj->setColor(parameter[0].to<Util::Color4f>(rt)), EScript::create(nullptr)));

	ES_MFUN(getTypeObject(), const Region, "display", 2, 2, (thisObj->display( parameter[0].to<MinSG::FrameContext&>(rt),parameter[1].to<float>(rt) ), EScript::create(nullptr)));

	ES_MFUN(getTypeObject(), const Region, "getBounds", 0, 0, EScript::create(thisObj->getBounds()));

	ES_MFUN(getTypeObject(), Region, "split", 3, 3, (thisObj->split(parameter[0].to<uint32_t>(rt), parameter[1].to<uint32_t>(rt), parameter[2].to<uint32_t>(rt)), EScript::create(nullptr)));
	ES_MFUN(getTypeObject(), Region, "splitCubeLike", 0, 0, (thisObj->splitCubeLike(), EScript::create(nullptr)));
	
	ES_MFUN(getTypeObject(), const Region, "getChildren", 0, 0, EScript::Array::create(thisObj->getChildren()) )

	ES_MFUN(getTypeObject(), const Region, "treeSize", 0, 0, static_cast<uint32_t>(thisObj->treeSize()))

	ES_MFUN(getTypeObject(), const Region, "getAttributes", 0, 0, E_Util::E_Utils::convertGenericAttributeToEScriptObject(thisObj->getAttributes()));
	ES_MFUN(getTypeObject(), const Region, "getAttribute", 1, 1, E_Util::E_Utils::convertGenericAttributeToEScriptObject(thisObj->getAttribute(parameter[0].to<std::string>(rt))))
	ES_MFUN(getTypeObject(), Region, "setAttribute", 2, 2, (thisObj->setAttribute( parameter[0].to<std::string>(rt),E_Util::E_Utils::convertEScriptObjectToGenericAttribute(parameter[1])), EScript::create(nullptr)))
	ES_MFUN(getTypeObject(), Region, "unsetAttribute", 1, 1, (thisObj->unsetAttribute(parameter[0].to<std::string>(rt)), EScript::create(nullptr)))
}

}
}

#endif // MINSG_EXT_MULTIALGORENDERING
