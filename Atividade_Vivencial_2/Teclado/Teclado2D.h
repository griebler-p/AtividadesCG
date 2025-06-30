// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Computação Gráfica
// Módulo 4
// Tarefa: Atividade Vivencial 2 - Técnica de Iluminação de 3 pontos
// Data: 31/05/2025
// Professor: Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior e Rodrigo Pires
// Registros Acadêmicos: 1930669 e 1917485

#ifndef TECLADO2D_H
#define TECLADO2D_H

/*#include <glad/glad.h> // É necessário que a inclusão do glad.h seja feita antes da inclusão do glfw3 -- aliás o glad.h precisa ser incluído ANTES de qualquer outro arquivo cabeçalho que use os arquivos cabeçalhos do OpenGL (tipo GL/gl.h)
#include <GLFW/glfw3.h>*/


class Teclado2D{
    private:
        GLFWwindow* window;
        //Transformacoes2D transf2D;
        //Transformacoes2D transf2D_ini;
        //Transformacoes2D* transf2D;
        shared_ptr<Transformacoes2D> transf2D;// Mudei para ponteiro pq não está dando certo a pasagem por referência -- será que é pq não tem o arquivo 'Teclado.cpp' ???
        //Transformacoes2D* transf2D_ini;
        shared_ptr<Transformacoes2D> transf2D_ini;// Configurações do Transformacoes2D na sua 1° inicialização - útil para quando for zerar as transformações ele volte para a sua posição inicial e não para a coordenada (0,0,0)
        bool teclaPressionada;

    // Google Gemini: "c++ pass by ref and pass by pointer"
    //Key Differences
    //Feature         | Pass by Reference                     |Pass by Pointer
    //Syntax          | Uses & in function parameter and                 direct variable name in the call        | Uses * in function parameter and & to get address in the call
    //Null Values     | Cannot be null                        |Can be null, requires null checks
    //Reassignment    | Cannot be reassigned to a different variable
    //Usage           |Preferred for modifying variables directly                                                |Used when null values are possible or reassignment is needed
    //When to Use Which|
    //    Pass by reference:
    //    Use when you want to modify the original variable and null values are not expected. It offers a cleaner syntax.
    //    Pass by pointer:
    //    Use when you need the possibility of null values or when you need to reassign the pointer to a different memory location. It requires more careful handling due to the risk of null pointer dereference.



    public:
        //Teclado(GLFWwindow* window, Transformacoes2D &transf2D, Transformacoes2D &transf2D_ini)
        //Teclado2D(GLFWwindow* window, Transformacoes2D* transf2D, Transformacoes2D* transf2D_ini)
        Teclado2D(GLFWwindow* window, shared_ptr<Transformacoes2D> transf2D, shared_ptr<Transformacoes2D> transf2D_ini)
        {
            this->window = window;
            this->transf2D = transf2D;
            this->transf2D_ini = transf2D_ini;
            this->teclaPressionada = false;
        }

        void avaliaTeclas(){
            const int xEsq = glfwGetKey(this->window, GLFW_KEY_LEFT);
            const int yRot = glfwGetKey(window, GLFW_KEY_Y);
            if (xEsq == GLFW_PRESS) {
                if (yRot == GLFW_PRESS) {
                    teclaPressionada = true;
                    transf2D->setTipoRot(transf2D->getTipoRot() | 2); // Ativa Rotacão eixo Y
                    transf2D->setAnguloY(transf2D->getAnguloY()-0.01);
                }
                else {
                    teclaPressionada = true;
                    transf2D->setXT(transf2D->getXT()-0.01);
                }
            }

            const int xDir = glfwGetKey(window, GLFW_KEY_RIGHT);
            if (xDir == GLFW_PRESS) {
                if (yRot == GLFW_PRESS) {
                    teclaPressionada = true;
                    transf2D->setTipoRot(transf2D->getTipoRot() | 2); // Ativa Rotacão eixo Y
                    transf2D->setAnguloY(transf2D->getAnguloY()+0.01);
                }
                else {
                    teclaPressionada = true;
                    transf2D->setXT(transf2D->getXT()+0.01);
                    //cout << "Diminuindo xT =" << xT << endl;
                }
            }

            const int yUp = glfwGetKey(window, GLFW_KEY_UP);
            const int xRot = glfwGetKey(window, GLFW_KEY_X);
            if (yUp == GLFW_PRESS) {
                if (xRot == GLFW_PRESS) {
                    teclaPressionada = true;
                    transf2D->setTipoRot(transf2D->getTipoRot() | 4); // Ativa Rotacão eixo X
                    transf2D->setAnguloX(transf2D->getAnguloX()-0.01);
                }
                else {
                    teclaPressionada = true;
                    transf2D->setYT(transf2D->getYT()+0.01);
                }
            }

            const int yDown = glfwGetKey(window, GLFW_KEY_DOWN);
            if (yDown == GLFW_PRESS) {
                if (xRot == GLFW_PRESS) {
                    teclaPressionada = true;
                    transf2D->setTipoRot(transf2D->getTipoRot() | 4); // Ativa Rotacão eixo X
                    transf2D->setAnguloX(transf2D->getAnguloX()+0.01);
                }
                else {
                    teclaPressionada = true;
                    transf2D->setYT(transf2D->getYT()-0.01);
                }
            }


            const int reduzEscala = glfwGetKey(window, GLFW_KEY_MINUS);
            if (reduzEscala == GLFW_PRESS) {
                teclaPressionada = true;
                transf2D->setEscala(transf2D->getEscala() - 0.01);
            }

            const int aumentaEscala = glfwGetKey(window, GLFW_KEY_EQUAL);
            if (aumentaEscala == GLFW_PRESS) {
                teclaPressionada = true;
                transf2D->setEscala(transf2D->getEscala() + 0.01);
            }

            const int origemEscala = glfwGetKey(window, GLFW_KEY_8);
            if (origemEscala == GLFW_PRESS) {
                teclaPressionada = true;
                transf2D->setEscala(transf2D_ini->getEscala()); // 1.0;
            }

            const int origemCoord = glfwGetKey(window, GLFW_KEY_9);
            if (origemCoord == GLFW_PRESS) {
                teclaPressionada = true;
                transf2D->setXT(transf2D_ini->getXT()); // 0.0;
                transf2D->setYT(transf2D_ini->getYT()); // 0.0;
            }

            const int zeraRot = glfwGetKey(window, GLFW_KEY_0);
            if (zeraRot == GLFW_PRESS) {
                teclaPressionada = true;
                transf2D->setTipoRot(transf2D_ini->getTipoRot()); // 0;
                transf2D->setAnguloX(transf2D_ini->getAnguloX()); // 0.0;
                transf2D->setAnguloY(transf2D_ini->getAnguloY()); // 0.0;
            }

            if (teclaPressionada) {
                cout << "xT =" << transf2D->getXT() << " | yT =" << transf2D->getYT() << " | tipoRot=" << transf2D->getTipoRot() << "| anguloX=" << transf2D->getAnguloX() <<"| anguloY=" << transf2D->getAnguloY() << " | escala=" << transf2D->getEscala() << endl;
                teclaPressionada = false;
                //cout << "tipoRot & 4=>" << (tipoRot & 4) << " | (tipoRot & 4) == 4 =>" << ((tipoRot & 4) == 4) << " | tipoRot & 4 == 4 =>" << (tipoRot & 4 == 4) << endl; // Debug
                cout << "transf2D.toString() =" << transf2D->toString() << endl;
            }
        }

};

#endif
