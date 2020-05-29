#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 Color;
in float v_TextureIndex;

// texture sampler
uniform sampler2D textures[16];

void main()
{
    int index = int(v_TextureIndex);
    float fIndex = float(index) + 0.5f;
    if (fIndex <= v_TextureIndex)
    {
        index = index + 1;
    }
    FragColor = Color * texture(textures[index], TexCoord);
    if (FragColor.a < 0.1)
    discard;
}