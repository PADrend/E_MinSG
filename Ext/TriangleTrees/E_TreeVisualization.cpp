/*
	This file is part of the E_MinSG library extension TriangleTrees.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_TRIANGLETREES

#include "E_TreeVisualization.h"
#include "../../ELibMinSG.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <MinSG/Ext/TriangleTrees/TreeVisualization.h>

namespace MinSG {
namespace SceneManagement {
class SceneManager;
}
}
namespace E_MinSG {

EScript::Type * E_TreeVisualization::getTypeObject() {
	// E_TreeVisualization ---|> E_State ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(E_State::getTypeObject());
	return typeObject.get();
}

void E_TreeVisualization::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	addFactory<MinSG::TriangleTrees::TreeVisualization,E_TreeVisualization>();

	using namespace MinSG::TriangleTrees;

	//! [ESF] TreeVisualization new TreeVisualization()
	ES_CTOR(typeObject, 0, 0, EScript::create(new MinSG::TriangleTrees::TreeVisualization));

	//! [ESMF] Number TreeVisualization.getDrawDepth()
	ES_MFUN(typeObject, TreeVisualization, "getDrawDepth", 0, 0, thisObj->getDrawDepth())
	//! [ESMF] self TreeVisualization.setDrawDepth(Number)
	ES_MFUN(typeObject, TreeVisualization, "setDrawDepth", 1, 1, (thisObj->setDrawDepth(parameter[0].toInt()), thisEObj))

	//! [ESMF] Bool TreeVisualization.getShowSplittingPlanes()
	ES_MFUN(typeObject, TreeVisualization, "getShowSplittingPlanes", 0, 0, thisObj->getShowSplittingPlanes())
	//! [ESMF] self TreeVisualization.setShowSplittingPlanes(Bool)
	ES_MFUN(typeObject, TreeVisualization, "setShowSplittingPlanes", 1, 1, (thisObj->setShowSplittingPlanes(parameter[0].toBool()), thisEObj))

	//![ESMF] Bool TreeVisualization.getShowBoundingBoxes()
	ES_MFUN(typeObject, TreeVisualization, "getShowBoundingBoxes", 0, 0, thisObj->getShowBoundingBoxes())
	//![ESMF] self TreeVisualization.setShowBoundingBoxes(Bool)
	ES_MFUN(typeObject, TreeVisualization, "setShowBoundingBoxes", 1, 1, (thisObj->setShowBoundingBoxes(parameter[0].toBool()), thisEObj))

	//! [ESMF] Bool TreeVisualization.getShowLines()
	ES_MFUN(typeObject, TreeVisualization, "getShowLines", 0, 0, thisObj->getShowLines())
	//! [ESMF] self TreeVisualization.setShowLines(Bool)
	ES_MFUN(typeObject, TreeVisualization, "setShowLines", 1, 1, (thisObj->setShowLines(parameter[0].toBool()), thisEObj))

}

}

#endif /* MINSG_EXT_TRIANGLETREES */
