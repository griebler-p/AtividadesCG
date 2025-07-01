/*
 *  Codificado por Rossana Baptista Queiroz
 *  para as disciplinas de Processamento Gráfico/Computação Gráfica - Unisinos
 *  Versão inicial: 07/04/2017
 *  Última atualização: 14/03/2025
 *
 *  Este arquivo contém a função `loadSimpleOBJ`, responsável por carregar arquivos
 *  no formato Wavefront .OBJ e armazenar seus vértices em um VAO para renderização
 *  com OpenGL.
 *
 *  Forma de uso (carregamento de um .obj)
 *  -----------------
 *  ...
 *  int nVertices;
 *  GLuint objVAO = loadSimpleOBJ("../Modelos3D/Cube.obj", nVertices);
 *  ...
 *
 *  Chamada de desenho (Polígono Preenchido - GL_TRIANGLES), no loop do programa:
 *  ----------------------------------------------------------
 *  ...
 *  glBindVertexArray(objVAO);
 *  glDrawArrays(GL_TRIANGLES, 0, nVertices);
 *
 */

 // Cabeçalhos necessários (para esta função), acrescentar ao seu código
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

// GLAD
//#include <glad/glad.h> // Arquivo ou diretório inexistente
#include "glad/glad.h"// É necessário que a inclusão do glad.h seja feita antes da inclusão do glfw3 -- aliás o glad.h precisa ser incluído ANTES de qualquer outro arquivo cabeçalho que use os arquivos cabeçalhos do OpenGL (tipo GL/gl.h)

// GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Mesh
{
    GLuint VAO;

};

//int loadSimpleOBJ(string filePATH, int &nVertices)
int loadSimpleOBJModificadoParaAdicionarTexturasNoVAO(string filePATH, int &nVertices, glm::vec3 color)
 {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<GLfloat> vBuffer;
    //glm::vec3 color = glm::vec3(1.0, 0.0, 0.0); // --> foi para o construtor !

    std::ifstream arqEntrada(filePATH.c_str());
    if (!arqEntrada.is_open())
	{
        std::cerr << "Erro ao tentar ler o arquivo " << filePATH << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(arqEntrada, line))
	{
        std::istringstream ssline(line);
        std::string word;
        ssline >> word;

        if (word == "v")
		{
            glm::vec3 vertice;
            ssline >> vertice.x >> vertice.y >> vertice.z;
            vertices.push_back(vertice);
        }
        else if (word == "vt")
		{
            glm::vec2 vt;
            ssline >> vt.s >> vt.t;
            texCoords.push_back(vt);
        }
        else if (word == "vn")
		{
            glm::vec3 normal;
            ssline >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        }
        else if (word == "f")
		 {
            while (ssline >> word)
			{
                int vi = 0, ti = 0, ni = 0;
                std::istringstream ss(word);
                std::string index;

                if (std::getline(ss, index, '/')) vi = !index.empty() ? std::stoi(index) - 1 : 0;
                if (std::getline(ss, index, '/')) ti = !index.empty() ? std::stoi(index) - 1 : 0;
                if (std::getline(ss, index)) ni = !index.empty() ? std::stoi(index) - 1 : 0;

                vBuffer.push_back(vertices[vi].x);
                vBuffer.push_back(vertices[vi].y);
                vBuffer.push_back(vertices[vi].z);
                vBuffer.push_back(color.r);
                vBuffer.push_back(color.g);
                vBuffer.push_back(color.b);
                // Alterado para adicionar normais e texturas no VAO:
                vBuffer.push_back(normals[vi].x);
                vBuffer.push_back(normals[vi].y);
                vBuffer.push_back(normals[vi].z);
                vBuffer.push_back(texCoords[vi].s);
                vBuffer.push_back(texCoords[vi].t);

            }
        }
    }

    arqEntrada.close();

    std::cout << "Gerando o buffer de geometria..." << std::endl;
    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vBuffer.size() * sizeof(GLfloat), vBuffer.data(), GL_STATIC_DRAW);
    //std::vector::data()
    // Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
    // Because elements in the vector are guaranteed to be stored in contiguous storage locations in the same order as represented by the vector, the pointer retrieved can be offset to access any element in the array.

    cout << "vBuffer.size() =" << vBuffer.size() << endl; //Debug
    cout << "vBuffer.data() =" << vBuffer.data() << endl; //Debug
    cout << "sizeof(GLfloat) =" << sizeof(GLfloat) << endl; // Debug
    cout << "Endereço = " << "valor" << endl;
    for (int i=0; i<vBuffer.size(); i++) {
        cout << vBuffer.data()+i << " =" << *(vBuffer.data()+i)  << endl; // Debug
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Normais:
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);

    // Texturas:
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(9 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

	nVertices = vBuffer.size() / 11;  // x, y, z, r, g, b, s, t, x, y, z (valores atualmente armazenados por vértice)

    return VAO;
}
