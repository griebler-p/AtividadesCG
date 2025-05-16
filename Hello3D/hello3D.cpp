// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Computação Gráfica
// Módulo 1
// Tarefa: Hello3D
// Data: 07/03/2025
// Professor: Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior
// Registros Acadêmicos: 1930669

// Versão Astrolabium:
// Pasta: cd '/mnt/astrolabium/home/griebler/Rsync/Unisinos/Atividade_Academica/2025-1/Computação Gráfica/Prototipo_3D'
//Compilar com: g++ prototipo_3D.cpp -o prototipo_3D ./src/glad.c -I include -I./include -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib64 -lGLEW -lGL -lX11 -lglfw -lrt -lm -ldl
// Rodar com: ./prototipo_3D

// Versão LOCAL:
// Pasta: cd /home/griebler/Rsync/Unisinos/Atividade_Academica/2025-1/Computação Gráfica/Github2/AtividadesCG/Hello3D
// Compilar: g++ hello3D.cpp -o hello3D ./src/glad.c -I include -I./include -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib64 -lGLEW -lGL -lX11 -lglfw -lrt -lm -ldl
// Rodar: ./hello3D

#include <glad/glad.h> // É necessário que a inclusão do glad.h seja feita antes da inclusão do glfw3 -- aliás o glad.h precisa ser incluído ANTES de qualquer outro arquivo cabeçalho que use os arquivos cabeçalhos do OpenGL (tipo GL/gl.h)
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
//#include <cmath> // para sin()
//#include <random>

#include "./Shader.h"


using namespace std;

void imprimeAsFuncoesDasTeclas() {
    cout << "Programa hello3D" << endl;
    cout << "Funcionamento:" << endl;
    cout << "Tecla: | Função:" << endl;
    cout << "↑      | Para cima" << endl;
    cout << "↓      | Para baixo" << endl;
    cout << "→      | Para direita" << endl;
    cout << "←      | Para esquerda" << endl;
    cout << "A      | Para dentro" << endl;
    cout << "Z      | Para fora" << endl;
    cout << "1 + ←  | Rotação eixo X " << endl;
    cout << "1 + →  | Rotação eixo X " << endl;
    cout << "2 + ↑  | Rotação eixo Y " << endl;
    cout << "2 + ↓  | Rotação eixo Y " << endl;
    cout << "3 + A  | Rotação eixo Z " << endl;
    cout << "3 + Z  | Rotação eixo Z " << endl;
    cout << "-      | Reduz o tamanho" << endl;
    cout << "+      | Aumenta o tamanho" << endl;
    cout << "9      | Retorna as coordenadas originais X, Y e Z" << endl;
    cout << "0      | Zera todas as rotações " << endl;
    //↶ ↷
}

// Ajusta o viewport para o tamanho da janela principal, no caso de ela ser maximizada ou mudar seu tamanho
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    //glViewport(0, 0, width/2, height/2); // Teste
}

// Processa os eventos disparados
void processInput(GLFWwindow* window) {
    // Pressionou a tecla ESC
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /*int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    cout << "Maximum nr of vertex attributes supported: " << nrAttributes << endl;*/ // Dá falha de segmentação...

    //GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGl", NULL, NULL); // Bibliotecalis
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Ola 3D - Paulo Griebler Júnior", NULL, NULL); // Lunaris
    if (window == NULL) {
        cout << "###Erro: Falha na criação da janela GLFW !" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Informa para o GLFW fazer com a janela criada seja o contexto principal na thread atual.

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Define a função a ser chamada se a janela principal mudar de tamanho

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "###Erro: Falha na inicialização do GLAD !" << endl;
        return -1;
    }

    //glViewport(0, 0, 800, 600); // Define o tamanho da janela de renderização --> PRECISA ?
    //glViewport(0, 0, 400, 300); // Teste


    //Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
    Shader meuShader1("./shader.vs", "./shader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    /*float vertices[] = { // 1 Triângulo 2D --> forma de uma pirâmide 2D
        -0.5f, -0.5f, 0.0f, // Vértice esq./inf.
        0.5f, -0.5f, 0.0f, // Vérice dir./inf.
        0.0f, 0.5f, 0.0f // Vértice centro eixo X/sup.
    };*/

    /*
    // Vista de frente
    //      V1
    //     /  \
    //    /    \
    //   /      \
    // V0________V2
    //

    // Vista pela lateral dir.
    //      V1
    //     /  \
    //    /    \
    //   /      \
    // V2________V3
    //

    // Vista pela lateral esq.
    //      V1
    //     /  \
    //    /    \
    //   /      \
    // V3________V2
    //

    // Vista por baixo.
    //      V3
    //     /  \
    //    /    \
    //   /      \
    // V0________V2
    //


    float vertices[] = { // 1 Triângulo 3D --> forma de uma pirâmide 3D
        //X,      Y,      Z,     R,   G,   B
        // Face 1 (frente):
        -0.5f,  -0.5f,  -0.5f,  1.0, 0.0, 0.0, // V0 -- Vermelho
        0.0f,   0.5f,   0.0f,   0.0, 1.0, 0.0, // V1
        0.5f,   -0.5f,  -0.5f,  0.0, 0.0, 1.0, // V2
        // Face 2 (lado dir.):
        0.5f,   -0.5f,  -0.5f,  0.0, 0.0, 1.0, // V2
        0.0f,   0.5f,   0.0f,   0.0, 1.0, 0.0, // V1
        0.0f,   -0.5f,   0.5f,   1.0, 1.0, 1.0, // V3
        // Face 3 (lado esq.):
       -0.5f,  -0.5f,  -0.5f,  1.0, 0.0, 0.0, // V0
        0.0f,   0.5f,   0.0f,   0.0, 1.0, 0.0, // V1
        0.0f,   -0.5f,   0.5f,   1.0, 1.0, 1.0, // V3
        // Face 4 (base):
        -0.5f,  -0.5f,  -0.5f,  1.0, 0.0, 0.0, // V0
        0.5f,   -0.5f,  -0.5f,  0.0, 0.0, 1.0, // V2
        0.0f,   -0.5f,   0.5f,   1.0, 1.0, 1.0  // V3
    };*/ // Isso é para um prisma NÃO uma pirâmide !


    float vertices[] = { // Pirâmide 3D - 4 faces e 1 base = 4+2 triângulos ==> total 6 triângulos
        // Seguindo esquema desenhado no caderno !
        //X,      Y,      Z,     R,   G,   B
        // Face 0 (frente):
        -0.3f,  0.0f,  -0.3f,  1.0, 0.0, 0.0, // V0 -- Vermelho
        0.0f,   0.6f,   0.0f,  1.0, 0.0, 0.0, // V1 ==> Ápice da pirâmide - aparece em todas as faces, exceto nas bases
        0.3f,   0.0f,  -0.3f,  1.0, 0.0, 0.0, // V2

        // Face 1 (lado esq.):
        -0.3f,  0.0f,  -0.3f,  1.0, 0.5, 0.0, // V0 -- Laranja
        0.0f,   0.6f,   0.0f,  1.0, 0.5, 0.0, // V1 ==> Ápice da pirâmide - aparece em todas as faces, exceto nas bases
        -0.3f,  0.0f,   0.3f,  1.0, 0.5, 0.0, // V3

        // Face 2 (trás):
        -0.3f,  0.0f,   0.3f,  1.0, 1.0, 0.0, // V3 -- Amarelo
        0.0f,   0.6f,   0.0f,  1.0, 1.0, 0.0, // V1 ==> Ápice da pirâmide - aparece em todas as faces, exceto nas bases
        0.3f,   0.0f,   0.3f,  1.0, 1.0, 0.0, // V4

        // Face 3(lado dir.):
        0.3f,   0.0f,  -0.3f,  0.0, 1.0, 0.0, // V2 -- Verde
        0.0f,   0.6f,   0.0f,  0.0, 1.0, 0.0, // V1 ==> Ápice da pirâmide - aparece em todas as faces, exceto nas bases
        0.3f,   0.0f,   0.3f,  0.0, 1.0, 0.0, // V4

        // Base 0(borda da frente/esq.):
        -0.3f,  0.0f,  -0.3f,  0.0, 0.0, 1.0, // V0 -- Azul
        -0.3f,  0.0f,   0.3f,  0.0, 0.0, 1.0, // V3
        0.3f,   0.0f,  -0.3f,  0.0, 0.0, 1.0, // V2

        // Face 3(borda de trás/dir.):
        0.3f,   0.0f,  -0.3f,  1.0, 0.0, 1.0, // V2 -- Roxo
        -0.3f,  0.0f,   0.3f,  1.0, 0.0, 1.0, // V3
        0.3f,   0.0f,   0.3f,  1.0, 0.0, 1.0 // V4
    };


    unsigned int VAO; // Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO; // Vertex Buffer Objects -> armazena os buffers de vértices na memória da GPU
    glGenBuffers(1, &VBO); // Gera um buffer com a ID do VBO -- seria a ID 1 ? ==> PERGUNTAR !

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Define que o tipo de buffer do VBO vai ser um buffer de arrays

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copia o buffer da RAM(vertices[]) para a memória da GPU


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Não precisa modificar aqui se o número de triângulos (vértices de triângulos a serem lidos) aumentar
    // Explica para o OpenGL como interpretar os dados do vértice // 6 * sizeof(float) ==> stride = avanço | (void*)0 ==> offset -- como o deslocamento é 0 (deve iniciar a leitura no índice 0 do buffer) fica 0 // Isso tudo é gravado no VAO
    glEnableVertexAttribArray(0); // Isso tudo é gravado no VAO

    //Atributo cor (r, g, b)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


     // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // Variáveis de transformação:
    float xT = 0.0;
    float yT = 0.0;
    float zT = 0.0;

    int tipoRot = 0; // Em binário !!!
    // 0 -> 0000_0000 -> nenhuma rotação
    // 1 -> 0000_0001 -> rotação eixo Z => tipoRot & 1 => se for 1 tem rotação no eixo Z
    // 2 -> 0000_0010 -> rotação eixo Y => tipoRot & 2 => se for 2 tem rotação no eixo Y
    // 3 -> 0000_0011 -> rotação eixo Y e Z
    // 4 -> 0000_0100 -> rotação eixo X => tipoRot & 4 => se for 4 tem rotação no eixo X
    // 5 -> 0000_0101 -> rotação eixo X e Z
    // 6 -> 0000_0111 -> rotação eixo X, Y e Z
    // Para ativar a rotação nos eixos:
    // rotação eixo Z => tipoRot | 1
    // rotação eixo Y => tipoRot | 2
    // rotação eixo X => tipoRot | 4

    float anguloX = 0.0;
    float anguloY = 0.0;
    float anguloZ = 0.0;

    float escala = 1.0;

    bool teclaPressionada = false;


    // Imprime as funções das teclas:
    imprimeAsFuncoesDasTeclas();

    // Ajuste para ver a pirâmide de fora (não de dentro dela) se não fizer esse ajuste em vez de ver o a face vermelha (frente) vai ver a face de trás amarela pq está "dentro" da pirâmide olhando para sua face de trás !
    // xT =0 | yT =0 | zT=0.999999 | tipoRot=0| anguloX=0| anguloY=0| anguloZ=0 | escala=1
    zT = 0.999999;

    // Loop de renderização
    while(!glfwWindowShouldClose(window)) { // Loop que mantém o desenho da janela principal --> Se glfwWindowShouldClose(window) retorna 'true' o loop pára e o programa encerra
        // Entradas:
        processInput(window); // Processa os eventos ocorridos

        //double mx, my;
        //glfwGetCursorPos(window, &mx, &my);


        const int xEsq = glfwGetKey(window, GLFW_KEY_LEFT);
        const int yRot = glfwGetKey(window, GLFW_KEY_1);
        if (xEsq == GLFW_PRESS) {
            if (yRot == GLFW_PRESS) {
                teclaPressionada = true;
                tipoRot = tipoRot | 2 ; // Ativa Rotacão eixo Y
                anguloY -= 0.01;
            }
            else {
                teclaPressionada = true;
                xT -= 0.01;
            }
        }

        const int xDir = glfwGetKey(window, GLFW_KEY_RIGHT);
        if (xDir == GLFW_PRESS) {
            if (yRot == GLFW_PRESS) {
                teclaPressionada = true;
                tipoRot = tipoRot | 2 ; // Ativa Rotacão eixo Y
                anguloY += 0.01;
            }
            else {
                teclaPressionada = true;
                xT += 0.01;
                //cout << "Diminuindo xT =" << xT << endl;
            }
        }

        const int yUp = glfwGetKey(window, GLFW_KEY_UP);
        const int xRot = glfwGetKey(window, GLFW_KEY_2);
        if (yUp == GLFW_PRESS) {
            if (xRot == GLFW_PRESS) {
                teclaPressionada = true;
                tipoRot = tipoRot | 4 ; // Ativa Rotacão eixo X
                anguloX -= 0.01;
            }
            else {
                teclaPressionada = true;
                yT = yT+0.01;
            }
        }

        const int yDown = glfwGetKey(window, GLFW_KEY_DOWN);
        if (yDown == GLFW_PRESS) {
             if (xRot == GLFW_PRESS) {
                teclaPressionada = true;
                tipoRot = tipoRot | 4 ; // Ativa Rotacão eixo X
                anguloX += 0.01;
             }
             else {
                teclaPressionada = true;
                yT = yT-0.01;
             }
        }

        const int zInc = glfwGetKey(window, GLFW_KEY_A);
        const int zRot = glfwGetKey(window, GLFW_KEY_3);
        if (zInc == GLFW_PRESS) {
             if (zRot == GLFW_PRESS) {
                teclaPressionada = true;
                tipoRot = tipoRot | 1 ; // Ativa Rotacão eixo Z
                anguloZ -= 0.01;
            }
            else {
                teclaPressionada = true;
                zT = zT+0.01;
            }
        }

        const int zDec = glfwGetKey(window, GLFW_KEY_Z);
        if (zDec == GLFW_PRESS) {
            if (zRot == GLFW_PRESS) {
                teclaPressionada = true;
                tipoRot = tipoRot | 1 ; // Ativa Rotacão eixo Z
                anguloZ += 0.01;
            }
            else {
                teclaPressionada = true;
                zT = zT-0.01;
            }
        }

        const int reduzEscala = glfwGetKey(window, GLFW_KEY_MINUS);
        if (reduzEscala == GLFW_PRESS) {
            teclaPressionada = true;
            escala -= 0.01;
        }

        const int aumentaEscala = glfwGetKey(window, GLFW_KEY_EQUAL);
        if (aumentaEscala == GLFW_PRESS) {
            teclaPressionada = true;
            escala += 0.01;
        }

        const int origemEscala = glfwGetKey(window, GLFW_KEY_8);
        if (origemEscala == GLFW_PRESS) {
            teclaPressionada = true;
            escala = 1.0;
        }

        const int origemCoord = glfwGetKey(window, GLFW_KEY_9);
        if (origemCoord == GLFW_PRESS) {
            teclaPressionada = true;
            xT = 0.0;
            yT = 0.0;
            zT = 0.0;
        }

        const int zeraRot = glfwGetKey(window, GLFW_KEY_0);
        if (zeraRot == GLFW_PRESS) {
            teclaPressionada = true;
            tipoRot = 0;
            anguloX = 0.0;
            anguloY = 0.0;
            anguloZ = 0.0;
        }

        if (teclaPressionada) {
            //cout << "xT =" << xT << " | yT =" << yT << " | zT=" << zT << " | tipoRot=" << tipoRot << "| anguloX=" << anguloX <<"| anguloY=" << anguloY << "| anguloZ=" << anguloZ << " | escala=" << escala << endl;
            teclaPressionada = false;
            //cout << "tipoRot & 4=>" << (tipoRot & 4) << " | (tipoRot & 4) == 4 =>" << ((tipoRot & 4) == 4) << " | tipoRot & 4 == 4 =>" << (tipoRot & 4 == 4) << endl; // Debug
        }



        // Comandos de renderização:
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // verde escuro leve
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // preto
        glClear(GL_COLOR_BUFFER_BIT); // Aplica as cores acima ao buffer de cor -- poderia aplicar as cores acima a outros buffers (GL_DEPTH_BUFFER_BIT OU GL_STENCIL_BUFFER_BIT)

        meuShader1.use();// Aqui define o programa de shader que cada chamada de renderização vai usar

        glBindVertexArray(VAO);

        // create transformations para triângulo 1
        glm::mat4 transform1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform1 = glm::translate(transform1, glm::vec3(0.0f+xT, 0.0f+yT, 0.0f+zT));
        //transform1 = glm::translate(transform1, glm::vec3(quad[i][j].getTX()*i, -quad[i][j].getTY()*j, 0.0f));
        //Model = glm::rotate(Model, angle_in_radians, glm::vec3(x, y, z)); // where x, y, z is axis of rotation (e.g. 0 1 0)

        //if (tipoRot & 4 == 4) {//Pq | (tipoRot & 4) == 4 =>1 | tipoRot & 4 == 4 =>0
        if ((tipoRot & 4) == 4) {// => se for 4 tem rotação no eixo X
            transform1 = glm::rotate(transform1, anguloX, glm::vec3(1, 0, 0));
        }
        if ((tipoRot & 2) == 2) {// => se for 2 tem rotação no eixo Y
            transform1 = glm::rotate(transform1, anguloY, glm::vec3(0, 1, 0));
        }
        if ((tipoRot & 1) == 1) {// => se for 1 tem rotação no eixo Z
            transform1 = glm::rotate(transform1, anguloZ, glm::vec3(0, 0, 1));
        }

        //if (escala != 1.0) {// => Se tiver alteração no fator de escala, faz a transformação
            //modelview = glm::scale( modelview, glm::vec3(Scale,Scale,Scale) )
            transform1 = glm::scale(transform1, glm::vec3(escala, escala, escala));
        //}

        // get matrix's uniform location and set matrix
        unsigned int transformLoc1 = glGetUniformLocation(meuShader1.ID, "transform");
        //cout << "transformLoc1 =" << transformLoc1 << endl;  // Debug
        if (transformLoc1 == -1) cout << "###Erro na localização da ID 'transformm' no shader !" << endl;
        glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(transform1));
        //glUniformMatrix4fv(transformLoc1, 0, GL_FALSE, glm::value_ptr(transform1));



        //glDrawArrays(GL_TRIANGLES, 0, 3); // 1 triângulo -- pode usar para ver só o 1° triângulo -- ajustes de geometria
        //glDrawArrays(GL_TRIANGLES, 0, 6); // 2 triângulos - Pq 6 ? -> Conforme aumenta os vértices dos triângulos deve aumentar esse valor aqui
        //glDrawArrays(GL_TRIANGLES, 0, 9); // 3 triângulos = 9 vértices
        glDrawArrays(GL_TRIANGLES, 0, 18); // 6 triângulos = 18 vértices = Pirâmide


        // Troca de buffers e checagem/chamada de eventos:
        glfwSwapBuffers(window); // Troca os buffers de cor -- evitar o flickering
        glfwPollEvents(); // Checa se algum evento foi disparado -- limpa os eventos já ocorridos e processados ?
    }

    glfwTerminate(); // Deleta todos os recursos que o GLFW alocou
    return 0;
}
