#version 330 core
out vec4 FragColor;

//in vec3 vsColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos; // position vector of the camera object
uniform vec3 objectColor;
uniform vec3 lightColor0;
uniform vec3 lightPos0;
uniform vec3 lightColor1;
uniform vec3 lightPos1;
uniform vec3 lightColor2;
uniform vec3 lightPos2;

void main()
{
    //FragColor = finalColor;
    //FragColor = vec4(vec3(1.0, 1.0, 1.0) * vsColor, 1.0); // Esfera normal - Funciona !
    //FragColor = vec4(vec3(0.0, 0.5, 1.0) * vsColor, 1.0); // Esfera verde com preto -- Funciona !
    //FragColor = vec4(lightColor * objectColor, 1.0);

    // Luz ambiente:
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor0;
    // Luz especular:
    float specularStrength = 0.5;
     // Luz difusa:
    vec3 norm = normalize(Normal);
    // Luz especular:
    vec3 viewDir = normalize(viewPos - FragPos);

    // Fonte de luz 0:
    // Luz difusa0:
    vec3 lightDir0 = normalize(lightPos0 - FragPos);
    float diff0 = max(dot(norm, lightDir0), 0.0);
    vec3 diffuse0 = diff0 * lightColor0;
    // Luz especular0:
    vec3 reflectDir0 = reflect(-lightDir0, norm);
    float spec0 = pow(max(dot(viewDir, reflectDir0), 0.0), 32);
    vec3 specular0 = specularStrength * spec0 * lightColor0;

    // Fonte de luz 0:
    // Luz difusa0:
    vec3 lightDir1 = normalize(lightPos1 - FragPos);
    float diff1 = max(dot(norm, lightDir1), 0.0);
    vec3 diffuse1 = diff1 * lightColor1;
    // Luz especular0:
    vec3 reflectDir1 = reflect(-lightDir1, norm);
    float spec1 = pow(max(dot(viewDir, reflectDir1), 0.0), 32);
    vec3 specular1 = specularStrength * spec1 * lightColor0;

    // Fonte de luz 2:
    // Luz difusa2:
    vec3 lightDir2 = normalize(lightPos2 - FragPos);
    float diff2 = max(dot(norm, lightDir2), 0.0);
    vec3 diffuse2 = diff2 * lightColor2;
    // Luz especular0:
    vec3 reflectDir2 = reflect(-lightDir2, norm);
    float spec2 = pow(max(dot(viewDir, reflectDir2), 0.0), 32);
    vec3 specular2 = specularStrength * spec2 * lightColor0;

    // Soma das luzes:
    //vec3 result0 = (ambient + diffuse0 + specular0) * objectColor;
    vec3 result0 = (diffuse0 + specular0);
    vec3 result1 = (diffuse1 + specular1);
    vec3 result2 = (diffuse2 + specular2);
    vec3 result = (ambient + result0 + result1 + result2) * objectColor;
    FragColor = vec4(result, 1.0);

}
