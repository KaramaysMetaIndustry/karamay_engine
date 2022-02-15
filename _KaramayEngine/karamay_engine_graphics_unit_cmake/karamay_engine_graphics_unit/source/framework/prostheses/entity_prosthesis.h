#ifndef ENTITY_PROSTHESIS_H
#define ENTITY_PROSTHESIS_H
#include "prosthesis.h"

class entity_prosthesis : public prosthesis
{
public:
	entity_prosthesis() = delete;
	entity_prosthesis(avatar* owner, const std::string_view& name);

	entity_prosthesis(const entity_prosthesis&) = delete;
	entity_prosthesis& operator=(const entity_prosthesis&) = delete;

	virtual ~entity_prosthesis() = default;

public:

	//glm::vec3 position;
	//glm::vec3 rotation;
	//glm::vec3 scale;

private:

	entity_prosthesis* _invoked_parent = nullptr;

	std::vector<entity_prosthesis*> _invoked_children = {};

public:

	void attach_to(entity_prosthesis* parent_entity) noexcept;

	void collect(entity_prosthesis* entity) noexcept;

	void collect(const std::vector<entity_prosthesis*>& entities) noexcept;

	void release(entity_prosthesis* entity) noexcept;

	void release(const std::vector<entity_prosthesis*>& entities) noexcept;

	void fetch_children_all(std::vector<entity_prosthesis*>& out) const noexcept;

public:

	void wake() override;

	void drive(float delta_time) override;

	void hibernate() override;

};

#endif
