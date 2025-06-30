// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Computação Gráfica
// Módulo 4
// Tarefa: Atividade Vivencial 2 - Técnica de Iluminação de 3 pontos
// Data: 31/05/2025
// Professor: Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior e Rodrigo Pires
// Registros Acadêmicos: 1930669 e 1917485


//#include <glad/glad.h> // Arquivo ou diretório inexistente
#include "Basico/glad/glad.h"// É necessário que a inclusão do glad.h seja feita antes da inclusão do glfw3 -- aliás o glad.h precisa ser incluído ANTES de qualquer outro arquivo cabeçalho que use os arquivos cabeçalhos do OpenGL (tipo GL/gl.h)
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath> // Para sin()
//#include <random>
#include <execinfo.h> // Para backtrace()


#include "Basico/Shader.h"

#include "Grade2D/Grade2D.h"

#include "Transformacoes/Transformacoes2D.h"
#include "Transformacoes/Transformacoes3D.h"
#include "Teclado/Teclado2D.h"
#include "Teclado/Teclado3D.h"
#include "Planeta3D/Planeta3D.h"

using namespace std;


void imprimeAsFuncoesDasTeclas() {
    cout << "Programa Atividade Vivencial 2 - Técnica de Iluminação de 3 pontos" << endl;
    cout << "Funcionamento:" << endl;
    cout << "Tecla: | Função:" << endl;
    cout << "M      | Mostra esta tela" << endl;
    cout << "G      | Desenha o componente Grade2D" << endl;
    cout << "P      | Desenha o componente Planeta3D" << endl;
    cout << "BACKSPACE| Apaga todos os componentes" << endl; //
    cout << "ESC    | Termina o programa" << endl; // GLFW_KEY_ESCAPE

    /*cout << "1      | Cubo 1" << endl;
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
    cout << "INSERT  | Aumenta vertIni." << endl;
    cout << "DELETE  | Diminui vertIni." << endl;
    cout << "PG_UP   | Aumenta vertFim." << endl;
    cout << "PG_DW   | Diminui vertFim." << endl;
    //cout << "   | " << endl;
    cout << endl;
    //↶ ↷*/
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

//int main(int argc, char* argv[]) {
void* janelaOpenGL(void* arg) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /*int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    cout << "Maximum nr of vertex attributes supported: " << nrAttributes << endl;*/ // Dá falha de segmentação...

    GLFWwindow* window = glfwCreateWindow(1024, 768, "Atividade Vivencial 2 - Técnica de Iluminação de 3 pontos", NULL, NULL); // Lunaris
    if (window == NULL) {
        cout << "###Erro: Falha na criação da janela GLFW !" << endl;
        glfwTerminate();
        //return -1;
        return nullptr; // Pq tem 'void*' no tipo de retorno !
    }

    glfwMakeContextCurrent(window); // Informa para o GLFW fazer com a janela criada seja o contexto principal na thread atual.

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Define a função a ser chamada se a janela principal mudar de tamanho

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "###Erro: Falha na inicialização do GLAD !" << endl;
        //return -1;
        return nullptr; // Pq tem 'void*' no tipo de retorno !
    }

    glm::mat4 projection;
    //projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    projection = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.1f, 100.0f); // Novos valores de janela

    // Inicializa o objeto a ser desenhado:
    Grade2D grad = Grade2D();
    //Planeta3D texto = Planeta3D();
    Planeta3D texto = Planeta3D(window, projection);

    // Indica se os componentes devem ou não ser desenhados:
    bool desenhaGrade2D = false;
    bool desenhaPlaneta3D = true;

    glEnable(GL_DEPTH_TEST); // Ativa o z-buffer que permite que os triângulos sejam desenhados na ordem correta -- sem isso os triângulos da parte de trás do cubo (que vem por último na descrição dos vértices) vão ser desenhados por cima dos da frente, o que leva a nunca poder ver os triângulos da frente (que são vermelhos).

    // Loop de renderização
    while(!glfwWindowShouldClose(window)) { // Loop que mantém o desenho da janela principal --> Se glfwWindowShouldClose(window) retorna 'true' o loop pára e o programa encerra
        // Entradas:
        processInput(window); // Processa os eventos ocorridos


        // Comandos de renderização:
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // preto
       // glClear(GL_COLOR_BUFFER_BIT); // Aplica as cores acima ao buffer de cor -- poderia aplicar as cores acima a outros buffers (GL_DEPTH_BUFFER_BIT OU GL_STENCIL_BUFFER_BIT)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Se vai usar 'glEnable(GL_DEPTH_TEST);' (acima), precisa limpar o 'depth_buffer' tb, senão não aparece nada na tela -- tela preta...

        const int mostrarComandosTecla = glfwGetKey(window, GLFW_KEY_M);
        if (mostrarComandosTecla == GLFW_PRESS) {
            imprimeAsFuncoesDasTeclas();
        }

        const int telaLimpaTecla = glfwGetKey(window, GLFW_KEY_BACKSPACE);
        if (telaLimpaTecla == GLFW_PRESS) {
            desenhaGrade2D = false;
            desenhaPlaneta3D = false;
        }

        const int desenhaGrade2DTecla = glfwGetKey(window, GLFW_KEY_G);
        if (desenhaGrade2DTecla == GLFW_PRESS) {
            //if (desenhaGrade2D) desenhaGrade2D = false;
            //else desenhaGrade2D = true; // Muito rápido a alternância de estados !
            desenhaGrade2D = true;
        }

        const int desenhaPlaneta3DTecla = glfwGetKey(window, GLFW_KEY_P);
        if (desenhaPlaneta3DTecla == GLFW_PRESS) {
            desenhaPlaneta3D = true;
        }


        if (desenhaPlaneta3D) texto.desenhar();
        if (desenhaGrade2D) grad.desenhar(); // A grade fica por último para ser desenhada por cima de todos -- teoricamente... | Teoricamante sim, pq só vai ficar por cima se a coordenada Z dela for muito mais positiva (regra da mão direita) que o último desenho que usa coordenada Z

        // Troca de buffers e checagem/chamada de eventos:
        glfwSwapBuffers(window); // Troca os buffers de cor -- evitar o flickering
        glfwPollEvents(); // Checa se algum evento foi disparado -- limpa os eventos já ocorridos e processados ?
    }

    glfwTerminate(); // Deleta todos os recursos que o GLFW alocou
    //return 0;
    return nullptr; // Pq tem 'void*' no tipo de retorno !
}
