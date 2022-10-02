#include "FrameBuffer.h"
#include "Globals.h"

FrameBuffer::FrameBuffer()
{
}

FrameBuffer::~FrameBuffer()
{
}

void FrameBuffer::SettingUpFrameBuffer(int width,int height)
{
	
	ClearFrameBuffer();

	glGenFramebuffers(1, &framebuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glGenTextures(1, &texcolorbuffer);
	glBindTexture(GL_TEXTURE_2D, texcolorbuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//attaching the image to the framebuffer.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texcolorbuffer, 0);

	glGenRenderbuffers(1, &rbodepthstencil);
	glBindRenderbuffer(GL_RENDERBUFFER, rbodepthstencil);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbodepthstencil);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("FrameBuffer is not complete!!!");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void FrameBuffer::ClearFrameBuffer()
{

	if (framebuffer != 0) 
	{ 
		glDeleteFramebuffers(1, &framebuffer); 
	};
	if (texcolorbuffer != 0)
	{ 
		glDeleteTextures(1, &texcolorbuffer); 
	};
	if (rbodepthstencil != 0) 
	{ 
		glDeleteRenderbuffers(1, &rbodepthstencil); 
	};
}
