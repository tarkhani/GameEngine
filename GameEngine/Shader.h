#pragma once
#include<iostream>
#include<fstream>
#include<gl\glew.h>
#include"glm\glm.hpp"
class Shader
{

	
public:

	 GLuint progeramID;
	 GLuint vertaxshaderID;
	 GLuint fragmentshaderID;

	 void start();
	 void stopProgeram();
	 void cleanUp();
     bool CheckObjectCompile(GLuint &ObjectID, PFNGLGETSHADERIVPROC ObjectProperty, PFNGLGETSHADERINFOLOGPROC Objectinfo, GLenum status);
	 void shaderProgeram(char* vertaxfileLoaction,char* fragmentfilelocation);
	 std::string ReadShader(char * fileAddres);
	 Shader();
	 ~Shader();

protected:

     virtual void getAllUniformLocations()=0;

	 int GetUniformlocation(char* location);
	 void loadFloatUni(float number, int location);
	 void loadIntUni(int number, int location);
	 void loadvectorUni(glm::fvec3 vector, int location);
	 void loadBoolUni(bool Bool, int location);
	 void loadMatrixUni(glm::fmat4 matrix, int location);


};

