// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Computação Gráfica
// Módulo 4
// Tarefa: Atividade Vivencial 2 - Técnica de Iluminação de 3 pontos
// Data: 31/05/2025
// Professor: Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior e Rodrigo Pires
// Registros Acadêmicos: 1930669 e 1917485

#ifndef GRADE2D_H
#define GRADE2D_H

#include <iostream>
#include <memory>

using namespace std;

class Grade2D{

    private:
        //  Linhas Eixos X e Y => 2 + 5 em X+, 5 em X-, 5 em Y+, 5 em Y- ==> 20 Linhas ==> Total 22 Linhas = 44 Vértices
        static const int VERT_GRADE10X10 = 700; // 498; //v =498 // 44; --> Se acessar a matriz vertices além do indice final gera: Program terminated with signal SIGBUS, Bus error.

        //Shader* shaderGrade2D; // Precisa ser um ponteiro para poder manter a classe só como '.h' // Dá erro: Process terminating with default action of signal 11 (SIGSEGV) ==73082==  Access not within mapped region at address 0x0
        unique_ptr<Shader> shaderGrade2D;
        int nVertices;
        unsigned int VAO;


    public:
        Grade2D() {
            // Cria o shader:
            //Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
            //*shaderGrade2D = Shader("./shader_grade2D.vs", "./shader_grade2D.fs");
            //*shaderGrade2D = Shader("../Grade2D/shader_grade2D.vs", "../Grade2D/shader_grade2D.fs"); // Ajuste para uso em 'teste.cpp'
            shaderGrade2D = make_unique<Shader>("Grade2D/shader_grade2D.vs", "Grade2D/shader_grade2D.fs");
            // Cria o VAO:
            VAO = criarGrade10x10(nVertices);

        }



        //  Linhas Eixos X e Y => 2 + 5 em X+, 5 em X-, 5 em Y+, 5 em Y- ==> 20 Linhas ==> Total 22 Linhas = 44 Vértices
        unsigned int criarGrade10x10(int &nVertices) {
            float vertices[VERT_GRADE10X10]; // Virou uma matriz local em vez de atributo da classe para que essa função pudesse ser chamada como 'static' -- O que não tem mais muito sentido agora que cada objeto ganhou a sua própria classe com seus VAOs e DrawCalls

            // Inicializa a matriz vertices para evitar "confusões" em caso de acesso à memória que não foi inicializada !
            for (int i0 = 0; i0 < VERT_GRADE10X10; i0++) {
                vertices [i0] = 0.0;
            }

            // Eixo X e Y:
            //         V4
            //         |
            //         |
            // V0------V1------V2
            //         |
            //         |
            //         V3
            vertices [0] = -1.0; // X do V0
            vertices [1] = 0.0; // Y do V0
            vertices [2] = 0.0; // Z do V0
            vertices [3] = 0.0; // R do V0
            vertices [4] = 0.0; // G do V0
            vertices [5] = 1.0; // B do V0

            vertices [6] = 0.0; // X do V1
            vertices [7] = 0.0; // Y do V1
            vertices [8] = 0.0; // Z do V1
            vertices [9] = 1.0; // R do V1
            vertices [10] = 1.0; // G do V1
            vertices [11] = 1.0; // B do V1

            vertices [12] = 0.0; // X do V1
            vertices [13] = 0.0; // Y do V1
            vertices [14] = 0.0; // Z do V1
            vertices [15] = 1.0; // R do V1
            vertices [16] = 1.0; // G do V1
            vertices [17] = 1.0; // B do V1

            vertices [18] = 1.0; // X do V2
            vertices [19] = 0.0; // Y do V2
            vertices [20] = 0.0; // Z do V2
            vertices [21] = 1.0; // R do V2
            vertices [22] = 0.0; // G do V2
            vertices [23] = 0.0; // B do V2

            vertices [24] = 0.0; // X do V3
            vertices [25] = -1.0; // Y do V3
            vertices [26] = 0.0; // Z do V3
            vertices [27] = 0.0; // R do V3
            vertices [28] = 1.0; // G do V3
            vertices [29] = 0.0; // B do V3

            vertices [30] = 0.0; // X do V1
            vertices [31] = 0.0; // Y do V1
            vertices [32] = 0.0; // Z do V1
            vertices [33] = 1.0; // R do V1
            vertices [34] = 1.0; // G do V1
            vertices [35] = 1.0; // B do V1

            vertices [36] = 0.0; // X do V1
            vertices [37] = 0.0; // Y do V1
            vertices [38] = 0.0; // Z do V1
            vertices [39] = 1.0; // R do V1
            vertices [40] = 1.0; // G do V1
            vertices [41] = 1.0; // B do V1

            vertices [42] = 0.0; // X do V4
            vertices [43] = 1.0; // Y do V4
            vertices [44] = 0.0; // Z do V4
            vertices [45] = 1.0; // R do V4
            vertices [46] = 1.0; // G do V4
            vertices [47] = 0.0; // B do V4

            // Linhas que cruzam o eixo X:
            int v = 48;
            for (float x=-1.0; x<=1.0; x+=0.1) {
                vertices [v] = x; // X do VY-
                vertices [v+1] = -1.0; // Y do VY-
                vertices [v+2] = 0.0; // Z do VY-
                vertices [v+3] = 1.0; // R do VY-
                vertices [v+4] = 1.0; // G do VY-
                vertices [v+5] = 1.0; // B do VY-

                vertices [v+6] = x; // X do VY+
                vertices [v+7] = 1.0; // Y do VY+
                vertices [v+8] = 0.0; // Z do VY+
                vertices [v+9] = 1.0; // R do VY+
                vertices [v+10] = 1.0; // G do VY+
                vertices [v+11] = 1.0; // B do VY+

                v += 12;
            }

            // Linhas que cruzam o eixo Y:
            for (float y=-1.0; y<=1.0; y+=0.1) {
                vertices [v] = -1.0; // X do VX-
                vertices [v+1] = y; // Y do VX-
                vertices [v+2] = 0.0; // Z do VX-
                vertices [v+3] = 1.0; // R do VX-
                vertices [v+4] = 1.0; // G do VX-
                vertices [v+5] = 1.0; // B do VX-

                vertices [v+6] = 1.0; // X do VX+
                vertices [v+7] = y; // Y do VX+
                vertices [v+8] = 0.0; // Z do VX+
                vertices [v+9] = 1.0; // R do VX+
                vertices [v+10] = 1.0; // G do VX+
                vertices [v+11] = 1.0; // B do VX+

                v += 12;
            }

            v = v-12; // Ajuste do incremento final dentro do loop acima

            cout << "v =" << v << endl;

            unsigned int VAO; // Vertex Array Object
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            unsigned int VBO; // Vertex Buffer Objects -> armazena os buffers de vértices na memória da GPU
            glGenBuffers(1, &VBO); // Gera um buffer com a ID do VBO -- seria a ID 1 ? ==> PERGUNTAR !

            glBindBuffer(GL_ARRAY_BUFFER, VBO); // Define que o tipo de buffer do VBO vai ser um buffer de arrays

            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copia o buffer da RAM(vertices[]) para a memória da GPU


            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Não precisa modificar aqui se o número de triângulos (vértices de triângulos a serem lidos) aumentar
            // Explica para o OpenGL como interpretar os dados do vértice // 6 * sizeof(float) ==> stride = avanço | (void*)0 ==> offset -- como o deslocamento é 0 (deve iniciar a leitura no índice 0 do buffer) fica 0 // Isso tudo é gravado no VAO
            //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0); // Isso tudo é gravado no VAO

            //Atributo Cor (r, g, b)
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
            glEnableVertexAttribArray(1);


            // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
            // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
            glBindVertexArray(0);

            nVertices = VERT_GRADE10X10/6;

            return VAO;
        }

        void desenhar(){
            shaderGrade2D->use();
            glBindVertexArray(VAO);
            glDrawArrays(GL_LINES, 0, nVertices);

        }
};

#endif
