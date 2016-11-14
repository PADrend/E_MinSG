/*
	This file is part of the E_MinSG library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2014 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "ELibMinSGExt.h"
#include "../ELibMinSG.h"

#include <E_Util/E_Utils.h>

// [ext:AdaptiveGlobalVisibilitySampling]
#ifdef MINSG_EXT_ADAPTIVEGLOBALVISIBILITYSAMPLING
#include "AdaptiveGlobalVisibilitySampling/E_AdaptiveGlobalVisibilitySampling.h"
#endif /* MINSG_EXT_ADAPTIVEGLOBALVISIBILITYSAMPLING */

// [ext:Behaviours]
#include <MinSG/Ext/Behaviours/SRTBehaviour.h>
#include "Behaviours/E_KeyFrameAnimationBehaviour.h"
#include "Behaviours/E_ScriptedBehaviour.h"
#include "Behaviours/E_SimplePhysics2.h"
#include "Behaviours/E_BehaviourGroup.h"
#include "Behaviours/E_AbstractBehaviourDecorator.h"
#include "Behaviours/E_TimedBehaviourDecorator.h"

// [ext:BlueSurfels]
#ifdef MINSG_EXT_BLUE_SURFELS
#include "BlueSurfels/E_LibBlueSurfels.h"
#endif // MINSG_EXT_BLUE_SURFELS

// [ext:ColorCubes]
#ifdef MINSG_EXT_COLORCUBES
#include "ColorCubes/E_ColorCube.h"
#include "ColorCubes/E_ColorCubeRenderer.h"
#endif // MINSG_EXT_COLORCUBES

// [ext:D3Fact]
#ifdef MINSG_EXT_D3FACT
#include "D3Fact/ELib_D3Fact.h"
#endif // MINSG_EXT_D3FACT

// [ext:MixedExtVisibility]
#ifdef MINSG_EXT_MIXED_EXTERN_VISIBILITY
#include "MixedExtVisibility/E_LibMixedExtVisibilityRendering.h"
#endif // MINSG_EXT_MIXED_EXTERN_VISIBILITY

// [ext:SVS]
#ifdef MINSG_EXT_SVS
#include "SVS/E_BudgetRenderer.h"
#include "SVS/E_GeometryNodeCollector.h"
#include "SVS/E_Helper.h"
#include "SVS/E_PreprocessingContext.h"
#include "SVS/E_Renderer.h"
#include "SVS/E_SamplePoint.h"
#include "SVS/E_SphereVisualizationRenderer.h"
#include "SVS/E_VisibilitySphere.h"
#endif /* MINSG_EXT_SVS */

// [ext:ThesisJonas]
#ifdef MINSG_EXT_THESISJONAS
#include "ThesisJonas/E_Renderer.h"
#include "ThesisJonas/E_Preprocessor.h"
#endif /* MINSG_EXT_THESISJONAS */

// [ext:ThesisPeter]
#ifdef MINSG_EXT_THESISPETER
#include "ThesisPeter/E_LightNodeManager.h"
#endif /* MINSG_EXT_THESISPETER */

// [ext:ThesisStanislaw]
#ifdef MINSG_EXT_THESISSTANISLAW
#include "ThesisStanislaw/E_PolygonIndexing.h"
#include "ThesisStanislaw/E_LightPatchRenderer.h"
#include "ThesisStanislaw/E_PhotonSampler.h"
#include "ThesisStanislaw/E_PhongGI.h"
#include "ThesisStanislaw/E_ApproxSceneDebug.h"
#include "ThesisStanislaw/E_PhotonRenderer.h"
#endif /* MINSG_EXT_THESISSTANISLAW */

// [ext:Triangulation]
#ifdef MINSG_EXT_TRIANGULATION
#include "Triangulation/E_Delaunay2d.h"
#include "Triangulation/E_Delaunay3d.h"
#endif  // MINSG_EXT_TRIANGULATION

// [ext:Evaluator]
#include "Evaluator/E_Evaluator.h"
#include "Evaluator/E_AreaEvaluator.h"
#include "Evaluator/E_ColorVisibilityEvaluator.h"
#include "Evaluator/E_VisibilityEvaluator.h"
#include "Evaluator/E_StatsEvaluator.h"
#include "Evaluator/E_OccOverheadEvaluator.h"
#include "Evaluator/E_OverdrawFactorEvaluator.h"
#include "Evaluator/E_TrianglesEvaluator.h"
#include "Evaluator/E_AdaptCullEvaluator.h"
#include "Evaluator/E_ScriptedEvaluator.h"
#include "Evaluator/E_BoxQualityEvaluator.h"

// misc
#include <MinSG/Ext/States/SkyboxState.h>
#include <MinSG/Ext/Behaviours/SimplePhysics.h>
#include "States/E_BudgetAnnotationState.h"
#include "States/E_StrangeExampleRenderer.h"
#include "States/E_EnvironmentState.h"
#include "States/E_MirrorState.h"
#include "States/E_ProjSizeFilterState.h"
#include "States/E_RandomColorRenderer.h"
#include "States/E_ShadowState.h"
#include "Nodes/E_BillboardNode.h"
#include "Nodes/E_FakeInstanceNode.h"
#include "Nodes/E_GenericMetaNode.h"

// scripted states
#include "States/E_ScriptedState.h"
#include "States/E_ScriptedNodeRendererState.h"
#include <MinSG/SceneManagement/SceneDescription.h>
#include <MinSG/SceneManagement/Exporter/ExporterTools.h>
#include <MinSG/SceneManagement/Importer/ImporterTools.h>


// [ext:ImageCompare]
#ifdef MINSG_EXT_IMAGECOMPARE
#include "ImageCompare/E_AbstractImageComparator.h"
#include "ImageCompare/E_PyramidComparator.h"
#include "ImageCompare/E_SSIMComparator.h"
#include "ImageCompare/E_AverageComparator.h"
#include "ImageCompare/E_AbstractOnGpuComparator.h"
#endif /* MINSG_EXT_IMAGECOMPARE */

// [ext:ImpostorFactory]
#include "ImpostorFactory/E_ImpostorFactory.h"

// [ext:KeyFrameAnimation]
#include "KeyFrameAnimation/E_KeyFrameAnimationNode.h"

// [ext:LODRenderer]
#include "States/E_LODRenderer.h"

// [ext:MultiAlgoRendering]
#ifdef MINSG_EXT_MULTIALGORENDERING
#include "MultiAlgoRendering/ELib_MAR.h"
#endif

// [ext:OcclusionCulling]
#include "OcclusionCulling/E_CHCppRenderer.h"
#include "OcclusionCulling/E_CHCRenderer.h"
#include "OcclusionCulling/E_HOMRenderer.h"
#include "OcclusionCulling/E_NaiveOccRenderer.h"
#include "OcclusionCulling/E_OccludeeRenderer.h"
#include "OcclusionCulling/E_OccRenderer.h"

// [ext:OutOfCore]
#ifdef MINSG_EXT_OUTOFCORE
#include "OutOfCore/E_OutOfCore.h"
#endif /* MINSG_EXT_OUTOFCORE */

// [ext:ParticleSystem]
#ifdef MINSG_EXT_PARTICLE
#include "ParticleSystem/E_ParticleSystemNode.h"
#include "ParticleSystem/E_ParticleStates.h"
#include "ParticleSystem/E_ParticlePointEmitter.h"
#include "ParticleSystem/E_ParticleBoxEmitter.h"
#include "ParticleSystem/E_ParticleGravityAffector.h"
#include "ParticleSystem/E_ParticleReflectionAffector.h"
#include "ParticleSystem/E_ParticleFadeOutAffector.h"
#include "ParticleSystem/E_ParticleAnimator.h"
#endif // MINSG_EXT_PARTICLE

// [ext:Physics]
#ifdef MINSG_EXT_PHYSICS
    #include "Physics/E_PhysicWorld.h"
#endif /* MINSG_EXT_PHYSICS */

// [ext:PipelineStatistics]
#ifdef MINSG_EXT_PIPELINESTATISTICS
#include "PipelineStatistics/E_Collector.h"
#endif /* MINSG_EXT_PIPELINESTATISTICS */

// [ext:RAPT]
#ifdef MINSG_EXT_RAPT
#include "RAPT/E_RAPT.h"
#include "RAPT/NodeExtensions/E_RAPTGeometryNode.h"
#include "RAPT/AnimationExtensions/E_RAPTAnimationBehaviour.h"
#include "RAPT/ShaderExtensions/E_RAPTShaderState.h"
#endif // MINSG_EXT_RAPT

// [ext:RTree]
#ifdef MINSG_EXT_RTREE
#include "RTree/E_RTree.h"
#endif

// [ext:SamplingAnalysis]
#ifdef MINSG_EXT_SAMPLING_ANALYSIS
#include "SamplingAnalysis/E_SamplingAnalysis.h"
#endif /* MINSG_EXT_SAMPLING_ANALYSIS */

// [ext:SkeletalAnimation]
#ifdef MINSG_EXT_SKELETAL_ANIMATION
#include "SkeletalAnimation/E_SkeletalNode.h"
#include "SkeletalAnimation/Joints/E_JointNode.h"
#include "SkeletalAnimation/E_SkeletalAnimationBehaviour.h"
#include "SkeletalAnimation/E_SkeletalHardwareRendererState.h"
#include "SkeletalAnimation/E_SkeletalSoftwareRendererState.h"
#include "SkeletalAnimation/Joints/E_ArmatureNode.h"
#include "SkeletalAnimation/JointPose/E_SkeletalAbstractPose.h"
#include "SkeletalAnimation/JointPose/E_SkeletalMatrixPose.h"
#include "SkeletalAnimation/JointPose/E_SkeletalSRTPose.h"
#include "SkeletalAnimation/Util/E_SkeletalAnimationUtils.h"
#include "SkeletalAnimation/Joints/E_RigidJoint.h"
#endif

// [ext:Sound]
#ifdef MINSG_EXT_SOUND
#include "Behaviours/E_SoundEmittingBehaviour.h"
#include "Behaviours/E_SoundReceivingBehaviour.h"
#endif // MINSG_EXT_SOUND

// [ext:Tools]
#include "Tools/E_StatChart.h"
#include "Tools/E_DebugCamera.h"

// [ext:TreeSync]
#ifdef MINSG_EXT_TREE_SYNC
#include "TreeSync/E_Server.h"
#include "TreeSync/E_TreeSyncClient.h"
#endif /* MINSG_EXT_TREE_SYNC */

// [ext:TreeBuilder]
#include "TreeBuilder/E_TreeBuilder.h"

// [ext:TriangleTrees]
#ifdef MINSG_EXT_TRIANGLETREES
#include "TriangleTrees/E_TreeVisualization.h"
#include "TriangleTrees/E_TriangleTreeBuilder.h"
#endif /* MINSG_EXT_TRIANGLETREES */

// [ext:TwinPartitions]
#ifdef MINSG_EXT_TWIN_PARTITIONS
#include "TwinPartitions/E_TwinPartitionsRenderer.h"
#include <MinSG/Ext/TwinPartitions/Loader.h>
#endif /* MINSG_EXT_TWIN_PARTITIONS */

// [ext:ValuatedRegion]
#include "ValuatedRegion/E_ValuatedRegionNode.h"
#include "ValuatedRegion/E_DirectionalInterpolator.h"

// [ext:VisibilityMerge]
#ifdef MINSG_EXT_VISIBILITYMERGE
#include <MinSG/Ext/VisibilityMerge/Helper.h>
#include <MinSG/Ext/VisibilityMerge/Statistics.h>
#include <MinSG/Ext/VisibilityMerge/VisibilityMerge.h>
#endif // MINSG_EXT_VISIBILITYMERGE

// [ext:VisibilitySubdivision]
#include "VisibilitySubdivision/E_CostEvaluator.h"
#include "VisibilitySubdivision/E_PVSRenderer.h"
#include "VisibilitySubdivision/E_VisibilitySubdivisionRenderer.h"
#include "VisibilitySubdivision/E_VisibilityVector.h"

// [ext:VoxelWorld]
#ifdef MINSG_EXT_VOXEL_WORLD
#include "VoxelWorld/E_VoxelWorld.h"
#endif // MINSG_EXT_VOXEL_WORLD

// [ext:Waypoints]
#ifdef MINSG_EXT_WAYPOINTS
#include "Waypoints/E_Waypoint.h"
#include "Waypoints/E_FollowPathBehaviour.h"
#include "Waypoints/E_PathNode.h"
#endif /* MINSG_EXT_WAYPOINTS */

// --

#include "../SceneManagement/E_SceneManager.h"
#include <MinSG/Helper/StdNodeVisitors.h>

#include <E_Geometry/E_Vec3.h>
#include <E_Geometry/E_Matrix4x4.h>
#include <E_Rendering/Texture/E_Texture.h>
#include <E_Rendering/Mesh/E_Mesh.h>

#include <Util/IO/FileName.h>
#include <Util/Macros.h>

using namespace MinSG;
using namespace E_Rendering;
using namespace E_Geometry;

namespace E_MinSG {

/*
 * init classes and Members
 */
void init_ext(EScript::Namespace * /*globals*/,EScript::Namespace * lib) {
	// [ext:AdaptiveGlobalVisibilitySampling]
#ifdef MINSG_EXT_ADAPTIVEGLOBALVISIBILITYSAMPLING
	{
		EScript::Namespace * ns = new EScript::Namespace();
		declareConstant(lib, "AGVS", ns);
		AGVS::E_AdaptiveGlobalVisibilitySampling::init(*ns);
	}
#endif /* MINSG_EXT_ADAPTIVEGLOBALVISIBILITYSAMPLING */

	// [ext:Behaviours]
	E_KeyFrameAnimationBehaviour::init(*lib);
	E_ScriptedNodeBehaviour::init(*lib);
	E_ScriptedStateBehaviour::init(*lib);
	E_SimplePhysics2::init(*lib);
	E_BehaviourGroup::init(*lib);
	E_AbstractBehaviourDecorator::init(*lib);
	E_TimedBehaviourDecorator::init(*lib);

	// [ext:BlueSurfels]
	#ifdef MINSG_EXT_BLUE_SURFELS
	BlueSurfels::init(*lib);
	#endif // MINSG_EXT_BLUE_SURFELS

	#ifdef MINSG_EXT_MIXED_EXTERN_VISIBILITY
	MixedExtVisibility::init(*lib);
	#endif // MINSG_EXT_MIXED_EXTERN_VISIBILITY

	// [ext:FancyStuff]
	E_BudgetAnnotationState::init(*lib);
	E_BillboardNode::init(*lib);
	E_FakeInstanceNode::init(*lib);
	E_GenericMetaNode::init(*lib);
	E_StrangeExampleRenderer::init(*lib);
	E_EnvironmentState::init(*lib);
	E_ImpostorFactory::init(lib);
	E_MirrorState::init(*lib);
	E_ProjSizeFilterState::init(*lib);
	E_RandomColorRenderer::init(*lib);
	E_ShadowState::init(*lib);

	// -----------------------------------------------------------
	// scripted states
	E_ScriptedState::init(*lib);
	E_ScriptedNodeRendererState::init(*lib);
	{ // export/import scripted states
		static const char *const STATE_TYPE_SCRIPTED_STATE = "scriptedState";

		using namespace MinSG::SceneManagement;

		static std::unique_ptr<std::pair<EScript::Runtime&,EScript::ObjRef>> exportHandler;

		const auto exporterFn = [&](ExporterContext &,DescriptionMap & desc,State *state) {
			desc.setString(Consts::ATTR_STATE_TYPE, STATE_TYPE_SCRIPTED_STATE);
//			std::cout << "Exporting ScriptedState..."<<std::endl;

			if(exportHandler){
				Util::Reference<State> refHolder(state);

				EScript::ObjRef eDescription = E_Util::E_Utils::convertGenericAttributeToEScriptObject(&desc);
				EScript::ObjRef result = EScript::callFunction(exportHandler->first,exportHandler->second.get(),
											EScript::ParameterValues(EScript::create(state),eDescription));

				std::unique_ptr<Util::GenericAttribute> desc2(E_Util::E_Utils::convertEScriptObjectToGenericAttribute(eDescription));
				if( dynamic_cast<Util::GenericAttributeMap*>(desc2.get()) )
					desc = std::move( *dynamic_cast<Util::GenericAttributeMap*>(desc2.get()) );
				refHolder.detachAndDecrease();
			}
		};

		ExporterTools::registerStateExporter(ScriptedState::getClassId(),exporterFn);
		ExporterTools::registerStateExporter(ScriptedNodeRendererState::getClassId(),exporterFn);

		//! [ESMF] MinSG.setScriptedStateImporter( callback(state,Map stateDescription) )
		ES_FUNCTION(lib,"setScriptedStateExporter",1,1,{
			if(parameter[0].toBool())
				exportHandler.reset(new std::pair<EScript::Runtime&,EScript::ObjRef>(rt,parameter[0]));
			else
				exportHandler.reset();
			return nullptr;
		})


		static std::unique_ptr<std::pair<EScript::Runtime&,EScript::ObjRef>> importHandler;
		ImporterTools::registerStateImporter([](ImportContext &,const std::string& stateType,const DescriptionMap & desc,Node *parent) -> bool {
			if(stateType != STATE_TYPE_SCRIPTED_STATE || !importHandler ) // check parent != nullptr is done by SceneManager
				return false;
//			std::cout << "Importing ScriptedState..."<<std::endl;
			Util::Reference<Node> refHolder(parent);

			EScript::ObjRef eDescription = E_Util::E_Utils::convertGenericAttributeToEScriptObject(&desc);
			EScript::ObjRef result = EScript::callFunction(importHandler->first,importHandler->second.get(),
												EScript::ParameterValues(EScript::create(parent),eDescription));
			refHolder.detachAndDecrease();
			return result.toBool();
		});
		//! [ESMF] MinSG.setScriptedStateImporter( callback(node,Map stateDescription) )
		ES_FUNCTION(lib,"setScriptedStateImporter",1,1,{
			if(parameter[0].toBool())
				importHandler.reset(new std::pair<EScript::Runtime&,EScript::ObjRef>(rt,parameter[0]));
			else
				importHandler.reset();
			return nullptr;
		})
	}
	// -----------------------------------------------------------


	/*! [ESF] Vec3 calculateSunPosition(timeOfDay[,julianDay=0,[timeZone=0[,longitude=0[,latitude=0]]]])
	 East = x,  up = y, South = z
	 All times in decimal form (6.25 = 6:15 AM)
	 All angles in Radians
	 From IES Lighting Handbook pg 361
	 \see http://www.cs.utah.edu/~shirley/papers/sunsky/code/
	*/
	ES_FUNCTION(lib,"calculateSunPosition",1,5,{
		// InitSunThetaPhi
		const float timeOfDay=parameter[0].toFloat();
		int julianDay=parameter[1].toInt(0);

		const float longitude=parameter[3].toFloat(0);
		const float latitude_rad=parameter[4].toFloat(0)*M_PI/180.0; //radians(latitude)
		const float standardMeridian = parameter[2].toFloat(0) * 15.f;  // sm is actually timezone number (east to west, zero based...)

		const float solarTime = timeOfDay +
				(0.170f*sin(4*M_PI*(julianDay - 80.f)/373.0f) -
				0.129f*sin(2*M_PI*(julianDay - 8.f)/355.0f)) +
				(standardMeridian - longitude)/15.f;

		const float solarDeclination = (0.4093f*sin(2.0f*M_PI*(julianDay - 81.f)/368.0f));

		const float solarAltitude= asin(sin(latitude_rad) * sin(solarDeclination) -
				cos(latitude_rad) * cos(solarDeclination) * cos(M_PI*solarTime/12.f));

		const float opp = -cos(solarDeclination) * sin(M_PI*solarTime/12.f);
		const float adj = -(cos(latitude_rad) * sin(solarDeclination) +
				sin(latitude_rad) * cos(solarDeclination) *  cos(M_PI*solarTime/12.f));
		const float solarAzimuth=atan2(opp,adj);

		const float phiS = -solarAzimuth;
		const float thetaS = M_PI / 2.0 - solarAltitude;

	//    return new E_Geometry::E_Vec3( Vec3(cos(phiS)*sin(thetaS), sin(phiS)*sin(thetaS), cos(thetaS))); // South = x,  East = y, up = z
		return new E_Geometry::E_Vec3( Geometry::Vec3(sin(phiS)*sin(thetaS), cos(thetaS), cos(phiS)*sin(thetaS))); // East = x,  up = y, South = z
	})

	//! [ESF] Node createSkybox(filename)
	ES_FUN(lib,"createSkybox",1,1,EScript::create(SkyboxState::createSkybox(parameter[0].toString())))

	// [ext:KeyFrameAnimation]
	E_KeyFrameAnimationNode::init(*lib);

	// [ext:LODRenderer]
	E_LODRenderer::init(*lib);

	// [ext:OcclusionCulling]
	E_CHCppRenderer::init(*lib);
	E_CHCRenderer::init(*lib);
	E_HOMRenderer::init(*lib);
	E_NaiveOccRenderer::init(*lib);
	E_OccludeeRenderer::init(*lib);
	E_OccRenderer::init(*lib);

	// [ext:Tools]
	E_StatChart::init(*lib);
	E_DebugCamera::init(*lib);

	// [ext:TreeBuilder]
	E_TreeBuilder::init(*lib);

	// [ext:ValuatedRegion]
	E_ValuatedRegionNode::init(*lib);
	E_DirectionalInterpolator::init(*lib);

	// ---- temp
	//! [ESF] AbstractBehaviour __createSimplePhysics(Node[,vec3])
	ES_FUN(lib,"__createSimplePhysics",1,2,new E_AbstractNodeBehaviour(
			parameter.count() < 2 ? new SimplePhysics(parameter[0].to<MinSG::Node*>(rt)) : new SimplePhysics(parameter[0].to<MinSG::Node*>(rt), parameter[1].to<Geometry::Vec3>(rt))))

	//! [ESF] AbstractBehaviour __loadCamPath(Node, filename)
	ES_FUN(lib,"__loadCamPath",2,2,new E_AbstractNodeBehaviour(
			new SRTBehaviour((parameter[0].to<MinSG::Node*>(rt)),Util::FileName(parameter[1].toString()))))


	// -----------------------------------------------------------------
	//	Guarded extensions (ordered by their guard!!!!!!!!!!!!)

	// [ext:ColorCube]
#ifdef MINSG_EXT_COLORCUBES
	E_ColorCube::init(*lib);
	E_ColorCubeRenderer::init(*lib);
#endif // MINSG_EXT_COLORCUBES

	// [ext:D3Fact]
#ifdef MINSG_EXT_D3FACT
	E_D3Fact::init(lib);
#endif  // MINSG_EXT_D3FACT

	// [ext:SVS]
#ifdef MINSG_EXT_SVS
	{
		EScript::Namespace * ns = new EScript::Namespace();
		declareConstant(lib, "SVS", ns);
		SVS::E_BudgetRenderer::init(*ns);
		SVS::E_GeometryNodeCollector::init(*ns);
		SVS::E_Helper::init(*ns);
		SVS::E_PreprocessingContext::init(*ns);
		SVS::E_Renderer::init(*ns);
		SVS::E_SamplePoint::init(*ns);
		SVS::E_SphereVisualizationRenderer::init(*ns);
		SVS::E_VisibilitySphere::init(*ns);
	}
#endif /* MINSG_EXT_SVS */

	// [ext:ThesisJonas]
#ifdef MINSG_EXT_THESISJONAS
	{
		EScript::Namespace * ns = new EScript::Namespace();
		declareConstant(lib, "ThesisJonas", ns);
		ThesisJonas::E_Renderer::init(*ns);
		ThesisJonas::E_Preprocessor::init(*ns);
	}
#endif /* MINSG_EXT_THESISJONAS */

	// [ext:ThesisPeter]
#ifdef MINSG_EXT_THESISPETER
	{
		EScript::Namespace * ns = new EScript::Namespace();
		declareConstant(lib, "ThesisPeter", ns);
		ThesisPeter::E_LightNodeManager::init(*ns);
	}
#endif /* MINSG_EXT_THESISPETER */

#ifdef MINSG_EXT_THESISSTANISLAW
	{
		EScript::Namespace * ns = new EScript::Namespace();
		declareConstant(lib, "ThesisStanislaw", ns);
		ThesisStanislaw::E_PolygonIndexingState::init(*ns);
		ThesisStanislaw::E_LightPatchRenderer::init(*ns);
		ThesisStanislaw::E_PhotonSampler::init(*ns);
		ThesisStanislaw::E_PhongGI::init(*ns);
		ThesisStanislaw::E_ApproxSceneDebug::init(*ns);
		ThesisStanislaw::E_PhotonRenderer::init(*ns);
	}
#endif // MINSG_EXT_THESISSTANISLAW

	// [ext:TreeSync]
#ifdef MINSG_EXT_TREE_SYNC
	{
		EScript::Namespace * ns = new EScript::Namespace();
		declareConstant(lib,"TreeSync",ns);
		TreeSync::E_Server::init(*ns);
		TreeSync::E_TreeSyncClient::init(*ns);
	}
#endif // MINSG_EXT_TREE_SYNC

	// [ext:DelaunayTriangulation]
#ifdef MINSG_EXT_TRIANGULATION
	{
		EScript::Namespace * ns = new EScript::Namespace();
		declareConstant(lib,"Triangulation",ns);
		Triangulation::E_Delaunay2d::init(*ns);
		Triangulation::E_Delaunay3d::init(*ns);

	}
#endif  // MINSG_EXT_TRIANGULATION

	// [ext:Evaluator]
#ifdef MINSG_EXT_EVALUATORS
	E_Evaluator::init(*lib);
	E_AdaptCullEvaluator::init(*lib);
	E_AreaEvaluator::init(*lib);
	E_BoxQualityEvaluator::init(*lib);
	E_ColorVisibilityEvaluator::init(*lib);
	E_OccOverheadEvaluator::init(*lib);
	E_OverdrawFactorEvaluator::init(*lib);
	E_ScriptedEvaluator::init(*lib);
	E_StatsEvaluator::init(*lib);
	E_TrianglesEvaluator::init(*lib);
	E_VisibilityEvaluator::init(*lib);
#endif /* MINSG_EXT_EVALUATORS */

	// [ext:ImageCompare]
#ifdef MINSG_EXT_IMAGECOMPARE
	E_AbstractImageComparator::init(*lib);
	E_AbstractOnGpuComparator::init(*lib);
	E_PyramidComparator::init(*lib);
	E_SSIMComparator::init(*lib);
	E_AverageComparator::init(*lib);
#endif // MINSG_EXT_IMAGECOMPARE

	// [ext:MultiAlgoRendering]
#ifdef MINSG_EXT_MULTIALGORENDERING
	E_MAR::init(lib);
#endif // MINSG_EXT_MULTIALGORENDERING

	// [ext:OutOfCore]
#ifdef MINSG_EXT_OUTOFCORE
	E_OutOfCore::init(*lib);
#endif // MINSG_EXT_OUTOFCORE

	// [ext:ParticleSystem]
#ifdef MINSG_EXT_PARTICLE
	E_ParticleSystemNode::init(*lib);
	E_ParticleAffector::init(*lib);
	E_ParticleEmitter::init(*lib);
	E_ParticlePointEmitter::init(*lib);
	E_ParticleBoxEmitter::init(*lib);
	E_ParticleGravityAffector::init(*lib);
	E_ParticleFadeOutAffector::init(*lib);
	E_ParticleReflectionAffector::init(*lib);
	E_ParticleAnimator::init(*lib);
#endif // MINSG_EXT_PARTICLE

    // [ext:Physics]
    #ifdef MINSG_EXT_PHYSICS
        Physics::E_PhysicWorld::init(*lib);
    #endif // MINSG_EXT_PHYSICS

#ifdef MINSG_EXT_PIPELINESTATISTICS
	{
		EScript::Namespace * ns = new EScript::Namespace();
		declareConstant(lib, "PipelineStatistics", ns);
		PipelineStatistics::E_Collector::init(*ns);
	}
#endif /* MINSG_EXT_PIPELINESTATISTICS */

    // [ext:RAPT]
#ifdef MINSG_EXT_RAPT
    initRAPT(lib);
    E_RAPTGeometryNode::init(*lib);
    E_RAPTAnimationBehaviour::init(*lib);
    E_RAPTShaderState::init(*lib);
#endif // MINSG_EXT_RAPT


	// [ext:RTree]
#ifdef MINSG_EXT_RTREE
	E_RTree::init(*lib);
#endif // MINSG_EXT_RTREE

	// [ext:SamplingAnalysis]
#ifdef MINSG_EXT_SAMPLING_ANALYSIS
	E_SamplingAnalysis::init(*lib);
#endif // MINSG_EXT_SAMPLING_ANALYSIS

	// [ext:SkeletalAnimation]
#ifdef MINSG_EXT_SKELETAL_ANIMATION
	E_SkeletalNode::init(*lib);
	E_SkeletalAnimationBehaviour::init(*lib);
	E_SkeletalHardwareRendererState::init(*lib);
    E_SkeletalSoftwareRendererState::init(*lib);
	E_JointNode::init(*lib);
	E_ArmatureNode::init(*lib);
    E_SkeletalAbstractPose::init(*lib);
    E_SkeletalMatrixPose::init(*lib);
    E_SkeletalSRTPose::init(*lib);
    E_RigidJoint::init(*lib);
    initSkeletalAnimationUtils(lib);
#endif // MINSG_EXT_SKELETAL_ANIMATION

	// [ext:Sound]
#ifdef MINSG_EXT_SOUND
	E_SoundEmittingBehaviour::init(*lib);
	E_SoundReceivingBehaviour::init(*lib);
#endif // MINSG_EXT_SOUND

	// [ext:TriangleTrees]
#ifdef MINSG_EXT_TRIANGLETREES
	E_TriangleTreeBuilder::init(*lib);
	E_TreeVisualization::init(*lib);
#endif // MINSG_EXT_TRIANGLETREES

	// [ext:TwinPartitions]
#ifdef MINSG_EXT_TWIN_PARTITIONS
	E_TwinPartitionsRenderer::init(*lib);
	ES_FUN(lib, "importTwinPartitions", 1, 1, EScript::create(MinSG::TwinPartitions::Loader::importPartitions(Util::FileName(parameter[0].toString()))))
#endif // MINSG_EXT_TWIN_PARTITIONS

	// [ext:VisibilitySubdivision]
#ifdef MINSG_EXT_VISIBILITY_SUBDIVISION
	E_CostEvaluator::init(*lib);
	E_PVSRenderer::init(*lib);
	E_VisibilitySubdivisionRenderer::init(*lib);
	E_VisibilityVector::init(*lib);
#endif // MINSG_EXT_VISIBILITY_SUBDIVISION


	// [ext:VisibilityMerge]
#ifdef MINSG_EXT_VISIBILITYMERGE
	//! [ValuatedRegionNode, ListNode] visibilityMerge(SceneManager, ValuatedRegionNode, Number, Number, Number, Number)
	ES_FUNCTION(lib, "visibilityMerge", 6, 6, {
		SceneManagement::SceneManager * mgr = **EScript::assertType<E_SceneManager>(rt, parameter[0]);
		ValuatedRegionNode * vrNode = **EScript::assertType<E_ValuatedRegionNode>(rt, parameter[1]);
		const auto result =
				MinSG::VisibilityMerge::VisibilityMerge::run(mgr,
															 vrNode,
															 parameter[2].toUInt(),
															 parameter[3].toUInt(),
															 parameter[4].toUInt(),
															 parameter[5].toUInt());
		EScript::Array * array = EScript::Array::create();
		array->pushBack(EScript::create(result.first));
		array->pushBack(EScript::create(result.second));
		return array;
	});

	//! Array getVisibilityCells(ValuatedRegionNode)
	ES_FUNCTION(lib, "getVisibilityCells", 1, 1, {
		ValuatedRegionNode * root = **EScript::assertType<E_ValuatedRegionNode>(rt, parameter[0]);

		const auto cells = MinSG::VisibilityMerge::Helper::collectVisibilityCells(root);

		EScript::Array * array = EScript::Array::create();
		for(const auto & cell : cells) {
			E_Node * en = EScript::create(cell);
			if(en) {
				array->pushBack(en);
			}
		}
		return array;
	});

	//! Number getRuntime(ValuatedRegionNode)
	ES_FUN(lib, "getRuntime", 1, 1, EScript::Number::create(MinSG::VisibilityMerge::Helper::getRuntime(**EScript::assertType<E_ValuatedRegionNode>(rt, parameter[0]))));
#endif // MINSG_EXT_VISIBILITYMERGE


// [ext:VoxelWorld]
#ifdef MINSG_EXT_VOXEL_WORLD
	VoxelWorld::init(*lib);
#endif // M

	// [ext:Waypoints]
#ifdef MINSG_EXT_WAYPOINTS
	E_PathNode::init(*lib);
	E_FollowPathBehaviour::init(*lib);
	E_Waypoint::init(*lib);
#endif // MINSG_EXT_WAYPOINTS



}

}
