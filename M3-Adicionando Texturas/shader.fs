#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;
//uniform vec3 cor; // Recebe do programa a cor que vai usar aqui

// pixels da textura
uniform sampler2D tex_buffer; // Recebe do programa a textura que vai usar aqui

void main()
{
    //FragColor = vec4(cor, 1.0);
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    //color = finalColor;
    //FragColor = texture(tex_buffer, TexCoord); // Só texturas
    FragColor = texture(tex_buffer, TexCoord) * vec4(ourColor, 1.0); // Inclui textura e cores


}
