#pragma once
#include<stdio.h>
#include <random>
#include<vector>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include"Rendrer.h"
#include"Loader.h"
#include"StaticShader.h"
#include"ModelTexture.h"
#include"textureModel.h"
#include"entity.h"
#include"Camera.h"
#include"objLoader.h"
#include"Light.h"
#include"RenderMaster.h"
#include"terrain.h"
glm::mat4 const RenderMaster::proj = glm::perspective(70.0f, ((float)1920 / 1080), 0.1f, 100.0f);

using namespace std;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
Camera camera;

int main(void)
{
	
	if (!glfwInit())
	{
		fprintf(stderr, "!glfwInit() failed");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	 GLFWwindow *window = glfwCreateWindow(1920,1080, "Game", glfwGetPrimaryMonitor(), NULL);
	if (window == NULL) {
		fprintf(stderr, "glfwCreateWindow() failed");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "FaglewInit() failed");
		getchar();
		glfwTerminate();
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	
	list<terrain> allTerrain;
	Loader loader;
	RenderMaster renderMaster;
	Light light(glm::vec3(0.0f,10.0f, -10.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelTexture  TerrainTexture(loader.loadTexture("terrain.png"));
	terrain Terrain(-1, 0, loader, TerrainTexture);

	allTerrain.push_back(Terrain);


	list<entity> allEntity;
	RawModel Treemodel = objLoader::LoadObj("tree.obj", loader);
	ModelTexture  treeTexture(loader.loadTexture("tree.png"));
	treeTexture.ReflectionScale = 0.4;
	treeTexture.ShineDamper = 0.4;
	textureModel TreeTexureModel(Treemodel, treeTexture);

	RawModel grass = objLoader::LoadObj("grass.obj", loader);
	ModelTexture  grassTexture(loader.loadTexture("grass.png"));
	grassTexture.ReflectionScale = 0.0;
	grassTexture.ShineDamper = 0.0;
	grassTexture.tansparent = true;
	grassTexture.FakeLightning = true;
	textureModel GrassTexureModel(grass, grassTexture);


	const int nrolls = 200;//number of tree
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(5, 100);//min and max of terrain
	float *randomx = new float[nrolls];
	float *randomz = new float[nrolls];
	for (int i = 0; i <nrolls; i++)
	{
		randomx[i] = distribution(generator);
		randomz[i] = distribution(generator);

		entity  grass = entity(GrassTexureModel, glm::fvec3(-randomx[i], 0.0f, -randomz[i]), 0, 180, 0, 0.5);
		allEntity.push_back(grass);

		entity  tree = entity(TreeTexureModel, glm::fvec3(-randomx[i], 0.0f,-randomz[i]), 0, 180, 0, 1);
		allEntity.push_back(tree);

	}
	delete[]randomx;
	delete[]randomz;

	do {

		for (std::list<entity>::iterator it1 = allEntity.begin(); it1 != allEntity.end(); ++it1)
		{
			renderMaster.ProcessEntity(*it1);
		}
		for (std::list<terrain>::iterator it2 = allTerrain.begin(); it2 != allTerrain.end(); ++it2)
		{
			renderMaster.ProcessTerrain(*it2);
		}

		renderMaster.Render(light, camera);
		glfwSwapBuffers(window);
		glfwPollEvents();
		
	} 
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	renderMaster.CleanUp();
	glfwTerminate();

	return 0;
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		camera.MoveForward();
	};
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		camera.MoveLeft();
	};
	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		camera.MoveRight();
	};
	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		camera.MoveBackward();
	};
	if (key == GLFW_KEY_R && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		camera.MoveUp();
	};
	if (key == GLFW_KEY_F && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		camera.MoveDown();
	};
}
