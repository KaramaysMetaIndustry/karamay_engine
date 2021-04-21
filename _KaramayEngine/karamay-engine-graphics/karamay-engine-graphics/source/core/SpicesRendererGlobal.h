#pragma once

#include "Abstract/MetaObject/MetaObject.h"

#include "Camera/CameraBase.h"

#include "Pipeline/PipelineBase.h"
#include "Pipeline/PipelineAssemblageInfoBase.h"

#include "PipelineRuntimeData/Abstract/PipelineRuntimeDataBase.h"
#include "PipelineRuntimeData/Light/Abstract/LightBase.h"
#include "PipelineRuntimeData/Light/DirectionalLightBase.h"
#include "PipelineRuntimeData/Light/PointLightBase.h"
#include "PipelineRuntimeData/Light/SpotLightBase.h"
#include "PipelineRuntimeData/Material/MaterialBase.h"
#include "PipelineRuntimeData/SceneRenderingData/SceneRenderingDataBase.h"
#include "PipelineRuntimeData/Texture/Abstract/TextureBase.h"
#include "PipelineRuntimeData/Texture/Texture2DBase.h"

#include "RenderableObject/Abstract/RenderableObjectBase.h"
#include "RenderableObject/Mesh/MeshBase.h"
#include "RenderableObject/ParticleSystem/ParticleBase.h"
#include "RenderableObject/ParticleSystem/ParticleSystemBase.h"

#include "Renderer/RendererBase.h"

#include "RendererAllocator/RendererAllocatorBase.h"

#include "Scene/SceneBase.h"

#include "Shader/ShaderBase.h"
#include "Shader/ShaderAssemblageInfoBase.h"

#include "Window/WindowBase.h"


extern CameraFactory* CameraCreator;

extern PipelineFactory* PipelineCreator;
extern PipelineAssemblageInfoFactory* PipelineAssemblageInfoCreator;

extern DirectionalLightFactory* DirectionalLightCreator;
extern PointLightFactory* PointLightCreator;
extern SpotLightFactory* SpotLightCreator;
extern MaterialFactory* MaterialCreator;
extern SceneRenderingDataFactory* SceneRenderingDataCreator;
extern Texture2DFactory* Texture2DCreator;

extern MeshFactory* MeshCreator;
extern ParticleFactory* ParticleCreator;
extern ParticleSystemFactory* ParticleSystemCreator;

extern RendererFactory* RendererCreator;

extern RendererAllocatorFactory* RendererAllocatorCreator;

extern SceneFactory* SceneCreator;

extern ShaderFactory* ShaderCreator;
extern ShaderAssemblageInfoFactory* ShaderAssemblageInfoCreator;

extern WindowFactory* WindowCreator;

extern RendererBase* DefaultRenderer;


