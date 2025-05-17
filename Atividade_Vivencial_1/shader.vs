#version 330 core
layout (location = 0) in vec3 aPos; // Um vetor para as coordenadas
layout (location = 1) in vec3 color; // Outro para as cores
uniform mat4 transform; // Recebe do OpenGl a matriz de transformação
uniform mat3 transfCor; // Recebe do OpenGl uma transformação para cor
out vec4 finalColor;
void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    //finalColor = vec4(color, 1.0); // Manda a cor para fragment shader
    finalColor = vec4(color*transfCor, 1.0); // Manda a cor para fragment shader
}
