
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// GLAD
//#include <glad/glad.h>// Arquivo ou diretório inexistente
#include "glad/glad.h"// É necessário que a inclusão do glad.h seja feita antes da inclusão do glfw3 -- aliás o glad.h precisa ser incluído ANTES de qualquer outro arquivo cabeçalho que use os arquivos cabeçalhos do OpenGL (tipo GL/gl.h)

// GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*struct Mesh
{
    GLuint VAO;

};*/

//int loadSimpleOBJ(string filePATH, int &nVertices);
//int loadSimpleOBJ(string filePATH, int &nVertices, glm::vec3 color);
int loadSimpleOBJModificadoParaAdicionarTexturasNoVAO(string filePATH, int &nVertices, glm::vec3 color);
