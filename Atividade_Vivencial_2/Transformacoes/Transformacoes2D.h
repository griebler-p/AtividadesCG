
#ifndef TRANSFORMACOES2D_H
#define TRANSFORMACOES2D_H

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Transformacoes2D{
    private:
        // Variáveis de transformação:
        float xT = 0.0;
        float yT = 0.0;

        int tipoRot = 0; // Em binário !!!
        // 0 -> 0000_0000 -> nenhuma rotação
        // 1 -> 0000_0001 -> rotação eixo Z => tipoRot & 1 => se for 1 tem rotação no eixo Z ==> NÃO USADA PARA 2D !
        // 2 -> 0000_0010 -> rotação eixo Y => tipoRot & 2 => se for 2 tem rotação no eixo Y
        // 3 -> 0000_0011 -> rotação eixo Y e Z ==> NÃO USADA PARA 2D !
        // 4 -> 0000_0100 -> rotação eixo X => tipoRot & 4 => se for 4 tem rotação no eixo X
        // 5 -> 0000_0101 -> rotação eixo X e Z ==> NÃO USADA PARA 2D !
        // 6 -> 0000_0110 -> rotação eixo Y e Z ==> NÃO USADA PARA 2D !
        // 7 -> 0000_0111 -> rotação eixo X e Y ==> MODIFICADA PARA 2D !
        // Para ativar a rotação nos eixos:
        // rotação eixo Z => tipoRot | 1 ==> NÃO USADA PARA 2D !
        // rotação eixo Y => tipoRot | 2
        // rotação eixo X => tipoRot | 4

        float anguloX = 0.0;
        float anguloY = 0.0;

        float escala = 1.0;


    public:
        Transformacoes2D(){
            this->xT = 0.0;
            this->yT = 0.0;
            this->tipoRot = 0;
            this->anguloX = 0.0;
            this->anguloY = 0.0;
            this->escala = 0.0;
        }


        Transformacoes2D(float xT, float yT, int tipoRot, float anguloX, float anguloY, float escala) {
            this->xT = xT;
            this->yT = yT;
            this->tipoRot = tipoRot;
            this->anguloX = anguloX;
            this->anguloY = anguloY;
            this->escala = escala;
        }

        Transformacoes2D clonar(){
            Transformacoes2D oN = Transformacoes2D();

            oN.xT = this->xT;
            oN.yT = this->yT;
            oN.tipoRot = this->tipoRot;
            oN.anguloX = this->anguloX;
            oN.anguloY = this->anguloY;
            oN.escala = this->escala;
            return oN;
        }

        void setXT(float xT){
            this->xT = xT;
        }
        float getXT(){
            return xT;
        }
        void setYT(float yT){
            this->yT = yT;
        }
        float getYT(){
            return yT;
        }

        void setTipoRot(int tipoRot){
            this->tipoRot = tipoRot;
        }
        int getTipoRot(){
            return tipoRot;
        }

        void setAnguloX(float anguloX){
            this->anguloX = anguloX;
        }
        float getAnguloX(){
            return anguloX;
        }
        void setAnguloY(float anguloY){
            this->anguloY = anguloY;
        }
        float getAnguloY(){
            return anguloY;
        }

        void setEscala(float escala){
            this->escala = escala;
        }
        float getEscala(){
            return escala;
        }

        glm::mat4 calculaTransformacoes(){

            // create transformations para triângulo 1
            //glm::mat4 transform1 = glm::mat4(1.0f);
            glm::mat4 transform1 = glm::mat4(1.0f);// make sure to initialize matrix to identity matrix first

            //transform1 = glm::translate(transform1, glm::vec3(xT, yT, 1));// NÃO PODE SER 1 NO Z QUANDO É 2D SENÃO NÃO APARECE NADA NA TELA !
            transform1 = glm::translate(transform1, glm::vec3(xT, yT, 0));// ###IMPORTANTE:  A translação deve ser a última operação a ser realizada para evitar deformações na imagem !!! --- Informação ainda não confirmada na prática ! -- Dica dada pelo professor Tonietto

            //Model = glm::rotate(Model, angle_in_radians, glm::vec3(x, y, z)); // where x, y, z is axis of rotation (e.g. 0 1 0)

            //if (tipoRot & 4 == 4) {//Pq | (tipoRot & 4) == 4 =>1 | tipoRot & 4 == 4 =>0
            if ((tipoRot & 4) == 4) {// => se for 4 tem rotação no eixo X
                transform1 = glm::rotate(transform1, anguloX, glm::vec3(1, 0, 0));
            }
            if ((tipoRot & 2) == 2) {// => se for 2 tem rotação no eixo Y
                transform1 = glm::rotate(transform1, anguloY, glm::vec3(0, 1, 0));
            }

            //if (escala != 1.0) {// => Se tiver alteração no fator de escala, faz a transformação
                //modelview = glm::scale( modelview, glm::vec3(Scale,Scale,Scale) )
            transform1 = glm::scale(transform1, glm::vec3(escala, escala, escala));

            return transform1;
        }

        void imprimeAsTransformacoes(glm::mat4 matriz) {
            for (int i =0; i<16; i++){ // mat4 => matriz 4x4
                    //cout << "transform0[" << i << "] =" << transform0[i] << endl; // error: no match for ‘operator<<’ (operand types are ‘std::basic_ostream<char>’ and ‘glm::mat<4, 4, float, glm::packed_highp>::col_type’ {aka ‘glm::vec<4, float, glm::packed_highp>’})
                    //cout << "&transform0[0][" << i << "] =" << &transform0[0][i] << endl; OK funciona ! --> &transform0[0][0] =0x7ffdce693740
                    //cout << "*transform0[0][" << i << "] =" << *transform0[0][i] << endl; // error: invalid type argument of unary ‘*’ (have ‘float’)
                    cout << "mat4[" << (i/4) << "][" << (i%4) << "] =" << matriz[i/4][i%4] << endl;
                }
        }

        string toString(){
            string s = "Transformacoes2D: [";
            s += "xT: ";
            s += to_string(xT);
            s += ", yT: ";
            s += to_string(yT);

            s += ", tipoRot: ";
            s += to_string(tipoRot);

            s += ", anguloX: ";
            s += to_string(anguloX);
            s += ", anguloY: ";
            s += to_string(anguloY);

            s += ", escala: ";
            s += to_string(escala);

            s += "]";
            return s;

        }
};

#endif
