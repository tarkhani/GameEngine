#include "Shader.h"




void Shader::shaderProgeram(char * vertaxfileLoaction, char * fragmentfilelocation)
{
	vertaxshaderID = glCreateShader(GL_VERTEX_SHADER);
	fragmentshaderID = glCreateShader(GL_FRAGMENT_SHADER);
	const char * adopter[1];
	std::string temp = ReadShader(vertaxfileLoaction);
	adopter[0] = temp.c_str();
	glShaderSource(vertaxshaderID, 1, adopter, 0);
	temp = ReadShader(fragmentfilelocation);
	adopter[0] = temp.c_str();
	glShaderSource(fragmentshaderID, 1, adopter, 0);
	glCompileShader(vertaxshaderID);
	glCompileShader(fragmentshaderID);

	CheckObjectCompile(vertaxshaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
	CheckObjectCompile(fragmentshaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);

	progeramID = glCreateProgram();
	glAttachShader(progeramID, vertaxshaderID);
	glAttachShader(progeramID, fragmentshaderID);
	CheckObjectCompile(progeramID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
	if (CheckObjectCompile(progeramID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS))
	{
		return;
	}

	glLinkProgram(progeramID);
	glUseProgram(progeramID);
}

std::string Shader::ReadShader(char * fileAddres)
{
	std::ifstream File(fileAddres);
	if (!File)
	{
		std::cout << "no such file" << std::endl;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(File),
		std::istreambuf_iterator<char>()

	);
	File.close();
}

void Shader::start()
{
	glUseProgram(progeramID);
}

void Shader::stopProgeram()
{
	glUseProgram(0);
}

void Shader::cleanUp()
{
	stopProgeram();
	glDetachShader(progeramID, vertaxshaderID);
	glDetachShader(progeramID, fragmentshaderID);
	glDeleteShader(vertaxshaderID);
    glDeleteShader(fragmentshaderID);
	glDeleteProgram(progeramID);
}

bool Shader::CheckObjectCompile(GLuint & ObjectID, PFNGLGETSHADERIVPROC ObjectProperty, PFNGLGETSHADERINFOLOGPROC Objectinfo, GLenum status)
{
	GLint VertaxCompileStatus;
	ObjectProperty(ObjectID, status, &VertaxCompileStatus);
	if (VertaxCompileStatus != GL_TRUE)
	{
		GLint logLength;
		ObjectProperty(ObjectID, GL_INFO_LOG_LENGTH, &logLength);
		char *log = new GLchar[logLength];
		GLsizei loglen;
		Objectinfo(ObjectID, logLength, &loglen, log);
		std::cout << log << std::endl;
		delete log;
		return false;


	}
	else true;
}


Shader::Shader()
{
}


Shader::~Shader()
{

}

int Shader::GetUniformlocation(char * location)
{
	return glGetUniformLocation(progeramID, location);
}

void Shader::loadFloatUni(float number, int location)
{
	glUniform1f(location, number);
}

void Shader::loadIntUni(int number, int location)
{
	glUniform1i(location, number);
}

void Shader::loadvectorUni(glm::fvec3 vector, int location)
{
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::loadvectorUni(glm::fvec2 vector, int location)
{
	glUniform2f(location, vector.x, vector.y);
}


void Shader::loadBoolUni(bool Bool, int location)
{
	float toload = 0;
	if (Bool) {
		toload = 1;
	}
	glUniform1f(location, toload);
}

void Shader::loadMatrixUni(glm::fmat4 matrix, int location)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}
