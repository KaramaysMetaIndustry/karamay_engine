#ifndef SINGULARITY_PROSTHESIS_H
#define SINGULARITY_PROSTHESIS_H
#include "prosthesis.h"

class singularity_prosthesis : public prosthesis
{
public:
	singularity_prosthesis() = delete;
	singularity_prosthesis(avatar* owner, const std::string_view& name);
	singularity_prosthesis(const singularity_prosthesis&) = delete;
	singularity_prosthesis& operator=(const singularity_prosthesis&) = delete;

	virtual ~singularity_prosthesis() = default;

private:

	std::string_view _name = {};

public:

	void wake() override;

	void drive(float delta_time) override;

	void hibernate() override;

};

#endif