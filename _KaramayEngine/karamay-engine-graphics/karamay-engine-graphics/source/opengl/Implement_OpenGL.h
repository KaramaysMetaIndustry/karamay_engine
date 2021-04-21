#pragma once
#include "Core/SpicesRendererGlobal.h"

#include "Camera/Camera_OpenGL.h"

#include "PipelineRuntimeData/Material/Material_OpenGL.h"
#include "PipelineRuntimeData/Texture/Texture2D_OpenGL.h"
#include "PipelineRuntimeData/Light/DirectionalLight_OpenGL.h"
#include "PipelineRuntimeData/Light/PointLight_OpenGL.h"
#include "PipelineRuntimeData/Light/SpotLight_OpenGL.h"
#include "PipelineRuntimeData/SceneRenderingData/SceneRenderingData_OpenGL.h"

#include "Pipeline/Pipeline_OpenGL.h"
#include "Pipeline/PipelineAssemblageInfo_OpenGL.h"
#include "RenderableObject/Mesh/Mesh_OpenGL.h"
#include "RenderableObject/ParticleSystem/ParticleSystem_OpenGL.h"

#include "Renderer/Renderer_OpenGL.h"

#include "Scene/Scene_OpenGL.h"

#include "Shader/Shader_OpenGL.h"
#include "Shader/ShaderAssemblageInfo_OpenGL.h"

#include "Window/Window_GLFW.h"

#include "Pipeline/PipelineCommonTool/PipelineCommonTool.h"

#include "RendererAllocator/RendererAllocator_OpenGL.h"

enum class EPrimitive
{
	Points = GL_POINTS,

	Lines = GL_LINES,
	Line_Strip = GL_LINE_STRIP,
	Line_Loop = GL_LINE_LOOP,

	Triangles = GL_TRIANGLES,
	Triangle_Strip = GL_TRIANGLE_STRIP,
	Triangle_Fan = GL_TRIANGLE_FAN
};