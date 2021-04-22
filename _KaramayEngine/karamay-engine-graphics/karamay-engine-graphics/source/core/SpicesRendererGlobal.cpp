#include "SpicesRendererGlobal.h"

CameraFactory* CameraCreator = nullptr;

PipelineFactory* PipelineCreator = nullptr;
PipelineAssemblageInfoFactory* PipelineAssemblageInfoCreator = nullptr;

DirectionalLightFactory* DirectionalLightCreator = nullptr;
PointLightFactory* PointLightCreator = nullptr;
SpotLightFactory* SpotLightCreator = nullptr;
MaterialFactory* MaterialCreator = nullptr;
SceneRenderingDataFactory* SceneRenderingDataCreator;
Texture2DFactory* Texture2DCreator = nullptr;

MeshFactory* MeshCreator = nullptr;
ParticleFactory* ParticleCreator = nullptr;
ParticleSystemFactory* ParticleSystemCreator;

RendererFactory* RendererCreator = nullptr;

RendererAllocatorFactory* RendererAllocatorCreator = nullptr;

SceneFactory* SceneCreator = nullptr;

ShaderFactory* ShaderCreator = nullptr;
ShaderAssemblageInfoFactory* ShaderAssemblageInfoCreator = nullptr;

WindowFactory* WindowCreator = nullptr;

RendererBase* DefaultRenderer = nullptr;



