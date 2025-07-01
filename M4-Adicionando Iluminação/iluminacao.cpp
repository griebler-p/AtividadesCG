// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Computação Gráfica
// Módulo 4
// Tarefa: Adicionando Iluminação
// Data: 31/05/2025
// Professor: Rossana Baptista Queiroz
// Aluno: Paulo Griebler Júnior
// Registro Acadêmico: 1930669

// Versão Astrolabium:
// Pasta: cd ''
//Compilar: g++ iluminacao.cpp -o iluminacao Basico/glad/glad.c Basico/loadSimpleOBJ.cpp Basico/stb_image.cpp -I ../include -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib64 -lGLEW -lGL -lX11 -lglfw -lrt -lm -ldl `pkg-config --cflags --libs gtk4` -std=c++17
// Rodar: ./iluminacao
// Debug:
// - Compilar com opção -g no g++
// - gdb ./teste
// - b "breakpoint"
// - n ou s
// - p para ver variáveis


// Versão LOCAL:


#include <pthread.h> // Para pthread_create()

#include "GUI.h"
#include "OpenGL.h"


// Este programa cria 2 threads.
// - A 1° abre uma janela em GTK para controle das transformações e demais parâmetros dos objetos
// - A 2° abra a janela OpenGL padrão que mostra os gráficos
// - A comunicação entre essas 2 treads se dá pelo uso das variáveis globais listadas abaixo:

// VARIÁVEIS GLOBAIS COMPARTILHADAS ENTRE AS THREADS:
float comp_xT_0 = 0.0; // Variáveis globais não tem por convenção em C/C++ serem escritas com maiúsculas, exceto se forem constantes
float comp_yT_0 = 0.0;
float comp_zT_0 = 0.0;
int   comp_tipoRot_0 = 0;
float comp_anguloX_0 = 0.0;
float comp_anguloY_0 = 0.0;
float comp_anguloZ_0 = 0.0;
float comp_escala_0 = 0.4;

float comp_obj0_cor_r = 1.0;
float comp_obj0_cor_g = 1.0;
float comp_obj0_cor_b = 1.0;

// Câmera:
float comp_xT_cam = 0.0;
float comp_yT_cam = 0.0;
float comp_zT_cam = -3.0;
float comp_anguloX_cam = 0.0;
float comp_anguloY_cam = 0.0;
float comp_anguloZ_cam = 0.0;

//Luz principal (key light): É a fonte de luz mais intensa, que ilumina o objeto principal e define o tom geral da cena.
bool comp_luz0_ligada = true;
float comp_luz0_cor_r = 1.0; //
float comp_luz0_cor_g = 0.0;
float comp_luz0_cor_b = 0.0;

 //Luz de preenchimento (fill light): Suaviza as sombras criadas pela luz principal, equilibrando a iluminação e evitando que a imagem fique muito contrastada.
bool comp_luz1_ligada = true;
float comp_luz1_cor_r = 0.0;
float comp_luz1_cor_g = 1.0;
float comp_luz1_cor_b = 0.0;

 //Luz de fundo (back light): Ilumina o fundo do objeto, criando profundidade e separando-o do fundo.
bool comp_luz2_ligada = true;
float comp_luz2_cor_r = 0.0;
float comp_luz2_cor_g = 0.0;
float comp_luz2_cor_b = 1.0;


int main(int argc, char* argv[]) {
    // Cria as threads
    pthread_t t0, t1;

    pthread_create(&t0, NULL, janelaDeControleGtk, NULL); // 'janelaDeControleGtk precisa ter a assinatura: void* (*)()
    pthread_create(&t1, NULL, janelaOpenGL, NULL);

    // Retorna as threads ao programa principal:
    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    return 0;
}
