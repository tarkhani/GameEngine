#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 uvCoord;
layout(location = 2) in vec3 normal;

out vec2 uv;
out vec3 SurfaceNormal;
out vec3 toLightVector;
out vec3 cameraPosition;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
uniform vec3 lightPosition;

void main(){

	vec4 worldLocation = transform*vec4(vertexPosition_modelspace,1.0);
	gl_Position =projection*view*worldLocation;
	uv=uvCoord;
	SurfaceNormal=(transform * vec4(normal,0.0)).xyz;
	cameraPosition= (inverse(view)*vec4(0.0,0.0,0.0,1.0)).xyz-worldLocation.xyz;
	toLightVector=lightPosition-(worldLocation.xyz);

}

