#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 uvCoord;
layout(location = 2) in vec3 normal;

out vec2 uv;
out vec3 SurfaceNormal;
out vec3 toLightVector[4];
out vec3 cameraPosition;
out float Visibility;

uniform float numberOfRows;
uniform vec2 xyoffset;
uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
uniform vec3 lightPosition[4];
uniform float FakeLightning;
uniform vec4 plane;

const float density=0.01;
const float FogGradient=1.5;



void main(){

	vec4 worldLocation = transform*vec4(vertexPosition_modelspace,1.0);
	gl_ClipDistance[0]=dot(worldLocation,plane);
	vec4 locationFromCamera=view*worldLocation;
	float Distance=length(locationFromCamera.xyz);
	Visibility=exp(-pow((Distance*density),FogGradient));
	Visibility=clamp(Visibility,0.0,1.0);

	gl_Position =projection*locationFromCamera;
	uv=(uvCoord/numberOfRows)+xyoffset;
	vec3 Normal=normal;
	if(FakeLightning>0.0){
	
	Normal=vec3(0.0,1.0,0.0);
	}
	SurfaceNormal=(transform * vec4(Normal,0.0)).xyz;
	cameraPosition= (inverse(view)*vec4(0.0,0.0,0.0,1.0)).xyz-worldLocation.xyz;

	for(int i=0; i<4; i++)
	{
	toLightVector[i]=lightPosition[i]-(worldLocation.xyz);
	}
}
