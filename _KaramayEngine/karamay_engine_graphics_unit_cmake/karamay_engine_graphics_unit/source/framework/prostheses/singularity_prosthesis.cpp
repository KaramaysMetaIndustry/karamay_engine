#include "singularity_prosthesis.h"

singularity_prosthesis::singularity_prosthesis(avatar* owner, const std::string_view& name) :
	prosthesis(owner, name)
{
}

void singularity_prosthesis::wake()
{
}

void singularity_prosthesis::drive(float delta_time)
{
}

void singularity_prosthesis::hibernate()
{
}
