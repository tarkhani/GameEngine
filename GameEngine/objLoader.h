#pragma once
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include"RawModel.h"
#include"Loader.h"
#include"StaticShader.h"

class objLoader
{
public:
	
	static RawModel LoadObj(char* file, Loader& loader);
	objLoader();
	~objLoader();
};

