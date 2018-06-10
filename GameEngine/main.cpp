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
#include"GuiTexture.h"
#include"GuiRenderer.h"
#include"SkyboxRenderer.h"
#include"MousePicker.h"
#include"WaterRenderer.h"
#include"WaterTile.h"
#include"WaterFrameBuffer.h"

 const int WaterFrameBuffer::REFLECTION_HEIGHT = 1080;
 const int WaterFrameBuffer::REFLECTION_WIDTH = 1920;
 const int WaterFrameBuffer::REFRACTION_HEIGHT = 1080;
 const int WaterFrameBuffer::REFRACTION_WIDTH = 1920;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

glm::mat4 const RenderMaster::proj = glm::perspective(70.0f, ((float)1920 / 1080), 0.1f, 200.0f);
float WaterTile::TILE_SIZE = 100;
float const WATERLEVEL = -0.89;
void checkInput(GLFWwindow* window, Player &player, Camera& camera);
struct Point {

	double x, y;

};

Point oldPoint, NewPoint, deltaMosePos;

using namespace std;


int main()
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
	
	 GLFWwindow *window = glfwCreateWindow(1920,1080, "Game", glfwGetPrimaryMonitor(),NULL);
	 
	if (window == NULL) {
		fprintf(stderr, "glfwCreateWindow() failed");
		getchar();
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetScrollCallback(window, scroll_callback);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "FaglewInit() failed");
		getchar();
		glfwTerminate();
		return -1;
	}
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_CLIP_DISTANCE0);
	
	
	list<terrain> allTerrain;
	Loader loader;
	RenderMaster renderMaster(loader);

	std::list<WaterTile> waters;
	WaterTile water1(1, 1, WATERLEVEL);
	waters.push_back(water1);


	Light light1(glm::vec3(-80.0f, 7.0f,-10.0f), glm::vec3(1.0f, 0.8f, 0.8f), glm::vec3(1.0f, 0.04f, 0.001f));
	Light light2(glm::vec3(-38.0f, 7.0f, -60.0f), glm::vec3(1.0f, 0.8f, 0.8f), glm::vec3(1.0f, 0.04f, 0.001f));
	Light light3(glm::vec3(-30.0f, 7.0f, -90.0f), glm::vec3(1.0f, 0.8f, 0.8f), glm::vec3(1.0f, 0.04f, 0.001f));
	Light light4(glm::vec3(-100.0f, 7.0f, -100.0f), glm::vec3(1.0f, 0.8f, 0.8f), glm::vec3(1.0f, 0.04f, 0.001f));
	std::vector<Light> lights;
	lights.reserve(4);
	lights.push_back(light1);
	lights.push_back(light2);
	lights.push_back(light3);
	lights.push_back(light4);


	TerrainTexture BackGroundTexture(loader.loadTexture("./res/hgrass.png"));
	TerrainTexture rTexture(loader.loadTexture("./res/hgrass.png"));
	TerrainTexture gTexture(loader.loadTexture("./res/hgrass.png"));
	TerrainTexture bTexture(loader.loadTexture("./res/hgrass.png"));
	TerrainTexture BlendMap(loader.loadTexture("./res/hgrass.png"));
	TerrainTexturePack terrainTexturePack (BackGroundTexture, rTexture, gTexture, bTexture);

	terrain Terrain(-1, 0, loader, terrainTexturePack, BlendMap, "./res/heightmap.png");
	Terrain.ReflectionScale = 0.0;
	Terrain.ShineDamper = 0.0;

	allTerrain.push_back(Terrain);

	GuiRenderer guiRenderer(loader);
	list<GuiTexture>allGuis;
	GuiTexture healthBar(loader.loadTexture("./res/healthBar.png"), glm::vec2(-0.75,-0.8), glm::vec3(.1, 0.1, 0.1));
	allGuis.push_back(healthBar);



	list<entity> allEntity;
	RawModel Treemodel = objLoader::LoadObj("./res/lptree1.obj", loader);
	ModelTexture  treeTexture(loader.loadTexture("./res/treecolor.png"));
	treeTexture.ReflectionScale = 0.0;
	treeTexture.ShineDamper = 0.0;
	treeTexture.NumberofRow = 1;
	textureModel TreeTexureModel(Treemodel, treeTexture);

	RawModel grassModel = objLoader::LoadObj("./res/lgrass.obj", loader);
	ModelTexture  grassTexture(loader.loadTexture("./res/hgrass.png"));
	grassTexture.ReflectionScale = 0.0;
	grassTexture.ShineDamper = 0.0;
	grassTexture.tansparent = false;
	grassTexture.FakeLightning = false;
	grassTexture.NumberofRow = 1;
	textureModel GrassTexureModel(grassModel, grassTexture);


	RawModel lampModel = objLoader::LoadObj("./res/lamp.obj", loader);
	ModelTexture lampTexture(loader.loadTexture("./res/lamp.png"));
	lampTexture.ReflectionScale = 0.1;
	lampTexture.ShineDamper = 0.1;
	lampTexture.tansparent = false;
	lampTexture.FakeLightning = true;
	lampTexture.NumberofRow = 1;
	textureModel lampTexureModel(lampModel, lampTexture);
	entity  lamp = entity(lampTexureModel, glm::fvec3(-38, Terrain.getHeightOfTerrian(-40, -60), -60), 0, 0, 0, 0.2);
	allEntity.push_back(lamp);
	lamp = entity(lampTexureModel, glm::fvec3(-80, Terrain.getHeightOfTerrian(-80, -10), -10), 0, 0, 0, 0.2);
	allEntity.push_back(lamp);
	lamp = entity(lampTexureModel, glm::fvec3(-30, Terrain.getHeightOfTerrian(-30, -90),-90), 0, 0, 0, 0.2);
	allEntity.push_back(lamp);
	lamp = entity(lampTexureModel, glm::fvec3(-100, 0, -100), 0, 0, 0, 0.3);
	allEntity.push_back(lamp);




	const double grassRolls = 100;//number of grass
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0, 100);//min and max of terrain
	std::uniform_real_distribution<double> Flowerdistribution(4, 12);
	std::uniform_real_distribution<double> HeightDistribution(0.6, 1.6);
	float *randomx = new float[grassRolls];
	float *randomz = new float[grassRolls];

	for (int i = 0; i < grassRolls; i++)
	{
		randomx[i] = distribution(generator);
		randomz[i] = distribution(generator);
		float height = Terrain.getHeightOfTerrian(-randomx[i], -randomz[i]);
		if (height > WATERLEVEL)
		{
			entity  grass_flower = entity(GrassTexureModel, 1, glm::fvec3(-randomx[i], height, -randomz[i]), 0, 0, 0, 0.09);
			allEntity.push_back(grass_flower);
		}
	}

	const double TreeRolls = 50;//number of tree
	double *randomHeghit = new double[TreeRolls];
	double *randomwidth = new double[TreeRolls];

	for (int i = 0; i < TreeRolls; i++) {

		randomx[i] = distribution(generator);
		randomz[i] = distribution(generator);
		randomHeghit[i] = HeightDistribution(generator);
		randomwidth[i] = HeightDistribution(generator);
		float height = Terrain.getHeightOfTerrian(-randomx[i], -randomz[i]);
		if (height > WATERLEVEL)
		{
			entity  tree = entity(TreeTexureModel, glm::fvec3(-randomx[i], height, -randomz[i]), 0, i*30, 0, 0.5, 0.5, 0.5);
			allEntity.push_back(tree);
		}
	}

	delete[] randomx;
	delete[] randomz;
	delete[] randomHeghit;
	delete[] randomwidth;
	

	RawModel playerRawModel = objLoader::LoadObj("./res/person.obj", loader);
	ModelTexture  playerTexture(loader.loadTexture("./res/playerTexture.png"));
	playerTexture.ReflectionScale = 0.0;
	playerTexture.ShineDamper = 0.0;
	textureModel PersonTexureModel(playerRawModel, playerTexture);

	Player player(PersonTexureModel, glm::fvec3(-50.0f, 0.0f,-50.0f), 0, 180, 0, 0.1);
	Camera camera(player);
	MousePicker Picker(camera,window,renderMaster.proj);


	glfwSetWindowUserPointer(window, &camera);

    WaterFrameBuffer waterframebuffer;
	WaterRenderer waterrnderer(loader, RenderMaster::proj, waterframebuffer);

	auto START = Time::now();
	float TimeOfDay = 0;
	int addoRsub = 1;///if it is 1 we add delta time so time goes up and when its -1 we subtract so time goes back again(we have 12h night and 12h morning )
	fsec deltaTime = Time::duration::zero();
	do {
		if (TimeOfDay>=12)
		{
			addoRsub = -1;
		}
		else if (TimeOfDay<=0)
		{
			addoRsub = 1;
		}
		
		renderMaster.processWorld(allTerrain, allEntity);

		checkInput(window, player,camera);
		waterframebuffer.bindRefractionFrameBuffer();
		renderMaster.Render(lights, camera, player, deltaTime.count(), TimeOfDay, glm::fvec4(0, -1, 0, WATERLEVEL));
		waterframebuffer.unbindCurrentFrameBuffer();

		waterframebuffer.bindReflectionFrameBuffer();
		camera.invertpitch();
		float distanceUnderwater = 2 * (camera.CameraLocation.y - WATERLEVEL);
		camera.CameraLocation.y -= distanceUnderwater;
		renderMaster.Render(lights, camera, player, deltaTime.count(), TimeOfDay, glm::fvec4(0, 1, 0, -WATERLEVEL));
		camera.invertpitch();
		camera.CameraLocation.y += distanceUnderwater;
		waterframebuffer.unbindCurrentFrameBuffer();

		
		renderMaster.Render(lights, camera,player,deltaTime.count(),TimeOfDay,glm::fvec4(0, 1, 0, 1000));
		waterrnderer.render(lights,waters, camera, deltaTime.count());
		guiRenderer.render(allGuis);

		auto END = Time::now();//getting delta time(how much time took to render frame)
		deltaTime =  END-START;
		TimeOfDay += addoRsub *deltaTime.count();
		START = END;
		
		player.Move(deltaTime.count(),Terrain);


		glfwGetCursorPos(window, &NewPoint.x, &NewPoint.y);
		deltaMosePos.x = NewPoint.x - oldPoint.x;
		deltaMosePos.y = NewPoint.y - oldPoint.y;
		oldPoint.x = NewPoint.x;
		oldPoint.y = NewPoint.y;

		
		camera.Move();
		Picker.update();
		
		renderMaster.CleanWorld();
		glfwSwapBuffers(window);
		glfwPollEvents();
		
	} 
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	renderMaster.CleanUp();
	waterframebuffer.cleanUp();
	glfwTerminate();

	return 0;
}

void checkInput(GLFWwindow* window,Player &player ,Camera& camera) {

	int state1 = glfwGetKey(window, GLFW_KEY_W);
	int state2 = glfwGetKey(window, GLFW_KEY_S);
	int state3 = glfwGetKey(window, GLFW_KEY_A);
	int state4 = glfwGetKey(window, GLFW_KEY_D);
	int state5 = glfwGetKey(window, GLFW_KEY_SPACE);
	int state6 = glfwGetKey(window, GLFW_MOUSE_BUTTON_MIDDLE);
	int state7 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
	int state8 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

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
	if (state7 == GLFW_PRESS)
	{
		camera.pitch += (float)deltaMosePos.y*0.02;
	}
	if (state8 == GLFW_PRESS)
	{
		camera.AngleAroundPlayer -= deltaMosePos.x*0.08;
	}

}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

	Camera *camera = reinterpret_cast<Camera*>(glfwGetWindowUserPointer(window));
	if (yoffset>0 )
	{
		camera->DistanceFromPlayer -= yoffset;
	}
	else if (yoffset < 0 ) {

		camera->DistanceFromPlayer -= yoffset;
	}
}


