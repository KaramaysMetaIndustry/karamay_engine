#ifndef H_GL_TRANSFORM_FEEDBACK
#define H_GL_TRANSFORM_FEEDBACK

#include "graphics/glo/gl_object.h"
class gl_buffer;

class gl_transform_feedback_descriptor
{
public:
    std::vector<std::string> varyings;
};


class gl_transform_feedback final : public gl_object
{
public:

	explicit gl_transform_feedback(const std::shared_ptr<gl_transform_feedback_descriptor>& descriptor);

	~gl_transform_feedback() override;

private:

    gl_transform_feedback_descriptor _descriptor;

	std::shared_ptr<gl_buffer> _output_buffer;

	void _generate_buffer();

public:

    [[nodiscard]] const auto& get_varyings() const {return _descriptor.varyings;}

	void associate_buffer(std::uint32_t index, const std::shared_ptr<gl_buffer>& buffer);

	void associate_buffer(std::uint32_t index, const std::shared_ptr<gl_buffer>& buffer, std::int64_t offset, std::int64_t size);

	void bind();

	void unbind();

	std::shared_ptr<const gl_buffer> get_output_buffer() const;

};


#endif
