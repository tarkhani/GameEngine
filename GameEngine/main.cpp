#pragma once
#include<stdio.h>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include"Rendrer.h"
#include"Loader.h"
#include"StaticShader.h"
#include"ModelTexture.h"
#include"textureModel.h"
#include"entity.h"
#include"Camera.h"
#include<vector>
#include"objLoader.h"

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

	
	
	Loader loader;
	StaticShader staticsahder;
	Rendrer rendrer(staticsahder);
	

	vector <glm::vec3> vertices = {
		
	glm::vec3(-0.5f,-0.5f,-0.5f),
	glm::vec3(-0.5f,0.5f,-0.5f),
	glm::vec3(0.5f,0.5f,-0.5f),
	glm::vec3(0.5f,-0.5f,-0.5f),
	glm::vec3(-0.5f,-0.5f,0.5f),
	glm::vec3(-0.5f,0.5f,0.5f),
	glm::vec3(0.5f,0.5f,0.5f),
	glm::vec3(0.5f,-0.5f,0.5f),
	glm::vec3(-0.5f,0.5f,0.5f),
	glm::vec3(0.5f,0.5f,0.5f),
	glm::vec3(-0.5f,0.5f,-0.5f),
	glm::vec3(0.5f,0.5f,-0.5f),
	glm::vec3(-0.5f,-0.5f,0.5f),
	glm::vec3(0.5f,-0.5f,0.5f),
	glm::vec3(-0.5f,-0.5f,-0.5f),
	glm::vec3(0.5f,-0.5f,-0.5f),
	glm::vec3(-0.5f,-0.5f,0.5f),
	glm::vec3(-0.5f,+0.5f,0.5f),
	glm::vec3(-0.5f,-0.5f,-0.5f),
	glm::vec3(-0.5f,+0.5f,-0.5f),
	glm::vec3(0.5f,-0.5f,0.5f),
	glm::vec3(0.5f,+0.5f,0.5f),
	glm::vec3(0.5f,-0.5f,-0.5f),
	glm::vec3(0.5f,+0.5f,-0.5f),

	};
	ARRAY<glm::vec3> ARvertices;
	ARvertices.arrayPointer = &vertices[0];
	ARvertices.numberOfElements = vertices.size();
	ARvertices.size = vertices.size()*sizeof(glm::vec3);
	
	
	vector < unsigned short> index{ 2,1,0, 0,3,2, 6,5,4, 4,7,6,  9,8,10, 10,11,9,  13,12,14, 14,15,13,  19,17,16, 16,18,19,  23,21,20,  20,22,23, 1,324,20 };
	ARRAY<unsigned short> ARindex;
	ARindex.arrayPointer = &index[0];
	ARindex.numberOfElements = index.size();
	ARindex.size = index.size()*sizeof(int);
	
vector<glm::vec2> uv= {
	glm::vec2(0.0f,1.0f),
	glm::vec2(0.0f,0.0f),
	glm::vec2(1.0f,0.0f),
	glm::vec2(1.0f,1.0f),
	glm::vec2(0.0f,1.0f),
	glm::vec2(0.0f,0.0f),
	glm::vec2(1.0f,0.0f),
	glm::vec2(1.0f,1.0f),
	glm::vec2(0.0f,0.0f),
	glm::vec2(1.0f,0.0f),
	glm::vec2(0.0f,1.0f),
	glm::vec2(1.0f,1.0f),
	glm::vec2(0.0f,0.0f),
	glm::vec2(1.0f,0.0f),
	glm::vec2(0.0f,1.0f),
	glm::vec2(1.0f,1.0f),
	glm::vec2(0.0f,1.0f),
	glm::vec2(0.0f,0.0f),
	glm::vec2(1.0f,1.0f),
	glm::vec2(1.0f,0.0f),
	glm::vec2(0.0f,1.0f),
	glm::vec2(0.0f,0.0f),
	glm::vec2(1.0f,1.0f),
	glm::vec2(1.0f,0.0f),
	};

	ARRAY<glm::vec2> ARuv;
	ARuv.arrayPointer = &uv[0];
	ARuv.numberOfElements = uv.size();
	ARuv.size = uv.size()*sizeof(glm::vec2);

	RawModel model = loader.loadToVAO(ARvertices, ARuv, ARindex);
	RawModel model2 = objLoader::LoadObj("stall1.obj", loader);

	ModelTexture  Modeltexture(loader.loadTexture("stallTexture.png"));
	textureModel TexureModel(model2, Modeltexture);
	entity entity1= entity(TexureModel, glm::fvec3(0.0f, 0.0f, -10.0f), 0, 180, 0, 1);

	

	do {

		//entity1.increaseRotation(1, 0, 0.0);
		rendrer.prepare();
		
		staticsahder.start();
		staticsahder.loadView(camera);
		rendrer.render(entity1, staticsahder);
		staticsahder.stopProgeram();
		
	
		glfwSwapBuffers(window);
		glfwPollEvents();
		
	} 
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);


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
