#version 330 core
layout (location = 0) in vec3 aPos; // Um vetor para as coordenadas
layout (location = 1) in vec3 aColor; // Um vetor para as cores
//uniform mat4 transform; // Recebe do OpenGl a matriz de transformação

out vec3 Color;

void main()
{
    //gl_Position = transform * vec4(aPos, 1.0);
    gl_Position = vec4(aPos, 1.0); // Posições fixas já determinadas no VAO
    Color = aColor;
}
