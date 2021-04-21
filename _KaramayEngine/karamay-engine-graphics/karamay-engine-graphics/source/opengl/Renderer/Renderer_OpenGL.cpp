#include "Renderer_OpenGL.h"
#include "OpenGL/Implement_OpenGL.h"

void Renderer_OpenGL::LoadContext()
{
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR: Initializing GLEW failed." << std::endl;
		return;
	}
	std::cout << "[GLEW] has been initialized successfully." << std::endl;

	//GLuint FramebufferObject;
	//glCreateFramebuffers(1, &FramebufferObject);
	//glBindFramebuffer(GL_FRAMEBUFFER, FramebufferObject);

	//GLuint RenderbufferObject;
	//glCreateRenderbuffers(1, &RenderbufferObject);
	//glBindRenderbuffer(GL_RENDERBUFFER, RenderbufferObject);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 2560, 1440);

	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RenderbufferObject);
	////渲染到一个不同的帧缓冲被叫做离屏渲染(Off-screen Rendering)

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer_OpenGL::SetViewport(size_t Width, size_t Height)
{
	RendererBase::SetViewport(Width, Height);
	glViewport(0, 0, Width, Height);
}

void Renderer_OpenGL::Render(float DeltaTime)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL_FILL GL_POINT
	glFrontFace(GL_CCW);//default 逆时针 GL_CW 顺时针

	glEnable(GL_COLOR_BUFFER_BIT);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//glEnable(GL_ACCUM_BUFFER_BIT);
	//glClearAccum(1.0f, 0.2f, 1.0f, 1.0f);

	// when current frag-z < 1.0, keep it
	// fragShader write its z value before working
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glClearDepth(1.0f);

	//glEnable(GL_STENCIL_TEST);
	//glStencilFunc(GL_ALWAYS, 1, 0xFF);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	//glStencilMask(GL_TRUE);
	//glClearStencil(0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//GL_STENCIL_BUFFER | GL_ACCUM_BUFFER_BIT
	
	RendererBase::Render(DeltaTime);
}

Renderer_OpenGL::Renderer_OpenGL()
{
	Allocator = new RendererAllocator_OpenGL();
	
}

Renderer_OpenGL::~Renderer_OpenGL()
{
}
