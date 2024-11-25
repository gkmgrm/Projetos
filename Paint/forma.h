#ifndef __FORMA_H__
#define __FORMA_H__

// Formas
#define RETANGULO 0
#define QUADRADO 1
#define TRINAGULO_ISOSCELES 2
#define TRIANGULO_EQUILATERO 3
#define LINHA 4
#define HEXAGONO 5
#define CIRCULO 6
#define ESTRELA 7
#define ELIPSE 8

// Modos
#define APAGAR -1
#define INSERIR -2
#define MUDARCORFORMA -3
#define MUDARCONTORNOFORMA -4
#define MOVERFORMA -5
#define ALTERARTAMANHO -6

typedef struct forma* Forma;

// Cria forma
Forma criar_forma(int tipo, float x, float y, float comprimento, float altura);
Forma criar_forma_centro(int tipo, float x, float y, float comprimento, float altura);

// Funções retângulo
Forma cria_retangulo(float Xi, float Yi, float Xf, float Yf);
Forma novo_retangulo(float x, float y, float comprimento, float altura);
void desenhar_retangulo(Forma f);
void desenhar_contorno_retangulo(Forma f);

// Funções quadrado
Forma cria_quadrado(float Xi, float Yi, float Xf, float Yf);
Forma novo_quadrado(float x, float y, float tamanho);
void desenharQuadrado(Forma f);
void desenhar_contorno_quadrado(Forma f);

// Funções triângulo isosceles
Forma criar_triangulo_isosceles(float Xi, float Yi, float Xf, float Yf);
Forma novo_triangulo_isosceles(float x, float y, float comprimento, float altura);
void desenhar_triangulo_isosceles(Forma f);
void desenhar_contorno_triangulo_isosceles(Forma f);

// Funções triângulo equilátero
Forma criar_triangulo_equilatero(float Xi, float Yi, float Xf, float Yf);
Forma novo_triangulo_equilatero(float x, float y, float lado);
void desenhar_triangulo_equilatero(Forma f);
void desenhar_contorno_triangulo_equilatero(Forma f);

// Funções linha
Forma criar_linha(float Xi, float Yi, float Xf, float Yf);
void desenhar_linha(Forma f);
void desenhar_contorno_linha(Forma f);

// Funções hexágono
Forma criar_hexagono(float Xi, float Yi, float Xf, float Yf);
Forma novo_hexagono(float x, float y, float comprimento, float altura);
void desenhar_hexagono(Forma f);
void desenhar_contorno_hexagono(Forma f);

// Funções elipse
Forma criar_elipse(float Xi, float Yi, float Xf, float Yf);
Forma nova_elipse(float x, float y, float, float);
void desenhar_elipse(Forma f);
void desenhar_contorno_elipse(Forma f);

// Funções círculo
void desenhar_circulo(Forma f);
void desenhar_contorno_circulo(Forma f);
Forma criar_circulo(float Xi, float Yi, float Xf, float Yf);
Forma novo_circulo(float x, float y, float raio);

// Funções estrela
void desenhar_estrela(Forma f);
Forma nova_estrela(float x, float y, float comprimento, float altura);
Forma criar_estrela(float Xi, float Yi, float Xf, float Yf);
void desenhar_contorno_estrela(Forma f);

// Funções dos modos apagar, inserir, mudar cor, etc
Forma novo_quadrado_apagar(float x, float y, float);
void desenhar_quadrado_apagar(Forma f);
Forma novo_quadrado_inserir(float x, float y, float lado);
void desenhar_quadrado_inserir(Forma f);
Forma novo_quadrado_mudar_cor_forma(float x, float y, float lado);
void desenhar_quadrado_mudar_cor_forma(Forma f);
Forma novo_quadrado_mudar_contorno(float x, float y, float lado);
void desenhar_quadrado_mudar_contorno(Forma f);
Forma novo_quadrado_mover_forma(float x, float y, float lado);
void desenhar_quadrado_mover_forma(Forma f);
Forma novo_quadrado_alterar_tamanho(float x, float y, float lado);
void desenhar_quadrado_alterar_tamanho(Forma f);

// Funções genéricas
void apagar_forma(Forma f);
void desenhar_forma(Forma f);
void definirCorFundo(Forma f, float r, float g, float b);
void get_cor(Forma f, float* c);
void muda_pontos(Forma f, float x, float y);
int apanha_clique(Forma f, float x, float y);
void set_tipo(Forma f, int tipo);
int get_tipo(Forma f);
void desenhar_contorno(Forma f);
void definir_contorno(Forma f, float r, float g, float b);
void desloca_forma(Forma f, float x, float y);
void get_coord_quadrado(float Xi, float Yi, float Xf, float Yf, float* coordenadas);
int esta_area_desenho(Forma f, int windowX, int windowY);


#endif