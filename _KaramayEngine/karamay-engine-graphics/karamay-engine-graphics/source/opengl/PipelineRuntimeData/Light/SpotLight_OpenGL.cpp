#include "SpotLight_OpenGL.h"
#include "OpenGL/Implement_OpenGL.h"

void SpotLight_OpenGL::Install()
{
}

void SpotLight_OpenGL::Submit(PipelineBase* AssociatedPipeline)
{
	if (AssociatedPipeline)
	{
		auto Submitter = dynamic_cast<Pipeline_OpenGL*>(AssociatedPipeline)->CommonTool;
		if (Submitter)
		{
			std::string ArrayName(PrefixAttributeName);
			std::string Attrib0 = ArrayName + ".color";
			std::string Attrib1 = ArrayName + ".position";
			std::string Attrib2 = ArrayName + ".direction";
			std::string Attrib3 = ArrayName + ".cos_phy";

			Submitter->UpdateUniform3f(Attrib0.c_str(), Color);
			Submitter->UpdateUniform3f(Attrib1.c_str(), Position);
			Submitter->UpdateUniform3f(Attrib2.c_str(), Direction);
			Submitter->UpdateUniform1f(Attrib3.c_str(), CosPhy);
		}
	}
}

void SpotLight_OpenGL::Uninstall()
{
}
