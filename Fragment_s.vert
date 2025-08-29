#version 330 core
out vec4 FragColor;
in vec2 VertPos;

vec2 iterate(vec2 vect, vec2 c);

void main()
{
    vec2 mainvec = vec2(0.0, 0.0);
    float iteration = 0;
    while (length(mainvec) < 10.0 && iteration < 100)
    {
        iteration += 1.0;
        mainvec = iterate(mainvec, VertPos);
    }

    if (iteration > 19)
    {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else
    {
        FragColor = vec4(1.0 - iteration * 0.04, 1.0 - iteration * 0.04, 1.0, 1.0);
    }
}
vec2 iterate(vec2 vect, vec2 c)
{
    float real = vect.x;
    vect.x = vect.x * vect.x - vect.y * vect.y;
    vect.y = 2.0 * real * vect.y;
    vect = vect + c;
    return vect;
}
