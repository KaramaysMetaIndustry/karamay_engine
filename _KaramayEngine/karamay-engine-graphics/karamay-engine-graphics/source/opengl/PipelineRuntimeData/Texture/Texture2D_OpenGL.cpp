#include "Texture2D_OpenGL.h"
#include "OpenGL/Implement_OpenGL.h"

#define STB_IMAGE_IMPLEMENTATION
#include "..//..//..//Dependencies/stb_image.h"

void Texture2D_OpenGL::LoadPixels(const std::string& FilePath)
{
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(FilePath.c_str(), &width, &height, &nrChannel, 0);

	if (data == nullptr) {
		std::cout << "load fail" << std::endl;
	}

	switch (nrChannel)
	{
	case 1: Type = GL_RED; break;
	case 3:	Type = GL_RGB;  break;
	case 4: Type = GL_RGBA; break;
	default:
		break;
	}

}

void Texture2D_OpenGL::Install()
{
	if (DefaultRenderer)
	{
		auto Allocator = dynamic_cast<RendererAllocator_OpenGL*>(DefaultRenderer->Allocator);
		if (Allocator)
		{
			Slot = Allocator->GetTexture2DSlot();
			glGenTextures(1, &TextureObject);
			glActiveTexture(GL_TEXTURE0 + Slot);
			glBindTexture(GL_TEXTURE_2D, TextureObject);
			glTexImage2D(GL_TEXTURE_2D, 0, Type, width, height, 0, Type, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			std::cout << Slot << std::endl;
		}
	}
	
}

void Texture2D_OpenGL::Submit(PipelineBase* AssociatedPipeline)
{
	if (AssociatedPipeline)
	{
		glActiveTexture(GL_TEXTURE0 + Slot);
		glBindTexture(GL_TEXTURE_2D, TextureObject);

		auto Submitter = dynamic_cast<Pipeline_OpenGL*>(AssociatedPipeline)->CommonTool;
		if (Submitter)
			Submitter->UpdateUniform1i(UniformName.c_str(), Slot);
	}
}

void Texture2D_OpenGL::Uninstall()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &TextureObject);
}
