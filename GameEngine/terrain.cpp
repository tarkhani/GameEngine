#include<iostream>
#include<SDL_image.h>
#include<glm\glm.hpp>
#include <math.h> 
#include "terrain.h"
#include"Mats.h"

terrain::terrain(int grindx, int grindy, Loader & loader, TerrainTexturePack & terrainTexturePack, TerrainTexture & blendMap, char * HightMapAddress):terrainTexturePack(terrainTexturePack), blendMap(blendMap), HightMapAddress(HightMapAddress)
{
	this->x = grindx*SIZE;
	this->z = grindx*SIZE;
	this->Rawmodel = GenrateTerrin(loader, HightMapAddress);
}


float terrain::getHeightOfTerrian(float worldX, float worldZ)
{
	float terrainx = worldX - x;
	float terrainz = worldZ - z;
	float gridSquareSize = SIZE /float (length - 1);
	int gridX = floor(terrainx / gridSquareSize);
	int gridZ = floor(terrainz / gridSquareSize);
	
	if (gridX >=length - 1 || gridZ >= length - 1 || gridX <= 0 || gridZ <= 0)
	{
		return 0;
	}
	float xCoord = fmod(terrainx, gridSquareSize)/ gridSquareSize;
	float zCoord = fmod(terrainz, gridSquareSize)/ gridSquareSize;
	float answer = 0;

	if (xCoord <= (1 - zCoord)) {
		answer = Mats::barryCentric(glm::fvec3(0, heights[gridZ][gridX], 0), glm::fvec3(1,
				heights[gridZ][gridX + 1], 0), glm::fvec3(0,
				heights[gridZ + 1][gridX], 1), glm::fvec2(xCoord, zCoord));
	}
	else {
		answer = Mats::barryCentric(glm::fvec3(1, heights[gridZ][gridX + 1], 0), glm::fvec3(1,
				heights[gridZ + 1][gridX + 1], 1), glm::fvec3(0,
					heights[gridZ + 1][gridX], 1), glm::fvec2(xCoord, zCoord));

	}
	return answer;
}

terrain::terrain(const terrain & orginal):terrainTexturePack(orginal.terrainTexturePack),
blendMap(orginal.blendMap), HightMapAddress(orginal.HightMapAddress),x(orginal.x),z(orginal.z),
Rawmodel(orginal.Rawmodel), length(orginal.length)
{
	this->heights = new float*[this->length];
	for (int i = 0; i < this->length; i++)
	{
		heights[i] = new float[this->length];
	}

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			heights[i][j] = orginal.heights[i][j];
		}
	}
}

terrain::~terrain()
{
	for (int i = 0; i < length; ++i) {
		delete[] heights[i];
	}
	delete[] heights;
}

float getHeight(int x, int z, SDL_Surface *image){

	if (x<0||x>=image->h||z<0||z>= image->h)
	{
		return 0;
	}
	float MAX_PIXEL_COLOR = 256 + 256 + 256;
	float MAX_height = 4;
	Uint32 *pixels = (Uint32 *)image->pixels;
	int  height = image->h;
	Uint8 RED;
	Uint8 GREEN;
	Uint8 BLUE;
	Uint8 ALPHA;
	SDL_GetRGBA(pixels[z*height + x], image->format, &RED, &GREEN, &BLUE, &ALPHA);
	float totalColor = RED + GREEN + BLUE;
	totalColor -= MAX_PIXEL_COLOR / 2;
	totalColor /= MAX_PIXEL_COLOR / 2;
	totalColor *= MAX_height;
	return totalColor;
}
glm::vec3 CalculateNormal(int x, int z, SDL_Surface *image) {

	float HeightL = getHeight(x - 1, z, image);
	float HeightR = getHeight(x + 1, z, image);
	float HeightD = getHeight(x , z-1, image);
	float HeightU = getHeight(x , z+1, image);
	glm::vec3 Normal = glm::vec3(HeightL - HeightR, 2.0f, HeightD - HeightU);
	glm::vec3 NormlizeNormal =glm::normalize(Normal);
	return NormlizeNormal;

}

RawModel terrain::GenrateTerrin(Loader& loader ,char * HightMapAddress)
{

	SDL_Surface *image = IMG_Load(HightMapAddress);
	int  height = image->h;
	length = height;
	heights = new float*[height];
	for (int i = 0; i < height; i++)
	{
		heights[i] = new float[height];
	}

	const int count = height *height;
	glm::vec3 *vertices=new glm::vec3[count];
	glm::vec3 * normals = new glm::vec3[count];
	glm::vec2 * textureCoords = new glm::vec2[count];
	unsigned short *indices = new unsigned short[6 * (height - 1)*(height - 1)];
	int vertexPointer = 0;
	for (int i = 0; i<height; i++) {
		for (int j = 0; j<height; j++) {

			heights[i][j] = getHeight(j, i, image);
			vertices[vertexPointer ].x = (float)j / ((float)height - 1) * SIZE;
			vertices[vertexPointer ].y = heights[i][j];
			vertices[vertexPointer ].z = (float)i / ((float)height - 1) * SIZE;
			glm::vec3 normal = CalculateNormal(j, i, image);
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



