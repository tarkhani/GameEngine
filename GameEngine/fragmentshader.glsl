#version 430

out vec4 Fcolor;

in vec2 uv;
in vec3 SurfaceNormal;
in vec3 toLightVector[4];
in vec3 cameraPosition;
in float Visibility;


uniform sampler2D Texture;
uniform vec3 lightColour[4];
uniform vec3  attenuation[4];
uniform float ShineDamper;
uniform float ReflectionScale;
uniform vec3 skyColor;
const int numberOflightLv=3;

void main()
{

vec3 unitNormal=normalize(SurfaceNormal);
vec3 unitcameraPosition=normalize(cameraPosition);
vec3 totalDiffuse=vec3(0.0);
vec3 totalSpecular=vec3(0.0);

for(int i=0; i<4; i++)
{
float distanceFromLight=length(toLightVector[i]);
float attfactor= (attenuation[i].x)+(attenuation[i].y*distanceFromLight)+ (attenuation[i].z*(distanceFromLight*distanceFromLight));
vec3 unitToLightVector=normalize(toLightVector[i]);
float nDot1=dot(unitNormal,unitToLightVector);
float brightness=max(nDot1,0.0);
float lightLv=floor(brightness*numberOflightLv);
brightness=lightLv/numberOflightLv;
totalDiffuse = totalDiffuse + (brightness*lightColour[i]/attfactor);

vec3 unitLightDirection=-unitToLightVector;
vec3 Reflactlight=reflect(unitLightDirection, unitNormal);
vec3 unitReflactlight=normalize(Reflactlight);
float specularFactor=dot(unitcameraPosition,unitReflactlight);
specularFactor=max(specularFactor,0.1);
float DumpedFactor=pow(specularFactor,ShineDamper);
totalSpecular=totalSpecular+(ReflectionScale*DumpedFactor*lightColour[i]/attfactor);

}
totalDiffuse=max(totalDiffuse,0.0);
vec4 TextureColor=texture2D(Texture,uv);
if(TextureColor.a<0.5){
discard;
}
Fcolor = vec4(totalDiffuse,1.0)*TextureColor+vec4(totalSpecular,1.0);
Fcolor = mix(vec4(skyColor,1.0),Fcolor,Visibility);

};