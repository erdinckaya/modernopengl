#version 330

out vec4 outColor;

in vec2 a_position;
in vec4 a_color;
in float a_borderThickness;
in float a_fill;



void main()
{
    float maxRadius = 0.5;
    float minRadius = maxRadius - a_borderThickness;
    float min = minRadius * minRadius;
    float max = maxRadius * maxRadius;
    float distSq = a_position.x * a_position.x + a_position.y * a_position.y;

    bool canPaint = false;
    if (a_fill > 0)
    {
        if (distSq <= max)
        {
            canPaint = true;
        }
        else
        {
            discard;
        }
    }
    else
    {
        if (distSq <= max && distSq >= min)
        {
            canPaint = true;
        }
        else
        {
            discard;
        }
    }

    if (canPaint)
    {
        outColor = a_color;
    }
    else
    {
        discard;
    }
}