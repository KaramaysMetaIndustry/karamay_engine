#include "DirectionalLight_OpenGL.h"
#include "OpenGL/Implement_OpenGL.h"

void DirectionalLight_OpenGL::Install()
{
}

void DirectionalLight_OpenGL::Submit(PipelineBase* AssociatedPipeline)
{
	
	if (AssociatedPipeline)
	{
		auto Submitter = dynamic_cast<Pipeline_OpenGL*>(AssociatedPipeline)->CommonTool;
		if (Submitter)
		{
			std::string ArrayName(PrefixAttributeName);
			std::string Attrib0 = ArrayName + ".color";
			std::string Attrib1 = ArrayName + ".direction";
			
			Submitter->UpdateUniform3f(Attrib0.c_str(), Color);
			Submitter->UpdateUniform3f(Attrib1.c_str(), Direction);
		}
	}
}

void DirectionalLight_OpenGL::Uninstall()
{
}

DirectionalLight_OpenGL::DirectionalLight_OpenGL()
{
}

DirectionalLight_OpenGL::~DirectionalLight_OpenGL()
{
}
