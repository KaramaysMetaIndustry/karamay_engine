#ifndef GRAPH_BUILFER
#define GRAPH_BUILDER

#include "../instance.h"
#include "../physical_device.h"
#include "../device.h"

class graph_builder final
{

private:

	std::unique_ptr<instance> _instance;
	
	std::vector<device*> _devices;

public:

	graph_builder();

	graph_builder(const graph_builder&) = delete;
	graph_builder& operator=(const graph_builder&) = delete;

	~graph_builder();


};


#endif