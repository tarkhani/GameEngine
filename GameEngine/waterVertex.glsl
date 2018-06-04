#version 400 core

layout(location = 0) in vec2 vertexPosition_modelspace;

out vec4 ClipSpace;
out vec2 TextureCoord;
out vec3 toCameraVector;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform float waterMoveOffSet;
uniform vec3 cameraLocation;

const float tilling = 50.0;

void main(void) {


    vec4 worldSpace = modelMatrix * vec4(vertexPosition_modelspace.x, 0.0, vertexPosition_modelspace.y, 1.0);
    ClipSpace = projectionMatrix * viewMatrix * worldSpace;
	toCameraVector = cameraLocation - worldSpace.xyz;
	TextureCoord = vec2(vertexPosition_modelspace.x/2.0 + 0.5,vertexPosition_modelspace.y/2.0 + 0.5) * tilling;
	gl_Position = ClipSpace;
 
}