#ifndef GL_SYNC_H
#define GL_SYNC_H

#include "public/_glew.h"

enum class gl_sync_result : GLenum
{
	ALREADY_SIGNALED = GL_ALREADY_SIGNALED,
	TIMEOUT_EXPIRED = GL_TIMEOUT_EXPIRED,
	CONDITION_SATISFIED = GL_CONDITION_SATISFIED,
	WAIT_FAILED = GL_WAIT_FAILED
};

class gl_fence
{
public:
	gl_fence()
	{
		_sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	}

	~gl_fence()
	{
		glDeleteSync(_sync);
	}

public:

	gl_sync_result client_wait(uint32 timeout)
	{
		return static_cast<gl_sync_result>(glClientWaitSync(_sync, GL_SYNC_FLUSH_COMMANDS_BIT, timeout));
	}

	void server_wait()
	{
		glWaitSync(_sync, 0, 0);
	}

private:

	GLsync _sync;

};

#endif