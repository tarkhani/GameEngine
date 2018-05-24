#include "WaterFrameBuffer.h"




GLuint WaterFrameBuffer::createFBO()
{
	numberofFBO++;
	glGenFramebuffers(1, &FBoIDes[numberofFBO]);
	return FBoIDes[numberofFBO];
}

GLuint WaterFrameBuffer::createFrameBuffer()
{
	GLuint frameBuffer = createFBO();
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return frameBuffer;
}

GLuint WaterFrameBuffer::createTexture()
{
	numberofTexture++;
	glGenTextures(1, &GLTextureIDes[numberofTexture]);
	return GLTextureIDes[numberofTexture];
}

GLuint WaterFrameBuffer::createRenderbuffers()
{
	numberofRenderbuffers++;
	glGenFramebuffers(1, &GLRenderbuffersIDes[numberofRenderbuffers]);
	return GLTextureIDes[numberofRenderbuffers];
}

int WaterFrameBuffer::createTextureAttachment(int width, int height)
{
	GLuint texture = createTexture();
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0 ,GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,texture, 0);
	return texture;
}

int WaterFrameBuffer::createDepthTextureAttachment(int width, int height)
{
	GLuint texture =  createTexture();
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT32, width, height, 0 , GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,texture, 0);
	return texture;
}

int WaterFrameBuffer::createDepthBufferAttachment(int width, int height)
{
	GLuint depthBuffer = createRenderbuffers();
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width,height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,depthBuffer);
	return depthBuffer;
}

void WaterFrameBuffer::unbindCurrentFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1920, 1080);
}

void WaterFrameBuffer::initialiseRefractionFrameBuffer()
{
	refractionFrameBuffer = createFrameBuffer();
	refractionTexture = createTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	unbindCurrentFrameBuffer();
}

void WaterFrameBuffer::initialiseReflectionFrameBuffer()
{
	reflectionFrameBuffer = createFrameBuffer();
	reflectionTexture = createTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	unbindCurrentFrameBuffer();
}

WaterFrameBuffer::WaterFrameBuffer()
{
	 initialiseRefractionFrameBuffer();
	 initialiseReflectionFrameBuffer();
}



