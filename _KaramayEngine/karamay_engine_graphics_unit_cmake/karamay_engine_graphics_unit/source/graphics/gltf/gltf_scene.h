#ifndef GLTF_SCENE_H
#define GLTF_SCENE_H

#include "public/nlohmann_json.h"
#include "gltf_node.h"
#include "gltf_accessor.h"
#include "gltf_buffer.h"
#include "gltf_buffer_view.h"

class gltf_scene
{
public:

	void load(const std::string& path)
	{
		std::string _scene_gltf_path = path + "\\scene.gltf";
		nlohmann::json _scene_gltf;
		std::ifstream(_scene_gltf_path) >> _scene_gltf;

		auto _obj = _scene_gltf.object();

		int index = _scene_gltf.at("scene");
		auto _scenes = _scene_gltf.at("scenes");
		auto _buffers = _scene_gltf.at("buffers");
		auto _buffer_views = _scene_gltf.at("bufferViews");
		auto _images = _scene_gltf.at("images");

		std::vector<gltf_buffer*> _gltf_buffers;
		for (auto _it = _buffers.cbegin(); _it != _buffers.cend(); ++_it)
		{
			auto _buf = new gltf_buffer(*_it);
			if (_buf) _gltf_buffers.push_back(_buf);
		}

		std::vector<gltf_buffer_view*> _gltf_buffer_views;
		for (auto _it = _buffer_views.cbegin(); _it != _buffer_views.cend(); ++_it)
		{
			auto _buf_view = new gltf_buffer_view(*_it);
			if (_buf_view) _gltf_buffer_views.push_back(_buf_view);
		}

		std::vector<gltf_image*> _gltf_images;
		for (auto _it = _images.cbegin(); _it != _images.cend(); ++_it)
		{
			auto _imag = new gltf_image(*_it);
			if (_imag) _gltf_images.push_back(_imag);
		}

		
		auto _first_scene = *_scenes.begin();
		_name = _first_scene.at("name");

		std::vector<gltf_node*> _tmp_nodes;

		auto _ref_node_indices = _first_scene.at("nodes");
		std::vector<int> _indices;
		for (auto _it = _ref_node_indices.begin(); _it != _ref_node_indices.end(); ++_it)
		{
			_indices.push_back(_it->get<int>());
		}


		int8 x = 0;

	}

private:

	std::string _name;
	std::vector<gltf_node*> _nodes;
	
};

#endif