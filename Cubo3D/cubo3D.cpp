// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Computação Gráfica
// Módulo 2
// Tarefa: Desafio
// Data: 17/05/2025
// Professor: Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior e Rodrigo Pires
// Registros Acadêmicos: 1930669 e 1917485

// Versão Astrolabium:
// Pasta: cd '/mnt/astrolabium/home/griebler/Rsync/Unisinos/Atividade_Academica/2025-1/Computação Gráfica/Github/AtividadesCG/Atividade_Vivencial_1'
//Compilar com: g++ cubo3D.cpp -o cubo3D Objeto3D.cpp ./src/glad.c -I include -I./include -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib64 -lGLEW -lGL -lX11 -lglfw -lrt -lm -ldl
// Rodar com: ./cubo3D

// Versão LOCAL:
// Pasta: cd /home/griebler/Rsync/Unisinos/Atividade_Academica/2025-1/Computação Gráfica/Github2/AtividadesCG/Atividade_Vivencial_1
// Compilar: g++ cubo3D.cpp -o cubo3D ./src/glad.c -I include -I./include -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib64 -lGLEW -lGL -lX11 -lglfw -lrt -lm -ldl
// Rodar: ./cubo3D

/*Agora vocês terão a primeira tarefa que envolve implementação. Vocês são livres para usar ou não o projeto de base, e mais importante: de acordo com a necessidade, criem sua própria arquitetura de software. Façam alterações que julgarem pertinentes. Os objetivos dessa implementação são:

    Alterar a geometria da pirâmide, transformando-a em um cubo (adicionar os vértices e triângulos necessários). Sugere-se fazer cada lado do cubo (composto de 2 triângulos, similar à base da pirâmide) de uma cor diferente, para que facilite nossa visualização neste momento que ainda não utilizamos texturas e iluminação adequada.
    No projeto de base, ao pressionar as teclas x, y e z, a pirâmide rotaciona nos respectivos eixos. Adicione controle via teclado para:
        Mover (transladar) o cubo nos 3 eixos (sugestão de teclas WASD para os eixos x e z, IJ para o eixo y)
        Promover a escala uniforme do cubo (sugestão de teclas [ para diminuir e ] para aumentar)
    Instanciar mais de um cubo na cena
*/

#include <glad/glad.h> // É necessário que a inclusão do glad.h seja feita antes da inclusão do glfw3 -- aliás o glad.h precisa ser incluído ANTES de qualquer outro arquivo cabeçalho que use os arquivos cabeçalhos do OpenGL (tipo GL/gl.h)
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
//#include <cmath> // para sin()
//#include <random>

#include "./Shader.h"


#include "Objeto3D.h"
#include "Teclado.h"


using namespace std;

void imprimeAsFuncoesDasTeclas() {
    cout << "Programa Cubo3D" << endl;
    cout << "Funcionamento:" << endl;
    cout << "Tecla: | Função:" << endl;
    cout << "M      | Mostra esta tela" << endl;
    cout << "1      | Cubo 1" << endl;
    cout << "2      | Cubo 2" << endl;
    cout << "3      | Cubo 1 e 2" << endl;
    cout << "↑      | Para cima" << endl;
    cout << "↓      | Para baixo" << endl;
    cout << "→      | Para direita" << endl;
    cout << "←      | Para esquerda" << endl;
    cout << "Q      | Para dentro" << endl;
    cout << "A      | Para fora" << endl;
    cout << "X + ←  | Rotação eixo X " << endl;
    cout << "X + →  | Rotação eixo X " << endl;
    cout << "Y + ↑  | Rotação eixo Y " << endl;
    cout << "Y + ↓  | Rotação eixo Y " << endl;
    cout << "Z + Q  | Rotação eixo Z (↶)" << endl;
    cout << "Z + A  | Rotação eixo Z (↷)" << endl;
    cout << "-      | Reduz o tamanho" << endl;
    cout << "+      | Aumenta o tamanho" << endl;
    cout << "9      | Retorna as coordenadas originais X, Y e Z" << endl;
    cout << "0      | Zera todas as rotações " << endl;
    cout << endl;
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
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Desafio M2 - Cubo3D - Paulo Griebler Júnior", NULL, NULL); // Lunaris
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


    float vertices[] = { // Cubo 3D - 4 faces e 1 base e 1 tampa = 2*6 faces ==> 12 triângulos = 12*3 ==> 36 vértices
        // Seguindo esquema desenhado no caderno !

        // Face frente (vendo de fora !)
        //- <-- Eixo X --> +
        // V1----V2
        // |      |
        // |      |
        // V0----V3

        //-0.2f,  -0.2f,  -0.2f, // V0
        //-0.2f,   0.2f,  -0.2f, // V1
        //0.2f,    0.2f,  -0.2f, // V2
        //0.2f,   -0.2f,  -0.2f, // V3

        // Face trás (vendo de fora ! -- não através da face da frente !)
        // + <-- Eixo X --> -
        // V5----V6
        // |      |
        // |      |
        // V4----V7

        //0.2f,   -0.2f,  0.2f, // V4
        //0.2f,    0.2f,  0.2f, // V5
        //-0.2f,   0.2f,  0.2f, // V6
        //-0.2f,  -0.2f,  0.2f, // V7


        //X,      Y,      Z,     R,   G,   B
        // Face 0 (frente):
            // T0 --> V0/V1/V2
        -0.2f,  -0.2f,  -0.2f,  1.0, 0.0, 0.0, // V0 -- Vermelho
        -0.2f,   0.2f,  -0.2f,  1.0, 0.0, 0.0, // V1
        0.2f,    0.2f,  -0.2f,  1.0, 0.0, 0.0, // V2

            // T1 --> V0/V2/V3
        -0.2f,  -0.2f,  -0.2f,  0.5, 0.0, 0.0, // V0 -- Vermelho escuro
        0.2f,    0.2f,  -0.2f,  0.5, 0.0, 0.0, // V2
        0.2f,   -0.2f,  -0.2f,  0.5, 0.0, 0.0, // V3

        // Face 1 (esq.):
            // T2 -->V0/V1/V6
        -0.2f,  -0.2f,  -0.2f,  1.0, 0.5, 0.0, // V0 -- Laranja
        -0.2f,   0.2f,  -0.2f,  1.0, 0.5, 0.0, // V1
        -0.2f,   0.2f,  0.2f,   1.0, 0.5, 0.0, // V6

            // T3 -->V6/V7/V0
        -0.2f,  -0.2f,  -0.2f,  0.5, 0.25, 0.0, // V0 -- Laranja escuro
        -0.2f,   0.2f,  0.2f,   0.5, 0.25, 0.0, // V6
        -0.2f,  -0.2f,  0.2f,   0.5, 0.25, 0.0, // V7

        // Face 3 (trás):
            // T4 --> V4/V5/V6
        0.2f,   -0.2f,  0.2f,   0.0, 1.0, 0.0, // V4 -- Verde
        0.2f,    0.2f,  0.2f,   0.0, 1.0, 0.0, // V5
        -0.2f,   0.2f,  0.2f,   0.0, 1.0, 0.0, // V6

            // T5 --> V4/V6/V7
        0.2f,   -0.2f,  0.2f,   0.0, 0.5, 0.0, // V4 -- Verde escuro
        -0.2f,   0.2f,  0.2f,   0.0, 0.5, 0.0, // V6
        -0.2f,  -0.2f,  0.2f,   0.0, 0.5, 0.0, // V7


        // Face 4 (dir.):
            // T6 -->V2/V3/V5
        0.2f,    0.2f,  -0.2f,   0.0, 0.5, 1.0,  // V2 -- Ciano
        0.2f,   -0.2f,  -0.2f,   0.0, 0.5, 1.0, // V3
        0.2f,   0.2f,   0.2f,    0.0, 0.5, 1.0,// V5

            // T7 -->V5/V4/V3
        0.2f,  -0.2f,   0.2f,    0.0, 0.25, 0.5, // V4 -- Ciano escuro
        0.2f,   0.2f,   0.2f,    0.0, 0.25, 0.5, // V5
        0.2f,   -0.2f,  -0.2f,   0.0, 0.25, 0.5, // V3

        // Face 5 (base):
            // T8 -->V0/V3/V4
        -0.2f,  -0.2f,  -0.2f,   1.0, 0.0, 1.0, // V0 -- Roxo
        0.2f,   -0.2f,  -0.2f,   1.0, 0.0, 1.0, // V3
        0.2f,   -0.2f,  0.2f,    1.0, 0.0, 1.0, // V4

            // T9 -->V4/V7/V3
        0.2f,   -0.2f,  0.2f,    0.5, 0.0, 0.5, // V4 -- Roxo escuro
        -0.2f,  -0.2f,  -0.2f,   1.0, 0.0, 1.0, // V0
        -0.2f,  -0.2f,  0.2f,    0.5, 0.0, 0.5, // V7
        //0.2f,   -0.2f,  -0.2f,   0.5, 0.0, 0.5, // V3

        // Face 6 (tampa):
            // T10 -->V1/V2/V5
        -0.2f,   0.2f,  -0.2f,   1.0, 1.0, 1.0, // V1, -- Branco
        0.2f,    0.2f,  -0.2f,   1.0, 1.0, 1.0, // V2
        0.2f,    0.2f,  0.2f,    1.0, 1.0, 1.0, // V5

            // T11 -->V5/V6/V2
        0.2f,    0.2f,  0.2f,    0.5, 0.5, 0.5, // V5 -- Cinza
        -0.2f,   0.2f,  0.2f,    0.5, 0.5, 0.5, // V6
        //0.2f,    0.2f,  -0.2f,   0.5, 0.5, 0.5, // V2
        -0.2f,   0.2f,  -0.2f,   0.5, 0.5, 0.5 // V1

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

    int nVertices = 36; // 36 vértices para cada cubo, porém como a maioria dos triângulos são 'ligados' eles compartilham muitos vértices... o valor real de vértices diferentes é de 8 apenas


    //Objeto3D(string caminhoArquivo, float xT, float yT, float zT, int tipoRot, float anguloX, float anguloY, float anguloZ, float escala);
    Objeto3D obj0 = Objeto3D("Cubo 1", "", -0.3, 0, 0, 0, 0, 0, 0, 0.2); // Este objeto fica à esq. da tela --> -0.3
    Objeto3D obj0_ini = obj0.clonar(); // Precisa aqui que seja uma cópia do obejto e não só uma ref. -- para guardar as configurações iniciais do objeto
    //Teclado(GLFWwindow* window, Objeto3D &obj3D, Objeto3D &obj3D_ini)
    //Teclado tec0 = Teclado(window, obj0, obj0_ini);
    //Teclado(GLFWwindow* window, Objeto3D* obj3D, Objeto3D* obj3D_ini)
    Teclado tec0 = Teclado(window, &obj0, &obj0_ini); // Usando passagem por ponteiro pq passagem por ref. não está atualizando os atributos do objeto ao usar o teclado ! -- ausência de Teclado.cpp ??? ==> PERGUNTAR !!!

    Objeto3D obj1 = Objeto3D("Cubo 2", "", 0.3, 0, 0, 0, 0, 0, 0, 0.2); // Este objeto fica à dir. da tela --> 0.3
    Objeto3D obj1_ini = obj1.clonar();
    //Teclado tec1 = Teclado(window, obj1, obj1_ini);
    Teclado tec1 = Teclado(window, &obj1, &obj1_ini);


    int figuraEscolhida = 0;


    // Imprime as funções das teclas:
    imprimeAsFuncoesDasTeclas();

    // Ajuste para ver a pirâmide de fora (não de dentro dela) se não fizer esse ajuste em vez de ver o a face vermelha (frente) vai ver a face de trás amarela pq está "dentro" da pirâmide olhando para sua face de trás !
    // xT =0 | yT =0 | zT=0.999999 | tipoRot=0| anguloX=0| anguloY=0| anguloZ=0 | escala=1
    //zT = 0.999999;

    // Loop de renderização
    while(!glfwWindowShouldClose(window)) { // Loop que mantém o desenho da janela principal --> Se glfwWindowShouldClose(window) retorna 'true' o loop pára e o programa encerra
        // Entradas:
        processInput(window); // Processa os eventos ocorridos

        //double mx, my;
        //glfwGetCursorPos(window, &mx, &my);

        const int mostrarComandos = glfwGetKey(window, GLFW_KEY_M);
            if (mostrarComandos == GLFW_PRESS) {
                imprimeAsFuncoesDasTeclas();
            }

        const int escolherFigura0 = glfwGetKey(window, GLFW_KEY_1);
            if (escolherFigura0 == GLFW_PRESS) {
                figuraEscolhida = 0;
                cout << "Trocou a figura escolhida para :" << figuraEscolhida << " (" << obj0.getNome() << ")" << endl;
            }

        const int escolherFigura1 = glfwGetKey(window, GLFW_KEY_2);
            if (escolherFigura1 == GLFW_PRESS) {
                figuraEscolhida = 1;
                cout << "Trocou a figura escolhida para :" << figuraEscolhida << " (" << obj1.getNome() << ")"<< endl;
            }

        const int escolherFigura0e1 = glfwGetKey(window, GLFW_KEY_3);
            if (escolherFigura0e1 == GLFW_PRESS) {
                figuraEscolhida = 2;
                cout << "Escolheu as 2 figuras ! :" << figuraEscolhida << " (" << obj0.getNome() << " e " << obj0.getNome() << ")" << endl;
            }


        // Processa os eventos de teclado conforme as figuras escolhidas:
        switch(figuraEscolhida){
            //case0: // Pode isso ? --  PERGUNTAR !!!
            case 0:
                tec0.avaliaTeclas();
                break;
            case 1:
                tec1.avaliaTeclas();
                break;
            default: // Escolheu as 2 (ou mais (em caso de expansão do programa)) figuras:
                tec0.avaliaTeclas();
                tec1.avaliaTeclas();
                break;
        }


        // Comandos de renderização:
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // verde escuro leve
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // preto
        glClear(GL_COLOR_BUFFER_BIT); // Aplica as cores acima ao buffer de cor -- poderia aplicar as cores acima a outros buffers (GL_DEPTH_BUFFER_BIT OU GL_STENCIL_BUFFER_BIT)

        meuShader1.use();// Aqui define o programa de shader que cada chamada de renderização vai usar

        //cout << "obj0.getVAO() =" << obj0.getVAO() << endl; // = 1 !!! errado !

        //glBindVertexArray(obj0.getVAO());
        //glBindVertexArray(0); // Deve usar o array de vertice 0 para desenhar a figura 0 -- estava usando 1 !!! Pq ?
        glBindVertexArray(VAO);
        glm::mat4 transform0 = obj0.calculaTransformacoes();
        //cout << "obj0.toString() =" << obj0.toString() << endl;
        //obj0.imprimeATransformacao(transform0);
        // Atualiza a matriz de transformação no vertex shader:
        // get matrix's uniform location and set matrix
        //unsigned int transformLoc1 = glGetUniformLocation(meuShader1.ID, "transform");
        unsigned int transformLoc0 = glGetUniformLocation(meuShader1.ID, "transform");
        //cout << "transformLoc0 =" << transformLoc0 << endl;  // Debug
        // transformLoc0 =4294967295 --> erro tb !
        if (transformLoc0 == -1) cout << "###Erro na localização da ID 'transform' no shader !" << endl;
        glUniformMatrix4fv(transformLoc0, 1, GL_FALSE, glm::value_ptr(transform0));
        //glUniformMatrix4fv(transformLoc0, 0, GL_FALSE, glm::value_ptr(transform0)); // Não desenha nada ! -- por causa do '0' ? --> '0, GL_FALSE'

        //cout << "obj0.getNVertices() =" << obj0.getNVertices() << endl; // obj0.getNVertices() =2901
        //glDrawArrays(GL_TRIANGLES, 0, obj0.getNVertices()); // HACK -- Pq não está carregando o objeto na classe Objeto3D !
        glDrawArrays(GL_TRIANGLES, 0, nVertices);

        glBindVertexArray(VAO); // Desenhando o mesmo VAO, porém com coordenadas diferentes
        glm::mat4 transform1 = obj1.calculaTransformacoes();
        // Atualiza a matriz de transformação no vertex shader:
        // get matrix's uniform location and set matrix
        //unsigned int transformLoc1 = glGetUniformLocation(meuShader1.ID, "transform");
        unsigned int transformLoc1 = glGetUniformLocation(meuShader1.ID, "transform");
        //cout << "transformLoc1 =" << transformLoc1 << endl;  // Debug
        // transformLoc0 =4294967295 --> erro tb !
        if (transformLoc1 == -1) cout << "###Erro na localização da ID 'transform' no shader !" << endl;
        glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(transform1));
        //glUniformMatrix4fv(transformLoc0, 0, GL_FALSE, glm::value_ptr(transform0)); // Não desenha nada ! -- por causa do '0' ? --> '0, GL_FALSE'

        //cout << "obj0.getNVertices() =" << obj0.getNVertices() << endl; // obj0.getNVertices() =2901
        //glDrawArrays(GL_TRIANGLES, 0, obj1.getNVertices()); // HACK -- Pq não está carregando o objeto na classe Objeto3D !
        glDrawArrays(GL_TRIANGLES, 0, nVertices);



        /*glm::mat3 transform3 = glm::mat3(1.0f);
        transform3 = transform * glm::vec3(0.5, 1.0, 1.0)) // Muda a cor do 2º macaco
        unsigned int transformCor2 = glGetUniformLocation(meuShader1.ID, "transfCor");
        //cout << "transformLoc1 =" << transformLoc1 << endl;  // Debug
        if (transformCor2 == -1) cout << "###Erro na localização da ID 'transfCor2' no shader !" << endl;
        glUniformMatrix3fv(transformCor2, 1, GL_FALSE, glm::value_ptr(transform3))*/






        // Troca de buffers e checagem/chamada de eventos:
        glfwSwapBuffers(window); // Troca os buffers de cor -- evitar o flickering
        glfwPollEvents(); // Checa se algum evento foi disparado -- limpa os eventos já ocorridos e processados ?
    }

    glfwTerminate(); // Deleta todos os recursos que o GLFW alocou
    return 0;
}
