#include "terrain.h"
#include<iostream>






terrain::terrain(int grindx, int grindz, Loader& loader, ModelTexture& modelTexture)
{
	this->x = grindx*SIZE;
	this->z = grindx*SIZE;
	this->Rawmodel= GenrateTerrin(loader);
	this->Modeltexture = modelTexture;
}

terrain::~terrain()
{
}

RawModel terrain::GenrateTerrin(Loader& loader)
{
	const int count = VERTEX_COUNT *VERTEX_COUNT;
	glm::vec3 *vertices=new glm::vec3[count];
	glm::vec3 * normals = new glm::vec3[count];
	glm::vec2 * textureCoords = new glm::vec2[count];
	unsigned short *indices = new unsigned short[6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1)];
	int vertexPointer = 0;
	for (int i = 0; i<VERTEX_COUNT; i++) {
		for (int j = 0; j<VERTEX_COUNT; j++) {
			vertices[vertexPointer ].x = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			vertices[vertexPointer ].y = 0;
			vertices[vertexPointer ].z = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
			normals[vertexPointer ].x = 0;
			normals[vertexPointer ].y= 1;
			normals[vertexPointer ].z = 0;
			textureCoords[vertexPointer ].x = (float)j / ((float)VERTEX_COUNT - 1);
			textureCoords[vertexPointer ].y = (float)i / ((float)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	
	ARRAY<glm::vec3> ARvertices;
	ARvertices.arrayPointer = vertices;
	ARvertices.numberOfElements = count;
	ARvertices.size = sizeof(glm::vec3)*count;

	ARRAY<glm::vec2> ARuv;
	ARuv.arrayPointer = textureCoords;
	ARuv.numberOfElements = count;
	ARuv.size = sizeof(glm::vec2)*count;

	ARRAY<glm::vec3> ARnormal;
	ARnormal.arrayPointer = normals;
	ARnormal.numberOfElements = count;
	ARnormal.size = sizeof(glm::vec3)*count;

	ARRAY<unsigned short> ARindex;
	ARindex.arrayPointer = indices;
	ARindex.numberOfElements = 6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1);
	ARindex.size = sizeof(unsigned short)*(6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1));


	RawModel terrin= loader.loadToVAO(ARvertices, ARuv, ARnormal, ARindex);
	delete[] vertices;
	delete[] textureCoords;
	delete[] normals;
	delete[] indices;

	return terrin;


}
