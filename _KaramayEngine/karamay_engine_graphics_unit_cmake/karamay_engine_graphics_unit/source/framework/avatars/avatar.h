#ifndef AVATAR_H
#define AVATAR_H
#include "public/stl.h"

class world;
class prosthesis;
class entity_prosthesis;
class singularity_prosthesis;

class avatar
{
public:

	avatar(world* owner);

	avatar(const avatar&) = delete;
	avatar& operator=(const avatar&) = delete;

	virtual ~avatar() = default;

private:

	world* _owner = nullptr;

public:

	world* owner() const noexcept { return _owner; }

private:

	// keep ownership of prosthesis
	std::unordered_map<std::string, std::unique_ptr<prosthesis>> _name_to_prosthesis_map = {};
	
	// singularity sequence
	std::vector<singularity_prosthesis*> _singularities = {};
	
	// entity sequence
	std::vector<entity_prosthesis*> _entities = {};
	// entity root
	entity_prosthesis* _entity_root = nullptr;

protected:

	void _register_entity_prostheses();

	void _unregister_entity_prostheses();

	void _recycle_prostheses();

public:

	//template<class singularity_prosthesis_t>
	//singularity_prosthesis_t* create_singularity(const std::string& name) noexcept
	//{
	//	if (_name_to_prosthesis_map.find(name) == _name_to_prosthesis_map.cend())
	//	{
	//		std::cerr << "name exists" << std::endl;
	//		return nullptr;
	//	}

	//	auto _prosthesis = std::make_unique<singularity_prosthesis_t>(this);
	//	auto _raw_prosthesis = _prosthesis.get();
	//	_name_to_prosthesis_map.emplace(name, std::move(_prosthesis));
	//	_singularities.push_back(_raw_prosthesis);
	//	return _raw_prosthesis;
	//}

	//template<class entity_prosthesis_t>
	//entity_prosthesis_t* create_entity(const std::string& name, uint64 parent_index = std::numeric_limits<uint64> ::max()) noexcept
	//{
	//	if (_name_to_prosthesis_map.find(name) == _name_to_prosthesis_map.cend())
	//	{
	//		std::cerr << "name exists" << std::endl;
	//		return nullptr;
	//	}

	//	if (parent_index >= _entities.size() && 
	//		parent_index != std::numeric_limits<uint64> ::max())
	//	{
	//		return nullptr;
	//	}

	//	auto _entity = std::make_unique<entity_prosthesis_t>(this);
	//	auto _raw_entity = _entity.get();
	//	_name_to_prosthesis_map.emplace(name, std::move(_entity));
	//	_entities.push_back(_raw_entity);

	//	// root index
	//	if (parent_index == std::numeric_limits<uint64> ::max())
	//	{

	//	}

	//	auto _parent_entity = _entities[parent_index];
	//	_parent_entity->collect(_raw_entity);
	//	_raw_entity->attch_to(_parent_entity);
	//	return _raw_entity;
	//}


	void destroy_entity(uint64 index) noexcept;

	void destroy_singularity(uint64 index) noexcept;


	// invoke prosthesis
	prosthesis* invoke(const std::string& name) const noexcept;

	// invoke all prostheses
	void invoke_all(std::vector<prosthesis*>& out) const noexcept;


	// invoke singularity by index
	singularity_prosthesis* invoke_singularity(uint64 index) const noexcept;

	// invoke all singularities
	void invoke_singularities_all(std::vector<singularity_prosthesis*>& out_singularities) const noexcept;


	// invoke entity root
	entity_prosthesis* invoke_entity_root() const noexcept;

	// invoke entity by index
	entity_prosthesis* invoke_entity(uint64 index) const noexcept;

	// invoke all entities
	void invoke_entities_all(std::vector<entity_prosthesis*>& out_entities) const noexcept;

public:

	/*
	* wake the avatar
	* when the avatar first be loaded into the world, would be called.
	*/
	virtual void wake() noexcept;

	/*
	* heartbeat the avatar
	*/
	virtual void heartbeat(float delta_time) noexcept;

	/*
	* hibernate the avatar
	*/
	virtual void hibernate() noexcept;

	/*
	* check whether the avatar is awake
	*/
	virtual bool is_awake() const noexcept;

};

#endif

