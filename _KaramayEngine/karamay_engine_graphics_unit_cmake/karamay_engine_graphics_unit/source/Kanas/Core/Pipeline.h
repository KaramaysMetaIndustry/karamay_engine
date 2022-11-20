#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class buffer;
class shader_module;
class pipeline_layout;
class pipeline_cache;
class descriptor_set;
class command_buffer;

class pipelineConstants
{

public:

	uint8* GetData();

	std::uint64_t GetSize();
};


class pipeline : public device_object<VkPipeline>
{
public:

	pipeline(device& owner, VkPipelineBindPoint InBindPoint);

	pipeline(const device&) = delete;
	pipeline& operator=(const device&) = delete;

	virtual ~pipeline() override;

	void CmdBind(command_buffer& InRecorder);

	void CmdBindDescriptorSets(command_buffer& InRecorder);

	void CmdPushConstants(command_buffer& InRecorder);

	std::shared_ptr<pipeline_layout> GetLayout() const;

	VkPipelineBindPoint GetBindPoint() const;

private:

	std::shared_ptr<pipeline_layout> Layout;

	VkPipelineBindPoint BindPoint;

	std::shared_ptr<pipelineConstants> Constants;

};

_KANAS_CORE_END

#endif