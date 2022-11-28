#ifndef _SHADER_H_
#define _SHADER_H_

#include "KanasCoreTypes.h"

_KANAS_CORE_BEGIN

class shader_module;

class FShader
{

	FString Name;

	std::shared_ptr<shader_module> ShaderModule;

public:

	FShader(const FString& InName, const FString& InPath);

	virtual ~FShader();

	std::shared_ptr<shader_module> GetShaderModule() const;

	const FString& GetName() const;

};


class compute_shader : public FShader
{
public:

	compute_shader(const FString& InName, const FString& InPath);

	virtual ~compute_shader() override;

};


_KANAS_CORE_END

#endif