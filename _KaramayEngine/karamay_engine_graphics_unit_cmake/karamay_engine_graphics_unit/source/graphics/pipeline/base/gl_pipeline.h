#include "graphics/program/gl_program.h"

class gl_pipeline 
{

protected:
	
	gl_pipeline() = default;

public:

	virtual bool initialize() = 0;

	virtual void install() = 0;

};