#version 400 core

in vec4 ClipSpace;
in vec2 TextureCoord;
in vec3 toCameraVector;

uniform sampler2D reflactionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D DuDv;
uniform sampler2D Normal;
uniform float waterMoveOffSet;

out vec4 out_Color;
const float wavePower = 0.012;

void main(void) {

    vec2 ndc = (ClipSpace.xy / ClipSpace.w) / 2.0 + 0.5;
	vec2 dudvTextureColor = (texture2D(DuDv,vec2(TextureCoord.x + waterMoveOffSet,TextureCoord.y)).rg * 2.0 - 1.0) *wavePower;
	vec2 dudvTextureColor2 = (texture2D(DuDv,vec2(-TextureCoord.x + waterMoveOffSet,TextureCoord.y + waterMoveOffSet )).rg * 2.0 - 1.0) *wavePower;
	vec2 total_dudvTextureColor=dudvTextureColor + dudvTextureColor2;
	vec2 refractionTexCoord=vec2(ndc.x,ndc.y);
	vec2 reflactionTexCoord=vec2(ndc.x,-ndc.y);

	refractionTexCoord += total_dudvTextureColor;
	refractionTexCoord=clamp(refractionTexCoord,0.001,0.999);

	reflactionTexCoord += total_dudvTextureColor;
	reflactionTexCoord.x=clamp(reflactionTexCoord.x,0.001,0.999);
	reflactionTexCoord.y=clamp(reflactionTexCoord.y,-0.999,-0.001);

    vec4 reflTextureColor = texture2D(reflactionTexture,reflactionTexCoord);
    vec4 refraTextureColor = texture2D(refractionTexture,refractionTexCoord);

	vec3 NormalizeToCameraVector = normalize(toCameraVector);
	float nDot1=dot(vec3(0.0,1.0,0.0),NormalizeToCameraVector);
	out_Color = mix(reflTextureColor,refraTextureColor,nDot1);
	out_Color = mix(out_Color , vec4(0.2,0.24,0.87,0.0),0.2);
	

}