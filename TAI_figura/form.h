#ifndef __FORM_H__
#define __FORM_H__

/*
*  This interface provides clients with handles to form objects,
*  but does not give any information about the internal representation.
*  (The struct is specified only by its tag name.)
*/


#define RETANGULO 0
#define QUADRADO 1
#define TRINAGULO_ISOSCELES 2
#define LINHA 3
#define HEXAGONO 4
#define TRIANGULO_EQUILATERO 5
#define CIRCULO 6

#define AZUL 0x0000FF
#define VERMELHO 0xFF0000
#define VERDE 0x00FF00
#define PRETO 0x000000
#define BRANCO 0x111111

typedef struct form* Form;

// create a new form by given the original point and the sides
Form newForm(float x, float y, float xSize, float ySize);
Form newFormC(int type, float x, float y, float xSize, float ySize);

//Figuras criadas no canto inferior esquerdo
Form novo_retangulo(float x, float y, float x_size, float y_size);
Form novo_quadrado(float x, float y, float lado);
Form novo_triangulo_isosceles(float x, float y, float x_size, float y_size);
Form nova_linha(float x, float y, float x_size, float y_size);
Form novo_hexagono(float x, float y, float lado);
Form novo_triangulo_equilatero(float x, float y, float lado);
Form novo_circulo(float x, float y, float lado);

//Figuras criadas pelo centro
Form novo_retangulo_centro(float x, float y, float x_size, float y_size);
Form novo_quadrado_centro(float x, float y, float lado);
Form novo_triangulo_isosceles_centro(float x, float y, float x_size, float y_size);
Form novo_hexagono_centro(float x, float y, float lado);
Form novo_triangulo_equilatero_centro(float x, float y, float lado);

// Figuras criadas por dois pontos
Form novo_retangulo_2pontos(float Xi, float Yi, float Xf, float Yf);
Form cria_quadrado(float Xi, float Yi, float Xf, float Yf);
Form novo_isosceles_2pontos(float Xi, float Yi, float Xf, float Yf);
Form criar_triangulo_equilatero(float Xi, float Yi, float Xf, float Yf);

//Cor
void set_background_color(Form f, float cor_r, float cor_g, float cor_b);
void set_type(Form f, int type);

// delete form
void deleteForm(Form f);

// update a form position - moving by (dx,dy)
void updateForm(Form f, float dx, float dy);

//Escolhe a forma a desenhar
void draw_form(Form f);

//Desenha a forma escolhida
void printfForm(Form f);
void draw_retangulo(Form f);
void draw_quadrado(Form f);
void draw_triangulo(Form f);
void draw_line(Form f);
void draw_hexagono(Form f);
void draw_triangulo_equilatero(Form f);
void draw_circulo(Form f);

float getVertex1_X(Form f);
float getVertex1_Y(Form f);
float getVertex2_X(Form f);
float getVertex2_Y(Form f);
float getVertex3_X(Form f);
float getVertex3_Y(Form f);
float getVertex4_X(Form f);
float getVertex4_Y(Form f);

int pick(Form f, float x, float y);

void set_clique(Form f, int n_clique);

#endif

