#version 400 core

in vec4 ClipSpace;
in vec2 TextureCoord;
in vec3 toCameraVector;
in vec3 toLightVector[4];

uniform sampler2D reflactionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D DuDv;
uniform sampler2D NormalMap;
uniform float waterMoveOffSet;
uniform vec3 LightColor;
uniform vec3 lightColour[4];
uniform vec3  attenuation[4];

out vec4 out_Color;
const float wavePower = 0.012;
const float ShineDamper = 2.0;
const float ReflectionScale = 0.2;

void main(void) {

    vec2 ndc = (ClipSpace.xy / ClipSpace.w) / 2.0 + 0.5;
	vec2 dudvTextureColor = (texture(DuDv,vec2(TextureCoord.x + waterMoveOffSet,TextureCoord.y)).rg * 2.0 - 1.0) *wavePower;
	vec2 dudvTextureColor2 = (texture(DuDv,vec2(-TextureCoord.x + waterMoveOffSet,TextureCoord.y + waterMoveOffSet )).rg * 2.0 - 1.0) *wavePower;
	vec2 totalDistortion = dudvTextureColor + dudvTextureColor2;
	
	vec2 refractionTexCoord=vec2(ndc.x,ndc.y);
	vec2 reflactionTexCoord=vec2(ndc.x,-ndc.y);

	refractionTexCoord += totalDistortion;
	refractionTexCoord=clamp(refractionTexCoord,0.001,0.999);

	reflactionTexCoord += totalDistortion;
	reflactionTexCoord.x=clamp(reflactionTexCoord.x,0.001,0.999);
	reflactionTexCoord.y=clamp(reflactionTexCoord.y,-0.999,-0.001);

    vec4 reflTextureColor = texture(reflactionTexture,reflactionTexCoord);
    vec4 refraTextureColor = texture(refractionTexture,refractionTexCoord);

    vec4 normal = texture(NormalMap,totalDistortion);
	vec3 normalVector=vec3(normal.r * 2.0 - 1.0 ,normal.b,normal.g* 2.0 - 1.0);
	vec3 unitNormal = normalize(normalVector);
	vec3 NormalizeToCameraVector = normalize(toCameraVector);

	vec3 totalSpecular=vec3(0.0);
	for(int i=0; i<4; i++)
    {
     float distanceFromLight=length(toLightVector[i]);
     float attfactor= (attenuation[i].x)+(attenuation[i].y*distanceFromLight)+ (attenuation[i].z*(distanceFromLight*distanceFromLight));
     vec3 unitToLightVector=normalize(toLightVector[i]);

     vec3 unitLightDirection=-unitToLightVector;
     vec3 Reflactlight=reflect(unitLightDirection, unitNormal);
     vec3 unitReflactlight=normalize(Reflactlight);
     float specularFactor=dot( NormalizeToCameraVector,unitReflactlight);
     specularFactor=max(specularFactor,0.01);
     float DumpedFactor=pow(specularFactor,ShineDamper);
     totalSpecular=totalSpecular+(DumpedFactor*ReflectionScale*lightColour[i]/attfactor);
    }

	float nDot1=dot(vec3(0.0,1.0,0.0),NormalizeToCameraVector);
	out_Color = mix(reflTextureColor/2,refraTextureColor/3,nDot1+0.2)+vec4(totalSpecular,1.0);
	
	

}