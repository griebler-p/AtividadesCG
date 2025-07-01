// UNISINOS
// Curso: Ciência da Computação - Híbrido
// Atividade Acadêmica - Computação Gráfica
// Módulo 4
// Tarefa: Atividade Vivencial 2 - Técnica de Iluminação de 3 pontos
// Data: 31/05/2025
// Professor: Rossana Baptista Queiroz
// Alunos: Paulo Griebler Júnior e Rodrigo Pires
// Registros Acadêmicos: 1930669 e 1917485

#ifndef AUX_H
#define AUX_H

#include <cmath>

using namespace std;

// Métodos estáticos auxiliares: - constantes e transformações matemáticas
class Aux{
    public:
        //static const float PI = 3.141516; // error: ‘constexpr’ needed for in-class initialization of static data member ‘const float Aux::PI’ of non-integral type
        static constexpr float PI = 3.141516;

        // conversão radianos - > graus
            // 180°  PI
            // --- = ---
            // x°    yRad

            // yRad = (x°. PI)/180°
        static float radianos(float g) {
            //float rad = (g*PI)/180;
            float rad = g*PI/180;
            return rad;
        }

        static float graus(float r) {
            float gra = r*180/PI;
            return gra;
        }

        // Gemini: "open gl normal of a triangle"
        /*Example:
        Let's say you have a triangle with vertices A(1, 0, 0), B(0, 1, 0), and C(0, 0, 1).
        1. Edge vectors:
            AB = B - A = (0, 1, 0) - (1, 0, 0) = (-1, 1, 0)
            AC = C - A = (0, 0, 1) - (1, 0, 0) = (-1, 0, 1)
        2. Cross product:
            N = AB x AC = ((-1 * 0) - (1 * 1), (1 * -1) - (-1 * 0), (-1 * 0) - (-1 * 0)) = (-1, -1, 0)
        3. Normalization:
            |N| = sqrt((-1)^2 + (-1)^2 + 0^2) = sqrt(2)
            Normalized normal = N / |N| = (-1/sqrt(2), -1/sqrt(2), 0)
        Important Considerations:
        Vertex order:
            The order in which you define the vertices for the triangle affects the direction of the normal. Using a consistent order (e.g., counter-clockwise or clockwise) ensures that the normals always point in the correct direction relative to the face.
        Normal per vertex vs. normal per face:
            You can calculate a normal for each triangle (per-face normal) or you can calculate a smooth normal at each vertex by averaging the normals of all triangles that share that vertex (per-vertex normal).
        Smooth shading:
            Smooth shading is a technique that uses per-vertex normals to create smoother lighting effects on curved surfaces, rather than the flat shading that would result from per-face normals.
        OpenGL functionality:
            In OpenGL, you can upload these calculated normals as attributes along with vertex data and use them for lighting calculations in your shaders.*/


        //A x B = <a2 * b3 - b2 * a3, b1 * a3 - a1 * b3, a1 * b2 - b1 * a2>
        static void produtoVetorial(float a1, float a2, float a3, float b1, float b2, float b3, float &c1, float&c2, float&c3) { // 'Cross Product'
            c1 = a2*b3-b2*a3;
            c2 = b1*a3-a1*b3;
            c3 = a1*b2-b1*a2;
        }

        static float moduloVetor(float a1, float a2, float a3) { // |N|
            //return sqrt((a1)^2 + (a2)^2 + (a3)^2); // error: invalid operands of types ‘float’ and ‘float’ to binary ‘operator^’
            return sqrtf((a1*a1) + (a2*a2) + (a3*a3)); // Sem uso de <cmath> pow(base, expoente), porém para sqrtf() (raiz quadrada de floats precisa do cmath)
        }
        static void normalizacaoDaNormal(float a1, float a2, float a3, float moduloV, float &b1, float &b2, float &b3) { // N/|N| -> produto vetorial / módulo do vetor do produto vetorial
            b1 = a1/moduloV;
            b2 = a2/moduloV;
            b3 = a3/moduloV;
        }


};

#endif
