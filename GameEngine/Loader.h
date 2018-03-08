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

	GLuint VaoIDes[10];
	GLuint VboIDes[10];
	GLuint VIboIDes[10];
	GLuint GLTextureIDes[20];
	unsigned char*textures[10];
	int numberofvao = -1;
	int numberofvbo = -1;
	int numberofindexBuffer = -1;
	int numberofTexture = -1;
	
	RawModel loadToVAO(ARRAY<glm::vec3> positions, ARRAY<glm::vec2> uv, ARRAY<int> index);
	GLuint createVAO();
	GLuint createVBO();
	GLuint LoadIndexBuffer(ARRAY<int> index);
	GLuint loadTexture(char* filepath);
	
	 Loader();
	~Loader();

private:
	template<class T>
	void storeDataInAttributeList(int attributeNumber, int Coordinatesize, ARRAY<T> data);
};
 
