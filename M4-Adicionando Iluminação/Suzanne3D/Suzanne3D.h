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

#include "../Basico/loadSimpleObj.h"
#include "../Basico/stb_image.h"

#include "../Aux.h"

using namespace std;

pthread_mutex_t mutex_suzanne3d; // Permite realizar a exclusão mútua na área crítica de código das threads

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


class Suzanne3D{

    private:
        unsigned int VAO; // Vertex Array Object
        int nVertices;

        unique_ptr<Shader> shaderSuzanne3D;
        shared_ptr<Transformacoes3D> transf3D_suz;
        shared_ptr<Transformacoes3D> transf3D_suz_ini;
        unique_ptr<Teclado3D> tec3D_suz;

        //unique_ptr<Shader> shaderLuz;
        //shared_ptr<Transformacoes3D> transf3D_luz0;
        //shared_ptr<Transformacoes3D> transf3D_luz1;
        //shared_ptr<Transformacoes3D> transf3D_luz2;

        glm::mat4 projection;

        float ka, kd, ks, q;
        glm::vec3 lightPos;
        glm::vec3 camPos;




    public:
        Suzanne3D(GLFWwindow* window, glm::mat4 projection) {
            this->projection = projection;

            // Cria o shader:
            shaderSuzanne3D = make_unique<Shader>("Suzanne3D/shader_suzanne3D.vs", "Suzanne3D/shader_suzanne3D.fs");
            // Cria o VAO:
            string filePATH = "Modelos_3D/Suzanne.obj";
            glm::vec3 color0 = glm::vec3(0.5, 0.5, 0.5); // Cinza
            VAO = loadSimpleOBJModificadoParaAdicionarTexturasNoVAO(filePATH, nVertices, color0);
            int imgWidth, imgHeight;
            //texID = loadTexture("..tex/pixelWall.png", imgWidth, imgHeight);


            //Transformacoes3D(float xT, float yT,floatzT,  int tipoRot, float anguloX, float anguloY,float anguloZ, float escala)
            transf3D_suz = make_shared<Transformacoes3D>(0.0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 0.5);
            transf3D_suz_ini = make_shared<Transformacoes3D>(transf3D_suz->clonar()); // Precisa aqui que seja uma cópia do objeto e não só uma ref. -- para guardar as configurações iniciais do objeto

            //Teclado3D(GLFWwindow* window, Transformacoes3D* transf3D, Transformacoes3D* transf3D_ini)
            tec3D_suz = make_unique<Teclado3D>(window, transf3D_suz, transf3D_suz_ini);

            // Inicializa 'k's, lightPos e camPos:
            ka = 0.1;
            kd =0.5;
            ks = 0.5;
            q = 10.0;
            lightPos = glm::vec3(0.6, 1.2, -0.5);
            camPos = glm::vec3(0.0, 0.0, -3.0);

            /*// Luzes:
            shaderLuz = make_unique<Shader>("Suzanne3D/shader_suzanne3D.vs", "Suzanne3D/shader_luz.fs");

            //Luz principal (key light): É a fonte de luz mais intensa, que ilumina o objeto principal e define o tom geral da cena.
            transf3D_luz0 = make_shared<Transformacoes3D>(-0.9, 0.0, 0.9, 0, 0.0, 0.0, 0.0, 0.05); // Esq./Frente
            //Luz de preenchimento (fill light): Suaviza as sombras criadas pela luz principal, equilibrando a iluminação e evitando que a imagem fique muito contrastada.
            transf3D_luz1 = make_shared<Transformacoes3D>(0.9, 0.0, 0.9, 0, 0.0, 0.0, 0.0, 0.05);// Dir./Frente
            //Luz de fundo (back light): Ilumina o fundo do objeto, criando profundidade e separando-o do fundo.
            transf3D_luz2 = make_shared<Transformacoes3D>(-0.9, 0.0, -0.9, 0, 0.0, 0.0, 0.0, 0.05); // Esq./Atrás*/




        }

        GLuint loadTexture(string filePath, int &width, int &height)
        {
            GLuint texID; // id da textura a ser carregada

            // Gera o identificador da textura na memória
            glGenTextures(1, &texID);
            glBindTexture(GL_TEXTURE_2D, texID);

            // Ajuste dos parâmetros de wrapping e filtering
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Carregamento da imagem usando a função stbi_load da biblioteca stb_image
            int nrChannels;

            unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

            if (data)
            {
                if (nrChannels == 3) // jpg, bmp
                {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                }
                else // assume que é 4 canais png
                {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                }
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture " << filePath << std::endl;
            }

            stbi_image_free(data);

            glBindTexture(GL_TEXTURE_2D, 0);

            return texID;
        }


        void desenhar(){
            shaderSuzanne3D->use();

            // Enviar a informação de qual variável armazenará o buffer da textura
            glUniform1i(glGetUniformLocation(shaderSuzanne3D->ID, "texBuff"), 0);

            glUniform1f(glGetUniformLocation(shaderSuzanne3D->ID, "ka"), ka);
            glUniform1f(glGetUniformLocation(shaderSuzanne3D->ID, "kd"), kd);
            glUniform1f(glGetUniformLocation(shaderSuzanne3D->ID, "ks"), ks);
            glUniform1f(glGetUniformLocation(shaderSuzanne3D->ID, "q"), q);
            glUniform3f(glGetUniformLocation(shaderSuzanne3D->ID, "lightPos"), lightPos.x,lightPos.y,lightPos.z);
            glUniform3f(glGetUniformLocation(shaderSuzanne3D->ID, "camPos"), camPos.x,camPos.y,camPos.z);


            glBindVertexArray(VAO);

            // Suzanne3D:
            // TRANSFORMAÇÕES:
            //tec3D_suz->avaliaTeclas(); // Usando controles do GTK

            //Sessão crítica !!! pq vai escrever nas variáveis compartilhadas entre as threads
            pthread_mutex_lock(&mutex_suzanne3d);
            //cout << "comp_escala_0 =" << comp_escala_0 << endl; // Debug
            transf3D_suz->setXT(comp_xT_0);
            transf3D_suz->setYT(comp_yT_0);
            transf3D_suz->setZT(comp_zT_0);
            transf3D_suz->setTipoRot(comp_tipoRot_0);
            transf3D_suz->setAnguloX(comp_anguloX_0);
            transf3D_suz->setAnguloY(comp_anguloY_0);
            transf3D_suz->setAnguloZ(comp_anguloZ_0);
            transf3D_suz->setEscala(comp_escala_0);
            pthread_mutex_unlock(&mutex_suzanne3d);
            //Fim da sessão crítica

            glm::mat4 model0 = transf3D_suz->calculaTransformacoes();
            //cout << "transf3D_suz.toString() =" << transf3D_suz->toString() << endl;
            //transf3D_suz->imprimeAsTransformacoes(model0);

            unsigned int modelLoc0 = glGetUniformLocation(shaderSuzanne3D->ID, "model");
            //cout << "modelLoc0 =" << modelLoc0 << endl;  // Debug
            // modelLoc0 =4294967295 --> erro tb !
            if (modelLoc0 == -1) cout << "###Erro na localização da ID 'model' no shader !" << endl;
            glUniformMatrix4fv(modelLoc0, 1, GL_FALSE, glm::value_ptr(model0));

             /*// CÂMERA:
            glm::mat4 view0 = glm::mat4(1.0f);
            // note that we’re translating the scene in the reverse direction
            //view0 = glm::translate(view0, glm::vec3(0.0f, 0.0f, -3.0f)); // Câmera simples - parada !
            //view0 = glm::translate(view0, glm::vec3(0.0f, 3.0f, 0.0f)); // Visão de cima -- não mostrou nada !

            view0 = glm::rotate(view0, comp_anguloX_cam, glm::vec3(1, 0, 0)); // Rotação da Cam no ângulo X
            view0 = glm::rotate(view0, comp_anguloY_cam, glm::vec3(0, 1, 0)); // Rotação da Cam no ângulo Y
            view0 = glm::rotate(view0, comp_anguloZ_cam, glm::vec3(0, 0, 1)); // Rotação da Cam no ângulo Z
            view0 = glm::translate(view0, glm::vec3(comp_xT_cam, comp_yT_cam, comp_zT_cam)); // Translate sempre por último senão fica 'estranha' a posição*/

            /*const float radius = 10.0f;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
            glm::mat4 view0;*/
            //view0 = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); // Câmera lookAt !
            //view0 = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 1.9)); // Câmera lookAt !

            /*unsigned int viewLoc0 = glGetUniformLocation(shaderSuzanne3D->ID, "view");
            //cout << "viewLoc0 =" << viewLoc0 << endl;  // Debug
            if (viewLoc0 == -1) cout << "###Erro na localização da ID 'view' no shader !" << endl;
            glUniformMatrix4fv(viewLoc0, 1, GL_FALSE, glm::value_ptr(view0));*/

            // PROJEÇÃO:
            unsigned int projectionLoc0 = glGetUniformLocation(shaderSuzanne3D->ID, "projection");
            //cout << "projectionLoc0 =" << projectionLoc0 << endl;  // Debug
            if (projectionLoc0 == -1) cout << "###Erro na localização da ID 'projection' no shader !" << endl;
            glUniformMatrix4fv(projectionLoc0, 1, GL_FALSE, glm::value_ptr(projection));


            /*unsigned int objectColorLoc0 = glGetUniformLocation(shaderSuzanne3D->ID, "objectColor");
            //cout << "objectColorLoc0 =" << objectColorLoc0 << endl;  // Debug
            if (objectColorLoc0 == -1) cout << "###Erro na localização da ID 'objectColor' no shader !" << endl;
            //glUniform3f(objectColorLoc0, 1.0f, 1.0f, 0.0f);
            glUniform3f(objectColorLoc0, comp_obj0_cor_r, comp_obj0_cor_g, comp_obj0_cor_b);

            // VIEWPOS: // position vector of the camera object
            unsigned int viewPosLoc0 = glGetUniformLocation(shaderSuzanne3D->ID, "viewPos");
            //cout << "lightColorLoc0 =" << lightColorLoc0 << endl;  // Debug
            if (viewPosLoc0 == -1) cout << "###Erro na localização da ID 'viewPos' no shader !" << endl;
            glUniform3f(viewPosLoc0, comp_xT_cam, comp_yT_cam, comp_zT_cam);

            if (comp_luz0_ligada) {
                unsigned int lightColor0Loc0 = glGetUniformLocation(shaderSuzanne3D->ID, "lightColor0");
                //cout << "lightColorLoc0 =" << lightColorLoc0 << endl;  // Debug
                if (lightColor0Loc0 == -1) cout << "###Erro na localização da ID 'lightColor0' no shader !" << endl;
                //glUniform3f(lightColorLoc0, 1.0f, 1.0f, 1.0f);
                glUniform3f(lightColor0Loc0, comp_luz0_cor_r, comp_luz0_cor_g, comp_luz0_cor_b);

                unsigned int lightPos0 = glGetUniformLocation(shaderSuzanne3D->ID, "lightPos0");
                //cout << "lightPos0 =" << lightPos0 << endl;  // Debug
                if (lightPos0 == -1) cout << "###Erro na localização da ID 'lightPos0' no shader !" << endl;
                //glUniform3f(lightPos0, 0.3f, 0.35f, -1.0f);
                glUniform3f(lightPos0, transf3D_luz0->getXT(), transf3D_luz0->getYT(), transf3D_luz0->getZT());
            }

             if (comp_luz1_ligada) {
                unsigned int lightColor1Loc0 = glGetUniformLocation(shaderSuzanne3D->ID, "lightColor1");
                //cout << "lightColorLoc0 =" << lightColorLoc0 << endl;  // Debug
                if (lightColor1Loc0 == -1) cout << "###Erro na localização da ID 'lightColor1' no shader !" << endl;
                glUniform3f(lightColor1Loc0, comp_luz1_cor_r, comp_luz1_cor_g, comp_luz1_cor_b);

                unsigned int lightPos1 = glGetUniformLocation(shaderSuzanne3D->ID, "lightPos1");
                //cout << "lightPos1 =" << lightPos1 << endl;  // Debug
                if (lightPos1 == -1) cout << "###Erro na localização da ID 'lightPos1' no shader !" << endl;
                glUniform3f(lightPos1, transf3D_luz1->getXT(), transf3D_luz1->getYT(), transf3D_luz1->getZT());
            }

             if (comp_luz2_ligada) {
                unsigned int lightColor2Loc0 = glGetUniformLocation(shaderSuzanne3D->ID, "lightColor2");
                //cout << "lightColorLoc0 =" << lightColorLoc0 << endl;  // Debug
                if (lightColor2Loc0 == -1) cout << "###Erro na localização da ID 'lightColor2' no shader !" << endl;
                //glUniform3f(lightColorLoc0, 1.0f, 1.0f, 1.0f);
                glUniform3f(lightColor2Loc0, comp_luz2_cor_r, comp_luz2_cor_g, comp_luz2_cor_b);

                unsigned int lightPos2 = glGetUniformLocation(shaderSuzanne3D->ID, "lightPos2");
                //cout << "lightPos2 =" << lightPos2 << endl;  // Debug
                if (lightPos2 == -1) cout << "###Erro na localização da ID 'lightPos2' no shader !" << endl;
                glUniform3f(lightPos2, transf3D_luz2->getXT(), transf3D_luz2->getYT(), transf3D_luz2->getZT());
            }*/

            glDrawArrays(GL_TRIANGLES, 0, nVertices);

            //glPointSize(40);
            //glDrawArrays(GL_POINTS, 0, nVertices);


            /*// Luzes:

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
            }*/



        }
};
