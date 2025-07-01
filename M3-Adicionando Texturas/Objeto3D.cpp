#include "Objeto3D.h"


Objeto3D::Objeto3D(){
    this->nome = "";
    //this->VAO = nullptr; error: cannot convert ‘std::nullptr_t’ to ‘unsigned int’ in assignment
    this->VAO = 0;
    this->nVertices = 0;

    this->caminhoArquivo = "";
    this->xT = 0.0;
    this->yT = 0.0;
    this->zT = 0.0;
    this->tipoRot = 0;
    this->anguloX = 0.0;
    this->anguloY = 0.0;
    this->anguloZ = 0.0;
    this->escala = 0.0;
}


// Construtor que não carrega objetos -- usa definição direto no main de VAOs
Objeto3D::Objeto3D(string nome, float xT, float yT, float zT, int tipoRot, float anguloX, float anguloY, float anguloZ, float escala){
    this->nome = nome;
    this->VAO = 0;
    this->nVertices = 0;

    this->caminhoArquivo = "";
    this->xT = xT;
    this->yT = yT;
    this->zT = zT;
    this->tipoRot = tipoRot;
    this->anguloX = anguloX;
    this->anguloY = anguloY;
    this->anguloZ = anguloZ;
    this->escala = escala;

}


Objeto3D::Objeto3D(string nome, string caminhoArquivo, float xT, float yT, float zT, int tipoRot, float anguloX, float anguloY, float anguloZ, float escala) {
    this->nome = nome;
    this->VAO = 0;
    this->nVertices = 0;

    this->caminhoArquivo = caminhoArquivo;
    this->xT = xT;
    this->yT = yT;
    this->zT = zT;
    this->tipoRot = tipoRot;
    this->anguloX = anguloX;
    this->anguloY = anguloY;
    this->anguloZ = anguloZ;
    this->escala = escala;

    //int nVertices2;
    //this->VAO = loadSimpleOBJ(this->caminhoArquivo, nVertices2);
    //this->nVertices = nVertices2;
    //HACK: Por enquanto feito direto em 'atividade_vivencial_1.cpp'
}

Objeto3D Objeto3D::clonar(){
    Objeto3D oN = Objeto3D();
    oN.VAO = this->VAO; // Pode ser '=' aqui para fazer a cópia pq são tipos primitivos ! -- Se fosse classe teria que usar '()' ou um método proprio tipo 'clonar()'
    oN.nVertices = this->nVertices;

    oN.caminhoArquivo = this->caminhoArquivo; //TODO '=' é correto aqui ???
    oN.xT = this->xT;
    oN.yT = this->yT;
    oN.zT = this->zT;
    oN.tipoRot = this->tipoRot;
    oN.anguloX = this->anguloX;
    oN.anguloY = this->anguloY;
    oN.anguloZ = this->anguloZ;
    oN.escala = this->escala;
    return oN;
};

string Objeto3D::getNome(){
    return nome;
};

int Objeto3D::getVAO(){
    return VAO;
};
//void Objeto3D::setVAO(int VAO); // Deletar ?

int Objeto3D::getNVertices(){
    return nVertices;
};
//void Objeto3D::setNVertices(int nVertices); // Deletar ?

string Objeto3D::getCaminhoArquivo(){
    return caminhoArquivo;
};
//void Objeto3D::setCaminhoArquivo(string caminhoArquivo); // Deletar ?

void Objeto3D::setXT(float xT){
    this->xT = xT;
};
float Objeto3D::getXT(){
    return xT;
};
void Objeto3D::setYT(float yT){
    this->yT = yT;
};
float Objeto3D::getYT(){
    return yT;
};
void Objeto3D::setZT(float zT){
    this->zT = zT;
};
float Objeto3D::getZT(){
    return zT;
};

void Objeto3D::setTipoRot(int tipoRot){
    this->tipoRot = tipoRot;
};
int Objeto3D::getTipoRot(){
    return tipoRot;
};

void Objeto3D::setAnguloX(float anguloX){
    this->anguloX = anguloX;
};
float Objeto3D::getAnguloX(){
    return anguloX;
};
void Objeto3D::setAnguloY(float anguloY){
    this->anguloY = anguloY;
};
float Objeto3D::getAnguloY(){
    return anguloY;
};
void Objeto3D::setAnguloZ(float anguloZ){
    this->anguloZ = anguloZ;
};
float Objeto3D::getAnguloZ(){
    return anguloZ;
};

void Objeto3D::setEscala(float escala){
    this->escala = escala;
};
float Objeto3D::getEscala(){
    return escala;
};

glm::mat4 Objeto3D::calculaTransformacoes(){

    // create transformations para triângulo 1
    //glm::mat4 transform1 = glm::mat4(1.0f);
    glm::mat4 transform1 = glm::mat4(1.0f);// make sure to initialize matrix to identity matrix first

    //transform1 = glm::translate(transform1, glm::vec3(quad[i][j].getTX()*i, -quad[i][j].getTY()*j, 0.0f));
    //transform1 = glm::translate(transform1, glm::vec3(0.0f+xT, 0.0f+yT, 0.0f+zT)); // Deletar !
    transform1 = glm::translate(transform1, glm::vec3(xT, yT, zT));// ###IMPORTANTE:  A translação deve ser a última operação a ser realizada para evitar deformações na imagem !!! --- Informação ainda não confirmada na prática ! -- Dica dada pelo professor Tonietto

    //Model = glm::rotate(Model, angle_in_radians, glm::vec3(x, y, z)); // where x, y, z is axis of rotation (e.g. 0 1 0)

    //if (tipoRot & 4 == 4) {//Pq | (tipoRot & 4) == 4 =>1 | tipoRot & 4 == 4 =>0
    if ((tipoRot & 4) == 4) {// => se for 4 tem rotação no eixo X
        transform1 = glm::rotate(transform1, anguloX, glm::vec3(1, 0, 0));
    }
    if ((tipoRot & 2) == 2) {// => se for 2 tem rotação no eixo Y
        transform1 = glm::rotate(transform1, anguloY, glm::vec3(0, 1, 0));
    }
    if ((tipoRot & 1) == 1) {// => se for 1 tem rotação no eixo Z
        transform1 = glm::rotate(transform1, anguloZ, glm::vec3(0, 0, 1));

    }

    //if (escala != 1.0) {// => Se tiver alteração no fator de escala, faz a transformação
        //modelview = glm::scale( modelview, glm::vec3(Scale,Scale,Scale) )
    transform1 = glm::scale(transform1, glm::vec3(escala, escala, escala));

    return transform1;
    }

void Objeto3D::imprimeATransformacao(glm::mat4 matriz) {
    for (int i =0; i<16; i++){ // mat4 => matriz 4x4
            //cout << "transform0[" << i << "] =" << transform0[i] << endl; // error: no match for ‘operator<<’ (operand types are ‘std::basic_ostream<char>’ and ‘glm::mat<4, 4, float, glm::packed_highp>::col_type’ {aka ‘glm::vec<4, float, glm::packed_highp>’})
            //cout << "&transform0[0][" << i << "] =" << &transform0[0][i] << endl; OK funciona ! --> &transform0[0][0] =0x7ffdce693740
            //cout << "*transform0[0][" << i << "] =" << *transform0[0][i] << endl; // error: invalid type argument of unary ‘*’ (have ‘float’)
            cout << "mat4[" << (i/4) << "][" << (i%4) << "] =" << matriz[i/4][i%4] << endl;
        }
}

string Objeto3D::toString(){
    string s = "Objeto3D: [";
    s += "nome: ";
    s += nome;
    s += ", VAO: ";
    s += to_string(VAO);
    s += ", nVertices: ";
    s += to_string(nVertices);
    s += ", caminhoArquivo: ";
    s += caminhoArquivo;

    s += ", xT: ";
    s += to_string(xT);
    s += ", yT: ";
    s += to_string(yT);
    s += ", zT: ";
    s += to_string(zT);

    s += ", tipoRot: ";
    s += to_string(tipoRot);

    s += ", anguloX: ";
    s += to_string(anguloX);
    s += ", anguloY: ";
    s += to_string(anguloY);
    s += ", anguloZ: ";
    s += to_string(anguloZ);

    s += ", escala: ";
    s += to_string(escala);

    s += "]";
    return s;

}
