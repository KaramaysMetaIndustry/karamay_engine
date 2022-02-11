#ifndef ENTITY_PROSTHESIS_H
#define ENTITY_PROSTHESIS_H
#include "prosthesis.h"

class entity_prosthesis : public prosthesis
{

public:

	void wake() override;

	void drive(float delta_time) override;

	void hibernate() override;

};

#endif
