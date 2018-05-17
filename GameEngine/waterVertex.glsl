#version 400 core

layout(location = 0) in vec2 vertexPosition_modelspace;

out vec2 textureCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;


void main(void) {

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition_modelspace.x, 0.0, vertexPosition_modelspace.y, 1.0);
	textureCoords = vec2(vertexPosition_modelspace.x/2.0 + 0.5, vertexPosition_modelspace.y/2.0 + 0.5);
 
}