#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec4 aColor;
layout (location = 3) in float aTextureIndex;

out vec2 TexCoord;
out vec4 Color;
out float v_TextureIndex;

uniform mat4 pvm;


void main()
{
	gl_Position = pvm * vec4(aPos, 1.0f);
	v_TextureIndex = aTextureIndex;
	TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
	Color = aColor;
}