#version 330 core
layout (location = 0) in vec3 aPos; // Um vetor para as coordenadas
//layout (location = 1) in vec3 color; // Outro para as cores
layout (location = 1) in vec3 aNormal; // Vetor da Normal

uniform mat4 model; // recebe as transformações dos vértices
uniform mat4 view; // recebe as transformações que simulam uma câmera
uniform mat4 projection; // Para poder computar a projeção em perspectiva

//out vec3 vsColor;
out vec3 Normal;
out vec3 FragPos; // Além de mandar a Normal para fragment shader, precisa enviar tb a posição do fragmento
//out vec3 ViewPos; // Manda a posição da câmera

void main()
{
    //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    //gl_Position = transform * vec4(aPos, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    //vsColor = color; // Manda a cor para fragment shader
    Normal = aNormal; // Manda a normal para o fragment shader
    FragPos = vec3(model * vec4(aPos, 1.0));
    //ViewPos = view; // Errado !
}
