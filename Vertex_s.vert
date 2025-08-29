#version 330 core
layout (location = 0) in vec3 aPos;
out vec2 VertPos;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    VertPos = vec2(aPos.x*2.0, aPos.y*2.0);\n"
}
