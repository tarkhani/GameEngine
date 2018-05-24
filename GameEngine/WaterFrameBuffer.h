#pragma once
#include<gl\glew.h>

class WaterFrameBuffer
{

private:
	GLuint FBoIDes[20];
	int numberofFBO = -1;

	GLuint GLTextureIDes[20];
	int numberofTexture = -1;

	GLuint GLRenderbuffersIDes[20];
	int numberofRenderbuffers = -1;

public:
	 static  const int REFLECTION_WIDTH ;
	 static  const int REFLECTION_HEIGHT ;
	 static  const int REFRACTION_WIDTH ;
	 static  const int REFRACTION_HEIGHT ;

	 GLuint reflectionFrameBuffer;
	 GLuint reflectionTexture;
	 GLuint reflectionDepthBuffer;

	 GLuint refractionFrameBuffer;
	 GLuint refractionTexture;
	 GLuint refractionDepthTexture;

	 void bindFrameBuffer(int frameBuffer, int width, int height) {
		 glBindTexture(GL_TEXTURE_2D, 0);
		 glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		 glViewport(0, 0, width, height);
	 }
	  void bindReflectionFrameBuffer() {
		 bindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
	 }

	 void bindRefractionFrameBuffer() {
		 bindFrameBuffer(refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
	 }

	 GLuint createFBO();
	 GLuint createFrameBuffer();
	 GLuint createTexture();
	 GLuint createRenderbuffers();
	 int createTextureAttachment(int width, int height);
	 int createDepthTextureAttachment(int width, int height);
	 int createDepthBufferAttachment(int width, int height);

	 void initialiseRefractionFrameBuffer();
	 void initialiseReflectionFrameBuffer();
	 WaterFrameBuffer::WaterFrameBuffer();
	
	 void unbindCurrentFrameBuffer();
	 void cleanUp() {
		 glDeleteFramebuffers(1,&reflectionFrameBuffer);
		 glDeleteTextures(1,&reflectionTexture);
		 glDeleteRenderbuffers(1, &reflectionDepthBuffer);
		 glDeleteFramebuffers(1, &refractionFrameBuffer);
		 glDeleteTextures(1, &refractionTexture);
		 glDeleteTextures(1, &refractionDepthTexture);
	 }

};

