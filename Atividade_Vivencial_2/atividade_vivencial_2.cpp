// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Computação Gráfica
// Módulo 2
// Tarefa: Atividade Vivencial 1
// Data: 17/05/2025
// Professor: Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior e Rodrigo Pires
// Registros Acadêmicos: 1930669 e 1917485

// Versão Astrolabium:
// Pasta: cd '/mnt/astrolabium/home/griebler/Rsync/Unisinos/Atividade_Academica/2025-1/Computação Gráfica/Github/AtividadesCG/Atividade_Vivencial_1'
//Compilar com: g++ atividade_vivencial_1.cpp -o atividade_vivencial_1 loadSimpleOBJ.cpp Objeto3D.cpp ./src/glad.c -I include -I./include -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib64 -lGLEW -lGL -lX11 -lglfw -lrt -lm -ldl
// Rodar com: ./atividade_vivencial_1

// Versão LOCAL:
// Pasta: cd /home/griebler/Rsync/Unisinos/Atividade_Academica/2025-1/Computação Gráfica/Github2/AtividadesCG/Atividade_Vivencial_1
// Compilar: g++ atividade_vivencial_1.cpp -o atividade_vivencial_1 loadSimpleOBJ.cpp ./src/glad.c -I include -I./include -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib64 -lGLEW -lGL -lX11 -lglfw -lrt -lm -ldl
// Rodar: ./atividade_vivencial_1

#include <glad/glad.h> // É necessário que a inclusão do glad.h seja feita antes da inclusão do glfw3 -- aliás o glad.h precisa ser incluído ANTES de qualquer outro arquivo cabeçalho que use os arquivos cabeçalhos do OpenGL (tipo GL/gl.h)
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
//#include <cmath> // para sin()
//#include <random>

#include "./Shader.h"

#include "loadSimpleObj.h"
#include "Objeto3D.h"
#include "Teclado.h"


using namespace std;

void imprimeAsFuncoesDasTeclas() {
    cout << "Programa Atividade_Vivencial_1" << endl;
    cout << "Funcionamento:" << endl;
    cout << "Tecla: | Função:" << endl;
    cout << "M      | Mostra esta tela" << endl;
    cout << "1      | Figura 1 (Suzanne vermelha)" << endl;
    cout << "2      | Figura 2 (Suzanne amarela)" << endl;
    cout << "3      | Figura 1 e 2" << endl;
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
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Atividade Vivencial 1 - Paulo Griebler Júnior e Rodrigo Pires", NULL, NULL); // Lunaris
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

    //Objeto3D(string caminhoArquivo, float xT, float yT, float zT, int tipoRot, float anguloX, float anguloY, float anguloZ, float escala);
    Objeto3D obj0 = Objeto3D("Suzanne_Vermelha", "./Modelos_3D/Suzanne.obj", -0.3, 0, 0, 0, 0, 0, 0, 0.2); // Este objeto fica à esq. da tela --> -0.3
    Objeto3D obj0_ini = obj0.clonar(); // Precisa aqui que seja uma cópia do obejto e não só uma ref. -- para guardar as configurações iniciais do objeto
    //Teclado(GLFWwindow* window, Objeto3D &obj3D, Objeto3D &obj3D_ini)
    //Teclado tec0 = Teclado(window, obj0, obj0_ini);
    //Teclado(GLFWwindow* window, Objeto3D* obj3D, Objeto3D* obj3D_ini)
    Teclado tec0 = Teclado(window, &obj0, &obj0_ini); // Usando passagem por ponteiro pq passagem por ref. não está atualizando os atributos do objeto ao usar o teclado ! -- ausência de Teclado.cpp ??? ==> PERGUNTAR !!!

    Objeto3D obj1 = Objeto3D("Suzanne_Amarela", "./Modelos_3D/Suzanne.obj", 0.3, 0, 0, 0, 0, 0, 0, 0.2); // Este objeto fica à dir. da tela --> 0.3
    Objeto3D obj1_ini = obj1.clonar();
    //Teclado tec1 = Teclado(window, obj1, obj1_ini);
    Teclado tec1 = Teclado(window, &obj1, &obj1_ini);


    int figuraEscolhida = 0;

    // HACK !
    string filePATH = "./Modelos_3D/Suzanne.obj";
    int nVertices;
    unsigned int VAO_0;
    glm::vec3 color0 = glm::vec3(1.0, 0.0, 0.0);
    //VAO_0 = loadSimpleOBJ(filePATH, nVertices);
    VAO_0 = loadSimpleOBJ(filePATH, nVertices, color0);

    unsigned int VAO_1;
    glm::vec3 color1 = glm::vec3(1.0, 1.0, 0.0);
    //VAO_1 = loadSimpleOBJ(filePATH, nVertices);
    VAO_1 = loadSimpleOBJ(filePATH, nVertices, color1);


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
        glBindVertexArray(VAO_0);
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

        glBindVertexArray(VAO_1);
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
        glUniformMatrix3fv(transformCor2, 1, GL_FALSE, glm::value_ptr(transform3));



        //glDrawArrays(GL_TRIANGLES, 0, 3); // 1 triângulo -- pode usar para ver só o 1° triângulo -- ajustes de geometria
        //glDrawArrays(GL_TRIANGLES, 0, 6); // 2 triângulos - Pq 6 ? -> Conforme aumenta os vértices dos triângulos deve aumentar esse valor aqui
        //glDrawArrays(GL_TRIANGLES, 0, 9); // 3 triângulos = 9 vértices
        //glDrawArrays(GL_TRIANGLES, 0, 12); // 4 triângulos = 12 vértices
        //glDrawArrays(GL_TRIANGLES, 0, 24); // 8 triângulos = 24 vértices
        //glDrawArrays(GL_TRIANGLES, 0, 36); // 12 triângulos = 36 vértices
        glDrawArrays(GL_TRIANGLES, 0, nVertices); // 12 triângulos = 36 vértices
        //glDrawArrays(GL_TRIANGLES, 0, 18); // 6 triângulos = 18 vértices = Pirâmide*/






        // Troca de buffers e checagem/chamada de eventos:
        glfwSwapBuffers(window); // Troca os buffers de cor -- evitar o flickering
        glfwPollEvents(); // Checa se algum evento foi disparado -- limpa os eventos já ocorridos e processados ?
    }

    glfwTerminate(); // Deleta todos os recursos que o GLFW alocou
    return 0;
}
