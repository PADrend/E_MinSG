#
# This file is part of the E_MinSG library.
# Copyright (C) 2009-2013 Benjamin Eikel <benjamin@eikel.org>
#
# This library is subject to the terms of the Mozilla Public License, v. 2.0.
# You should have received a copy of the MPL along with this library; see the 
# file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
#
cmake_minimum_required(VERSION 2.8.11)
project(E_MinSG CXX)

set(E_MINSG_VERSION_MAJOR 0)
set(E_MINSG_VERSION_MINOR 1)
set(E_MINSG_VERSION_PATCH 4)
set(E_MINSG_VERSION_STRING ${E_MINSG_VERSION_MAJOR}.${E_MINSG_VERSION_MINOR}.${E_MINSG_VERSION_PATCH})

# Set up install directories
include(GNUInstallDirs)
set(CMAKE_INSTALL_CMAKECONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/E_MinSG)

add_library(E_MinSG
	Core/Behaviours/E_AbstractBehaviour.cpp
	Core/Behaviours/E_Behavior.cpp
	Core/Behaviours/E_BehaviorStatus.cpp
	Core/Behaviours/E_BehaviourManager.cpp
	Core/Behaviours/E_ScriptedBehavior.cpp	
	Core/E_FrameContext.cpp
	Core/E_RenderParam.cpp
	Core/E_Statistics.cpp
	Core/Nodes/E_AbstractCameraNode.cpp
	Core/Nodes/E_CameraNode.cpp
	Core/Nodes/E_CameraNodeOrtho.cpp
	Core/Nodes/E_GeometryNode.cpp
	Core/Nodes/E_GroupNode.cpp
	Core/Nodes/E_LightNode.cpp
	Core/Nodes/E_ListNode.cpp
	Core/Nodes/E_Node.cpp
	Core/States/E_AlphaTestState.cpp
	Core/States/E_BlendingState.cpp
	Core/States/E_CullFaceState.cpp
	Core/States/E_GroupState.cpp
	Core/States/E_LightingState.cpp
	Core/States/E_MaterialState.cpp
	Core/States/E_NodeRendererState.cpp
	Core/States/E_PolygonModeState.cpp
	Core/States/E_ShaderState.cpp
	Core/States/E_ShaderUniformState.cpp
	Core/States/E_State.cpp
	Core/States/E_TextureState.cpp
	Core/States/E_TransparencyRenderer.cpp
	ELibMinSG.cpp
	Ext/AdaptiveGlobalVisibilitySampling/E_AdaptiveGlobalVisibilitySampling.cpp
	Ext/Behaviours/E_AbstractBehaviourDecorator.cpp
	Ext/Behaviours/E_BehaviourGroup.cpp
	Ext/Behaviours/E_KeyFrameAnimationBehaviour.cpp
	Ext/Behaviours/E_ScriptedBehaviour.cpp
	Ext/Behaviours/E_SoundEmittingBehaviour.cpp
	Ext/Behaviours/E_SoundReceivingBehaviour.cpp
	Ext/Behaviours/E_SimplePhysics2.cpp
	Ext/Behaviours/E_TimedBehaviourDecorator.cpp
	Ext/BlueSurfels/E_SurfelGenerator.cpp
	Ext/ColorCubes/E_ColorCube.cpp
	Ext/ColorCubes/E_ColorCubeRenderer.cpp
	Ext/D3Fact/E_ClientUnit.cpp
	Ext/D3Fact/E_ConsoleStream.cpp
	Ext/D3Fact/ELib_D3Fact.cpp
	Ext/D3Fact/E_Message.cpp
	Ext/D3Fact/E_MessageDispatcher.cpp
	Ext/D3Fact/E_MessageHandler.cpp
	Ext/D3Fact/E_ObjectRegistry.cpp
	Ext/D3Fact/E_ScriptedMessageHandler.cpp
	Ext/D3Fact/E_Session.cpp
	Ext/D3Fact/E_SyncHandler.cpp
	Ext/ELibMinSGExt.cpp
	Ext/Evaluator/E_AdaptCullEvaluator.cpp
	Ext/Evaluator/E_AreaEvaluator.cpp
	Ext/Evaluator/E_BoxQualityEvaluator.cpp
	Ext/Evaluator/E_ColorVisibilityEvaluator.cpp
	Ext/Evaluator/E_Evaluator.cpp
	Ext/Evaluator/E_OccOverheadEvaluator.cpp
	Ext/Evaluator/E_OverdrawFactorEvaluator.cpp
	Ext/Evaluator/E_ScriptedEvaluator.cpp
	Ext/Evaluator/E_StatsEvaluator.cpp
	Ext/Evaluator/E_TrianglesEvaluator.cpp
	Ext/Evaluator/E_VisibilityEvaluator.cpp
	Ext/ImageCompare/E_AbstractImageComparator.cpp
	Ext/ImageCompare/E_AbstractOnGpuComparator.cpp
	Ext/ImageCompare/E_AverageComparator.cpp
	Ext/ImageCompare/E_PyramidComparator.cpp
	Ext/ImageCompare/E_SSIMComparator.cpp
	Ext/ImpostorFactory/E_ImpostorFactory.cpp
	Ext/KeyFrameAnimation/E_KeyFrameAnimationNode.cpp
	Ext/MultiAlgoRendering/E_AlgoSelector.cpp
	Ext/MultiAlgoRendering/ELib_MAR.cpp
	Ext/MultiAlgoRendering/E_MultiAlgoGroupNode.cpp
	Ext/MultiAlgoRendering/E_Region.cpp
	Ext/MultiAlgoRendering/E_RegionEvaluator.cpp
	Ext/MultiAlgoRendering/E_SampleContext.cpp
	Ext/MultiAlgoRendering/E_SampleRegion.cpp
	Ext/MultiAlgoRendering/E_SampleStorage.cpp
	Ext/MultiAlgoRendering/E_SurfelRenderer.cpp
	Ext/Nodes/E_BillboardNode.cpp
	Ext/Nodes/E_FakeInstanceNode.cpp
	Ext/Nodes/E_GenericMetaNode.cpp
	Ext/OcclusionCulling/E_CHCppRenderer.cpp
	Ext/OcclusionCulling/E_HOMRenderer.cpp
	Ext/OcclusionCulling/E_OccludeeRenderer.cpp
	Ext/OcclusionCulling/E_OccRenderer.cpp
	Ext/OutOfCore/E_OutOfCore.cpp
	Ext/ParticleSystem/E_ParticleAnimator.cpp
	Ext/ParticleSystem/E_ParticleBoxEmitter.cpp
	Ext/ParticleSystem/E_ParticleFadeOutAffector.cpp
	Ext/ParticleSystem/E_ParticleGravityAffector.cpp
	Ext/ParticleSystem/E_ParticlePointEmitter.cpp
	Ext/ParticleSystem/E_ParticleStates.cpp
	Ext/ParticleSystem/E_ParticleSystemNode.cpp
	Ext/Physics/E_PhysicWorld.cpp
	Ext/RTree/E_RTree.cpp
	Ext/SamplingAnalysis/E_SamplingAnalysis.cpp
	Ext/SkeletalAnimation/E_SkeletalAnimationBehaviour.cpp
	Ext/SkeletalAnimation/E_SkeletalHardwareRendererState.cpp
	Ext/SkeletalAnimation/E_SkeletalNode.cpp
	Ext/SkeletalAnimation/E_SkeletalSoftwareRendererState.cpp
	Ext/SkeletalAnimation/JointPose/E_SkeletalAbstractPose.cpp
	Ext/SkeletalAnimation/JointPose/E_SkeletalMatrixPose.cpp
	Ext/SkeletalAnimation/JointPose/E_SkeletalSRTPose.cpp
	Ext/SkeletalAnimation/Joints/E_ArmatureNode.cpp
	Ext/SkeletalAnimation/Joints/E_JointNode.cpp
	Ext/SkeletalAnimation/Joints/E_RigidJoint.cpp
	Ext/SkeletalAnimation/Util/E_SkeletalAnimationUtils.cpp
	Ext/States/E_BudgetAnnotationState.cpp
	Ext/States/E_EnvironmentState.cpp
	Ext/States/E_LODRenderer.cpp
	Ext/States/E_MirrorState.cpp
	Ext/States/E_ProjSizeFilterState.cpp
	Ext/States/E_RandomColorRenderer.cpp
	Ext/States/E_ScriptedNodeRendererState.cpp
	Ext/States/E_ScriptedState.cpp
	Ext/States/E_ShadowState.cpp
	Ext/States/E_StrangeExampleRenderer.cpp
	Ext/SVS/E_BudgetRenderer.cpp
	Ext/SVS/E_GeometryNodeCollector.cpp
	Ext/SVS/E_Helper.cpp
	Ext/SVS/E_PreprocessingContext.cpp
	Ext/SVS/E_Renderer.cpp
	Ext/SVS/E_SamplePoint.cpp
	Ext/SVS/E_SamplingSphere.cpp
	Ext/SVS/E_SphereVisualizationRenderer.cpp
	Ext/ThesisJonas/E_Preprocessor.cpp
	Ext/ThesisJonas/E_Renderer.cpp
	Ext/Tools/E_DebugCamera.cpp
	Ext/Tools/E_StatChart.cpp
	Ext/TreeBuilder/E_TreeBuilder.cpp
	Ext/TreeSync/E_Server.cpp
	Ext/TreeSync/E_TreeSyncClient.cpp
	Ext/TriangleTrees/E_TreeVisualization.cpp
	Ext/TriangleTrees/E_TriangleTreeBuilder.cpp
	Ext/Triangulation/E_Delaunay2d.cpp
	Ext/Triangulation/E_Delaunay3d.cpp
	Ext/TwinPartitions/E_TwinPartitionsRenderer.cpp
	Ext/ValuatedRegion/E_DirectionalInterpolator.cpp
	Ext/ValuatedRegion/E_ValuatedRegionNode.cpp
	Ext/VisibilitySubdivision/E_CostEvaluator.cpp
	Ext/VisibilitySubdivision/E_PVSRenderer.cpp
	Ext/VisibilitySubdivision/E_VisibilitySubdivisionRenderer.cpp
	Ext/VisibilitySubdivision/E_VisibilityVector.cpp
	Ext/Waypoints/E_FollowPathBehaviour.cpp
	Ext/Waypoints/E_PathNode.cpp
	Ext/Waypoints/E_Waypoint.cpp
	Helper/E_GraphVizOutput.cpp
	Helper/E_StdNodeVisitors.cpp
	SceneManagement/E_ImportContext.cpp
	SceneManagement/E_SceneManager.cpp
)

# Dependency to EScript
if(TARGET EScript)
	set(ESCRIPT_INCLUDE_DIRS ${EScript_SOURCE_DIR})
	set(ESCRIPT_LIBRARIES EScript)
else()
	find_package(EScript 0.6.4 REQUIRED NO_MODULE)
	if(NOT ESCRIPT_LIBRARIES)
		set(ESCRIPT_LIBRARIES EScript)
	endif()
endif()
if(ESCRIPT_INCLUDE_DIRS)
	target_include_directories(E_MinSG PRIVATE ${ESCRIPT_INCLUDE_DIRS})
endif()
target_link_libraries(E_MinSG LINK_PUBLIC ${ESCRIPT_LIBRARIES})

# Dependency to E_Geometry
if(NOT TARGET E_Geometry)
	find_package(E_Geometry 0.1.2 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_MinSG LINK_PUBLIC E_Geometry)

# Dependency to E_Rendering
if(NOT TARGET E_Rendering)
	find_package(E_Rendering 0.1.3 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_MinSG LINK_PUBLIC E_Rendering)

# Dependency to E_Util
if(NOT TARGET E_Util)
	find_package(E_Util 0.1.2 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_MinSG LINK_PUBLIC E_Util)

# Dependency to Geometry
if(NOT TARGET Geometry)
	find_package(Geometry 0.1.3 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_MinSG LINK_PUBLIC Geometry)

# Dependency to MinSG
if(NOT TARGET MinSG)
	find_package(MinSG 0.1.4 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_MinSG LINK_PUBLIC MinSG)

# Dependency to Rendering
if(NOT TARGET Rendering)
	find_package(Rendering 0.1.3 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_MinSG LINK_PUBLIC Rendering)

# Dependency to Util
if(NOT TARGET Util)
	find_package(Util 0.1.3 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_MinSG LINK_PUBLIC Util)

# Optional dependency to Sound and E_Sound
if(NOT TARGET Sound)
	find_package(Sound 0.1.2 QUIET NO_MODULE)
endif()
if(NOT TARGET E_Sound)
	find_package(E_Sound 0.1.2 QUIET NO_MODULE)
endif()
if(TARGET Sound AND TARGET E_Sound)
	target_link_libraries(E_MinSG LINK_PUBLIC Sound E_Sound)
endif()

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set_property(TARGET E_MinSG APPEND_STRING PROPERTY COMPILE_FLAGS "-std=c++11 ")
elseif(COMPILER_SUPPORTS_CXX0X)
	set_property(TARGET E_MinSG APPEND_STRING PROPERTY COMPILE_FLAGS "-std=c++0x ")
else()
	message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Set version of library
set_target_properties(E_MinSG PROPERTIES VERSION ${E_MINSG_VERSION_STRING}
                                         SOVERSION ${E_MINSG_VERSION_MAJOR})

# Install the header files
#file(GLOB E_MINSG_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
#install(FILES ${E_MINSG_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/E_MinSG)
install(DIRECTORY .
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/E_MinSG COMPONENT headers
	FILES_MATCHING PATTERN "*.h"
	PATTERN ".svn" EXCLUDE
	PATTERN ".git" EXCLUDE
	PATTERN "CMakeFiles" EXCLUDE
)

# Install the library
install(TARGETS E_MinSG EXPORT LibraryExport
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT runtimelibraries
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT runtimelibraries
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT developmentlibraries
)

# Set include directories for users of this library
target_include_directories(E_MinSG
                           INTERFACE
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>"
                           "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")

# Library export
install(EXPORT LibraryExport DESTINATION ${CMAKE_INSTALL_CMAKECONFIGDIR} FILE E_MinSGTargets.cmake COMPONENT developmentlibraries)

# Create the configuration files
include(CMakePackageConfigHelpers)
configure_package_config_file(E_MinSGConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/E_MinSGConfig.cmake
                              INSTALL_DESTINATION ${CMAKE_INSTALL_CMAKECONFIGDIR}
                              PATH_VARS CMAKE_INSTALL_CMAKECONFIGDIR
                              NO_SET_AND_CHECK_MACRO
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/E_MinSGConfigVersion.cmake
                                 VERSION ${E_MINSG_VERSION_STRING}
                                 COMPATIBILITY SameMajorVersion)

# Install the configuration files
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/E_MinSGConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/E_MinSGConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_CMAKECONFIGDIR} COMPONENT developmentlibraries)

# Packaging
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "libminsg${E_MINSG_VERSION_MAJOR}-escript")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "E_MinSG library")
set(CPACK_PACKAGE_VENDOR "Benjamin Eikel; Claudius Jaehn; Ralf Petring")
set(CPACK_PACKAGE_CONTACT "Benjamin Eikel <benjamin@eikel.org>")
set(CPACK_PACKAGE_VERSION_MAJOR ${E_MINSG_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${E_MINSG_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${E_MINSG_VERSION_PATCH})
set(CPACK_PACKAGE_FILE_NAME "libE_MinSG")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_STRIP_FILES ON)

include(CPack)
