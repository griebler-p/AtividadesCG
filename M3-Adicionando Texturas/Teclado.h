#include <glad/glad.h> // É necessário que a inclusão do glad.h seja feita antes da inclusão do glfw3 -- aliás o glad.h precisa ser incluído ANTES de qualquer outro arquivo cabeçalho que use os arquivos cabeçalhos do OpenGL (tipo GL/gl.h)
#include <GLFW/glfw3.h>


class Teclado{
    private:
        GLFWwindow* window;
        //Objeto3D obj3D;
        //Objeto3D obj3D_ini;
        Objeto3D* obj3D; // Mudei para ponteiro pq não está dando certo a pasagem por referência -- será que é pq não tem o arquivo 'Teclado.cpp' ???
        Objeto3D* obj3D_ini;// Configurações do Objeto3D na sua 1° inicialização - útil para quando for zerar as transformações ele volte para a sua posição inicial e não para a coordenada (0,0,0)
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
        //Teclado(GLFWwindow* window, Objeto3D &obj3D, Objeto3D &obj3D_ini)
        Teclado(GLFWwindow* window, Objeto3D* obj3D, Objeto3D* obj3D_ini)
        {
            this->window = window;
            this->obj3D = obj3D;
            this->obj3D_ini = obj3D_ini;
            this->teclaPressionada = false;
        }

        void avaliaTeclas(){
            const int xEsq = glfwGetKey(this->window, GLFW_KEY_LEFT);
            const int yRot = glfwGetKey(window, GLFW_KEY_Y);
            if (xEsq == GLFW_PRESS) {
                if (yRot == GLFW_PRESS) {
                    teclaPressionada = true;
                    obj3D->setTipoRot(obj3D->getTipoRot() | 2); // Ativa Rotacão eixo Y
                    obj3D->setAnguloY(obj3D->getAnguloY()-0.01);
                }
                else {
                    teclaPressionada = true;
                    obj3D->setXT(obj3D->getXT()-0.01);
                }
            }

            const int xDir = glfwGetKey(window, GLFW_KEY_RIGHT);
            if (xDir == GLFW_PRESS) {
                if (yRot == GLFW_PRESS) {
                    teclaPressionada = true;
                    obj3D->setTipoRot(obj3D->getTipoRot() | 2); // Ativa Rotacão eixo Y
                    obj3D->setAnguloY(obj3D->getAnguloY()+0.01);
                }
                else {
                    teclaPressionada = true;
                    obj3D->setXT(obj3D->getXT()+0.01);
                    //cout << "Diminuindo xT =" << xT << endl;
                }
            }

            const int yUp = glfwGetKey(window, GLFW_KEY_UP);
            const int xRot = glfwGetKey(window, GLFW_KEY_X);
            if (yUp == GLFW_PRESS) {
                if (xRot == GLFW_PRESS) {
                    teclaPressionada = true;
                    obj3D->setTipoRot(obj3D->getTipoRot() | 4); // Ativa Rotacão eixo X
                    obj3D->setAnguloX(obj3D->getAnguloX()-0.01);
                }
                else {
                    teclaPressionada = true;
                    obj3D->setYT(obj3D->getYT()+0.01);
                }
            }

            const int yDown = glfwGetKey(window, GLFW_KEY_DOWN);
            if (yDown == GLFW_PRESS) {
                if (xRot == GLFW_PRESS) {
                    teclaPressionada = true;
                    obj3D->setTipoRot(obj3D->getTipoRot() | 4); // Ativa Rotacão eixo X
                    obj3D->setAnguloX(obj3D->getAnguloX()+0.01);
                }
                else {
                    teclaPressionada = true;
                    obj3D->setYT(obj3D->getYT()-0.01);
                }
            }

            const int zInc = glfwGetKey(window, GLFW_KEY_Q);
            const int zRot = glfwGetKey(window, GLFW_KEY_Z);
            if (zInc == GLFW_PRESS) {
                if (zRot == GLFW_PRESS) {
                    teclaPressionada = true;
                    obj3D->setTipoRot(obj3D->getTipoRot() | 1); // Ativa Rotacão eixo Z
                    obj3D->setAnguloZ(obj3D->getAnguloZ()-0.01);
                }
                else {
                    teclaPressionada = true;
                    obj3D->setZT(obj3D->getZT()+0.01);
                }
            }

            const int zDec = glfwGetKey(window, GLFW_KEY_A);
            if (zDec == GLFW_PRESS) {
                if (zRot == GLFW_PRESS) {
                    teclaPressionada = true;
                    obj3D->setTipoRot(obj3D->getTipoRot() | 1); // Ativa Rotacão eixo Z
                    obj3D->setAnguloZ(obj3D->getAnguloZ()+0.01);
                }
                else {
                    teclaPressionada = true;
                    obj3D->setZT(obj3D->getZT()-0.01);
                }
            }

            const int reduzEscala = glfwGetKey(window, GLFW_KEY_MINUS);
            if (reduzEscala == GLFW_PRESS) {
                teclaPressionada = true;
                obj3D->setEscala(obj3D->getEscala() - 0.01);
            }

            const int aumentaEscala = glfwGetKey(window, GLFW_KEY_EQUAL);
            if (aumentaEscala == GLFW_PRESS) {
                teclaPressionada = true;
                obj3D->setEscala(obj3D->getEscala() + 0.01);
            }

            const int origemEscala = glfwGetKey(window, GLFW_KEY_8);
            if (origemEscala == GLFW_PRESS) {
                teclaPressionada = true;
                obj3D->setEscala(obj3D_ini->getEscala()); // 1.0;
            }

            const int origemCoord = glfwGetKey(window, GLFW_KEY_9);
            if (origemCoord == GLFW_PRESS) {
                teclaPressionada = true;
                obj3D->setXT(obj3D_ini->getXT()); // 0.0;
                obj3D->setYT(obj3D_ini->getYT()); // 0.0;
                obj3D->setZT(obj3D_ini->getZT()); // 0.0;
            }

            const int zeraRot = glfwGetKey(window, GLFW_KEY_0);
            if (zeraRot == GLFW_PRESS) {
                teclaPressionada = true;
                obj3D->setTipoRot(obj3D_ini->getTipoRot()); // 0;
                obj3D->setAnguloX(obj3D_ini->getAnguloX()); // 0.0;
                obj3D->setAnguloY(obj3D_ini->getAnguloY()); // 0.0;
                obj3D->setAnguloZ(obj3D_ini->getAnguloZ()); // 0.0;
            }

            if (teclaPressionada) {
                cout << "xT =" << obj3D->getXT() << " | yT =" << obj3D->getYT() << " | zT=" << obj3D->getZT() << " | tipoRot=" << obj3D->getTipoRot() << "| anguloX=" << obj3D->getAnguloX() <<"| anguloY=" << obj3D->getAnguloY() << "| anguloZ=" << obj3D->getAnguloZ() << " | escala=" << obj3D->getEscala() << endl;
                teclaPressionada = false;
                //cout << "tipoRot & 4=>" << (tipoRot & 4) << " | (tipoRot & 4) == 4 =>" << ((tipoRot & 4) == 4) << " | tipoRot & 4 == 4 =>" << (tipoRot & 4 == 4) << endl; // Debug
                cout << "obj3D.toString() =" << obj3D->toString() << endl;
            }
        }

};
