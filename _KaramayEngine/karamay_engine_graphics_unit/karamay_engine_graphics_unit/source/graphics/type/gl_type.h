#pragma once
#include "public/opengl.h"


class gl_type
{
};


class gl_transparent_type
{
public:
	
	gl_transparent_type(){}

private:

	

};


class gl_transparent_data
{
private:

	gl_transparent_type _type;
};


class gl_float : public gl_transparent_data
{
	
public:

};

class gl_vec2 : public gl_transparent_data
{

};

class gl_mat4 : public gl_transparent_data
{

};


class gl_double : public gl_transparent_data
{

};

class gl_dvec2 : public gl_transparent_data
{

};

class gl_dmat4 : public gl_transparent_data
{

};



