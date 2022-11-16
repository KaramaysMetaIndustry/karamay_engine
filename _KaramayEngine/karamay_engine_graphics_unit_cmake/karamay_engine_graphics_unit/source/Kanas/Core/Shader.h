#ifndef _SHADER_H_
#define _SHADER_H_

#include "KanasCoreTypes.h"

_KANAS_CORE_BEGIN

class FShaderModule;

class FShader
{

	FString Name;

	TSharedPtr<FShaderModule> ShaderModule;

public:

	FShader(const FString& InName, const FString& InPath);

	virtual ~FShader();

	TSharedPtr<FShaderModule> GetShaderModule() const;

	const FString& GetName() const;

};


class FComputeShader : public FShader
{
public:

	FComputeShader(const FString& InName, const FString& InPath);

	virtual ~FComputeShader() override;

};


_KANAS_CORE_END

#endif