/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifdef MINSG_EXT_OUTOFCORE

#include "E_OutOfCore.h"
#include "../../ELibMinSG.h"
#include "../../Core/E_FrameContext.h"
#include "../../SceneManagement/E_SceneManager.h"


#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <MinSG/Ext/OutOfCore/CacheLevel.h>
#include <MinSG/Ext/OutOfCore/CacheManager.h>
#include <MinSG/Ext/OutOfCore/CacheObject.h>
#include <MinSG/Ext/OutOfCore/DataStrategy.h>
#include <MinSG/Ext/OutOfCore/OutOfCore.h>

#include <Util/StringUtils.h>
#include <Util/Macros.h>

namespace E_MinSG {
namespace E_OutOfCore {

void init(EScript::Namespace & lib) {
	using namespace MinSG::OutOfCore;
	EScript::Namespace * ns = new EScript::Namespace;
	declareConstant(&lib, "OutOfCore", ns);

	declareConstant(ns, "CACHELEVELTYPE_FILE_SYSTEM", EScript::Number::create(static_cast<uint32_t>(CacheLevelType::FILE_SYSTEM)));
	declareConstant(ns, "CACHELEVELTYPE_FILES", EScript::Number::create(static_cast<uint32_t>(CacheLevelType::FILES)));
	declareConstant(ns, "CACHELEVELTYPE_MAIN_MEMORY", EScript::Number::create(static_cast<uint32_t>(CacheLevelType::MAIN_MEMORY)));
	declareConstant(ns, "CACHELEVELTYPE_GRAPHICS_MEMORY", EScript::Number::create(static_cast<uint32_t>(CacheLevelType::GRAPHICS_MEMORY)));

	//! [ESF] Void MinSG.OutOfCore.setUp(FrameContext)
	ES_FUN(ns, "setUp", 1, 1, (setUp(parameter[0].to<MinSG::FrameContext&>(rt)), 
									EScript::create(nullptr)))

	//! [ESF] Number MinSG.OutOfCore.addCacheLevel(Number, Number)
	ES_FUNCTION(ns, "addCacheLevel", 2, 2, {
		const uint64_t mebibyte = 1024 * 1024;
		const auto type = static_cast<CacheLevelType>(parameter[0].toUInt());
		const uint64_t size = static_cast<uint64_t>(parameter[1].toInt());
		CacheManager & manager = getCacheManager();
		try {
			return EScript::Number::create(manager.addCacheLevel(type, size * mebibyte));
		} catch(const std::exception & e) {
			WARN(std::string("Adding a cache level failed:\n") + e.what());
		}
		return EScript::create(nullptr);
	})

	//! [ESF] Map|Void MinSG.OutOfCore.getStatisticsForLevel(Number)
	ES_FUNCTION(ns, "getStatisticsForLevel", 1, 1, {
		const double mebibyte = 1024.0 * 1024.0;
		const CacheManager & manager = getCacheManager();

		const uint8_t levelNumber = static_cast<uint8_t>(parameter[0].to<uint32_t>(rt));

		const CacheLevel * level = manager.getCacheLevel(levelNumber);
		if(level == nullptr) {
			return EScript::create(nullptr);
		}

		auto * levelStats = new EScript::ExtObject;

		levelStats->setAttribute("usedMemory", EScript::Number::create(static_cast<double>(level->getUsedMemory()) / mebibyte));
		levelStats->setAttribute("overallMemory", EScript::Number::create(static_cast<double>(level->getOverallMemory()) / mebibyte));
		levelStats->setAttribute("objects", EScript::Number::create(level->getNumObjects()));
		levelStats->setAttribute("lastWorkDuration", EScript::Number::create(level->getLastWorkDuration()));

		return levelStats;
	})

	declareConstant(ns, "MISSINGMODE_NOWAITDONOTHING", EScript::Number::create(DataStrategy::NO_WAIT_DO_NOTHING));
	declareConstant(ns, "MISSINGMODE_NOWAITDISPLAYCOLOREDBOX", EScript::Number::create(DataStrategy::NO_WAIT_DISPLAY_COLORED_BOX));
	declareConstant(ns, "MISSINGMODE_NOWAITDISPLAYDEPTHBOX", EScript::Number::create(DataStrategy::NO_WAIT_DISPLAY_DEPTH_BOX));
	declareConstant(ns, "MISSINGMODE_WAITDISPLAY", EScript::Number::create(DataStrategy::WAIT_DISPLAY));

	//! [ESF] Number MinSG.OutOfCore.getMissingMode()
	ES_FUN(ns, "getMissingMode", 0, 0,
				EScript::Number::create(getDataStrategy().getMissingMode()));

	//! [ESF] Void MinSG.OutOfCore.setMissingMode(Number)
	ES_FUN(ns, "setMissingMode", 1, 1,
				(getDataStrategy().setMissingMode(static_cast<DataStrategy::missing_mode_t>(parameter[0].toUInt())), EScript::create(nullptr)));
}

}
}

#endif /* MINSG_EXT_OUTOFCORE */
