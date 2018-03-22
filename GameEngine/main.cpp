#pragma once
#include<stdio.h>
#include <random>
#include<vector>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include<chrono>
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
#include"TerrainTexture.h"
#include"TerrainTexturePack.h"
#include"Player.h"
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;


glm::mat4 const RenderMaster::proj = glm::perspective(70.0f, ((float)1920 / 1080), 0.1f, 100.0f);
void checkInput(GLFWwindow* window, Player& player);

using namespace std;
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
	TerrainTexture BackGroundTexture(loader.loadTexture("terrain.png"));
	TerrainTexture rTexture(loader.loadTexture("mud.png"));
	TerrainTexture gTexture(loader.loadTexture("path.png"));
	TerrainTexture bTexture(loader.loadTexture("grassFlowers.png"));
	TerrainTexture BlendMap(loader.loadTexture("blendMap.png"));
	TerrainTexturePack terrainTexturePack (BackGroundTexture, rTexture, gTexture, bTexture);


	terrain Terrain(-1, 0, loader, terrainTexturePack, BlendMap);

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


	RawModel playerRawModel = objLoader::LoadObj("person.obj", loader);
	ModelTexture  playerTexture(loader.loadTexture("playerTexture.png"));
	playerTexture.ReflectionScale = 0.0;
	playerTexture.ShineDamper = 0.0;
	
	textureModel PersonTexureModel(playerRawModel, playerTexture);

	Player player(PersonTexureModel, glm::fvec3(0.0f, 0.0f, 0.0f), 0, 0, 0, 0.4);
	

	do {
		auto START = Time::now();
		
		for (std::list<entity>::iterator it1 = allEntity.begin(); it1 != allEntity.end(); ++it1)
		{
			renderMaster.ProcessEntity(*it1);
			
		}
		for (std::list<terrain>::iterator it2 = allTerrain.begin(); it2 != allTerrain.end(); ++it2)
		{
			renderMaster.ProcessTerrain(*it2);
		}

		checkInput(window, player);
		renderMaster.Render(light, camera);

		auto END = Time::now();//getting delta time(how much time took to render frame)
		fsec delta =  END-START;
		
		player.Move(delta.count());
		allEntity.push_front(player);
		allEntity.unique();

		
		glfwSwapBuffers(window);
		glfwPollEvents();
		
	} 
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	renderMaster.CleanUp();
	glfwTerminate();

	return 0;
}

void checkInput(GLFWwindow* window, Player& player) {

	int state1 = glfwGetKey(window, GLFW_KEY_W);
	int state2 = glfwGetKey(window, GLFW_KEY_S);
	int state3 = glfwGetKey(window, GLFW_KEY_A);
	int state4 = glfwGetKey(window, GLFW_KEY_D);
	int state5 = glfwGetKey(window, GLFW_KEY_SPACE);

	if (state1 == GLFW_PRESS){ player.MoveForward();}
	else if (state2 == GLFW_PRESS) {player.MoveBackward();}
	else {player.CurrectSpeed = 0;}

	if (state3 == GLFW_PRESS) {player.MoveLeft();}
	else if (state4 == GLFW_PRESS) {player.MoveRight();}
	else {player.CurrectTurnSpeed = 0;}

	if (state5 == GLFW_PRESS)
	{
		player.playerJump();
	}

}


