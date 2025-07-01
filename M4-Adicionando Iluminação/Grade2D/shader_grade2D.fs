#version 330 core
in vec3 Color;

out vec4 FragColor;
//uniform vec3 cor; // Recebe do programa a cor que vai usar aqui

void main()
{
    //FragColor = vec4(cor, 1.0);
    FragColor = vec4(Color, 1.0); // Cores já determinadas no VAO
}
