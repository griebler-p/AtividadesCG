#version 330 core
layout (location = 0) in vec3 aPos; // Um vetor para as coordenadas
layout (location = 1) in vec3 aColor; // Outro para as cores
layout (location = 2) in vec2 aTexCoord; // outro para as texturas
uniform mat4 transform; // Recebe do OpenGl a matriz de transformação
uniform mat4 projection; // Para poder computar a projeção em perspectiva

out vec3 ourColor; // Exporta a cor
out vec2 TexCoord; // e as texturas para o fragment shader

void main()
{
    //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    //gl_Position = transform * vec4(aPos, 1.0);

    gl_Position = projection * transform * vec4(aPos, 1.0);
    //finalColor = vec4(aColor, 1.0); // Manda a cor para fragment shader
    //texCoord = vec2(tex_coord.x, tex_coord.y);
    TexCoord = aTexCoord;
    ourColor = aColor;
}
