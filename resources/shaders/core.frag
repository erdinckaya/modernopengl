#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 Color;
in float v_TextureIndex;

// texture sampler
uniform sampler2D textures[16];

//https://stackoverflow.com/questions/46871866/glsl-es1-0-and-passing-texture-unit-indices-to-the-fragment-shader
// Apply binary search
vec4 getTexture(float index, vec2 uv) {
    if (index < 0.5) {
       return texture(textures[0], uv);
    } else if (index < 1.5) {
        return texture(textures[1], uv);
    } else if (index < 2.5) {
        return texture(textures[2], uv);
    } else if (index < 3.5) {
        return texture(textures[3], uv);
    } else if (index < 4.5) {
        return texture(textures[4], uv);
    } else if (index < 5.5) {
        return texture(textures[5], uv);
    } else if (index < 6.5) {
        return texture(textures[6], uv);
    } else if (index < 7.5) {
        return texture(textures[7], uv);
    } else if (index < 8.5) {
        return texture(textures[8], uv);
    } else if (index < 9.5) {
        return texture(textures[9], uv);
    } else if (index < 10.5) {
        return texture(textures[10], uv);
    } else if (index < 11.5) {
        return texture(textures[11], uv);
    } else if (index < 12.5) {
        return texture(textures[12], uv);
    } else if (index < 13.5) {
        return texture(textures[13], uv);
    } else if (index < 14.5) {
        return texture(textures[14], uv);
    } else if (index < 15.5) {
        return texture(textures[15], uv);
    }


    return texture(textures[0], uv);
}

void main()
{

    FragColor = Color * getTexture(v_TextureIndex, TexCoord);
    if (FragColor.a < 0.1)
    discard;
}