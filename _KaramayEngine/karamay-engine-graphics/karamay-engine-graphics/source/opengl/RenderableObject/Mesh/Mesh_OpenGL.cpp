#include "Mesh_OpenGL.h"
#include "OpenGL/Implement_OpenGL.h"
#include "OpenGL/Pipeline/PipelineCommonTool/PipelineCommonTool.h"

#define AttributeOffset(offset) (const GLvoid*)(offset * sizeof(GLfloat))

void Mesh_OpenGL::Install()
{
	if (Positions.size() != 0 && UVs.size() != 0)
	{
		glGenVertexArrays(1, &vertexArrayObject);
		glGenBuffers(vertexBufferObjects.size(), &vertexBufferObjects[0]);
		glGenBuffers(1, &instanceBufferObject);
		glGenBuffers(1, &elementBufferObject);

		// set elements array
		if (Indices.size() != 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * Indices.size(), &Indices.at(0), GL_STATIC_DRAW);
		}
		// set vertex array
		glBindVertexArray(vertexArrayObject);
		// set vertex attrib pointer
		// set attrib position [vec3]
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Positions.size(), &Positions.at(0), GL_STATIC_DRAW);
		glVertexAttribPointer(0, PositionSize, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * PositionSize, AttributeOffset(0));
		// set attrib uv [vec2]
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * UVs.size(), &UVs.at(0), GL_STATIC_DRAW);
		glVertexAttribPointer(1, UVSize, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * UVSize, AttributeOffset(0));
		if (Normals.size() != 0)
		{
			// set attrib normal [vec3]
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[2]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Normals.size(), &Normals.at(0), GL_STATIC_DRAW);
			glVertexAttribPointer(2, NormalSize, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * NormalSize, AttributeOffset(0));
		}
		// set attrib instanced offset_position [vec3]
		if (OffsetPositions.size() > 2)
		{
			glBindBuffer(GL_ARRAY_BUFFER, instanceBufferObject);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * OffsetPositions.size(), &OffsetPositions.at(0), GL_STATIC_DRAW);
			glVertexAttribPointer(3, OffsetPositionSize, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * OffsetPositionSize, AttributeOffset(0));
			glVertexAttribDivisor(3, 1);
		}
		else {
			GLfloat offset_position[] = { 0.0f, 0.0f, 0.0f };
			glBindBuffer(GL_ARRAY_BUFFER, instanceBufferObject);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3, offset_position, GL_STATIC_DRAW);
			glVertexAttribPointer(3, OffsetPositionSize, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * OffsetPositionSize, AttributeOffset(0));
			glVertexAttribDivisor(3, 1);
		}
		// reset vertex array
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// install material/scene data/render data
		MeshBase::Install();
	}
}

void Mesh_OpenGL::Render(float DeltaTime)
{
	// submit material/scene data/render data
	MeshBase::Render(DeltaTime);

	// submit mesh coustom data
	if (true)
	{
		if (OwnedScene && AssociatedRenderer && AssociatedPipeline)
		{
			auto Camera = OwnedScene->GetDefaultCamera();
			auto Submitter = dynamic_cast<Pipeline_OpenGL*>(AssociatedPipeline)->CommonTool;

			if (Submitter)
			{
				// update uniform begin
				Submitter->UpdateUniform3f("camera_position", Camera->Position);
				Submitter->UpdateUniformMatrix4("projection_matrix", AssociatedRenderer->GetProjectionMatrix());
				Submitter->UpdateUniformMatrix4("view_matrix", Camera->GetViewMatrix());
				Submitter->UpdateUniformMatrix4("model_matrix", GenerateModelMatrix());

				
				// update uniform end

				// call render command
				glBindVertexArray(vertexArrayObject);

				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);
				glEnableVertexAttribArray(2);
				glEnableVertexAttribArray(3);
				
				GLenum PrimitiveModeOp = GL_TRIANGLES;
				
				switch (PrimitiveMode)
				{
				case EPrimitiveMode::Points:
				{
					PrimitiveModeOp = GL_POINTS;
				}break;
				case EPrimitiveMode::Triangles:
				{
					PrimitiveModeOp = GL_TRIANGLES;
				}break;
				case EPrimitiveMode::TriangleStrip:
				{
					PrimitiveModeOp = GL_TRIANGLE_STRIP;
				}break;
				case EPrimitiveMode::Patches:
				{
					glPatchParameteri(GL_PATCH_VERTICES, PrimitivePointNum); //GL_PATCHES GL_TRIANGLES
					PrimitiveModeOp = GL_PATCHES;
				}break;
				default:
					break;
				}
				
				size_t instanceNum = 1;
				if (OffsetPositions.size() > 2)
					instanceNum = OffsetPositions.size() / OffsetPositionSize;

				if (Indices.size() != 0)
				{
					glDrawElementsInstancedBaseVertexBaseInstance(PrimitiveModeOp, Indices.size(), GL_UNSIGNED_INT, &Indices.at(0), instanceNum, 0, 0);
				}
				else
				{
					glDrawArraysInstancedBaseInstance(PrimitiveModeOp, 0, Positions.size() / PositionSize, instanceNum, 0);
				}	

				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);
				glDisableVertexAttribArray(2);
				glDisableVertexAttribArray(3);

				// end render command
				glBindVertexArray(0);
			}
		}
	}
}

void Mesh_OpenGL::Uninstall()
{

}

Mesh_OpenGL::Mesh_OpenGL()
{
	// set pipeline assemblage info
	PipelineAssemblageInfo = new PipelineAssemblageInfo_OpenGL();
	//PipelineAssemblageInfo->PipelineName = "BasicMeshPiepline";
	PipelineAssemblageInfo->PipelineName = "PBRMeshPiepline";
	auto Vert = new ShaderAssemblageInfo_OpenGL();
	auto Tesc = new ShaderAssemblageInfo_OpenGL();
	auto Tese = new ShaderAssemblageInfo_OpenGL();
	auto Geom = new ShaderAssemblageInfo_OpenGL();
	auto Frag = new ShaderAssemblageInfo_OpenGL();
	//Vert->FilePath = "Shader\\Mesh\\BasicMesh\\BasicMesh.vert";
	Vert->FilePath = "Shader\\Mesh\\PBRMesh\\PBRMesh.vert";
	Vert->Type = EShaderType::VertexShader;
	//Tesc->FilePath = "Shader\\Mesh\\BasicMesh\\BasicMesh.tesc";
	Tesc->FilePath = "Shader\\Mesh\\PBRMesh\\PBRMesh.tesc";
	Tesc->Type = EShaderType::TessellationControlShader;
	//Tese->FilePath = "Shader\\Mesh\\BasicMesh\\BasicMesh.tese";
	Tese->FilePath = "Shader\\Mesh\\PBRMesh\\PBRMesh.tese";
	Tese->Type = EShaderType::TessellationEvaluationShader;
	//Geom->FilePath = "Shader\\Mesh\\BasicMesh\\BasicMesh.geom";
	Geom->FilePath = "Shader\\Mesh\\PBRMesh\\PBRMesh.geom";
	Geom->Type = EShaderType::GeometryShader;
	//Frag->FilePath = "Shader\\Mesh\\BasicMesh\\BasicMesh.frag";
	Frag->FilePath = "Shader\\Mesh\\PBRMesh\\PBRMesh.frag";
	Frag->Type = EShaderType::FragmentShader;
	PipelineAssemblageInfo->ShaderAssmblageInfos.push_back(Vert);
	PipelineAssemblageInfo->ShaderAssmblageInfos.push_back(Tesc);
	PipelineAssemblageInfo->ShaderAssmblageInfos.push_back(Tese);
	PipelineAssemblageInfo->ShaderAssmblageInfos.push_back(Geom);
	PipelineAssemblageInfo->ShaderAssmblageInfos.push_back(Frag);

	Position = glm::vec3(0.0f, 0.0f, 0.0f);

	vertexArrayObject = 0;
	vertexBufferObjects = { 0, 0, 0};
	elementBufferObject = 0;
}

Mesh_OpenGL::~Mesh_OpenGL()
{
}
