#ifndef AVATAR_H
#define AVATAR_H
#include "public/glm.h"
#include "framework/world/world.h"
#include "framework/prostheses/singularity_prosthesis.h"
#include "framework/prostheses/entity_prosthesis.h"

class avatar
{
public:
	avatar() = delete;
	avatar(world* owner, const std::string_view& name);
	avatar(const avatar&) = delete;
	avatar& operator=(const avatar&) = delete;

	virtual ~avatar() = default;

private:

	// for invoked ptr, the keeper's lifesycle must <= the invoked ptr's instance's lifesycle
	world* _invoked_owner = nullptr;
	
	// the unique name in the world
	std::string_view _name = {};

public:

	// invoke the owner  : world
	world* owner() const noexcept { return _invoked_owner; }

	// invoke the unique name
	const std::string_view& name() const noexcept { return _name; }

private:

	// keep ownership of prosthesis
	std::unordered_map<std::string_view, std::unique_ptr<prosthesis>> _name_to_prosthesis_map = {};
	
	// singularity sequence
	std::vector<singularity_prosthesis*> _singularities = {};
	
	// entity sequence
	std::vector<entity_prosthesis*> _entities = {};
	// entity root
	entity_prosthesis* _entity_root = nullptr;

public:

	template<class singularity_prosthesis_t>
	singularity_prosthesis_t* create_singularity(const std::string_view& name) noexcept
	{
		if (_name_to_prosthesis_map.find(name) != _name_to_prosthesis_map.cend())
		{
			std::cerr << "name exists" << std::endl;
			return nullptr;
		}
		// create the unique ptr and return the invoked ptr
		auto _prosthesis = std::make_unique<singularity_prosthesis_t>(this);
		auto _raw_prosthesis = _prosthesis.get();
		_name_to_prosthesis_map.emplace(name, std::move(_prosthesis));
		_singularities.push_back(_raw_prosthesis);
		return _raw_prosthesis;
	}

	template<class entity_prosthesis_t>
	entity_prosthesis_t* create_entity(const std::string_view& name, uint64 parent_index = std::numeric_limits<uint64> ::max()) noexcept
	{
		if (_name_to_prosthesis_map.find(name) != _name_to_prosthesis_map.cend())
		{
			std::cerr << "name exists" << std::endl;
			return nullptr;
		}

		if (parent_index >= _entities.size() && 
			parent_index != std::numeric_limits<uint64> ::max())
		{
			std::cerr << "parent index must does not exist" << std::endl;
			return nullptr;
		}

		auto _entity = std::make_unique<entity_prosthesis_t>(this);
		auto _raw_entity = _entity.get();
		_name_to_prosthesis_map.emplace(name, std::move(_entity));
		_entities.push_back(_raw_entity);

		// root index
		if (parent_index == std::numeric_limits<uint64> ::max())
		{

		}

		auto _parent_entity = _entities[parent_index];
		_parent_entity->collect(_raw_entity);
		_raw_entity->attch_to(_parent_entity);
		return _raw_entity;
	}

public:

	// invoke prosthesis by [unique name]
	prosthesis* invoke(const std::string_view& name) const noexcept;

	// invoke all prostheses
	// promise sequence :singularities ->  entities
	void invoke_all(std::vector<prosthesis*>& out_prostheses) const noexcept;


	// invoke singularity prosthesis by index
	singularity_prosthesis* invoke_singularity(uint64 index) const noexcept;

	// invoke all singularity prostheses
	// promise sequence : creation sequence
	void invoke_singularities_all(std::vector<singularity_prosthesis*>& out_singularities) const noexcept;


	// invoke entity prosthesis by index
	entity_prosthesis* invoke_entity(uint64 index) const noexcept;

	// invoke all entity prostheses
	// promise sequence : creation sequence
	void invoke_entities_all(std::vector<entity_prosthesis*>& out_entities) const noexcept;

	// invoke entity root
	// when you create an entity prosthesis for avatar, it will be 
	entity_prosthesis* invoke_entity_root() const noexcept;

public:

	// make an entity prosthesis to dispace the old root, if do not have root, return;
	// if old_root_recipient is nullptr, the old root will be destroy otherwise it will be attach to the recipient
	void displace_entity_root(entity_prosthesis* invoked_insurgent, entity_prosthesis* invoked_old_root_recipient = nullptr) noexcept;

public:

	// destroy prosthesis by name
	void destroy(const std::string_view& prosthesis_name) noexcept;

	// destroy entity prosthesis by index
	void destroy_entity(uint64 index) noexcept;

	// destroy entiy prosthesis by ptr
	void destroy_entity(entity_prosthesis* entity) noexcept;

	// destroy singularity prosthesis by index
	void destroy_singularity(uint64 index) noexcept;

	// destroy singularity prosthesis by ptr
	void destroy_singularity(singularity_prosthesis* singularity) noexcept;

public:

	uint64 num_of_prostheses() const noexcept { return _name_to_prosthesis_map.size(); }

	uint64 num_of_entities() const noexcept { return _entities.size(); }

	uint64 num_of_singularities() const noexcept { return _singularities.size(); }

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

