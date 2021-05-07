#pragma once

#include "public/stl.h"
#include "Interface/texture/texture_2d.h"

class material
{
	std::float_t opacity;

	std::shared_ptr<texture_2d> albedo_map;

	std::shared_ptr<texture_2d> metallic_map;
	
	std::shared_ptr<texture_2d> displacement_map;
	
	std::shared_ptr<texture_2d> normal_map;

};

