#include "shader.h"

kanas::core::FShader::FShader(const FString& InName, const FString& InPath) :
	Name(InName)
{
}

kanas::core::FShader::~FShader()
{
}

kanas::core::compute_shader::compute_shader(const FString& InName, const FString& InPath) :
	FShader(InName, InPath)
{
}

kanas::core::compute_shader::~compute_shader()
{
}
