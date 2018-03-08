#version 330 core


layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 uvCoord;

out vec2 uv;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main(){

    vec4 v = vec4(vertexPosition_modelspace,1.0);
	gl_Position =projection*view*transform*v;
	uv=uvCoord;

}

