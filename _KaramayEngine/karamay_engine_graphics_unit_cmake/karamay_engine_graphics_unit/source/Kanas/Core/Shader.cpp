#include "Shader.h"

Kanas::Core::FShader::FShader(const FString& InName, const FString& InPath) :
	Name(InName)
{
}

Kanas::Core::FShader::~FShader()
{
}

Kanas::Core::FComputeShader::FComputeShader(const FString& InName, const FString& InPath) :
	FShader(InName, InPath)
{
}

Kanas::Core::FComputeShader::~FComputeShader()
{
}
