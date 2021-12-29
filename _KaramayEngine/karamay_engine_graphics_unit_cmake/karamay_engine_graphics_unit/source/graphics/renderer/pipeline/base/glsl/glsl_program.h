#ifndef GLSL_PROGRAM_H
#define GLSL_PROGRAM_H

#include "glsl.h"
#include "glsl_shader.h"
#include "graphics/renderer/pipeline/base/resource/program/gl_program.h"

class glsl_program 
{
public:
	glsl_program() = default;

	glsl_program(const glsl_program&) = delete;
	glsl_program& operator=(const glsl_program&) = delete;

	~glsl_program() = default;

public:

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

	glsl_atomic_counter* atomic_uint(const std::string& block_name)
	{
		auto _it = _atomic_counters.find(block_name);
		if (_it != _atomic_counters.cend()) return _it->second;
		return nullptr;
	}

private:

	std::unordered_map<std::string, glsl_uniform_block*> _uniform_blocks;
	std::unordered_map<std::string, glsl_shader_storage_block*> _shader_storage_blocks;
	std::unordered_map<std::string, glsl_atomic_counter*> _atomic_counters;

	//std::unordered_map<std::string, glsl_sampler1D*> _sampler1Ds;
	//std::unordered_map<std::string, glsl_sampler1DArray*> _sampler1DArrays;
	//std::unordered_map<std::string, glsl_sampler2D*> _sampler2Ds;
	//std::unordered_map<std::string, glsl_sampler2DArray*> _sampler2DArrays;
	//std::unordered_map<std::string, glsl_samplerCube*> _samplerCubes;
	//std::unordered_map<std::string, glsl_samplerCubeArray*> _samplerCubeArrays;
	//std::unordered_map<std::string, glsl_sampler2DMS*> _sampler2DMSs;
	//std::unordered_map<std::string, glsl_sampler2DMSArray*> _sampler2DMSArrays;
	//std::unordered_map<std::string, glsl_sampler2DRect*> _sampler2DRects;
	//std::unordered_map<std::string, glsl_samplerBuffer*> _samplerBuffers;
	//std::unordered_map<std::string, glsl_sampler1DShadow*> _sampler1DShadows;
	//std::unordered_map<std::string, glsl_sampler1DArrayShadow*> _sampler1DArrayShadows;
	//std::unordered_map<std::string, glsl_sampler2DShadow*> _sampler2DShadows;
	//std::unordered_map<std::string, glsl_sampler2DArrayShadow*> _sampler2DArrayShadows;
	//std::unordered_map<std::string, glsl_samplerCubeShadow*> _samplerCubeShadows;
	//std::unordered_map<std::string, glsl_samplerCubeArrayShadow*> _samplerCubeArrayShadows;
	//std::unordered_map<std::string, glsl_sampler2DRectShadow*> _sampler2DRectShadows;

	//std::unordered_map<std::string, glsl_isampler1D*> _isampler1Ds;
	//std::unordered_map<std::string, glsl_isampler1DArray*> _isampler1DArrays;
	//std::unordered_map<std::string, glsl_isampler2D*> _isampler2Ds;
	//std::unordered_map<std::string, glsl_isampler2DArray*> _isampler2DArrays;
	//std::unordered_map<std::string, glsl_isampler2DMS*> _isampler2DMSs;
	//std::unordered_map<std::string, glsl_isampler2DMSArray*> _isampler2DMSArrays;
	//std::unordered_map<std::string, glsl_isamplerCube*> _isamplerCubes;
	//std::unordered_map<std::string, glsl_isamplerCubeArray*> _isamplerCubeArrays;
	//std::unordered_map<std::string, glsl_isampler2DRect*> _isampler2DRects;
	//std::unordered_map<std::string, glsl_isamplerBuffer*> _isamplerBuffers;

	//std::unordered_map<std::string, glsl_usampler1D*> _usampler1Ds;
	//std::unordered_map<std::string, glsl_usampler1DArray*> _usampler1DArrays;
	//std::unordered_map<std::string, glsl_usampler2D*> _usampler2Ds;
	//std::unordered_map<std::string, glsl_usampler2DArray*> _usampler2DArrays;
	//std::unordered_map<std::string, glsl_usampler2DMS*> _usampler2DMSs;
	//std::unordered_map<std::string, glsl_usampler2DMSArray*> _usampler2DMSArrays;
	//std::unordered_map<std::string, glsl_usamplerCube*> _usamplerCubes;
	//std::unordered_map<std::string, glsl_usamplerCubeArray*> _usamplerCubeArrays;
	//std::unordered_map<std::string, glsl_usampler2DRect*> _usampler2DRects;
	//std::unordered_map<std::string, glsl_usamplerBuffer*> _usamplerBuffers;

	//std::unordered_map<std::string, glsl_image1D*> _image1Ds;
	//std::unordered_map<std::string, glsl_image1DArray*> _image1DArrays;
	//std::unordered_map<std::string, glsl_image2D*> _image2Ds;
	//std::unordered_map<std::string, glsl_image2DArray*> _image2DArrays;
	//std::unordered_map<std::string, glsl_imageCube*> _imageCubes;
	//std::unordered_map<std::string, glsl_imageCubeArray*> _imageCubeArrays;
	//std::unordered_map<std::string, glsl_image2DMS*> _image2DMSs;
	//std::unordered_map<std::string, glsl_image2DMSArray*> _image2DMSArrays;
	//std::unordered_map<std::string, glsl_image2DRect*> _image2DRects;
	//std::unordered_map<std::string, glsl_image3D*> _image3Ds;
	//std::unordered_map<std::string, glsl_imageBuffer*> _imageBuffers;

	//std::unordered_map<std::string, glsl_iimage1D*> _iimage1Ds;
	//std::unordered_map<std::string, glsl_iimage1DArray*> _iimage1DArrays;
	//std::unordered_map<std::string, glsl_iimage2D*> _iimage2Ds;
	//std::unordered_map<std::string, glsl_iimage2DArray*> _iimage2DArrays;
	//std::unordered_map<std::string, glsl_iimageCube*> _iimageCubes;
	//std::unordered_map<std::string, glsl_iimageCubeArray*> _iimageCubeArrays;
	//std::unordered_map<std::string, glsl_iimage2DMS*> _iimage2DMSs;
	//std::unordered_map<std::string, glsl_iimage2DMSArray*> _iimage2DMSArrays;
	//std::unordered_map<std::string, glsl_iimage2DRect*> _iimage2DRects;
	//std::unordered_map<std::string, glsl_iimage3D*> _iimage3Ds;
	//std::unordered_map<std::string, glsl_iimageBuffer*> _iimageBuffers;

	//std::unordered_map<std::string, glsl_uimage1D*> _uimage1Ds;
	//std::unordered_map<std::string, glsl_uimage1DArray*> _uimage1DArrays;
	//std::unordered_map<std::string, glsl_uimage2D*> _uimage2Ds;
	//std::unordered_map<std::string, glsl_uimage2DArray*> _uimage2DArrays;
	//std::unordered_map<std::string, glsl_uimageCube*> _uimageCubes;
	//std::unordered_map<std::string, glsl_uimageCubeArray*> _uimageCubeArrays;
	//std::unordered_map<std::string, glsl_uimage2DMS*> _uimage2DMSs;
	//std::unordered_map<std::string, glsl_uimage2DMSArray*> _uimage2DMSArrays;
	//std::unordered_map<std::string, glsl_uimage2DRect*> _uimage2DRects;
	//std::unordered_map<std::string, glsl_uimage3D*> _uimage3Ds;
	//std::unordered_map<std::string, glsl_uimageBuffer*> _uimageBuffers;

};

class glsl_graphics_pipeline_program : public glsl_program 
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

	void enable() {}

	void disable() {}

private:
	gl_program* _program;
	glsl_vertex_shader* _vertex_shader;
	glsl_tessellation_shader* _tessellation_shader;
	glsl_geometry_shader* _geometry_shader;
	glsl_fragment_shader* _fragment_shader;

};

class glsl_compute_pipeline_program : public glsl_program
{
public:
	glsl_compute_pipeline_program(glsl_compute_shader* compute_shader) :
		_program(nullptr),
		_cs(compute_shader)
	{}

	glsl_compute_pipeline_program(const glsl_compute_pipeline_program&) = delete;
	glsl_compute_pipeline_program& operator=(const glsl_compute_pipeline_program&) = delete;

	~glsl_compute_pipeline_program()
	{
		delete _program;
		delete _cs;
	}

private:
	gl_program* _program;
	glsl_compute_shader* _cs;

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


#define graphicsPipelineProgram()

#define computePipelineProgram()


#endif