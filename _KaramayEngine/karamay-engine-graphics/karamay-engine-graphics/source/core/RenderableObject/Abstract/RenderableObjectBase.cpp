#include "RenderableObjectBase.h"
#include "Core/SpicesRendererGlobal.h"

glm::mat4 RenderableObjectBase::GenerateModelMatrix() const
{
	glm::mat4 model_matrix(1.0f);
	model_matrix = glm::translate(model_matrix, Position);
	model_matrix = glm::rotate(model_matrix, glm::radians(Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	model_matrix = glm::rotate(model_matrix, glm::radians(Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	model_matrix = glm::rotate(model_matrix, glm::radians(Roll), glm::vec3(0.0f, 0.0f, 1.0f));

	return model_matrix;
}

void RenderableObjectBase::SetPrimitiveMode(EPrimitiveMode Mode, size_t PointNum)
{
	if (Mode == EPrimitiveMode::Patches)
		PrimitivePointNum = PointNum;
	PrimitiveMode = Mode;
}

RenderableObjectBase::RenderableObjectBase()
{
	OwnedScene = nullptr;
	PipelineAssemblageInfo = nullptr;
	AssociatedPipeline = nullptr;
	AssociatedRenderer = nullptr;

	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Pitch = Yaw = Roll = 0.0f;
}

RenderableObjectBase::~RenderableObjectBase()
{
}
