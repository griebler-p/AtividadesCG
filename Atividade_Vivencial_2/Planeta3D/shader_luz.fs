#version 330 core
uniform vec3 corDaLuz;

out vec4 FragColor;

void main()
{
    FragColor = vec4(corDaLuz, 1.0);
}
