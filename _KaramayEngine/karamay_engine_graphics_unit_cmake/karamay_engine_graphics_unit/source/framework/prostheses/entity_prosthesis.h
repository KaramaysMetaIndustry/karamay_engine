#ifndef ENTITY_PROSTHESIS_H
#define ENTITY_PROSTHESIS_H
#include "prosthesis.h"

class entity_prosthesis : public prosthesis
{
public:

	entity_prosthesis(avatar* owner);

	entity_prosthesis(const entity_prosthesis&) = delete;
	entity_prosthesis& operator=(const entity_prosthesis&) = delete;

	virtual ~entity_prosthesis() = default;

private:

	entity_prosthesis* _parent = nullptr;

	std::vector<entity_prosthesis*> _children = {};

public:

	void collect(entity_prosthesis* entity) noexcept;

	void attach_to(entity_prosthesis* parent_entity) noexcept;

	void release(entity_prosthesis* entity) noexcept;

public:

	void wake() override;

	void drive(float delta_time) override;

	void hibernate() override;

};

#endif
