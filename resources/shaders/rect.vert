#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 translation;
layout (location = 2) in vec3 scale;
layout (location = 3) in vec3 rotation;
layout (location = 4) in vec4 color;
layout (location = 5) in float borderThickness;
layout (location = 6) in float fill;


out vec2 a_position;
out vec4 a_color;
out float a_borderThickness;
out float a_fill;


uniform mat4 pv;



mat4 translate(float x, float y, float z){
    return mat4(
    vec4(1.0, 0.0, 0.0, 0.0),
    vec4(0.0, 1.0, 0.0, 0.0),
    vec4(0.0, 0.0, 1.0, 0.0),
    vec4(x,   y,   z,   1.0)
    );
}

mat4 scaleMat(float x, float y, float z){
    return mat4(
    vec4(x,   0.0, 0.0, 0.0),
    vec4(0.0, y,   0.0, 0.0),
    vec4(0.0, 0.0, z,   0.0),
    vec4(0.0, 0.0, 0.0, 1.0)
    );
}



mat4 rotateX(float phi){
    return mat4(
    vec4(1.,0.,0.,0),
    vec4(0.,cos(phi),-sin(phi),0.),
    vec4(0.,sin(phi),cos(phi),0.),
    vec4(0.,0.,0.,1.));
}

mat4 rotateY(float theta){
    return mat4(
    vec4(cos(theta),0.,-sin(theta),0),
    vec4(0.,1.,0.,0.),
    vec4(sin(theta),0.,cos(theta),0.),
    vec4(0.,0.,0.,1.));
}

mat4 rotateZ(float psi){
    return mat4(
    vec4(cos(psi),-sin(psi),0.,0),
    vec4(sin(psi),cos(psi),0.,0.),
    vec4(0.,0.,1.,0.),
    vec4(0.,0.,0.,1.));
}


void main()
{

    mat4 model = translate(translation.x, translation.y, translation.z);
    model = model * rotateX(radians(rotation.x));
    model = model * rotateY(radians(rotation.y));
    model = model * rotateY(radians(rotation.z));
    model = model * scaleMat(scale.x, scale.y, scale.z);

    gl_Position = pv * model * vec4(position.x, position.y, 0.0, 1.0);

    a_position = position;
    a_color = color;
    a_borderThickness = borderThickness;
    a_fill = fill;
}