// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Computação Gráfica
// Módulo 4
// Tarefa: Atividade Vivencial 2 - Técnica de Iluminação de 3 pontos
// Data: 31/05/2025
// Professor: Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior e Rodrigo Pires
// Registros Acadêmicos: 1930669 e 1917485

#include <vector>

#include "../Aux.h"

using namespace std;

pthread_mutex_t mutex_planeta3d; // Permite realizar a exclusão mútua na área crítica de código das threads

// VARIÁVEIS GLOBAIS COMPARTILHADAS ENTRE AS THREADS:
extern float comp_xT_0; // Variáveis globais não tem por convenção em C/C++ serem escritas com maiúsculas, exceto se forem constantes
extern float comp_yT_0;
extern float comp_zT_0;
extern int   comp_tipoRot_0;
extern float comp_anguloX_0;
extern float comp_anguloY_0;
extern float comp_anguloZ_0;
extern float comp_escala_0;

extern float comp_obj0_cor_r;
extern float comp_obj0_cor_g;
extern float comp_obj0_cor_b;

// Câmera:
extern float comp_xT_cam;
extern float comp_yT_cam;
extern float comp_zT_cam;
extern float comp_anguloX_cam;
extern float comp_anguloY_cam;
extern float comp_anguloZ_cam;

extern bool comp_luz0_ligada;
extern float comp_luz0_cor_r;
extern float comp_luz0_cor_g;
extern float comp_luz0_cor_b;

extern bool comp_luz1_ligada;
extern float comp_luz1_cor_r;
extern float comp_luz1_cor_g;
extern float comp_luz1_cor_b;

extern bool comp_luz2_ligada;
extern float comp_luz2_cor_r;
extern float comp_luz2_cor_g;
extern float comp_luz2_cor_b;


class Planeta3D{
// Como calcular os vértices de um planeta ?
    // - raio
    // - intervalo em graus entre os círculos de latitude (graus do eixo Y)
    // - intervalo em graus entre os círculos de longitude (graus do eixo Z) --> intZ =

    // - começe desenhando um círculo no eixo variando X e Y e sendo o eixo Z = 0 - círculo perfeito
    // - faça com que a extremidade deste círculo em X-R(R de raio) seja desenhada na coordenada Z-graus de intervalo, enquanto que a X+R seja desenhada com Z+graus de intervalo

    //     cat. adj.
    //     ____
    // cat.| °/ <-ângulo
    // opo.| / <-hipotenusa
    //     |/

    //          cat.op      --> pq o seno começa em 0 (0°) e vai subindo até 1 (90°)
    // sin =    __________
    //          hipotenusa


    /*// Planeta visto de lado (lado esq.)

    //          ^+
    //          | _
    //    eixo Y|  /)
    //          | /  )
    //          |/°   )
    //----------------------> +  < Observador
    //          |       eixo Z
    // o seno define o comprimento do eixo Y
    // o cosseno define o comprimento do eixo Z

    // Planeta visto de frente

    //          ^+
    //          | _
    //    eixo Y|  /)
    //          | /  )
    //          |/°   )
    //---------------------->+
    //          |       eixo X
    // o seno define o comprimento do eixo Y
    // o cosseno define o comprimento do eixo X



    float x, y, z;

    // Variando o ângulo YZ de 90 à -90°: -- Obtêm
    //for (float angYZ = (90*PI)/180; angYZ < (-90*PI)/180; angYZ = angYZ - (5*PI)/180) {
    for (float angYZ = radianos(90); angYZ < radianos(-90); angYZ = angYZ - radianos(5)) { // 1º varia a latitude -- manter nº de passos par
        z = cos(angYZ);
        y = sin(angYZ);
        // Variando o ângulo YX de -90 à -90
        for (float angYX = radianos(90); angYX < radianos(-90); angYX = angYX - radianos(5) { // 2º para cada latitude calcula as longitudes
            x = cos(angYX);
        }
    }*/

    // NOVA ABORDAGEM: CÍRCULOS CONCÊNTRICOS DE RAIOS CRESCENTES REDUZINDO O EIXO Y

    // POR EXEMPLO: r = 100px

    //   () --> CÍRCULO 0 - r = 10 y = 100-r = 90

    //   ()
    //  (  ) --> CÍRCULO 1 - r = 20 y = 100-r = 80
    //   ()

    //   ()
    //  (  )
    // (    ) --> CÍRCULO 2 r = 30 y = 100-r = 70
    //  (  )
    //   ()
    private:
        //const int CIRC_T0 = 20; // error: invalid use of non-static data member ‘Planeta3D::CIRC_T0’
        static const int CIRC_T0 = 37; // ay =-1.57076 | ax =6.12596 | cir =36 | pos =39 | rc =0.00392954 --> última linha de preenchimento das matrizes
        static const int CIRC_T1 = 40;
        static const int CIRC_T2 = 4;
        float circulos[CIRC_T0][CIRC_T1][CIRC_T2]; // circulos [0][0][0] --> coordenada X do 1º ponto do 1º círculo

        const float r_f = 100.0; // Raio final (máximo) - do maior círculo
        float rc = 0.0; // raio do círculo (deitado) em questão
        int cir_f = 0; // Número total de círculos criados
        int pos_f = 0; // Número total de posições do círculo
        int cir = 0; // Contador de círculos criados
        int pos = 0; // Contador de posições do círculo

        static const int VERT_T = 53280; //vert =53280 //vert =26676 //vert =6840
        float vertices[VERT_T];
        unsigned int VAO; // Vertex Array Object
        int nVertices;

        unique_ptr<Shader> shaderPlaneta3D;
        shared_ptr<Transformacoes3D> transf3D_pla;
        shared_ptr<Transformacoes3D> transf3D_pla_ini;
        unique_ptr<Teclado3D> tec3D_pla;

        unique_ptr<Shader> shaderLuz;
        shared_ptr<Transformacoes3D> transf3D_luz0;
        shared_ptr<Transformacoes3D> transf3D_luz1;
        shared_ptr<Transformacoes3D> transf3D_luz2;

        glm::mat4 projection;


    public:
        Planeta3D(GLFWwindow* window, glm::mat4 projection) {
            this->projection = projection;

            popularCirculos();
            popularVertices();
            // Cria o shader:
            shaderPlaneta3D = make_unique<Shader>("Planeta3D/shader_planeta3D.vs", "Planeta3D/shader_planeta3D.fs");
            // Cria o VAO:
            criarVAO();

            //Transformacoes3D(float xT, float yT,floatzT,  int tipoRot, float anguloX, float anguloY,float anguloZ, float escala)
            transf3D_pla = make_shared<Transformacoes3D>(0.0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 0.5);
            transf3D_pla_ini = make_shared<Transformacoes3D>(transf3D_pla->clonar()); // Precisa aqui que seja uma cópia do objeto e não só uma ref. -- para guardar as configurações iniciais do objeto

            //Teclado3D(GLFWwindow* window, Transformacoes3D* transf3D, Transformacoes3D* transf3D_ini)
            tec3D_pla = make_unique<Teclado3D>(window, transf3D_pla, transf3D_pla_ini);

            // Luzes:
            shaderLuz = make_unique<Shader>("Planeta3D/shader_planeta3D.vs", "Planeta3D/shader_luz.fs");

            //Luz principal (key light): É a fonte de luz mais intensa, que ilumina o objeto principal e define o tom geral da cena.
            transf3D_luz0 = make_shared<Transformacoes3D>(-0.9, 0.0, 0.9, 0, 0.0, 0.0, 0.0, 0.05); // Esq./Frente
            //Luz de preenchimento (fill light): Suaviza as sombras criadas pela luz principal, equilibrando a iluminação e evitando que a imagem fique muito contrastada.
            transf3D_luz1 = make_shared<Transformacoes3D>(0.9, 0.0, 0.9, 0, 0.0, 0.0, 0.0, 0.05);// Dir./Frente
            //Luz de fundo (back light): Ilumina o fundo do objeto, criando profundidade e separando-o do fundo.
            transf3D_luz2 = make_shared<Transformacoes3D>(-0.9, 0.0, -0.9, 0, 0.0, 0.0, 0.0, 0.05); // Esq./Atrás




        }

        //float* getCirculos(){
        vector<vector<vector<float>>> getCirculos(){ // Melhor retornar um vector em vez de um ponteiro para array devido ao manejo automático de memória de vector
            vector<vector<vector<float>>> cV0;
            vector<vector<float>> cV1;
            vector<float> cV2;
            for (int i0=0; i0<CIRC_T0; i0++) {
                for (int i1=0; i1<CIRC_T1; i1++) {
                    for (int i2=0; i2<CIRC_T2; i2++) {
                        cV2.push_back(circulos[i0][i1][i2]);
                    }
                    cV1.push_back(cV2);
                }
                cV0.push_back(cV1);
            }
            return cV0;
        }

        vector<float> getVertices(){
            vector<float> vV;
            for (int i0=0; i0<VERT_T; i0++) {
                vV.push_back(vertices[i0]);
            }
            return vV;
        }

        void popularCirculos(){
            // Inicializa a matriz circulos para evitar "confusões" em caso de acesso à memória que não foi inicializada !
            for (int i0 = 0; i0 < CIRC_T0; i0++) {
                for (int i1 = 0; i1 < CIRC_T1; i1++) {
                    for (int i2 = 0; i2 < CIRC_T2; i2++) {
                        circulos [i0][i1][i2] = 0.0;
                    }
                }
            }

            //for (float y = 100.0; y > 0; y=y-10) { // Número de círculos da metade superior da esfera
            //for (float ay = Aux::radianos(90); ay > Aux::radianos(-90); ay=ay-Aux::radianos(10)) {
            for (float ay = Aux::radianos(90); ay > Aux::radianos(-90); ay=ay-Aux::radianos(5)) { // Itera no eixo Y
                //for (float ax = Aux::radianos(0); ax < Aux::radianos(360); ax=ax+Aux::radianos(36))
                for (float ax = Aux::radianos(0); ax < Aux::radianos(360); ax=ax+Aux::radianos(9)) { // Itera de 0 à 6.25 radianos para calcular as coordenadas de um círculo para as variáveis X e Z (círculo visto de cima) -- precisa que o número de passos do for sejam pares para facilitar o encaixe dos quadriláteros/triângulos
                    //rc = r-y; // Assim fica uma pirâmide e não uma esfera
                    rc = cos(ay)*r_f; // Círculo
                    //rc = (sin(ay)*r_f)-r_f; // em formato de 'tenda de circo'
                    //rc = sin(ay)*r_f; // em formato de 'ampulheta'

                    cout << "ay =" << ay << " | ax =" << ax << " | cir =" << cir << " | pos =" << pos << " | rc =" << rc << endl; // Debug
                    circulos [cir][pos][0] = cos(ax)*rc;// Variável x desta posição neste círculo -- considerando o eixo 0º onde num círculo visto de cima (deitado) o eixo X na posição 0º atinge o valor máximo positivo ==> cos(0°)
                    //circulos [cir][pos][1] = Aux::graus(ay)*0.5; // < 1.0 para arredondar mais a esfera (assim está pontiaguda nas pontas) -- Não deu certo, só diminuiu o tamanho da esfera
                    //circulos [cir][pos][1] = r_f - rc; // Gera 2 pirâmides 1 "dentro" da outra !
                    circulos [cir][pos][1] = sin(ay)*r_f; // Bola perfeita !!!
                    circulos [cir][pos][2] = sin(ax)*rc; // Variável z desta posição neste círculo -- para 0º o valor em Z é 0 ==> sin(0º)
                    circulos [cir][pos][3] = ax; // Valor do ângulo em radianos

                    pos++;
                }
                cir++;
                pos_f = pos -1; // -1 pq tem esse pos++  no final do loop que pode superestimar o valor de pos e pegar bytes errados na memória !!!
                pos = 0;
            }
            cir_f = cir -1; // -1 pq tem esse cir++  no final do loop que pode superestimar o valor de pos e pegar bytes errados na memória !!!

            // Mostra os valores no console
            for (int c=0; c <= cir_f; c++) { // Itera pelos círculos
                for (int p=0; p<= pos_f; p++) { // Itera pelas posições
                    cout << "circulos [" << c << "][" << p << "][] =" << circulos[c][p][0] << "|"<< circulos[c][p][1] << "|" << circulos[c][p][2] << "|" << circulos[c][p][3] << "rad" << endl;
                }

            }
        }

        void popularVertices(){
            // Inicializa a matriz vertices para evitar "confusões" em caso de acesso à memória que não foi inicializada !
            for (int i0 = 0; i0 < VERT_T; i0++) {
                vertices [i0] = 0.0;
            }

            int vert = 0;
            for (int c=0; c<=cir_f; c++) { // Itera pelos círculos
                for (int p=0; p<=pos_f; p++) { // Itera pelas posições // Não deve pular de 2 em 2 pq os quadrados devem se encostar
                    // Cria o triângulo superior
                    // V0--V1 // circulos[c]...
                    // |  /
                    // | /
                    // V3     // circulos[c+1]...
                    vertices[vert]   = circulos[c][p][0]/(r_f*1.1); // Coord. X do V0 -- / por 110% do raio para ficar dentro dos limites -1.0 e +1.0
                    vertices[vert+1] = circulos[c][p][1]/(r_f*1.1); // Coord. Y do V0
                    vertices[vert+2] = circulos[c][p][2]/(r_f*1.1); // Coord. Z do V0
                    //vertices[vert+3] =  1.0; // Cor R do V0
                    //vertices[vert+4] =  0.0; // Cor G do V0
                    //vertices[vert+5] =  0.0; // Cor B do V0

                    vertices[vert+6] = circulos[c][p+1][0]/(r_f*1.1); // Coord. X do V1 -- / por 110% do raio para ficar dentro dos limites -1.0 e +1.0
                    vertices[vert+7] = circulos[c][p+1][1]/(r_f*1.1); // Coord. Y do V1
                    vertices[vert+8] = circulos[c][p+1][2]/(r_f*1.1); // Coord. Z do V1
                    //vertices[vert+9] =  1.0; // Cor R do V1
                    //vertices[vert+10] =  0.0; // Cor G do V1
                    //vertices[vert+11] =  0.0; // Cor B do V1


                    vertices[vert+12] = circulos[c+1][p][0]/(r_f*1.1); // Coord. X do V3 -- / por 110% do raio para ficar dentro dos limites -1.0 e +1.0
                    vertices[vert+13] = circulos[c+1][p][1]/(r_f*1.1); // Coord. Y do V3
                    vertices[vert+14] = circulos[c+1][p][2]/(r_f*1.1); // Coord. Z do V3
                    //vertices[vert+15] =  1.0; // Cor R do V3
                    //vertices[vert+16] =  0.0; // Cor G do V3
                    //vertices[vert+17] =  0.0; // Cor B do V3

                    // Calcula a Normal usando 2 vertices em sentido horário (no caso do triângulo superior V0 -> V1):
                    float prodVet[3]; // Matriz não inicializada -- Problema ???
                    //static void produtoVetorial(float a1, float a2, float a3, float b1, float b2, float b3, float &c1, float&c2, float&c3) { // 'Cross Product'
                    Aux::produtoVetorial(vertices[vert], vertices[vert+1], vertices[vert+2], vertices[vert+6], vertices[vert+7], vertices[vert+8], prodVet[0], prodVet[1], prodVet[2]);

                    //static float moduloVetor(float a1, float a2, float a3) { // |N|
                    float moduloV = Aux::moduloVetor(prodVet[0], prodVet[1], prodVet[2]);

                    float normalVet[3]; // Matriz não inicializada -- Problema ???
                    //static void normalizacaoDaNormal(float a1, float a2, float a3, float moduloV, float &b1, float &b2, float &b3) { // N/|N| -> produto vetorial / módulo do vetor do produto vetorial
                    Aux::normalizacaoDaNormal(prodVet[0], prodVet[1], prodVet[2], moduloV, normalVet[0], normalVet[1], normalVet[2]);

                    // Preenche as normais dos vértices:
                    vertices[vert+3] = normalVet[0]; // Normal do Triângulo Sup. para V0
                    vertices[vert+4] = normalVet[1]; // Normal do Triângulo Sup. para V0
                    vertices[vert+5] = normalVet[2]; // Normal do Triângulo Sup. para V0

                    vertices[vert+9] = normalVet[0]; // Normal do Triângulo Sup. para V1
                    vertices[vert+10] = normalVet[1]; // Normal do Triângulo Sup. para V1
                    vertices[vert+11] = normalVet[2]; // Normal do Triângulo Sup. para V1

                    vertices[vert+15] = normalVet[0]; // Normal do Triângulo Sup. para V3
                    vertices[vert+16] = normalVet[1]; // Normal do Triângulo Sup. para V3
                    vertices[vert+17] = normalVet[2]; // Normal do Triângulo Sup. para V3

                    // Cria o triângulo inferior
                    //     V1 // circulos[c]...
                    //    / |
                    //   /  |
                    // V3--V2 // circulos[c+1]...
                    vertices[vert+18] = circulos[c][p+1][0]/(r_f*1.1); // Coord. X do V1 -- / por 110% do raio para ficar dentro dos limites -1.0 e +1.0
                    vertices[vert+19] = circulos[c][p+1][1]/(r_f*1.1); // Coord. Y do V1
                    vertices[vert+20] = circulos[c][p+1][2]/(r_f*1.1); // Coord. Z do V1
                    //vertices[vert+21] =  1.0; // Cor R do V1
                    //vertices[vert+22] =  1.0; // Cor G do V1
                    //vertices[vert+23] =  0.0; // Cor B do V1

                    vertices[vert+24] = circulos[c+1][p+1][0]/(r_f*1.1); // Coord. X do V2 -- / por 110% do raio para ficar dentro dos limites -1.0 e +1.0
                    vertices[vert+25] = circulos[c+1][p+1][1]/(r_f*1.1); // Coord. Y do V2
                    vertices[vert+26] = circulos[c+1][p+1][2]/(r_f*1.1); // Coord. Z do V2
                    //vertices[vert+27] =  1.0; // Cor R do V1
                    //vertices[vert+28] =  1.0; // Cor G do V1
                    //vertices[vert+29] =  0.0; // Cor B do V1

                    vertices[vert+30] = circulos[c+1][p][0]/(r_f*1.1); // Coord. X do V3 -- / por 110% do raio para ficar dentro dos limites -1.0 e +1.0
                    vertices[vert+31] = circulos[c+1][p][1]/(r_f*1.1); // Coord. Y do V3
                    vertices[vert+32] = circulos[c+1][p][2]/(r_f*1.1); // Coord. Z do V3
                    //vertices[vert+33] =  1.0; // Cor R do V3
                    //vertices[vert+34] =  1.0; // Cor G do V3
                    //vertices[vert+35] =  0.0; // Cor B do V3

                    // Calcula a Normal usando 2 vertices em sentido horário (no caso do triângulo inferior V1 -> V2):
                    //float prodVet[3]; // Matriz não inicializada -- Problema ???
                    //static void produtoVetorial(float a1, float a2, float a3, float b1, float b2, float b3, float &c1, float&c2, float&c3) { // 'Cross Product'
                    Aux::produtoVetorial(vertices[vert+18], vertices[vert+19], vertices[vert+20], vertices[vert+24], vertices[vert+25], vertices[vert+26], prodVet[0], prodVet[1], prodVet[2]);

                    //static float moduloVetor(float a1, float a2, float a3) { // |N|
                    moduloV = Aux::moduloVetor(prodVet[0], prodVet[1], prodVet[2]);

                    //float normalVet[3]; // Matriz não inicializada -- Problema ???
                    //static void normalizacaoDaNormal(float a1, float a2, float a3, float moduloV, float &b1, float &b2, float &b3) { // N/|N| -> produto vetorial / módulo do vetor do produto vetorial
                    Aux::normalizacaoDaNormal(prodVet[0], prodVet[1], prodVet[2], moduloV, normalVet[0], normalVet[1], normalVet[2]);

                    // Preenche as normais dos vértices:
                    vertices[vert+21] = normalVet[0]; // Normal do Triângulo Sup. para V0
                    vertices[vert+22] = normalVet[1]; // Normal do Triângulo Sup. para V0
                    vertices[vert+23] = normalVet[2]; // Normal do Triângulo Sup. para V0

                    vertices[vert+27] = normalVet[0]; // Normal do Triângulo Sup. para V1
                    vertices[vert+28] = normalVet[1]; // Normal do Triângulo Sup. para V1
                    vertices[vert+29] = normalVet[2]; // Normal do Triângulo Sup. para V1

                    vertices[vert+33] = normalVet[0]; // Normal do Triângulo Sup. para V3
                    vertices[vert+34] = normalVet[1]; // Normal do Triângulo Sup. para V3
                    vertices[vert+35] = normalVet[2]; // Normal do Triângulo Sup. para V3


                    cout << "vertices [" << vert << "] do T Sup. - V0 =" << vertices[vert] << "|" << vertices[vert+1] << "|" << vertices[vert+2] << "| c =" << c << "|" << circulos[c][p][3] << "rad" << endl;
                    cout << "vertices [" << vert << "] do T Sup. - V1 =" << vertices[vert+6] << "|" << vertices[vert+7] << "|" << vertices[vert+8] << "|" << circulos[c][p+1][3] << "rad" << endl;
                    cout << "vertices [" << vert << "] do T Sup. - V3 =" << vertices[vert+12] << "|" << vertices[vert+13] << "|" << vertices[vert+14] << "|" << circulos[c+1][p][3] << "rad" << endl;

                    cout << "vertices [" << vert << "] do T Sup. - NORMAL V0*V1 =" << vertices[vert+3] << "|" << vertices[vert+4] << "|" << vertices[vert+5] << endl;

                    cout << "vertices [" << vert << "] do T Inf. - V1 =" << vertices[vert+18] << "|" << vertices[vert+19] << "|" << vertices[vert+20] << endl;
                    cout << "vertices [" << vert << "] do T Inf. - V2 =" << vertices[vert+24] << "|" << vertices[vert+25] << "|" << vertices[vert+26] << endl;
                    cout << "vertices [" << vert << "] do T Inf. - V3 =" << vertices[vert+30] << "|" << vertices[vert+31] << "|" << vertices[vert+32] << endl;

                    cout << "vertices [" << vert << "] do T Inf. - NORMAL V1*V2 =" << vertices[vert+21] << "|" << vertices[vert+22] << "|" << vertices[vert+23] << endl;

                    vert += 36;
                }
            }

            cout << "vert =" << vert << endl; // vert =13320
        }

        //unsigned int criarVAO(int &nVertices) {
        void criarVAO() {
            //unsigned int VAO; // Vertex Array Object
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            unsigned int VBO; // Vertex Buffer Objects -> armazena os buffers de vértices na memória da GPU
            glGenBuffers(1, &VBO); // Gera um buffer com a ID do VBO -- seria a ID 1 ? ==> PERGUNTAR !

            glBindBuffer(GL_ARRAY_BUFFER, VBO); // Define que o tipo de buffer do VBO vai ser um buffer de arrays

            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copia o buffer da RAM(vertices[]) para a memória da GPU


            //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Não precisa modificar aqui se o número de triângulos (vértices de triângulos a serem lidos) aumentar
            // Explica para o OpenGL como interpretar os dados do vértice // 6 * sizeof(float) ==> stride = avanço | (void*)0 ==> offset -- como o deslocamento é 0 (deve iniciar a leitura no índice 0 do buffer) fica 0 // Isso tudo é gravado no VAO
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0); // Isso tudo é gravado no VAO

            //Atributo Normal (nX, nY, nZ)
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
            glEnableVertexAttribArray(1);


            // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
            // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
            glBindVertexArray(0);

            //int nVertices = (13320/2); // 36 vértices para cada cubo, porém como a maioria dos triângulos são 'ligados' eles compartilham muitos vértices... o valor real de vértices diferentes é de 8 apenas
            //int nVertices = (144);
            //nVertices = 1080; // Aumentando vertFim para: 1080 <-- Vertice final correto para desenhar a ampulheta corretamente !!!
            //nVertices = VERT_T; //vert =53280
            // Na verdade para desenhar o planeta precisa só de uns +-8550 vértices
            nVertices = VERT_T/6;  //53280/6 = 8880

            //return VAO;
        }

        void desenhar(){
            shaderPlaneta3D->use();
            glBindVertexArray(VAO);

            // Planeta3D:
            // TRANSFORMAÇÕES:
            //tec3D_pla->avaliaTeclas(); // Usando controles do GTK

            //Sessão crítica !!! pq vai escrever nas variáveis compartilhadas entre as threads
            pthread_mutex_lock(&mutex_planeta3d);
            //cout << "comp_escala_0 =" << comp_escala_0 << endl; // Debug
            transf3D_pla->setXT(comp_xT_0);
            transf3D_pla->setYT(comp_yT_0);
            transf3D_pla->setZT(comp_zT_0);
            transf3D_pla->setTipoRot(comp_tipoRot_0);
            transf3D_pla->setAnguloX(comp_anguloX_0);
            transf3D_pla->setAnguloY(comp_anguloY_0);
            transf3D_pla->setAnguloZ(comp_anguloZ_0);
            transf3D_pla->setEscala(comp_escala_0);
            pthread_mutex_unlock(&mutex_planeta3d);
            //Fim da sessão crítica

            glm::mat4 model0 = transf3D_pla->calculaTransformacoes();
            //cout << "transf3D_pla.toString() =" << transf3D_pla->toString() << endl;
            //transf3D_pla->imprimeAsTransformacoes(model0);

            unsigned int modelLoc0 = glGetUniformLocation(shaderPlaneta3D->ID, "model");
            //cout << "modelLoc0 =" << modelLoc0 << endl;  // Debug
            // modelLoc0 =4294967295 --> erro tb !
            if (modelLoc0 == -1) cout << "###Erro na localização da ID 'model' no shader !" << endl;
            glUniformMatrix4fv(modelLoc0, 1, GL_FALSE, glm::value_ptr(model0));

             // CÂMERA:
            glm::mat4 view0 = glm::mat4(1.0f);
            // note that we’re translating the scene in the reverse direction
            //view0 = glm::translate(view0, glm::vec3(0.0f, 0.0f, -3.0f)); // Câmera simples - parada !
            //view0 = glm::translate(view0, glm::vec3(0.0f, 3.0f, 0.0f)); // Visão de cima -- não mostrou nada !

            view0 = glm::rotate(view0, comp_anguloX_cam, glm::vec3(1, 0, 0)); // Rotação da Cam no ângulo X
            view0 = glm::rotate(view0, comp_anguloY_cam, glm::vec3(0, 1, 0)); // Rotação da Cam no ângulo Y
            view0 = glm::rotate(view0, comp_anguloZ_cam, glm::vec3(0, 0, 1)); // Rotação da Cam no ângulo Z
            view0 = glm::translate(view0, glm::vec3(comp_xT_cam, comp_yT_cam, comp_zT_cam)); // Translate sempre por último senão fica 'estranha' a posição

            /*const float radius = 10.0f;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
            glm::mat4 view0;*/
            //view0 = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); // Câmera lookAt !
            //view0 = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 1.9)); // Câmera lookAt !

            unsigned int viewLoc0 = glGetUniformLocation(shaderPlaneta3D->ID, "view");
            //cout << "viewLoc0 =" << viewLoc0 << endl;  // Debug
            if (viewLoc0 == -1) cout << "###Erro na localização da ID 'view' no shader !" << endl;
            glUniformMatrix4fv(viewLoc0, 1, GL_FALSE, glm::value_ptr(view0));

            // PROJEÇÃO:
            unsigned int projectionLoc0 = glGetUniformLocation(shaderPlaneta3D->ID, "projection");
            //cout << "projectionLoc0 =" << projectionLoc0 << endl;  // Debug
            if (projectionLoc0 == -1) cout << "###Erro na localização da ID 'projection' no shader !" << endl;
            glUniformMatrix4fv(projectionLoc0, 1, GL_FALSE, glm::value_ptr(projection));


            unsigned int objectColorLoc0 = glGetUniformLocation(shaderPlaneta3D->ID, "objectColor");
            //cout << "objectColorLoc0 =" << objectColorLoc0 << endl;  // Debug
            if (objectColorLoc0 == -1) cout << "###Erro na localização da ID 'objectColor' no shader !" << endl;
            //glUniform3f(objectColorLoc0, 1.0f, 1.0f, 0.0f);
            glUniform3f(objectColorLoc0, comp_obj0_cor_r, comp_obj0_cor_g, comp_obj0_cor_b);

            // VIEWPOS: // position vector of the camera object
            unsigned int viewPosLoc0 = glGetUniformLocation(shaderPlaneta3D->ID, "viewPos");
            //cout << "lightColorLoc0 =" << lightColorLoc0 << endl;  // Debug
            if (viewPosLoc0 == -1) cout << "###Erro na localização da ID 'viewPos' no shader !" << endl;
            glUniform3f(viewPosLoc0, comp_xT_cam, comp_yT_cam, comp_zT_cam);

            if (comp_luz0_ligada) {
                unsigned int lightColor0Loc0 = glGetUniformLocation(shaderPlaneta3D->ID, "lightColor0");
                //cout << "lightColorLoc0 =" << lightColorLoc0 << endl;  // Debug
                if (lightColor0Loc0 == -1) cout << "###Erro na localização da ID 'lightColor0' no shader !" << endl;
                //glUniform3f(lightColorLoc0, 1.0f, 1.0f, 1.0f);
                glUniform3f(lightColor0Loc0, comp_luz0_cor_r, comp_luz0_cor_g, comp_luz0_cor_b);

                unsigned int lightPos0 = glGetUniformLocation(shaderPlaneta3D->ID, "lightPos0");
                //cout << "lightPos0 =" << lightPos0 << endl;  // Debug
                if (lightPos0 == -1) cout << "###Erro na localização da ID 'lightPos0' no shader !" << endl;
                //glUniform3f(lightPos0, 0.3f, 0.35f, -1.0f);
                glUniform3f(lightPos0, transf3D_luz0->getXT(), transf3D_luz0->getYT(), transf3D_luz0->getZT());
            }

             if (comp_luz1_ligada) {
                unsigned int lightColor1Loc0 = glGetUniformLocation(shaderPlaneta3D->ID, "lightColor1");
                //cout << "lightColorLoc0 =" << lightColorLoc0 << endl;  // Debug
                if (lightColor1Loc0 == -1) cout << "###Erro na localização da ID 'lightColor1' no shader !" << endl;
                glUniform3f(lightColor1Loc0, comp_luz1_cor_r, comp_luz1_cor_g, comp_luz1_cor_b);

                unsigned int lightPos1 = glGetUniformLocation(shaderPlaneta3D->ID, "lightPos1");
                //cout << "lightPos1 =" << lightPos1 << endl;  // Debug
                if (lightPos1 == -1) cout << "###Erro na localização da ID 'lightPos1' no shader !" << endl;
                glUniform3f(lightPos1, transf3D_luz1->getXT(), transf3D_luz1->getYT(), transf3D_luz1->getZT());
            }

             if (comp_luz2_ligada) {
                unsigned int lightColor2Loc0 = glGetUniformLocation(shaderPlaneta3D->ID, "lightColor2");
                //cout << "lightColorLoc0 =" << lightColorLoc0 << endl;  // Debug
                if (lightColor2Loc0 == -1) cout << "###Erro na localização da ID 'lightColor2' no shader !" << endl;
                //glUniform3f(lightColorLoc0, 1.0f, 1.0f, 1.0f);
                glUniform3f(lightColor2Loc0, comp_luz2_cor_r, comp_luz2_cor_g, comp_luz2_cor_b);

                unsigned int lightPos2 = glGetUniformLocation(shaderPlaneta3D->ID, "lightPos2");
                //cout << "lightPos2 =" << lightPos2 << endl;  // Debug
                if (lightPos2 == -1) cout << "###Erro na localização da ID 'lightPos2' no shader !" << endl;
                glUniform3f(lightPos2, transf3D_luz2->getXT(), transf3D_luz2->getYT(), transf3D_luz2->getZT());
            }

            glDrawArrays(GL_TRIANGLES, 0, nVertices);

            //glPointSize(40);
            //glDrawArrays(GL_POINTS, 0, nVertices);


            // Luzes:

            shaderLuz->use();
            //glBindVertexArray(VAO_1); // Desenhando o mesmo VAO, porém com coordenadas diferentes
            glBindVertexArray(VAO);

            //

            // Ativa as luzes conforme seus estados:
            if (comp_luz0_ligada) { // Acesso de leitura em variável compartilhada entre threads sem usar MUTEX -- pode ?
                glm::mat4 model1 = transf3D_luz0->calculaTransformacoes();
                unsigned int modelLoc1 = glGetUniformLocation(shaderLuz->ID, "model");
                //cout << "modelLoc1 =" << modelLoc1 << endl;  // Debug
                if (modelLoc1 == -1) cout << "###Erro na localização da ID 'model' no shader !" << endl;
                glUniformMatrix4fv(modelLoc1, 1, GL_FALSE, glm::value_ptr(model1));

                // CÂMERA: // USANDO A MESMA CÂMERA DO OBJETO ACIMA
                unsigned int viewLoc1 = glGetUniformLocation(shaderLuz->ID, "view");
                //cout << "viewLoc1 =" << viewLoc1 << endl;  // Debug
                if (viewLoc1 == -1) cout << "###Erro na localização da ID 'view' no shader !" << endl;
                glUniformMatrix4fv(viewLoc1, 1, GL_FALSE, glm::value_ptr(view0));

                // PROJEÇÃO:
                unsigned int projectionLoc1 = glGetUniformLocation(shaderLuz->ID, "projection");
                //cout << "projectionLoc1 =" << projectionLoc0 << endl;  // Debug
                if (projectionLoc1 == -1) cout << "###Erro na localização da ID 'projection' no shader !" << endl;
                glUniformMatrix4fv(projectionLoc1, 1, GL_FALSE, glm::value_ptr(projection));

                // COR DA LUZ:
                unsigned int corDaLuzLoc0 = glGetUniformLocation(shaderLuz->ID, "corDaLuz");
                //cout << "lightColorLoc0 =" << lightColorLoc0 << endl;  // Debug
                if (corDaLuzLoc0 == -1) cout << "###Erro na localização da ID 'corDaLuz' no shader !" << endl;
                glUniform3f(corDaLuzLoc0, comp_luz0_cor_r, comp_luz0_cor_g, comp_luz0_cor_b);

                glDrawArrays(GL_TRIANGLES, 0, nVertices);
            }

            // Ativa as luzes conforme seus estados:
            if (comp_luz1_ligada) { // Acesso de leitura em variável compartilhada entre threads sem usar MUTEX -- pode ?
                glm::mat4 model1 = transf3D_luz1->calculaTransformacoes();
                unsigned int modelLoc1 = glGetUniformLocation(shaderLuz->ID, "model");
                //cout << "modelLoc1 =" << modelLoc1 << endl;  // Debug
                if (modelLoc1 == -1) cout << "###Erro na localização da ID 'model' no shader !" << endl;
                glUniformMatrix4fv(modelLoc1, 1, GL_FALSE, glm::value_ptr(model1));

                // CÂMERA: // USANDO A MESMA CÂMERA DO OBJETO ACIMA
                unsigned int viewLoc1 = glGetUniformLocation(shaderLuz->ID, "view");
                //cout << "viewLoc1 =" << viewLoc1 << endl;  // Debug
                if (viewLoc1 == -1) cout << "###Erro na localização da ID 'view' no shader !" << endl;
                glUniformMatrix4fv(viewLoc1, 1, GL_FALSE, glm::value_ptr(view0));

                // PROJEÇÃO:
                unsigned int projectionLoc1 = glGetUniformLocation(shaderLuz->ID, "projection");
                //cout << "projectionLoc1 =" << projectionLoc0 << endl;  // Debug
                if (projectionLoc1 == -1) cout << "###Erro na localização da ID 'projection' no shader !" << endl;
                glUniformMatrix4fv(projectionLoc1, 1, GL_FALSE, glm::value_ptr(projection));

                 // COR DA LUZ:
                unsigned int corDaLuzLoc0 = glGetUniformLocation(shaderLuz->ID, "corDaLuz");
                //cout << "lightColorLoc0 =" << lightColorLoc0 << endl;  // Debug
                if (corDaLuzLoc0 == -1) cout << "###Erro na localização da ID 'corDaLuz' no shader !" << endl;
                glUniform3f(corDaLuzLoc0, comp_luz1_cor_r, comp_luz1_cor_g, comp_luz1_cor_b);


                glDrawArrays(GL_TRIANGLES, 0, nVertices);
            }

            // Ativa as luzes conforme seus estados:
            if (comp_luz2_ligada) { // Acesso de leitura em variável compartilhada entre threads sem usar MUTEX -- pode ?
                glm::mat4 model1 = transf3D_luz2->calculaTransformacoes();
                unsigned int modelLoc1 = glGetUniformLocation(shaderLuz->ID, "model");
                //cout << "modelLoc1 =" << modelLoc1 << endl;  // Debug
                if (modelLoc1 == -1) cout << "###Erro na localização da ID 'model' no shader !" << endl;
                glUniformMatrix4fv(modelLoc1, 1, GL_FALSE, glm::value_ptr(model1));

                // CÂMERA: // USANDO A MESMA CÂMERA DO OBJETO ACIMA
                unsigned int viewLoc1 = glGetUniformLocation(shaderLuz->ID, "view");
                //cout << "viewLoc1 =" << viewLoc1 << endl;  // Debug
                if (viewLoc1 == -1) cout << "###Erro na localização da ID 'view' no shader !" << endl;
                glUniformMatrix4fv(viewLoc1, 1, GL_FALSE, glm::value_ptr(view0));

                // PROJEÇÃO:
                unsigned int projectionLoc1 = glGetUniformLocation(shaderLuz->ID, "projection");
                //cout << "projectionLoc1 =" << projectionLoc0 << endl;  // Debug
                if (projectionLoc1 == -1) cout << "###Erro na localização da ID 'projection' no shader !" << endl;
                glUniformMatrix4fv(projectionLoc1, 1, GL_FALSE, glm::value_ptr(projection));

                 // COR DA LUZ:
                unsigned int corDaLuzLoc0 = glGetUniformLocation(shaderLuz->ID, "corDaLuz");
                //cout << "lightColorLoc0 =" << lightColorLoc0 << endl;  // Debug
                if (corDaLuzLoc0 == -1) cout << "###Erro na localização da ID 'corDaLuz' no shader !" << endl;
                glUniform3f(corDaLuzLoc0, comp_luz2_cor_r, comp_luz2_cor_g, comp_luz2_cor_b);


                glDrawArrays(GL_TRIANGLES, 0, nVertices);
            }



        }
};
