#include "Material_OpenGL.h"
#include "OpenGL/Implement_OpenGL.h"
#include "OpenGL/Pipeline/PipelineCommonTool/PipelineCommonTool.h"

void Material_OpenGL::Install()
{
	MaterialBase::Install();
}

void Material_OpenGL::Submit(PipelineBase* AssociatedPipeline)
{
	if (AssociatedPipeline)
	{
		auto Submitter = dynamic_cast<Pipeline_OpenGL*>(AssociatedPipeline)->CommonTool;
		if (Submitter)
		{
			auto AlbedoMapOp = static_cast<Texture2D_OpenGL*>(AlbedoMap);
			if (AlbedoMapOp)
				AlbedoMapOp->UniformName = "mat.albedo_map";

			auto NormalMapOp = static_cast<Texture2D_OpenGL*>(NormalMap);
			if (NormalMapOp)
				NormalMapOp->UniformName = "mat.normal_map";
			
			auto MetalnessMapOp = static_cast<Texture2D_OpenGL*>(MetalnessMap);
			if (MetalnessMapOp)
				MetalnessMapOp->UniformName = "mat.metalness_map";
			
			auto RoughnessMapOp = static_cast<Texture2D_OpenGL*>(RoughnessMap);
			if (RoughnessMapOp)
				RoughnessMapOp->UniformName = "mat.roughness_map";
			
			auto DisplacementMapOp = static_cast<Texture2D_OpenGL*>(DisplacementMap);
			if (DisplacementMapOp)
				DisplacementMapOp->UniformName = "mat.displacement_map";
			
			auto AmbientOcclusionOp = static_cast<Texture2D_OpenGL*>(AmbientOcclusionMap);
			if (AmbientOcclusionOp)
				AmbientOcclusionOp->UniformName = "mat.ambient_acclusion_map";
		}
	}

	MaterialBase::Submit(AssociatedPipeline);
}

void Material_OpenGL::Uninstall()
{
	MaterialBase::Uninstall();
}

Material_OpenGL::Material_OpenGL()
{
}

Material_OpenGL::~Material_OpenGL()
{
}
