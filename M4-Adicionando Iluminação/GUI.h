// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Computação Gráfica
// Módulo 4
// Tarefa: Atividade Vivencial 2 - Técnica de Iluminação de 3 pontos
// Data: 31/05/2025
// Professor: Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior e Rodrigo Pires
// Registros Acadêmicos: 1930669 e 1917485

#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>

#include "Aux.h"

pthread_mutex_t mutex_gui; // Permite realizar a exclusão mútua na área crítica de código das threads

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

static void scale_comp_xT_0_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_xT_0 = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_yT_0_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_yT_0 = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_zT_0_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_zT_0 = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void check_button_comp_tipoRot_0semRot_changed(GtkCheckButton *checkbutton, gpointer user_data) {
    bool value = gtk_check_button_get_active(checkbutton);
    g_print("Check Button value changed to: %b\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    if (value) comp_tipoRot_0 = 0; // Desativa as rotações
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void check_button_comp_tipoRot_0z_changed(GtkCheckButton *checkbutton, gpointer user_data) {
    bool value = gtk_check_button_get_active(checkbutton);
    g_print("Check Button value changed to: %b\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    if (value) comp_tipoRot_0 = comp_tipoRot_0 | 1; // Ativa Rotacão eixo Z
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void check_button_comp_tipoRot_0y_changed(GtkCheckButton *checkbutton, gpointer user_data) {
    bool value = gtk_check_button_get_active(checkbutton);
    g_print("Check Button value changed to: %b\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    if (value) comp_tipoRot_0 = comp_tipoRot_0 | 2; // Ativa Rotacão eixo Y
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void check_button_comp_tipoRot_0x_changed(GtkCheckButton *checkbutton, gpointer user_data) {
    bool value = gtk_check_button_get_active(checkbutton);
    g_print("Check Button value changed to: %b\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    if (value) comp_tipoRot_0 = comp_tipoRot_0 | 4; // Ativa Rotacão eixo X
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_anguloX_0_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_anguloX_0 = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_anguloY_0_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_anguloY_0 = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_anguloZ_0_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_anguloZ_0 = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_escala_0_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_escala_0 = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

//###Cam:
static void scale_comp_xT_cam_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_xT_cam = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_yT_cam_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_yT_cam = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_zT_cam_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_zT_cam = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_anguloX_cam_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_anguloX_cam = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_anguloY_cam_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_anguloY_cam = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_anguloZ_cam_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_anguloY_cam = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

//###LUZ_0:
static void check_button_comp_luz0_ligada_changed(GtkCheckButton *checkbutton, gpointer user_data) { // checkbutton ? Pq 'switch' é palavra reservada !
    bool value = gtk_check_button_get_active(checkbutton);
    g_print("Bool value changed to: %b\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_luz0_ligada = !value; // Pq !value ? -> Pq 0 é ligado(empurrar para dir.) e 1 é desligado (empurrar para esq.)
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_luz0_cor_r_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_luz0_cor_r = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_luz0_cor_g_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_luz0_cor_g = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_luz0_cor_b_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_luz0_cor_b = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

//###LUZ_1:
static void check_button_comp_luz1_ligada_changed(GtkCheckButton *checkbutton, gpointer user_data) { // checkbutton ? Pq 'switch' é palavra reservada !
    bool value = gtk_check_button_get_active(checkbutton);
    g_print("Bool value changed to: %b\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_luz1_ligada = !value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_luz1_cor_r_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_luz1_cor_r = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_luz1_cor_g_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_luz1_cor_g = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_luz1_cor_b_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_luz1_cor_b = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

//###LUZ_2:
static void check_button_comp_luz2_ligada_changed(GtkCheckButton *checkbutton, gpointer user_data) { // checkbutton ? Pq 'switch' é palavra reservada !
    bool value = gtk_check_button_get_active(checkbutton);
    g_print("Bool value changed to: %b\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_luz2_ligada = !value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_luz2_cor_r_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_luz2_cor_r = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_luz2_cor_g_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_luz2_cor_g = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}

static void scale_comp_luz2_cor_b_changed(GtkRange *range, gpointer user_data) {
    gdouble value = gtk_range_get_value(range);
    g_print("Scale value changed to: %f\n", value);
    //Sessão crítica !!!
    pthread_mutex_lock(&mutex_gui);
    comp_luz2_cor_b = value;
    pthread_mutex_unlock(&mutex_gui);
    //Fim da sessão crítica
}



static void activate (GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    //GtkWidget *box;
    GtkWidget *grid;
    GtkWidget *label_comp_xT_0, *label_comp_yT_0, *label_comp_zT_0, *label_comp_anguloX_0, *label_comp_anguloY_0, *label_comp_anguloZ_0, *label_comp_escala_0;
    GtkWidget *scale_comp_xT_0, *scale_comp_yT_0, *scale_comp_zT_0, *scale_comp_anguloX_0, *scale_comp_anguloY_0, *scale_comp_anguloZ_0, *scale_comp_escala_0;
    //GtkWidget *button;
    GtkAdjustment *adj_eixo, *adj_angulo, *adj_escala, *adjustment;

    GtkWidget *label_comp_tipoRot_0semRot, *label_comp_tipoRot_0z, *label_comp_tipoRot_0y, *label_comp_tipoRot_0x;
    GtkWidget *check_button_comp_tipoRot_0semRot, *check_button_comp_tipoRot_0z, *check_button_comp_tipoRot_0y, *check_button_comp_tipoRot_0x;

    GtkWidget *label_comp_xT_cam, *label_comp_yT_cam, *label_comp_zT_cam, *label_comp_anguloX_cam, *label_comp_anguloY_cam, *label_comp_anguloZ_cam;
    GtkWidget *scale_comp_xT_cam, *scale_comp_yT_cam, *scale_comp_zT_cam, *scale_comp_anguloX_cam, *scale_comp_anguloY_cam, *scale_comp_anguloZ_cam;

    GtkWidget *label_comp_luz0_ligada, *label_comp_luz0_cor_r, *label_comp_luz0_cor_g, *label_comp_luz0_cor_b;
    GtkWidget *check_button_comp_luz0_ligada, *scale_comp_luz0_cor_r, *scale_comp_luz0_cor_g, *scale_comp_luz0_cor_b;

    GtkWidget *label_comp_luz1_ligada, *label_comp_luz1_cor_r, *label_comp_luz1_cor_g, *label_comp_luz1_cor_b;
    GtkWidget *check_button_comp_luz1_ligada, *scale_comp_luz1_cor_r, *scale_comp_luz1_cor_g, *scale_comp_luz1_cor_b;

    GtkWidget *label_comp_luz2_ligada, *label_comp_luz2_cor_r, *label_comp_luz2_cor_g, *label_comp_luz2_cor_b;
    GtkWidget *check_button_comp_luz2_ligada, *scale_comp_luz2_cor_r, *scale_comp_luz2_cor_g, *scale_comp_luz2_cor_b;


    window = gtk_application_window_new (app);
    gtk_window_set_title(GTK_WINDOW (window), "Controles");
    gtk_window_set_default_size(GTK_WINDOW (window), 700, 500);
    gtk_window_present(GTK_WINDOW (window));

    /*box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
    gtk_window_set_child (GTK_WINDOW(window), box);*/

    grid = gtk_grid_new();
    /*gtk_grid_insert_row(GTK_GRID(grid), 0);
    gtk_grid_insert_row(GTK_GRID(grid), 0);
    gtk_grid_insert_column(GTK_GRID(grid), 0);
    gtk_grid_insert_column(GTK_GRID(grid), 0);*/

    gtk_grid_set_row_spacing(GTK_GRID(grid), 17);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);



    //gtk_grid_attach(GtkGrid* grid, GtkWidget* child, int column, int row, int width, int height)




    label_comp_xT_0 = gtk_label_new("xT:");
    //GtkAdjustment* gtk_adjustment_new(double value, double lower, double upper, double step_increment, double page_increment, double page_size)
    //adj_eixo = gtk_adjustment_new(comp_xT_0, -1.0, 1.0, 0.001, 1.0, 0.1);// Com esses valores o slider não se mexe quase nada !
    //adj_eixo = gtk_adjustment_new(0.0, -50.0, 50.0, 1.0, 1.0, 10);
    //GtkWidget* gtk_scale_new (GtkOrientation orientation,  GtkAdjustment* adjustment)
    //scale_comp_xT_0 = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adj_eixo); // float comp_xT_0 = 0.0;
    //gtk_scale_set_digits(GTK_SCALE(scale_comp_xT_0), 0); // Display integer values
    scale_comp_xT_0 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -5.0, 5.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_xT_0), comp_xT_0); // gtk_RANGE_set_value ? Pq o gtx_scale_set_value não existe e o Scale herda o Range
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_xT_0), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_xT_0), TRUE);
    //gtk_box_append(GTK_BOX(box), scale_comp_xT_0);
    //gtk_grid_attach(GtkGrid* grid, GtkWidget* child, int column, int row, int width, int height)
    gtk_grid_attach(GTK_GRID(grid), label_comp_xT_0, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_xT_0, 1, 0, 1, 1);
    g_signal_connect(scale_comp_xT_0, "value-changed", G_CALLBACK(scale_comp_xT_0_changed), NULL);

    label_comp_yT_0 = gtk_label_new("yT:");
    scale_comp_yT_0 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -5.0, 5.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_yT_0), comp_yT_0);
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_yT_0), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_yT_0), TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_yT_0, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_yT_0, 1, 1, 1, 1);
    g_signal_connect(scale_comp_yT_0, "value-changed", G_CALLBACK(scale_comp_yT_0_changed), NULL);

    label_comp_zT_0 = gtk_label_new("zT:");
    scale_comp_zT_0 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -5.0, 5.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_zT_0), comp_zT_0);
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_zT_0), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_zT_0), TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_zT_0, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_zT_0, 1, 2, 1, 1);
    g_signal_connect(scale_comp_zT_0, "value-changed", G_CALLBACK(scale_comp_zT_0_changed), NULL);

    label_comp_tipoRot_0semRot = gtk_label_new("Sem Rot:");
    check_button_comp_tipoRot_0semRot = gtk_check_button_new();
    gtk_grid_attach(GTK_GRID(grid), label_comp_tipoRot_0semRot, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), check_button_comp_tipoRot_0semRot, 1, 3, 1, 1);
    g_signal_connect(check_button_comp_tipoRot_0semRot, "toggled", G_CALLBACK(check_button_comp_tipoRot_0semRot_changed), NULL);


    label_comp_tipoRot_0z = gtk_label_new("Rot_Z:");
    check_button_comp_tipoRot_0z = gtk_check_button_new();
    gtk_grid_attach(GTK_GRID(grid), label_comp_tipoRot_0z, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), check_button_comp_tipoRot_0z, 1, 4, 1, 1);
    g_signal_connect(check_button_comp_tipoRot_0z, "toggled", G_CALLBACK(check_button_comp_tipoRot_0z_changed), NULL);

    label_comp_tipoRot_0y = gtk_label_new("Rot_Y:");
    check_button_comp_tipoRot_0y = gtk_check_button_new();
    gtk_grid_attach(GTK_GRID(grid), label_comp_tipoRot_0y, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), check_button_comp_tipoRot_0y, 1, 5, 1, 1);
    g_signal_connect(check_button_comp_tipoRot_0y, "toggled", G_CALLBACK(check_button_comp_tipoRot_0y_changed), NULL);

    label_comp_tipoRot_0x = gtk_label_new("Rot_X:");
    check_button_comp_tipoRot_0x = gtk_check_button_new();
    gtk_grid_attach(GTK_GRID(grid), label_comp_tipoRot_0x, 0, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), check_button_comp_tipoRot_0x, 1, 6, 1, 1);
    g_signal_connect(check_button_comp_tipoRot_0x, "toggled", G_CALLBACK(check_button_comp_tipoRot_0x_changed), NULL);

    //adj_angulo = gtk_adjustment_new(Aux::radianos(0.0), Aux::radianos(-360), Aux::radianos(360), 0.001, 1.0, 0.1);
    label_comp_anguloX_0 = gtk_label_new("anguloX:");
    //scale_comp_anguloX_0 = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adj_angulo); // float comp_anguloX_0 = 0.0;
    scale_comp_anguloX_0 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, Aux::radianos(-360), Aux::radianos(360), Aux::radianos(0.01));
    gtk_range_set_value(GTK_RANGE(scale_comp_anguloX_0), comp_anguloX_0);
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_anguloX_0), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_anguloX_0), TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_anguloX_0, 0, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_anguloX_0, 1, 7, 1, 1);
    g_signal_connect(scale_comp_anguloX_0, "value-changed", G_CALLBACK(scale_comp_anguloX_0_changed), NULL);

    label_comp_anguloY_0 = gtk_label_new("anguloY:");
    scale_comp_anguloY_0 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, Aux::radianos(-360), Aux::radianos(360), Aux::radianos(0.01));
    gtk_range_set_value(GTK_RANGE(scale_comp_anguloY_0), comp_anguloY_0);
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_anguloY_0), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_anguloY_0), TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_anguloY_0, 0, 8, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_anguloY_0, 1, 8, 1, 1);
    g_signal_connect(scale_comp_anguloY_0, "value-changed", G_CALLBACK(scale_comp_anguloY_0_changed), NULL);

    label_comp_anguloZ_0 = gtk_label_new("anguloZ:");
    scale_comp_anguloZ_0 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, Aux::radianos(-360), Aux::radianos(360), Aux::radianos(0.01));
    gtk_range_set_value(GTK_RANGE(scale_comp_anguloZ_0), comp_anguloZ_0);
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_anguloZ_0), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_anguloZ_0), TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_anguloZ_0, 0, 9, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_anguloZ_0, 1, 9, 1, 1);
    g_signal_connect(scale_comp_anguloZ_0, "value-changed", G_CALLBACK(scale_comp_anguloZ_0_changed), NULL);


    label_comp_escala_0 = gtk_label_new("escala:");
    //adj_escala = gtk_adjustment_new(0.0, -1.0, 1.0, 0.001, 0.001, 0.001);
    //scale_comp_escala_0 = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adj_escala); // float comp_escala_0 = 1.0;
    scale_comp_escala_0 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -1.0, 1.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_escala_0), comp_escala_0); // gtk_RANGE_set_value ? Pq o gtx_scale_set_value não existe e o Scale herda o Range
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_escala_0), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_escala_0), TRUE);
    gtk_widget_set_hexpand(scale_comp_escala_0, TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_escala_0, 0, 10, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_escala_0, 1, 10, 1, 1);
    g_signal_connect(scale_comp_escala_0, "value-changed", G_CALLBACK(scale_comp_escala_0_changed), NULL);

    //###Cam:
    label_comp_xT_cam = gtk_label_new("Cam X:");
    scale_comp_xT_cam = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -10.0, 10.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_xT_cam), comp_xT_cam);
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_xT_cam), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_xT_cam), TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_xT_cam, 0, 11, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_xT_cam, 1, 11, 1, 1);
    g_signal_connect(scale_comp_xT_cam, "value-changed", G_CALLBACK(scale_comp_xT_cam_changed), NULL);

    label_comp_yT_cam = gtk_label_new("Cam Y:");
    scale_comp_yT_cam = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -10.0, 10.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_yT_cam), comp_yT_cam);
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_yT_cam), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_yT_cam), TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_yT_cam, 0, 12, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_yT_cam, 1, 12, 1, 1);
    g_signal_connect(scale_comp_yT_cam, "value-changed", G_CALLBACK(scale_comp_yT_cam_changed), NULL);

    label_comp_zT_cam = gtk_label_new("Cam Z:");
    scale_comp_zT_cam = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -10.0, 10.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_zT_cam), comp_zT_cam);
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_zT_cam), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_zT_cam), TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_zT_cam, 0, 13, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_zT_cam, 1, 13, 1, 1);
    g_signal_connect(scale_comp_zT_cam, "value-changed", G_CALLBACK(scale_comp_zT_cam_changed), NULL);

    label_comp_anguloX_cam = gtk_label_new("Cam angX:");
    scale_comp_anguloX_cam = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -10.0, 10.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_anguloX_cam), comp_anguloX_cam);
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_anguloX_cam), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_anguloX_cam), TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_anguloX_cam, 0, 14, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_anguloX_cam, 1, 14, 1, 1);
    g_signal_connect(scale_comp_anguloX_cam, "value-changed", G_CALLBACK(scale_comp_anguloX_cam_changed), NULL);

    label_comp_anguloY_cam = gtk_label_new("Cam angY:");
    scale_comp_anguloY_cam = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -10.0, 10.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_anguloY_cam), comp_anguloY_cam);
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_anguloY_cam), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_anguloY_cam), TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_anguloY_cam, 0, 15, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_anguloY_cam, 1, 15, 1, 1);
    g_signal_connect(scale_comp_anguloY_cam, "value-changed", G_CALLBACK(scale_comp_anguloY_cam_changed), NULL);

    label_comp_anguloZ_cam = gtk_label_new("Cam angZ:");
    scale_comp_anguloZ_cam = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -10.0, 10.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_anguloZ_cam), comp_anguloZ_cam);
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_anguloZ_cam), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_anguloZ_cam), TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_anguloZ_cam, 0, 16, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_anguloZ_cam, 1, 16, 1, 1);
    g_signal_connect(scale_comp_anguloZ_cam, "value-changed", G_CALLBACK(scale_comp_anguloZ_cam_changed), NULL);


    //###LUZ_0:
    label_comp_luz0_ligada = gtk_label_new("Key_Light:");
    check_button_comp_luz0_ligada = gtk_check_button_new();
    gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_comp_luz0_ligada), comp_luz0_ligada);
    //gtk_widget_set_hexpand(check_button_comp_luz0_ligada, FALSE); // FALSE pq fica deformado (muito esticado com TRUE)
    gtk_grid_attach(GTK_GRID(grid), label_comp_luz0_ligada, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), check_button_comp_luz0_ligada, 3, 0, 1, 1);
    g_signal_connect(check_button_comp_luz0_ligada, "toggled", G_CALLBACK(check_button_comp_luz0_ligada_changed), NULL);

    label_comp_luz0_cor_r = gtk_label_new("Key_Light-R:");
    scale_comp_luz0_cor_r = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -1.0, 1.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_luz0_cor_r), comp_luz0_cor_r); // gtk_RANGE_set_value ? Pq o gtx_scale_set_value não existe e o Scale herda o Range
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_luz0_cor_r), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_luz0_cor_r), TRUE);
    gtk_widget_set_hexpand(scale_comp_luz0_cor_r, TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_luz0_cor_r, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_luz0_cor_r, 3, 1, 1, 1);
    g_signal_connect(scale_comp_luz0_cor_r, "value-changed", G_CALLBACK(scale_comp_luz0_cor_r_changed), NULL);

    label_comp_luz0_cor_g = gtk_label_new("Key_Light-G:");
    scale_comp_luz0_cor_g = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -1.0, 1.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_luz0_cor_g), comp_luz0_cor_g); // gtk_RANGE_set_value ? Pq o gtx_scale_set_value não existe e o Scale herda o Range
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_luz0_cor_g), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_luz0_cor_g), TRUE);
    gtk_widget_set_hexpand(scale_comp_luz0_cor_g, TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_luz0_cor_g, 2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_luz0_cor_g, 3, 2, 1, 1);
    g_signal_connect(scale_comp_luz0_cor_g, "value-changed", G_CALLBACK(scale_comp_luz0_cor_g_changed), NULL);

    label_comp_luz0_cor_b = gtk_label_new("Key_Light-B:");
    scale_comp_luz0_cor_b = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -1.0, 1.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_luz0_cor_b), comp_luz0_cor_b); // gtk_RANGE_set_value ? Pq o gtx_scale_set_value não existe e o Scale herda o Range
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_luz0_cor_b), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_luz0_cor_b), TRUE);
    gtk_widget_set_hexpand(scale_comp_luz0_cor_b, TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_luz0_cor_b, 2, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_luz0_cor_b, 3, 3, 1, 1);
    g_signal_connect(scale_comp_luz0_cor_b, "value-changed", G_CALLBACK(scale_comp_luz0_cor_b_changed), NULL);

    //###LUZ_1:
    label_comp_luz1_ligada = gtk_label_new("Fill_Light:");
    check_button_comp_luz1_ligada = gtk_check_button_new();
    gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_comp_luz1_ligada), comp_luz1_ligada);
    gtk_widget_set_hexpand(check_button_comp_luz1_ligada, FALSE); // FALSE pq fica deformado (muito esticado com TRUE)
    gtk_grid_attach(GTK_GRID(grid), label_comp_luz1_ligada, 2, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), check_button_comp_luz1_ligada, 3, 4, 1, 1);
    g_signal_connect(check_button_comp_luz1_ligada, "toggled", G_CALLBACK(check_button_comp_luz1_ligada_changed), NULL);

    label_comp_luz1_cor_r = gtk_label_new("Fill_Light-R:");
    scale_comp_luz1_cor_r = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -1.0, 1.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_luz1_cor_r), comp_luz1_cor_r); // gtk_RANGE_set_value ? Pq o gtx_scale_set_value não existe e o Scale herda o Range
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_luz1_cor_r), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_luz1_cor_r), TRUE);
    gtk_widget_set_hexpand(scale_comp_luz1_cor_r, TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_luz1_cor_r, 2, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_luz1_cor_r, 3, 5, 1, 1);
    g_signal_connect(scale_comp_luz1_cor_r, "value-changed", G_CALLBACK(scale_comp_luz1_cor_r_changed), NULL);

    label_comp_luz1_cor_g = gtk_label_new("Fill_Light-G:");
    scale_comp_luz1_cor_g = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -1.0, 1.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_luz1_cor_g), comp_luz1_cor_g); // gtk_RANGE_set_value ? Pq o gtx_scale_set_value não existe e o Scale herda o Range
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_luz1_cor_g), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_luz1_cor_g), TRUE);
    gtk_widget_set_hexpand(scale_comp_luz1_cor_g, TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_luz1_cor_g, 2, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_luz1_cor_g, 3, 6, 1, 1);
    g_signal_connect(scale_comp_luz1_cor_g, "value-changed", G_CALLBACK(scale_comp_luz1_cor_g_changed), NULL);

    label_comp_luz1_cor_b = gtk_label_new("Fill_Light-B:");
    scale_comp_luz1_cor_b = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -1.0, 1.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_luz1_cor_b), comp_luz1_cor_b); // gtk_RANGE_set_value ? Pq o gtx_scale_set_value não existe e o Scale herda o Range
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_luz1_cor_b), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_luz1_cor_b), TRUE);
    gtk_widget_set_hexpand(scale_comp_luz1_cor_b, TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_luz1_cor_b, 2, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_luz1_cor_b, 3, 7, 1, 1);
    g_signal_connect(scale_comp_luz1_cor_b, "value-changed", G_CALLBACK(scale_comp_luz1_cor_b_changed), NULL);


    //###Luz_2:
    label_comp_luz2_ligada = gtk_label_new("Back_Light:");
    check_button_comp_luz2_ligada = gtk_check_button_new();
    gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_comp_luz2_ligada), comp_luz2_ligada);
    gtk_widget_set_hexpand(check_button_comp_luz2_ligada, FALSE); // FALSE pq fica deformado (muito esticado com TRUE)
    gtk_grid_attach(GTK_GRID(grid), label_comp_luz2_ligada, 2, 8, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), check_button_comp_luz2_ligada, 3, 8, 1, 1);
    g_signal_connect(check_button_comp_luz2_ligada, "toggled", G_CALLBACK(check_button_comp_luz2_ligada_changed), NULL);

    label_comp_luz2_cor_r = gtk_label_new("Back_Light-R:");
    scale_comp_luz2_cor_r = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -1.0, 1.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_luz2_cor_r), comp_luz2_cor_r); // gtk_RANGE_set_value ? Pq o gtx_scale_set_value não existe e o Scale herda o Range
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_luz2_cor_r), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_luz2_cor_r), TRUE);
    gtk_widget_set_hexpand(scale_comp_luz2_cor_r, TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_luz2_cor_r, 2, 9, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_luz2_cor_r, 3, 9, 1, 1);
    g_signal_connect(scale_comp_luz2_cor_r, "value-changed", G_CALLBACK(scale_comp_luz2_cor_r_changed), NULL);

    label_comp_luz2_cor_g = gtk_label_new("Back_Light-G:");
    scale_comp_luz2_cor_g = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -1.0, 1.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_luz2_cor_g), comp_luz2_cor_g); // gtk_RANGE_set_value ? Pq o gtx_scale_set_value não existe e o Scale herda o Range
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_luz2_cor_g), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_luz2_cor_g), TRUE);
    gtk_widget_set_hexpand(scale_comp_luz2_cor_g, TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_luz2_cor_g, 2, 10, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_luz2_cor_g, 3, 10, 1, 1);
    g_signal_connect(scale_comp_luz2_cor_g, "value-changed", G_CALLBACK(scale_comp_luz2_cor_g_changed), NULL);

    label_comp_luz2_cor_b = gtk_label_new("Back_Light-B:");
    scale_comp_luz2_cor_b = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -1.0, 1.0, 0.001);
    gtk_range_set_value(GTK_RANGE(scale_comp_luz2_cor_b), comp_luz2_cor_b); // gtk_RANGE_set_value ? Pq o gtx_scale_set_value não existe e o Scale herda o Range
    gtk_scale_set_value_pos(GTK_SCALE(scale_comp_luz2_cor_b), GTK_POS_LEFT);
    gtk_scale_set_draw_value(GTK_SCALE(scale_comp_luz2_cor_b), TRUE);
    gtk_widget_set_hexpand(scale_comp_luz2_cor_b, TRUE);
    gtk_grid_attach(GTK_GRID(grid), label_comp_luz2_cor_b, 2, 11, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale_comp_luz2_cor_b, 3, 11, 1, 1);
    g_signal_connect(scale_comp_luz2_cor_b, "value-changed", G_CALLBACK(scale_comp_luz2_cor_b_changed), NULL);




    gtk_window_set_child(GTK_WINDOW(window), grid);


    /*// creates the spinbutton, with three decimal places
    adjustment = gtk_adjustment_new (2.500, 0.0, 5.0, 0.001, 0.1, 0.0);
    button = gtk_spin_button_new (adjustment, 0.001, 3);
    gtk_window_set_child (GTK_WINDOW (window), button);*/
}

void* janelaDeControleGtk(void* arg) { // Usando Gtk4 e não Gtkmm para inicializar

    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL); // <-- Precisa criar um sinal 'activate' que vai chamar a funcão 'activate' que instancia uma janela
    //status = g_application_run (G_APPLICATION (app), argc, argv);
    status = g_application_run (G_APPLICATION (app), 0, NULL);
    g_object_unref (app);

    //return status;
    return nullptr; // Pq tem 'void*' no tipo de retorno !
}


#endif
