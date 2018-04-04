#pragma once
#include<list>
#include"RawModel.h"
#include"GL\glew.h"
#include<iostream>
#include"ARRAY.h"
#include"glm\common.hpp"


 class Loader
{
public:


	GLuint VaoIDes[30];
	GLuint VboIDes[30];
	GLuint VIboIDes[30];
	GLuint GLTextureIDes[30];
	unsigned char*textures[30];
	int numberofvao = -1;
	int numberofvbo = -1;
	int numberofindexBuffer = -1;
	int numberofTexture = -1;
	
	RawModel loadToVAO(ARRAY<glm::vec3> positions, ARRAY<glm::vec2> uv, ARRAY<glm::vec3> Normal, ARRAY<unsigned short> index);
	RawModel loadToVAO(ARRAY<glm::vec2> positions);
	GLuint createVAO();
	GLuint createVBO();
	GLuint LoadIndexBuffer(ARRAY<unsigned short> index);
	GLuint loadTexture(char* filepath);
	
	 Loader();
	~Loader();

private:
	template<class T>
	void storeDataInAttributeList(int attributeNumber, int Coordinatesize, ARRAY<T> data);
};
 
