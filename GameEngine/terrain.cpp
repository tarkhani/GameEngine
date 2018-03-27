#include<iostream>
#include<SDL_image.h>
#include<glm\glm.hpp>
#include "terrain.h"

terrain::terrain(int grindx, int grindy, Loader & loader, TerrainTexturePack & terrainTexturePack, TerrainTexture & blendMap, char * HightMapAddress):terrainTexturePack(terrainTexturePack), blendMap(blendMap), HightMapAddress(HightMapAddress)
{
	this->x = grindx*SIZE;
	this->z = grindx*SIZE;
	this->Rawmodel = GenrateTerrin(loader, HightMapAddress);
}

terrain::~terrain()
{
}

float getHeight(int x, int y, SDL_Surface *image){

	if (x<0||x>=image->h||y<0||y>= image->h)
	{
		return 0;
	}
	float MAX_PIXEL_COLOR = 256 + 256 + 256;
	float MAX_height = 5;
	Uint32 *pixels = (Uint32 *)image->pixels;
	int  height = image->h;
	Uint8 RED;
	Uint8 GREEN;
	Uint8 BLUE;
	Uint8 ALPHA;
	SDL_GetRGBA(pixels[y*height + x], image->format, &RED, &GREEN, &BLUE, &ALPHA);
	float totalColor = RED + GREEN + BLUE;
	totalColor -= MAX_PIXEL_COLOR / 2;
	totalColor /= MAX_PIXEL_COLOR / 2;
	totalColor *= MAX_height;
	return totalColor;
}
glm::vec3 CalculateNormal(int x, int y, SDL_Surface *image) {

	float HeightL = getHeight(x - 1, y, image);
	float HeightR = getHeight(x + 1, y, image);
	float HeightD = getHeight(x , y-1, image);
	float HeightU = getHeight(x , y+1, image);
	glm::vec3 normal = glm::vec3(HeightR - HeightL, 2.0f, HeightU - HeightD);
	glm::vec3 nnormal =glm::normalize(normal);
	return nnormal;

}

RawModel terrain::GenrateTerrin(Loader& loader ,char * HightMapAddress)
{

	SDL_Surface *image = IMG_Load(HightMapAddress);
	int  height = image->h;


	const int count = height *height;
	glm::vec3 *vertices=new glm::vec3[count];
	glm::vec3 * normals = new glm::vec3[count];
	glm::vec2 * textureCoords = new glm::vec2[count];
	unsigned short *indices = new unsigned short[6 * (height - 1)*(height - 1)];
	int vertexPointer = 0;
	for (int i = 0; i<height; i++) {
		for (int j = 0; j<height; j++) {

		
			vertices[vertexPointer ].x = (float)j / ((float)height - 1) * SIZE;
			vertices[vertexPointer ].y = getHeight(i,j, image);
			vertices[vertexPointer ].z = (float)i / ((float)height - 1) * SIZE;
			glm::vec3 normal = CalculateNormal(i, j, image);
			normals[vertexPointer ].x = normal.x;
			normals[vertexPointer ].y= normal.y;
			normals[vertexPointer ].z = normal.z;
			textureCoords[vertexPointer ].x = (float)j / ((float)height - 1);
			textureCoords[vertexPointer ].y = (float)i / ((float)height - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz<height - 1; gz++) {
		for (int gx = 0; gx<height - 1; gx++) {
			int topLeft = (gz*height) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*height) + gx;
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
	ARindex.numberOfElements = 6 * (height - 1)*(height - 1);
	ARindex.size = sizeof(unsigned short)*(6 * (height - 1)*(height - 1));


	RawModel terrin= loader.loadToVAO(ARvertices, ARuv, ARnormal, ARindex);
	delete[] vertices;
	delete[] textureCoords;
	delete[] normals;
	delete[] indices;


	return terrin;


}



