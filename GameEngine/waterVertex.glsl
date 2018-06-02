#version 400 core

layout(location = 0) in vec2 vertexPosition_modelspace;

out vec4 ClipSpace;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;


void main(void) {

    ClipSpace = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition_modelspace.x, 0.0, vertexPosition_modelspace.y, 1.0);
	gl_Position = ClipSpace;
 
}