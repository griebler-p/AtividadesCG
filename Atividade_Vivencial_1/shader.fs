#version 330 core
in vec4 finalColor;
out vec4 FragColor;
//uniform vec3 cor; // Recebe do programa a cor que vai usar aqui
void main()
{
    //FragColor = vec4(cor, 1.0);
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    FragColor = finalColor;

}
