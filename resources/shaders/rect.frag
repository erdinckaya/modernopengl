#version 330

out vec4 outColor;

in vec2 a_position;
in vec4 a_color;
in float a_borderThickness;
in float a_fill;



void main()
{
    float tickness = a_borderThickness;
    float xBorder = 0.5 - tickness;
    float yBorder = 0.5 - tickness;
    if (a_fill > 0)
    {
        outColor = vec4(a_color.x, a_color.y, a_color.z, a_color.w);
    }
    else
    {
        if(a_position.x > -xBorder && a_position.x < xBorder && a_position.y > -yBorder && a_position.y < yBorder)
        {
            discard;
        }
        else
        {
            outColor = vec4(a_color.x, a_color.y, a_color.z, a_color.w);
        }
    }
}