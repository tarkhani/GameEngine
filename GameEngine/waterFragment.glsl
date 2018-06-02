#version 400 core

in vec4 ClipSpace;

uniform sampler2D reflactionTexture;
uniform sampler2D refractionTexture;
out vec4 out_Color;


void main(void) {
    vec2 ndc = (ClipSpace.xy / ClipSpace.w) / 2.0 + 0.5;
	vec2 refractionTexCoord=vec2(ndc.x,ndc.y);
	vec2 reflactionTexCoord=vec2(ndc.x,-ndc.y);
    vec4 reflTextureColor = texture2D(reflactionTexture,reflactionTexCoord);
    vec4 refraTextureColor = texture2D(refractionTexture,refractionTexCoord);
	out_Color = mix(reflTextureColor,refraTextureColor,0.5);

}