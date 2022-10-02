#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include "glew.h"

class FrameBuffer
{
public:
	FrameBuffer();

	~FrameBuffer();

	void SettingUpFrameBuffer(int width, int height);
	void ClearFrameBuffer();

	GLuint GetFrameBuffer() { return framebuffer; }
	GLuint GetTextureBuffer() { return texcolorbuffer; }
	GLuint GetRenderBufferObject() { return rbodepthstencil; }
private:
	GLuint texcolorbuffer;
	GLuint framebuffer;
	//RenderBufferObject
	GLuint rbodepthstencil;
};

#endif //_FRAMEBUFFER_H_