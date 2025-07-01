#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include "loadSimpleObj.h" // Não usado para o programa do cubo3D

using namespace std;

class Objeto3D{
    private:
        string nome;
        unsigned int VAO; // VAO deste objeto3D
        int nVertices; // Número de vértices do objeto -- necessário para indicar em 'glDrawArrays' o número de vértices que devem ser desenhados -- glDrawArrays(GL_TRIANGLES, 0, nVertices);
        string caminhoArquivo;

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


    public:
        Objeto3D(); // Para evitar os erros onde o Objeto3D é um parâmetro de outra classe -- Ex.:  error: no matching function for call to ‘Objeto3D::Objeto3D() --  ao chamar: Teclado(GLFWwindow* window, Objeto3D &obj3D, Objeto3D &obj3D_ini)

        // Construtor que não carrega objetos -- usa definição direto no main de VAOs
        Objeto3D(string nome, float xT, float yT, float zT, int tipoRot, float anguloX, float anguloY, float anguloZ, float escala);

        Objeto3D(string nome, string caminhoArquivo, float xT, float yT, float zT, int tipoRot, float anguloX, float anguloY, float anguloZ, float escala);

        Objeto3D clonar();

        string getNome();

        int getVAO();
        //void setVAO(int VAO); // Deletar ?

        int getNVertices();
        //void setNVertices(int nVertices); // Deletar ?

        string getCaminhoArquivo();
        //void setCaminhoArquivo(string caminhoArquivo); // Deletar ?

        void setXT(float xT);
        float getXT();
        void setYT(float yT);
        float getYT();
        void setZT(float zT);
        float getZT();

        void setTipoRot(int tipoRot);
        int getTipoRot();

        void setAnguloX(float anguloX);
        float getAnguloX();
        void setAnguloY(float anguloY);
        float getAnguloY();
        void setAnguloZ(float anguloZ);
        float getAnguloZ();

        void setEscala(float escala);
        float getEscala();

        //Só preciso devolver para 'main' o resultado final das transformações que é o que vai ser 'injetado' no vertex shader na variavel 'transform' em:
        //  gl_Position = transform * vec4(aPos, 1.0);
        // @return: - glm::mat4 - o resultado final das transformações para este objeto3D
        glm::mat4 calculaTransformacoes();
        void imprimeATransformacao(glm::mat4 matriz);

        string toString();


};
