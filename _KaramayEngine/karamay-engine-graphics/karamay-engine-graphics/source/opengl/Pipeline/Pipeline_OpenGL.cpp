#include "Pipeline_OpenGL.h"
#include "OpenGL/Implement_OpenGL.h"
#include "OpenGL/Pipeline/PipelineCommonTool/PipelineCommonTool.h"

void Pipeline_OpenGL::Assembly(PipelineAssemblageInfoBase* Info)
{
	PipelineBase::Assembly(Info);

	auto InfoOp = dynamic_cast<PipelineAssemblageInfo_OpenGL*>(Info);
	if (InfoOp)
	{
		// create shaders
		auto ShaderAssemblageInfos = InfoOp->ShaderAssmblageInfos;
		for (auto It = ShaderAssemblageInfos.begin(); It != ShaderAssemblageInfos.end(); ++It)
		{
			auto ShaderInfo = *It;
			if (ShaderInfo)
			{
				ShaderBase* Shader = new Shader_OpenGL();
				Shader->Assembly(ShaderInfo);
				Shaders.push_back(Shader);
			}
		}

		// create program
		programObj = glCreateProgram();
		std::cout << PipelineAssemblageInfo->PipelineName << ", " << programObj << std::endl;

		for (auto It = Shaders.begin(); It != Shaders.end(); ++It)
		{
			auto Shader = dynamic_cast<Shader_OpenGL*>(*It);
			if (Shader)
			{
				glAttachShader(programObj, Shader->GetShaderObj());
			}
		}

		glLinkProgram(programObj);

		CommonTool->Initalize(programObj);
	}

}

void Pipeline_OpenGL::PipelineRender(float DeltaTime)
{
	glUseProgram(programObj);
	PipelineBase::PipelineRender(DeltaTime);
}

void Pipeline_OpenGL::AssociateTo(RenderableObjectBase* RenderableObject)
{
	PipelineBase::AssociateTo(RenderableObject);
	RenderableObject->Install();
}

void Pipeline_OpenGL::CheckState()
{
	// GL_DELETE_STATUS, GL_LINK_STATUS, GL_VALIDATE_STATUS, GL_INFO_LOG_LENGTH, GL_ATTACHED_SHADERS, 
	// GL_ACTIVE_ATTRIBUTES, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, GL_ACTIVE_UNIFORMS, GL_ACTIVE_UNIFORM_MAX_LENGTH
	GLint result;

	glGetProgramiv(programObj, GL_ATTACHED_SHADERS, &result);
	std::cout << "this program has " << result << " shaders" << std::endl;
	
	glGetProgramiv(programObj, GL_ACTIVE_ATTRIBUTES, &result);
	std::cout << "this program has " << result << " attributes" << std::endl;

	glGetProgramiv(programObj, GL_ACTIVE_UNIFORMS, &result);
	std::cout << "this program has " << result << " uniforms" << std::endl;

	char info[512];
	glGetProgramiv(programObj, GL_LINK_STATUS, &result);
	if (result != GL_TRUE) {
		glGetProgramInfoLog(programObj, 512, NULL, info);
		std::cout << "program link fail : " << info << std::endl;
	}
}

Pipeline_OpenGL::Pipeline_OpenGL()
{
	CommonTool = new PipelineCommonTool();
}

Pipeline_OpenGL::~Pipeline_OpenGL()
{
}

PipelineBase* PipelineFactory_OpenGL::CreatePipeline()
{
	return new Pipeline_OpenGL();
}
