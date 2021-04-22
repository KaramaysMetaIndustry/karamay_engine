#include "Shader_OpenGL.h"
#include "OpenGL/Shader/ShaderAssemblageInfo_OpenGL.h"

void Shader_OpenGL::Assembly(ShaderAssemblageInfoBase* Info)
{
	ShaderBase::Assembly(Info);

	//... load bytes
	ShaderAssemblageInfo_OpenGL* InfoOp 
		= dynamic_cast<ShaderAssemblageInfo_OpenGL*>(Info);

	if (InfoOp)
	{
		auto FilePath = InfoOp->FilePath;
		auto ShaderType = InfoOp->GetOpenGLShaderType();

		// load bytes - FilePath
		std::ifstream File;
		std::string Content;
		File.exceptions(std::fstream::failbit | std::fstream::badbit);
		try {
			File.open(FilePath);
			std::stringstream SStream;
			SStream << File.rdbuf();
			File.close();
			Content = SStream.str();
		}
		catch (const std::exception& e) {
			std::cout << "Exception: [ " << e.what() << " ]" << std::endl;
		}
		sourceCode = Content.c_str();

		// create opengl shader - ShaderTpe
		shaderObj = glCreateShader(ShaderType);
		glShaderSource(shaderObj, 1, &sourceCode, NULL);
		glCompileShader(shaderObj);

		GLint result;
		char info[512];
		glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &result);
		if (result != GL_TRUE) {
			glGetShaderInfoLog(shaderObj, 512, NULL, info);
			std::cout << "shader compile fail : " << info << std::endl;
		}

		//std::cout << sourceCode << std::endl;
	}
}
