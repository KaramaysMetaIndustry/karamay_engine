#ifndef GLSL_PROGRAM_H
#define GLSL_PROGRAM_H

#include "glsl.h"
#include "glsl_shader.h"
#include "graphics/renderer/pipeline/base/resource/program/gl_program.h"

class glsl_program 
{
public:
	glsl_program()
	{}

	~glsl_program()
	{}

public:
//	glsl_sampler1D* sampler1D(const std::string& name)
//	{
//		auto _it = _sampler1Ds.find(name);
//		if (_it != _sampler1Ds.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_sampler1DArray* sampler1DArray(const std::string& name)
//	{
//		auto _it = _sampler1DArrays.find(name);
//		if (_it != _sampler1DArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_sampler2D* sampler2D(const std::string& name)
//	{
//		auto _it = _sampler2Ds.find(name);
//		if (_it != _sampler2Ds.cend()) return _it->second;
//#ifdef _DEBUG
//		throw std::exception("can not find sampler2D");
//#endif // _DEBUG
//		return nullptr;
//	}
//	glsl_sampler2DArray* sampler2DArray(const std::string& name)
//	{
//		auto _it = _sampler2DArrays.find(name);
//		if (_it != _sampler2DArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_sampler2DMS* sampler2DMS(const std::string& name)
//	{
//		auto _it = _sampler2DMSs.find(name);
//		if (_it != _sampler2DMSs.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_sampler2DMSArray* sampler2DMSArray(const std::string& name)
//	{
//		auto _it = _sampler2DMSArrays.find(name);
//		if (_it != _sampler2DMSArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_samplerCube* samplerCube(const std::string& name)
//	{
//		auto _it = _samplerCubes.find(name);
//		if (_it != _samplerCubes.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_samplerCubeArray* samplerCubeArray(const std::string& name)
//	{
//		auto _it = _samplerCubeArrays.find(name);
//		if (_it != _samplerCubeArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_sampler2DRect* sampler2DRect(const std::string& name)
//	{
//		auto _it = _sampler2DRects.find(name);
//		if (_it != _sampler2DRects.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_samplerBuffer* samplerBuffer(const std::string& name)
//	{
//		auto _it = _samplerBuffers.find(name);
//		if (_it != _samplerBuffers.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_sampler1DShadow* sampler1DShadow(const std::string& name)
//	{
//		auto _it = _sampler1DShadows.find(name);
//		if (_it != _sampler1DShadows.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_sampler1DArrayShadow* sampler1DArrayShadow(const std::string& name)
//	{
//		auto _it = _sampler1DArrayShadows.find(name);
//		if (_it != _sampler1DArrayShadows.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_sampler2DShadow* sampler2DShadow(const std::string& name)
//	{
//		auto _it = _sampler2DShadows.find(name);
//		if (_it != _sampler2DShadows.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_sampler2DArrayShadow* sampler2DArrayShadow(const std::string& name)
//	{
//		auto _it = _sampler2DArrayShadows.find(name);
//		if (_it != _sampler2DArrayShadows.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_samplerCubeShadow* samplerCubeShadow(const std::string& name)
//	{
//		auto _it = _samplerCubeShadows.find(name);
//		if (_it != _samplerCubeShadows.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_samplerCubeArrayShadow* samplerCubeArrayShadow(const std::string& name)
//	{
//		auto _it = _samplerCubeArrayShadows.find(name);
//		if (_it != _samplerCubeArrayShadows.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_sampler2DRectShadow* sampler2DRectShadow(const std::string& name)
//	{
//		auto _it = _sampler2DRectShadows.find(name);
//		if (_it != _sampler2DRectShadows.cend()) return _it->second;
//		return nullptr;
//	}
//
//	glsl_isampler1D* isampler1D(const std::string& name)
//	{
//		auto _it = _isampler1Ds.find(name);
//		if (_it != _isampler1Ds.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_isampler1DArray* isampler1DArray(const std::string& name)
//	{
//		auto _it = _isampler1DArrays.find(name);
//		if (_it != _isampler1DArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_isampler2D* isampler2D(const std::string& name)
//	{
//		auto _it = _isampler2Ds.find(name);
//		if (_it != _isampler2Ds.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_isampler2DArray* isampler2DArray(const std::string& name)
//	{
//		auto _it = _isampler2DArrays.find(name);
//		if (_it != _isampler2DArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_isampler2DMS* isampler2DMS(const std::string& name)
//	{
//		auto _it = _isampler2DMSs.find(name);
//		if (_it != _isampler2DMSs.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_isampler2DMSArray* isampler2DMSArray(const std::string& name)
//	{
//		auto _it = _isampler2DMSArrays.find(name);
//		if (_it != _isampler2DMSArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_isamplerCube* isamplerCube(const std::string& name)
//	{
//		auto _it = _isamplerCubes.find(name);
//		if (_it != _isamplerCubes.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_isamplerCubeArray* isamplerCubeArray(const std::string& name)
//	{
//		auto _it = _isamplerCubeArrays.find(name);
//		if (_it != _isamplerCubeArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_isampler2DRect* isampler2DRect(const std::string& name)
//	{
//		auto _it = _isampler2DRects.find(name);
//		if (_it != _isampler2DRects.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_isamplerBuffer* isamplerBuffer(const std::string& name)
//	{
//		auto _it = _isamplerBuffers.find(name);
//		if (_it != _isamplerBuffers.cend()) return _it->second;
//		return nullptr;
//	}
//
//	glsl_usampler1D* usampler1D(const std::string& name)
//	{
//		auto _it = _usampler1Ds.find(name);
//		if (_it != _usampler1Ds.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_usampler1DArray* usampler1DArray(const std::string& name)
//	{
//		auto _it = _usampler1DArrays.find(name);
//		if (_it != _usampler1DArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_usampler2D* usampler2D(const std::string& name)
//	{
//		auto _it = _usampler2Ds.find(name);
//		if (_it != _usampler2Ds.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_usampler2DArray* usampler2DArray(const std::string& name)
//	{
//		auto _it = _usampler2DArrays.find(name);
//		if (_it != _usampler2DArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_usampler2DMS* usampler2DMS(const std::string& name)
//	{
//		auto _it = _usampler2DMSs.find(name);
//		if (_it != _usampler2DMSs.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_usampler2DMSArray* usampler2DMSArray(const std::string& name)
//	{
//		auto _it = _usampler2DMSArrays.find(name);
//		if (_it != _usampler2DMSArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_usamplerCube* usamplerCube(const std::string& name)
//	{
//		auto _it = _usamplerCubes.find(name);
//		if (_it != _usamplerCubes.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_usamplerCubeArray* usamplerCubeArray(const std::string& name)
//	{
//		auto _it = _usamplerCubeArrays.find(name);
//		if (_it != _usamplerCubeArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_usampler2DRect* usampler2DRect(const std::string& name)
//	{
//		auto _it = _usampler2DRects.find(name);
//		if (_it != _usampler2DRects.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_usamplerBuffer* usamplerBuffer(const std::string& name)
//	{
//		auto _it = _usamplerBuffers.find(name);
//		if (_it != _usamplerBuffers.cend()) return _it->second;
//		return nullptr;
//	}
//
//	glsl_image1D* image1D(const std::string& name)
//	{
//		auto _it = _image1Ds.find(name);
//		if (_it != _image1Ds.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_image1DArray* image1DArray(const std::string& name)
//	{
//		auto _it = _image1DArrays.find(name);
//		if (_it != _image1DArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_image2D* image2D(const std::string& name)
//	{
//		auto _it = _image2Ds.find(name);
//		if (_it != _image2Ds.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_image2DArray* image2DArray(const std::string& name)
//	{
//		auto _it = _image2DArrays.find(name);
//		if (_it != _image2DArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_imageCube* imageCube(const std::string& name)
//	{
//		auto _it = _imageCubes.find(name);
//		if (_it != _imageCubes.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_imageCubeArray* imageCubeArray(const std::string& name)
//	{
//		auto _it = _imageCubeArrays.find(name);
//		if (_it != _imageCubeArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_image2DMS* image2DMS(const std::string& name)
//	{
//		auto _it = _image2DMSs.find(name);
//		if (_it != _image2DMSs.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_image2DMSArray* image2DMSArray(const std::string& name)
//	{
//		auto _it = _image2DMSArrays.find(name);
//		if (_it != _image2DMSArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_image2DRect* image2DRect(const std::string& name)
//	{
//		auto _it = _image2DRects.find(name);
//		if (_it != _image2DRects.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_image3D* image3D(const std::string& name)
//	{
//		auto _it = _image3Ds.find(name);
//		if (_it != _image3Ds.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_imageBuffer* imageBuffer(const std::string& name)
//	{
//		auto _it = _imageBuffers.find(name);
//		if (_it != _imageBuffers.cend()) return _it->second;
//		return nullptr;
//	}
//
//	glsl_iimage1D* iimage1D(const std::string& name)
//	{
//		auto _it = _iimage1Ds.find(name);
//		if (_it != _iimage1Ds.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_iimage1DArray* iimage1DArray(const std::string& name)
//	{
//		auto _it = _iimage1DArrays.find(name);
//		if (_it != _iimage1DArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_iimage2D* iimage2D(const std::string& name)
//	{
//		auto _it = _iimage2Ds.find(name);
//		if (_it != _iimage2Ds.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_iimage2DArray* iimage2DArray(const std::string& name)
//	{
//		auto _it = _iimage2DArrays.find(name);
//		if (_it != _iimage2DArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_iimageCube* iimageCube(const std::string& name)
//	{
//		auto _it = _iimageCubes.find(name);
//		if (_it != _iimageCubes.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_iimageCubeArray* iimageCubeArray(const std::string& name)
//	{
//		auto _it = _iimageCubeArrays.find(name);
//		if (_it != _iimageCubeArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_iimage2DMS* iimage2DMS(const std::string& name)
//	{
//		auto _it = _iimage2DMSs.find(name);
//		if (_it != _iimage2DMSs.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_iimage2DMSArray* iimage2DMSArray(const std::string& name)
//	{
//		auto _it = _iimage2DMSArrays.find(name);
//		if (_it != _iimage2DMSArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_iimage2DRect* iimage2DRect(const std::string& name)
//	{
//		auto _it = _iimage2DRects.find(name);
//		if (_it != _iimage2DRects.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_iimage3D* iimage3D(const std::string& name)
//	{
//		auto _it = _iimage3Ds.find(name);
//		if (_it != _iimage3Ds.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_iimageBuffer* iimageBuffer(const std::string& name)
//	{
//		auto _it = _iimageBuffers.find(name);
//		if (_it != _iimageBuffers.cend()) return _it->second;
//		return nullptr;
//	}
//
//	glsl_uimage1D* uimage1D(const std::string& name)
//	{
//		auto _it = _uimage1Ds.find(name);
//		if (_it != _uimage1Ds.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_uimage1DArray* uimage1DArray(const std::string& name)
//	{
//		auto _it = _uimage1DArrays.find(name);
//		if (_it != _uimage1DArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_uimage2D* uimage2D(const std::string& name)
//	{
//		auto _it = _uimage2Ds.find(name);
//		if (_it != _uimage2Ds.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_uimage2DArray* uimage2DArray(const std::string& name)
//	{
//		auto _it = _uimage2DArrays.find(name);
//		if (_it != _uimage2DArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_uimageCube* uimageCube(const std::string& name)
//	{
//		auto _it = _uimageCubes.find(name);
//		if (_it != _uimageCubes.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_uimageCubeArray* uimageCubeArray(const std::string& name)
//	{
//		auto _it = _uimageCubeArrays.find(name);
//		if (_it != _uimageCubeArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_uimage2DMS* uimage2DMS(const std::string& name)
//	{
//		auto _it = _uimage2DMSs.find(name);
//		if (_it != _uimage2DMSs.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_uimage2DMSArray* uimage2DMSArray(const std::string& name)
//	{
//		auto _it = _uimage2DMSArrays.find(name);
//		if (_it != _uimage2DMSArrays.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_uimage2DRect* uimage2DRect(const std::string& name)
//	{
//		auto _it = _uimage2DRects.find(name);
//		if (_it != _uimage2DRects.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_uimage3D* uimage3D(const std::string& name)
//	{
//		auto _it = _uimage3Ds.find(name);
//		if (_it != _uimage3Ds.cend()) return _it->second;
//		return nullptr;
//	}
//	glsl_uimageBuffer* uimageBuffer(const std::string& name)
//	{
//		auto _it = _uimageBuffers.find(name);
//		if (_it != _uimageBuffers.cend()) return _it->second;
//		return nullptr;
//	}

	glsl_atomic_counter* atomic_uint(const std::string& block_name)
	{
		auto _it = _atomic_counters.find(block_name);
		if (_it != _atomic_counters.cend()) return _it->second;
		return nullptr;
	}

	glsl_uniform_block* uniform_block(const std::string& block_name)
	{
		auto _it = _uniform_blocks.find(block_name);
		if (_it != _uniform_blocks.cend()) return _it->second;
		return nullptr;
	}
	glsl_shader_storage_block* shader_storage_block(const std::string& block_name)
	{
		auto _it = _shader_storage_blocks.find(block_name);
		if (_it != _shader_storage_blocks.cend()) return _it->second;
		return nullptr;
	}

private:

	std::unordered_map<std::string, glsl_sampler1D*> _sampler1Ds;
	std::unordered_map<std::string, glsl_sampler1DArray*> _sampler1DArrays;
	std::unordered_map<std::string, glsl_sampler2D*> _sampler2Ds;
	std::unordered_map<std::string, glsl_sampler2DArray*> _sampler2DArrays;
	std::unordered_map<std::string, glsl_samplerCube*> _samplerCubes;
	std::unordered_map<std::string, glsl_samplerCubeArray*> _samplerCubeArrays;
	std::unordered_map<std::string, glsl_sampler2DMS*> _sampler2DMSs;
	std::unordered_map<std::string, glsl_sampler2DMSArray*> _sampler2DMSArrays;
	std::unordered_map<std::string, glsl_sampler2DRect*> _sampler2DRects;
	std::unordered_map<std::string, glsl_samplerBuffer*> _samplerBuffers;
	std::unordered_map<std::string, glsl_sampler1DShadow*> _sampler1DShadows;
	std::unordered_map<std::string, glsl_sampler1DArrayShadow*> _sampler1DArrayShadows;
	std::unordered_map<std::string, glsl_sampler2DShadow*> _sampler2DShadows;
	std::unordered_map<std::string, glsl_sampler2DArrayShadow*> _sampler2DArrayShadows;
	std::unordered_map<std::string, glsl_samplerCubeShadow*> _samplerCubeShadows;
	std::unordered_map<std::string, glsl_samplerCubeArrayShadow*> _samplerCubeArrayShadows;
	std::unordered_map<std::string, glsl_sampler2DRectShadow*> _sampler2DRectShadows;

	std::unordered_map<std::string, glsl_isampler1D*> _isampler1Ds;
	std::unordered_map<std::string, glsl_isampler1DArray*> _isampler1DArrays;
	std::unordered_map<std::string, glsl_isampler2D*> _isampler2Ds;
	std::unordered_map<std::string, glsl_isampler2DArray*> _isampler2DArrays;
	std::unordered_map<std::string, glsl_isampler2DMS*> _isampler2DMSs;
	std::unordered_map<std::string, glsl_isampler2DMSArray*> _isampler2DMSArrays;
	std::unordered_map<std::string, glsl_isamplerCube*> _isamplerCubes;
	std::unordered_map<std::string, glsl_isamplerCubeArray*> _isamplerCubeArrays;
	std::unordered_map<std::string, glsl_isampler2DRect*> _isampler2DRects;
	std::unordered_map<std::string, glsl_isamplerBuffer*> _isamplerBuffers;

	std::unordered_map<std::string, glsl_usampler1D*> _usampler1Ds;
	std::unordered_map<std::string, glsl_usampler1DArray*> _usampler1DArrays;
	std::unordered_map<std::string, glsl_usampler2D*> _usampler2Ds;
	std::unordered_map<std::string, glsl_usampler2DArray*> _usampler2DArrays;
	std::unordered_map<std::string, glsl_usampler2DMS*> _usampler2DMSs;
	std::unordered_map<std::string, glsl_usampler2DMSArray*> _usampler2DMSArrays;
	std::unordered_map<std::string, glsl_usamplerCube*> _usamplerCubes;
	std::unordered_map<std::string, glsl_usamplerCubeArray*> _usamplerCubeArrays;
	std::unordered_map<std::string, glsl_usampler2DRect*> _usampler2DRects;
	std::unordered_map<std::string, glsl_usamplerBuffer*> _usamplerBuffers;

	std::unordered_map<std::string, glsl_image1D*> _image1Ds;
	std::unordered_map<std::string, glsl_image1DArray*> _image1DArrays;
	std::unordered_map<std::string, glsl_image2D*> _image2Ds;
	std::unordered_map<std::string, glsl_image2DArray*> _image2DArrays;
	std::unordered_map<std::string, glsl_imageCube*> _imageCubes;
	std::unordered_map<std::string, glsl_imageCubeArray*> _imageCubeArrays;
	std::unordered_map<std::string, glsl_image2DMS*> _image2DMSs;
	std::unordered_map<std::string, glsl_image2DMSArray*> _image2DMSArrays;
	std::unordered_map<std::string, glsl_image2DRect*> _image2DRects;
	std::unordered_map<std::string, glsl_image3D*> _image3Ds;
	std::unordered_map<std::string, glsl_imageBuffer*> _imageBuffers;

	std::unordered_map<std::string, glsl_iimage1D*> _iimage1Ds;
	std::unordered_map<std::string, glsl_iimage1DArray*> _iimage1DArrays;
	std::unordered_map<std::string, glsl_iimage2D*> _iimage2Ds;
	std::unordered_map<std::string, glsl_iimage2DArray*> _iimage2DArrays;
	std::unordered_map<std::string, glsl_iimageCube*> _iimageCubes;
	std::unordered_map<std::string, glsl_iimageCubeArray*> _iimageCubeArrays;
	std::unordered_map<std::string, glsl_iimage2DMS*> _iimage2DMSs;
	std::unordered_map<std::string, glsl_iimage2DMSArray*> _iimage2DMSArrays;
	std::unordered_map<std::string, glsl_iimage2DRect*> _iimage2DRects;
	std::unordered_map<std::string, glsl_iimage3D*> _iimage3Ds;
	std::unordered_map<std::string, glsl_iimageBuffer*> _iimageBuffers;

	std::unordered_map<std::string, glsl_uimage1D*> _uimage1Ds;
	std::unordered_map<std::string, glsl_uimage1DArray*> _uimage1DArrays;
	std::unordered_map<std::string, glsl_uimage2D*> _uimage2Ds;
	std::unordered_map<std::string, glsl_uimage2DArray*> _uimage2DArrays;
	std::unordered_map<std::string, glsl_uimageCube*> _uimageCubes;
	std::unordered_map<std::string, glsl_uimageCubeArray*> _uimageCubeArrays;
	std::unordered_map<std::string, glsl_uimage2DMS*> _uimage2DMSs;
	std::unordered_map<std::string, glsl_uimage2DMSArray*> _uimage2DMSArrays;
	std::unordered_map<std::string, glsl_uimage2DRect*> _uimage2DRects;
	std::unordered_map<std::string, glsl_uimage3D*> _uimage3Ds;
	std::unordered_map<std::string, glsl_uimageBuffer*> _uimageBuffers;

	std::unordered_map<std::string, glsl_atomic_counter*> _atomic_counters;

	std::unordered_map<std::string, glsl_uniform_block*> _uniform_blocks;
	std::unordered_map<std::string, glsl_shader_storage_block*> _shader_storage_blocks;


};

class glsl_graphics_pipeline_program final : public glsl_program 
{
public:
	glsl_graphics_pipeline_program() = default;
	glsl_graphics_pipeline_program(glsl_vertex_shader* vs, glsl_fragment_shader* fs) :
		_vertex_shader(vs), _tessellation_shader(nullptr), _geometry_shader(nullptr), _fragment_shader(fs)
	{}
	glsl_graphics_pipeline_program(glsl_vertex_shader* vs, glsl_tessellation_shader* ts, glsl_fragment_shader* fs) :
		_vertex_shader(vs), _tessellation_shader(ts), _geometry_shader(nullptr), _fragment_shader(fs)
	{}
	glsl_graphics_pipeline_program(glsl_vertex_shader* vs, glsl_geometry_shader* gs, glsl_fragment_shader* fs) :
		_vertex_shader(vs), _tessellation_shader(nullptr), _geometry_shader(gs), _fragment_shader(fs)
	{}
	glsl_graphics_pipeline_program(glsl_vertex_shader* vs, glsl_tessellation_shader* ts, glsl_geometry_shader* gs, glsl_fragment_shader* fs) :
		_vertex_shader(vs), _tessellation_shader(ts), _geometry_shader(gs), _fragment_shader(fs)
	{}

	glsl_graphics_pipeline_program(const glsl_graphics_pipeline_program&) = delete;
	glsl_graphics_pipeline_program& operator=(const glsl_graphics_pipeline_program&) = delete;

	~glsl_graphics_pipeline_program()
	{
		if (_vertex_shader) delete _vertex_shader;
		if (_tessellation_shader) delete _tessellation_shader;
		if (_geometry_shader) delete _geometry_shader;
		if (_fragment_shader) delete _fragment_shader;
		delete _program;
	}

public:

	void load()
	{
		// generate template, if has no file, generate
		
		// generate template, if has file and but 'force' is active generate file

		// if has file and forces is not active, load file and validate with template
		std::string renderer_path = "C:/PrivateRepos/Karamays/_KaramayEngine/karamay_engine_graphics_unit_cmake/karamay_engine_graphics_unit/shaders/Mesh/PBRMesh";
		std::vector<gl_shader*> _shaders;
		if (_vertex_shader) {
			_vertex_shader->load(renderer_path + "/PBRMesh.vert");
			_shaders.push_back(_vertex_shader->get_shader());
		}
		if (_tessellation_shader)
		{
			if (_tessellation_shader->load(renderer_path + "/PBRMesh.tesc", renderer_path + "/PBRMesh.tese"))
			{
				auto _shader_pair = _tessellation_shader->get_shader();
				_shaders.push_back(_shader_pair.first);
				_shaders.push_back(_shader_pair.second);
			}
		}
		if (_geometry_shader)
		{
			_geometry_shader->load(renderer_path + "/PBRMesh.geom");
			_shaders.push_back(_geometry_shader->get_shader());
		}
		if (_fragment_shader) 
		{
			_fragment_shader->load(renderer_path + "/PBRMesh.frag");
			_shaders.push_back(_fragment_shader->get_shader());
		}

		_program = new gl_program();
		
		if (_program->load(_shaders))
			std::cout << "program load successful" << std::endl;
		else
			std::cerr << "program load failed" << std::endl;
	}

	void enable()
	{
		
	}

	void disable()
	{

	}

private:

	glsl_vertex_shader* _vertex_shader;
	glsl_tessellation_shader* _tessellation_shader;
	glsl_geometry_shader* _geometry_shader;
	glsl_fragment_shader* _fragment_shader;
	gl_program* _program;

};

class glsl_compute_pipeline_program final : public glsl_program
{
public:
	glsl_compute_pipeline_program(glsl_compute_shader* compute_shader) :
		_program(nullptr),
		_cs(compute_shader)
	{
	}

	~glsl_compute_pipeline_program()
	{
		delete _program;
		delete _cs;
	}

private:

	glsl_compute_shader* _cs;
	gl_program* _program;

public:
	
	void load()
	{

	}

	void enable()
	{

	}

	void disable()
	{

	}

};



#define TOKEN(__NAME__) #__NAME__
#define DEFINE_GLSL_STRUCT(STRUCT_NAME, ...)\
struct STRUCT_NAME{\
STRUCT_NAME(){ glsl_program_t::register_glsl_struct(TOKEN(__VA_ARGS__));}\
\
static const char* token(){return TOKEN(__VA_ARGS__);}\
__VA_ARGS__\
}\



#define DECLARE_STD140_UNIFORM_BLOCK(NAME, ...)\
struct NAME {\
\
NAME() = default;\
static const char* token(){return TOKEN(__VA_ARGS__);}\
virtual const std::uint8_t* data() const {return reinterpret_cast<const std::uint8_t*>(this);}\
virtual std::uint8_t* data() {return reinterpret_cast<std::uint8_t*>(this);}\
virtual std::int64_t size() const {return sizeof(NAME);}\
\
\
__VA_ARGS__\
} global_std140_uniform_block\


#endif