#version 430

out vec4 Fcolor;

in vec2 uv;
in vec3 SurfaceNormal;
in vec3 toLightVector;
in vec3 cameraPosition;
in float Visibility;

uniform sampler2D BackGroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D BlendMap;

uniform vec3 lightColour;
uniform float ShineDamper;
uniform float ReflectionScale;
uniform vec3 skyColor;

void main()
{
vec4 BlendMapColor=texture2D(BlendMap,uv);
float backTextureAmount=1-(BlendMapColor.r+BlendMapColor.g+BlendMapColor.b);
vec2 TiledCoords=uv*30;
vec4 BackGroundTextureColor = texture2D(BackGroundTexture,TiledCoords)*backTextureAmount;
vec4 rTextureColor = texture2D(rTexture,TiledCoords)*BlendMapColor.r;
vec4 bTextureColor = texture2D(bTexture,TiledCoords)*BlendMapColor.g;
vec4 gTextureColor = texture2D(gTexture,TiledCoords)*BlendMapColor.b;

vec4 mixColor = BackGroundTextureColor + rTextureColor+gTextureColor+bTextureColor;


vec3 unitNormal=normalize(SurfaceNormal);
vec3 unitToLightVector=normalize(toLightVector);
float nDot1=dot(unitNormal,unitToLightVector);
float brightness=max(nDot1,0.5);
vec3 diffuse=brightness*lightColour;


vec3 unitLightDirection=-unitToLightVector;
vec3 Reflactlight=reflect(unitLightDirection, unitNormal);
vec3 unitReflactlight=normalize(Reflactlight);
vec3 unitcameraPosition=normalize(cameraPosition);
  
float specularFactor=dot(unitcameraPosition,unitReflactlight);
specularFactor=max(specularFactor,0.3);
float DumpedFactor=pow(specularFactor,ShineDamper);
vec3 FinalSpecular=ReflectionScale*DumpedFactor*lightColour;


Fcolor = mixColor;
Fcolor = mix(vec4(skyColor,1.0),Fcolor,Visibility);

};
