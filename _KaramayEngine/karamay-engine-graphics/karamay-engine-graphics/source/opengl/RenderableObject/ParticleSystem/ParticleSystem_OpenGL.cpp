#include "ParticleSystem_OpenGL.h"
#include "OpenGL/Implement_OpenGL.h"
#include "OpenGL/Pipeline/PipelineCommonTool/PipelineCommonTool.h"

void ParticleSystem_OpenGL::Install()
{
	if (AssociatedPipeline)
	{
		auto CommonTool 
			= dynamic_cast<Pipeline_OpenGL*>(AssociatedPipeline)->CommonTool;
		if (CommonTool)
		{
			glGenVertexArrays(1, &vertexArrayObject0);
			glGenVertexArrays(1, &vertexArrayObject1);
			glGenBuffers(1, &vertexBufferObject0);
			glGenBuffers(1, &vertexBufferObject1);
			glGenBuffers(1, &elementBufferObject);

			float vertices[] = {
				-0.5f, -0.5f, -0.5f,
				 0.5f, -0.6f, -0.2f,
				 0.5f,  0.7f, -0.5f,

				 0.9f,  0.1f, -0.3f,
				-0.2f,  0.8f, -0.5f,
				-0.4f, -0.5f, -0.6f,
			};

			glBindVertexArray(vertexArrayObject0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject0);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 108, vertices, GL_DYNAMIC_COPY);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (const GLvoid*)0);

			glBindVertexArray(vertexArrayObject1);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject1);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 108, vertices, GL_DYNAMIC_COPY);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (const GLvoid*)0);

			glCreateTransformFeedbacks(1, &transformFeedbackObject);
			glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedbackObject);
			static const char* const varings[] = { "position_out" };
			CommonTool->SetTransformFeedbackVarings(1, varings, GL_INTERLEAVED_ATTRIBS);


			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
		}
	}

}

void ParticleSystem_OpenGL::Render(float DeltaTime)
{
	glm::vec3 PatchPositions[] = {
					glm::vec3(0.0f,  0.0f,  0.0f),
					glm::vec3(2.0f,  5.0f, -15.0f),
					glm::vec3(-1.5f, -2.2f, -2.5f),
					glm::vec3(-3.8f, -2.0f, -12.3f),
					glm::vec3(2.4f, -0.4f, -3.5f),
					glm::vec3(-1.7f,  3.0f, -7.5f),
					glm::vec3(1.3f, -2.0f, -2.5f),
					glm::vec3(1.5f,  2.0f, -2.5f),
					glm::vec3(1.5f,  0.2f, -1.5f),
					glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	if (OwnedScene && AssociatedRenderer && AssociatedPipeline)
	{
		glBindVertexArray(bZero ? vertexArrayObject0 : vertexArrayObject1);
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedbackObject);
		glTransformFeedbackBufferBase(transformFeedbackObject, 0, bZero ? vertexBufferObject1 : vertexBufferObject0);

		auto Camera = OwnedScene->GetDefaultCamera();
		auto CommonTool = dynamic_cast<Pipeline_OpenGL*>(AssociatedPipeline)->CommonTool;
		if (Camera && CommonTool)
		{
			// fetch transform matrix and MVP matrix
			glm::mat4 TransformMatrix(1.0f); // transform
			glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), Position); // local -> world
			glm::mat4 ViewMatrix = Camera->GetViewMatrix(); // world -> view
			glm::mat4 ProjectionMatrix = AssociatedRenderer->GetProjectionMatrix(); // view -> clip

			CommonTool->UpdateUniformMatrix4("TransformMatrix", TransformMatrix);
			CommonTool->UpdateUniformMatrix4("ModelMatrix", ModelMatrix);
			CommonTool->UpdateUniformMatrix4("ViewMatrix", ViewMatrix);
			CommonTool->UpdateUniformMatrix4("ProjectionMatrix", ProjectionMatrix);

			for (size_t i = 0; i < 10; ++i)
			{
				std::string Name = "PatchPositions[" + std::to_string(i) + "]";
				CommonTool->UpdateUniform3f(Name.c_str(), PatchPositions[i]);
			}
			

			glPointSize(1.0f);

			glEnableVertexAttribArray(0);
			glBeginTransformFeedback(GL_POINTS);
			glDrawArraysInstancedBaseInstance(GL_POINTS, 0, 6, 4, 0);
			glEndTransformFeedback();
			glDisableVertexAttribArray(0);

			glBindVertexArray(0);
		}
	}

	bZero = !bZero;
}

void ParticleSystem_OpenGL::Uninstall()
{
}

ParticleSystem_OpenGL::ParticleSystem_OpenGL()
{
	// set pipeline assemblage info
	PipelineAssemblageInfo = new PipelineAssemblageInfo_OpenGL();
	PipelineAssemblageInfo->PipelineName = "BasicParticleSystemPipeline";
	auto Vert = new ShaderAssemblageInfo_OpenGL();
	auto Frag = new ShaderAssemblageInfo_OpenGL();
	Vert->FilePath = "Shader\\ParticleSystem\\ParticleSystem.vert";
	Vert->Type = EShaderType::VertexShader;
	Frag->FilePath = "Shader\\ParticleSystem\\ParticleSystem.frag";
	Frag->Type = EShaderType::FragmentShader;
	PipelineAssemblageInfo->ShaderAssmblageInfos.push_back(Vert);
	PipelineAssemblageInfo->ShaderAssmblageInfos.push_back(Frag);

	bZero = true;
}

ParticleSystem_OpenGL::~ParticleSystem_OpenGL()
{
}
