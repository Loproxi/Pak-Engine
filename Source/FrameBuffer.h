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
	int GetWidthFrame() { return width; }
	int GetHeightFrame() { return height; }
	void SetWidthFrame(int width) { this->width = width; }
	void SetHeightFrame(int height) { this->height = height; }
private:
	GLuint texcolorbuffer;
	GLuint framebuffer;
	//RenderBufferObject
	GLuint rbodepthstencil;
	int width;
	int height;
};

#endif //_FRAMEBUFFER_H_