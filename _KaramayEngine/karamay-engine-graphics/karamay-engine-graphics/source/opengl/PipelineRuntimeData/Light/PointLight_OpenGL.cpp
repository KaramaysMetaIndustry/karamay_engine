#include "PointLight_OpenGL.h"
#include "OpenGL/Implement_OpenGL.h"

void PointLight_OpenGL::Install()
{
}

void PointLight_OpenGL::Submit(PipelineBase* AssociatedPipeline)
{
	if (AssociatedPipeline)
	{
		auto Submitter = dynamic_cast<Pipeline_OpenGL*>(AssociatedPipeline)->CommonTool;
		if (Submitter)
		{
			std::string ArrayName(PrefixAttributeName);
			std::string Attrib0 = ArrayName + ".position";
			std::string Attrib1 = ArrayName + ".color";
			std::string Attrib2 = ArrayName + ".constant";
			std::string Attrib3 = ArrayName + ".linear";
			std::string Attrib4 = ArrayName + ".quadratic";

			Submitter->UpdateUniform3f(Attrib0.c_str(), Position);
			Submitter->UpdateUniform3f(Attrib1.c_str(), Color);
			Submitter->UpdateUniform1f(Attrib2.c_str(), Constant);
			Submitter->UpdateUniform1f(Attrib3.c_str(), Linear);
			Submitter->UpdateUniform1f(Attrib4.c_str(), Quadratic);
		}
	}
	
}

void PointLight_OpenGL::Uninstall()
{
}

PointLight_OpenGL::PointLight_OpenGL()
{
}

PointLight_OpenGL::~PointLight_OpenGL()
{
}
