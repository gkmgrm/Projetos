#include "forma.h"
#include <stdlib.h>
#include<gl/glut.h>
#include <math.h>

#include <stdio.h>
struct forma {
	int tipo;
	float x, y;             
	float comprimento, altura;     
	float r, g, b;
	float r_contorno, g_contorno, b_contorno;
};

Forma criar_forma(int tipo, float x, float y, float comprimento, float altura) {
	Forma f = (Forma)malloc(sizeof(struct forma));

	f->x = x;
	f->y = y;
	f->comprimento = comprimento;
	f->altura = altura;

	f->tipo = tipo;
	f->r = 1;
	f->g = 1;
	f->b = 1;
	f->r_contorno = 1;
	f->g_contorno = 1;
	f->b_contorno = 1;

	return f;
}

Forma criar_forma_centro(int tipo, float x, float y, float comprimento, float altura) {
	return criar_forma(tipo, x + (comprimento / 2), y + (altura / 2), comprimento, altura);
}

void definirCorFundo(Forma f, float r, float g, float b)
{
	f->r = r;
	f->g = g;
	f->b = b;
}


void definir_contorno(Forma f, float r, float g, float b)
{
	f->r_contorno = r;
	f->g_contorno = g;
	f->b_contorno = b;
}

void apagar_forma(Forma f) {
	free(f);
}

/* Retângulo */
Forma cria_retangulo(float Xi, float Yi, float Xf, float Yf) {
	return criar_forma(RETANGULO, Xi, Yi, (Xf - Xi), (Yf - Yi));
}

Forma novo_retangulo(float x, float y, float comprimento, float altura) {
	return criar_forma(RETANGULO, x, y, comprimento, altura);
}

void desenhar_retangulo(Forma f) {
	glColor3f(f->r, f->g, f->b);
	glBegin(GL_POLYGON);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x, f->y + f->altura);
	glVertex2f(f->x + f->comprimento, f->y + f->altura);
	glVertex2f(f->x + f->comprimento, f->y);
	glEnd();
	
}

void desenhar_contorno_retangulo(Forma f) {
	glColor3f(f->r_contorno, f->g_contorno, f->b_contorno);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x, f->y + f->altura);
	glVertex2f(f->x + f->comprimento, f->y + f->altura);
	glVertex2f(f->x + f->comprimento, f->y);
	glEnd();
}

/* Quadrado */
Forma cria_quadrado(float Xi, float Yi, float Xf, float Yf) {
	float coordenadas[2], novoXf, novoYf;

	get_coord_quadrado(Xi, Yi, Xf, Yf, coordenadas);
	novoXf = coordenadas[0];
	novoYf = coordenadas[1];
	
	return criar_forma(QUADRADO, Xi, Yi, novoXf - Xi, novoYf - Yi);
}

Forma novo_quadrado(float x, float y, float tamanho) {
	return criar_forma(QUADRADO, x, y, tamanho, tamanho);
}

void desenharQuadrado(Forma f) {
	glColor3f(f->r, f->g, f->b);
	glBegin(GL_POLYGON);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x, f->y + f->altura);
	glVertex2f(f->x + f->comprimento, f->y + f->altura);
	glVertex2f(f->x + f->comprimento, f->y);
	glEnd();
}

void desenhar_contorno_quadrado(Forma f) {
	glColor3f(f->r_contorno, f->g_contorno, f->b_contorno);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x, f->y + f->altura);
	glVertex2f(f->x + f->comprimento, f->y + f->altura);
	glVertex2f(f->x + f->comprimento, f->y);
	glEnd();
}

/* Trinângulo Isosceles */
Forma criar_triangulo_isosceles(float Xi, float Yi, float Xf, float Yf) {
	return criar_forma(TRINAGULO_ISOSCELES, Xi, Yi, (Xf - Xi), (Yf - Yi));
}

Forma novo_triangulo_isosceles(float x, float y, float comprimento, float altura) {
	return criar_forma(TRINAGULO_ISOSCELES, x, y, comprimento, altura);
}

void desenhar_triangulo_isosceles(Forma f) {
	glColor3f(f->r, f->g, f->b);
	glBegin(GL_TRIANGLES);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x + (f->comprimento / 2), f->y + f->altura);
	glVertex2f(f->x + f->comprimento, f->y);
	glEnd();
}

void desenhar_contorno_triangulo_isosceles(Forma f) {
	glColor3f(f->r_contorno, f->g_contorno, f->b_contorno);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x + (f->comprimento / 2), f->y + f->altura);
	glVertex2f(f->x + f->comprimento, f->y);
	glEnd();
}

/* Trinâgulo Equilátero */
Forma criar_triangulo_equilatero(float Xi, float Yi, float Xf, float Yf) {
	float coordenadas[2], novoXf, novoYf;

	get_coord_quadrado(Xi, Yi, Xf, Yf, coordenadas);
	novoXf = coordenadas[0];
	novoYf = coordenadas[1];

	return criar_forma(TRIANGULO_EQUILATERO, Xi, Yi, novoXf - Xi, novoYf - Yi);
}

Forma novo_triangulo_equilatero(float x, float y, float lado) {
	return criar_forma(TRIANGULO_EQUILATERO, x, y, lado, lado);
}

void desenhar_triangulo_equilatero(Forma f) {
	glColor3f(f->r, f->g, f->b);
	glBegin(GL_TRIANGLES);
		glVertex2f(f->x, f->y);
		glVertex2f(f->x + (f->comprimento / 2), f->y + f->altura);
		glVertex2f(f->x + f->comprimento, f->y);
	glEnd();
}

void desenhar_contorno_triangulo_equilatero(Forma f) {
	glColor3f(f->r_contorno, f->g_contorno, f->b_contorno);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x + (f->comprimento / 2), f->y + f->altura);
	glVertex2f(f->x + f->comprimento, f->y);
	glEnd();
}

/* Linha */
Forma criar_linha(float Xi, float Yi, float Xf, float Yf) {
	return criar_forma(LINHA, Xi, Yi, (Xf - Xi), (Yf - Yi));
}

void desenhar_linha(Forma f) {
	glColor3f(f->r, f->g, f->b);
	glBegin(GL_LINES);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x + f->comprimento, f->y + f->altura);
	glEnd();
}

void desenhar_contorno_linha(Forma f) {
	glColor3f(f->r_contorno, f->g_contorno, f->b_contorno);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x + f->comprimento, f->y + f->altura);
	glEnd();
}

/* Hexágono */
Forma criar_hexagono(float Xi, float Yi, float Xf, float Yf) {
	return criar_forma(HEXAGONO, Xi, Yi, (Xf - Xi), (Yf - Yi));
}

Forma novo_hexagono(float x, float y, float comprimento, float altura) {
	return criar_forma(HEXAGONO, x, y, comprimento, altura);
}

void desenhar_hexagono(Forma f) {
	glColor3f(f->r, f->g, f->b);
	glBegin(GL_POLYGON);
	glVertex2f(f->x, f->y + f->altura / 2);
	glVertex2f(f->x + f->comprimento/3, f->y + f->altura);
	glVertex2f(f->x + 2 * f->comprimento / 3, f->y + f->altura);
	glVertex2f(f->x + f->comprimento, f->y + f->altura / 2);
	glVertex2f(f->x + 2*f->comprimento/3, f->y);
	glVertex2f(f->x + f->comprimento / 3, f->y);
	glEnd();
}

void desenhar_contorno_hexagono(Forma f) {
	glColor3f(f->r_contorno, f->g_contorno, f->b_contorno);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glVertex2f(f->x, f->y + f->altura / 2);
	glVertex2f(f->x + f->comprimento / 3, f->y + f->altura);
	glVertex2f(f->x + 2 * f->comprimento / 3, f->y + f->altura);
	glVertex2f(f->x + f->comprimento, f->y + f->altura / 2);
	glVertex2f(f->x + 2 * f->comprimento / 3, f->y);
	glVertex2f(f->x + f->comprimento / 3, f->y);
	glEnd();
}

/* Elipse */
Forma criar_elipse(float Xi, float Yi, float Xf, float Yf) {
	return criar_forma(ELIPSE, Xi, Yi, (Xf - Xi), (Yf - Yi));
}

Forma nova_elipse(float x, float y, float comprimento, float altura) {
	return criar_forma(ELIPSE, x, y, comprimento, altura);
}

void desenhar_elipse(Forma f) {
	float teta, x, y, centroX, centroY;
	
	centroX = f->comprimento / 2;
	centroY = f->altura / 2;

	glColor3f(f->r, f->g, f->b);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10)
	{
		teta = i * 3.1416 / 180;
		x = f->x + centroX + cos(teta) * centroX;
		y = f->y + centroY + sin(teta) * centroY;
		glVertex2f(x, y);
	}
	glEnd();
}

void desenhar_contorno_elipse(Forma f){
	float teta, x, y, centroX, centroY;
	
	centroX = f->comprimento / 2;
	centroY = f->altura / 2;

	glColor3f(f->r_contorno, f->g_contorno, f->b_contorno);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i += 10)
	{
		teta = i * 3.1416 / 180;
		x = f->x + centroX + cos(teta) * centroX;
		y = f->y + centroY + sin(teta) * centroY;
		glVertex2f(x, y);
	}
	glEnd();
}

/* Circulo */
Forma criar_circulo(float Xi, float Yi, float Xf, float Yf) {
	return criar_forma(CIRCULO, Xi, Yi, (Xf - Xi), (Yf - Yi));
}

Forma novo_circulo(float x, float y, float raio) {
	return criar_forma(CIRCULO, x, y, raio, raio);
}

void desenhar_circulo(Forma f) {
	float teta, raio, centroX, centroY;
	
	// Calcula raio e coordenadas do centro
	raio = f->comprimento / 2; 
	centroX = f->x + f->comprimento / 2; 
	centroY = f->y + f->altura / 2;     

	glColor3f(f->r, f->g, f->b);
	
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 10) { 
		teta = i * 3.1416 / 180; 
		float x = centroX + cos(teta) * raio;
		float y = centroY + sin(teta) * raio;
		glVertex2f(x, y);
	}
	glEnd();
}

void desenhar_contorno_circulo(Forma f) {
	float teta, raio, centroX, centroY;

	raio = f->comprimento / 2;
	centroX = f->x + f->comprimento / 2;
	centroY = f->y + f->altura / 2;

	glColor3f(f->r_contorno, f->g_contorno, f->b_contorno); 
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i += 10) {
		teta = i * 3.1416 / 180;
		float x = centroX + cos(teta) * raio;
		float y = centroY + sin(teta) * raio;
		glVertex2f(x, y);
	}
	glEnd();

}

/* Estrela */
Forma nova_estrela(float x, float y, float comprimento, float altura) {
	return criar_forma(ESTRELA, x, y, comprimento, altura);
}

Forma criar_estrela(float Xi, float Yi, float Xf, float Yf) {
	return criar_forma(ESTRELA, Xi, Yi, (Xf - Xi), (Yf - Yi));
}

void desenhar_estrela(Forma f) {
	glColor3f(f->r, f->g, f->b);
	
	// Triângulo esquerdo cima
	glBegin(GL_TRIANGLES);
	glVertex2f(f->x + 2 * f->comprimento/6, f->y + 2.5 * f->altura /6);
	glVertex2f(f->x, f->y + 3.75 * f->altura /6);
	glVertex2f(f->x + 2.25 * f->comprimento/6, f->y + 3.75 * f->altura /6);
	glEnd();

	// Triângulo esquerdo baixo
	glBegin(GL_TRIANGLES);
	glVertex2f(f->x + 2 * f->comprimento / 6, f->y + 2.5 * f->altura / 6);
	glVertex2f(f->x + 1.5 * f->comprimento/6, f->y);
	glVertex2f(f->x + f->comprimento / 2, f->y + 1.5 * f->altura / 6);
	glEnd();

	// Triângulo direito baixo
	glBegin(GL_TRIANGLES);
	glVertex2f(f->x + f->comprimento / 2, f->y + 1.5 * f->altura / 6);
	glVertex2f(f->x + 4 * f->comprimento / 6, f->y + 2.5 * f->altura / 6);
	glVertex2f(f->x + 4.5 * f->comprimento / 6, f->y);
	glEnd();

	// Triângulo direito cima
	glBegin(GL_TRIANGLES);
	glVertex2f(f->x + 4 * f->comprimento / 6, f->y + 2.5 * f->altura / 6);
	glVertex2f(f->x + f->comprimento, f->y + 3.75 * f->altura / 6);
	glVertex2f(f->x + 3.75 * f->comprimento / 6, f->y + 3.75 * f->altura / 6);
	glEnd();

	// Triângulo cima
	glBegin(GL_TRIANGLES);
	glVertex2f(f->x + 2.25 * f->comprimento / 6, f->y + 3.75 * f->altura / 6);
	glVertex2f(f->x + f->comprimento/2, f->y + f->altura);
	glVertex2f(f->x + 3.75 * f->comprimento / 6, f->y + 3.75 * f->altura / 6);
	glEnd();

	// Pentágono
	glBegin(GL_POLYGON);
	glVertex2f(f->x + 2 * f->comprimento / 6, f->y + 2.5 * f->altura / 6);
	glVertex2f(f->x + 2.25 * f->comprimento / 6, f->y + 3.75 * f->altura / 6);
	glVertex2f(f->x + 3.75 * f->comprimento / 6, f->y + 3.75 * f->altura / 6);
	glVertex2f(f->x + 4 * f->comprimento / 6, f->y + 2.5 * f->altura / 6);
	glVertex2f(f->x + f->comprimento / 2, f->y + 1.5 * f->altura / 6);
	glEnd();
}

void desenhar_contorno_estrela(Forma f) {
	glColor3f(f->r_contorno, f->g_contorno, f->b_contorno);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glVertex2f(f->x, f->y + 3.75 * f->altura / 6);
	glVertex2f(f->x + 2 * f->comprimento/6, f->y + 2.5 * f->altura / 6);
	glVertex2f(f->x + 1.5 * f->comprimento / 6, f->y);
	glVertex2f(f->x + f->comprimento / 2, f->y + 1.5 * f->altura / 6);
	glVertex2f(f->x + 4.5 * f->comprimento / 6, f->y);
	glVertex2f(f->x + 4 * f->comprimento / 6, f->y + 2.5 * f->altura / 6);
	glVertex2f(f->x + f->comprimento, f->y + 3.75 * f->altura / 6);
	glVertex2f(f->x + 3.75 * f->comprimento / 6, f->y + 3.75 * f->altura / 6);
	glVertex2f(f->x + f->comprimento / 2, f->y + f->altura);
	glVertex2f(f->x + 2.25 * f->comprimento / 6, f->y + 3.75 * f->altura / 6);
	glEnd();
}

/* Apagar */
Forma novo_quadrado_apagar(float x, float y, float lado) {
	return criar_forma(APAGAR, x, y, lado, lado);
}

void desenhar_quadrado_apagar(Forma f) {
	float lado = f->comprimento;
	glColor3f(.8, .8, .8);
	glBegin(GL_POLYGON);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x, f->y + lado);
	glVertex2f(f->x + lado, f->y + lado);
	glVertex2f(f->x + lado, f->y);
	glEnd();

	// Desenha corpo da borracha (rosa escuro)
	glColor3f(.9, .55, .55);
	glBegin(GL_POLYGON);
	glVertex2f(f->x + 1.5*lado/5, f->y + lado/5);
	glVertex2f(f->x + 1.5*lado/5, f->y + 3*lado/5);
	glVertex2f(f->x + 3.5*lado/5, f->y + 3*lado/5);
	glVertex2f(f->x + 3.5*lado/5, f->y + lado /5);
	glEnd();	
	
	// Desenha cabeça borracha (branco)
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(f->x + 1.5*lado/5, f->y + 3*lado/5);
	glVertex2f(f->x + 1.5*lado/5, f->y + 4*lado/5);
	glVertex2f(f->x + 3.5*lado/5, f->y + 4*lado /5);
	glVertex2f(f->x + 3.5*lado/5, f->y + 3*lado/5);
	glEnd();

	// Linha esquerda
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(f->x + 1.5*lado/5, f->y + lado / 5);
	glVertex2f(f->x + 1.5*lado / 5, f->y + 4*lado/5);
	glEnd();	
	
	// Linha direita
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(f->x + 3.5*lado/5, f->y + lado / 5);
	glVertex2f(f->x + 3.5*lado / 5, f->y + 4*lado/5);
	glEnd();	
	
	// Linha baixo corpo
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(f->x + 1.5*lado/5, f->y + lado / 5);
	glVertex2f(f->x + 3.5*lado / 5, f->y + lado/5);
	glEnd();

	// Linha cima cabeça
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(f->x + 1.5*lado/5, f->y + 4*lado / 5);
	glVertex2f(f->x + 3.5*lado / 5, f->y + 4*lado/5);
	glEnd();

	// Linha cima corpo
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(f->x + 1.5*lado/5, f->y + 3*lado / 5);
	glVertex2f(f->x + 3.5*lado / 5, f->y + 3*lado/5);
	glEnd();

}

/* Inserir */
Forma novo_quadrado_inserir(float x, float y, float lado) {
	return criar_forma(INSERIR, x, y, lado, lado);
}

void desenhar_quadrado_inserir(Forma f) {
	float lado = f->comprimento;
	glColor3f(.8, .8, .8);
	glBegin(GL_POLYGON);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x, f->y + lado);
	glVertex2f(f->x + lado, f->y + lado);
	glVertex2f(f->x + lado, f->y);
	glEnd();

	// Desenha corpo do lápis (amarelo)
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(f->x + 1.5 * lado / 5, f->y + lado / 5);
	glVertex2f(f->x + 1.5 * lado / 5, f->y + 2.5 * lado / 5);
	glVertex2f(f->x + 3.5 * lado / 5, f->y + 2.5 * lado / 5);
	glVertex2f(f->x + 3.5 * lado / 5, f->y + lado / 5);
	glEnd();

	// Desenha cabeça (amarelo claro)
	glColor3f(1, 1, 0.6);
	glBegin(GL_TRIANGLES);
	glVertex2f(f->x + 1.5 * lado / 5, f->y + 2.5*lado / 5);
	glVertex2f(f->x + 2.5 * lado / 5, f->y + 4 * lado / 5);
	glVertex2f(f->x + 3.5 * lado / 5, f->y + 2.5*lado / 5);
	glEnd();

	// Linha esquerda corpo
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(f->x + 1.5 * lado / 5, f->y + lado / 5);
	glVertex2f(f->x + 1.5 * lado / 5, f->y + 2.5 * lado / 5);
	glEnd();

	// Linha direita corpo
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(f->x + 3.5 * lado / 5, f->y + lado / 5);
	glVertex2f(f->x + 3.5 * lado / 5, f->y + 2.5 * lado / 5);
	glEnd();	
	
	// Linha meio corpo
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(f->x + 2.5 * lado / 5, f->y + lado / 5);
	glVertex2f(f->x + 2.5 * lado / 5, f->y + 2.5 * lado / 5);
	glEnd();

	// Linha baixo 
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(f->x + 1.5 * lado / 5, f->y + lado / 5);
	glVertex2f(f->x + 3.5 * lado / 5, f->y + lado / 5);
	glEnd();	

	// Linha cima 
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(f->x + 1.5 * lado / 5, f->y + 2.5*lado / 5);
	glVertex2f(f->x + 3.5 * lado / 5, f->y + 2.5*lado / 5);
	glEnd();	

	// Linha esquerda cabeça
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(f->x + 1.5 * lado / 5, f->y + 2.5*lado / 5);
	glVertex2f(f->x + 2.5 * lado / 5, f->y + 4*lado / 5);
	glEnd();

	// Linha direita cabeça
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(f->x + 3.5 * lado / 5, f->y + 2.5*lado / 5);
	glVertex2f(f->x + 2.5 * lado / 5, f->y + 4*lado / 5);
	glEnd();	
}

/* Mudar cor da forma */
Forma novo_quadrado_mudar_cor_forma(float x, float y, float lado) {
	return criar_forma(MUDARCORFORMA, x, y, lado, lado);
}

void desenhar_quadrado_mudar_cor_forma(Forma f) {
	float lado = f->comprimento;
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_POLYGON);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x, f->y + lado);
	glVertex2f(f->x + lado, f->y + lado);
	glVertex2f(f->x + lado, f->y);
	glEnd();

	// Desenha o quadrado pequeno
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(f->x + lado / 5, f->y + lado / 5);
	glVertex2f(f->x + lado / 5, f->y + 4*lado / 5);
	glVertex2f(f->x + 4*lado / 5, f->y + 4*lado / 5);
	glVertex2f(f->x + 4 * lado / 5, f->y + lado / 5);
	glEnd();
}

/* Mudar cor de contorno */
Forma novo_quadrado_mudar_contorno(float x, float y, float lado) {
	return criar_forma(MUDARCONTORNOFORMA, x, y, lado, lado);
}

void desenhar_quadrado_mudar_contorno(Forma f) {
	float lado = f->comprimento;
	glColor3f(.8, .8, .8);
	glBegin(GL_POLYGON);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x, f->y + lado);
	glVertex2f(f->x + lado, f->y + lado);
	glVertex2f(f->x + lado, f->y);
	glEnd();

	// Linha baixo
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(f->x + lado/5, f->y + lado / 5);
	glVertex2f(f->x + 4*lado / 5, f->y + lado / 5);
	glEnd();

	// Linha cima
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(f->x + lado / 5, f->y + 4*lado / 5);
	glVertex2f(f->x + 4 * lado / 5, f->y + 4*lado / 5);
	glEnd();

	// Linha esqueda
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(f->x + lado / 5, f->y + lado / 5);
	glVertex2f(f->x + lado / 5, f->y + 4*lado / 5);
	glEnd();

	// Linha direita
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(f->x + 4*lado / 5, f->y + lado / 5);
	glVertex2f(f->x + 4*lado / 5, f->y + 4*lado / 5);
	glEnd();
}

/* Mover forma */
Forma novo_quadrado_mover_forma(float x, float y, float lado) {
	return criar_forma(MOVERFORMA, x, y, lado, lado);
}

void desenhar_quadrado_mover_forma(Forma f) {
	float lado = f->comprimento;
	glColor3f(.8, .8, .8);
	glBegin(GL_POLYGON);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x, f->y + lado);
	glVertex2f(f->x + lado, f->y + lado);
	glVertex2f(f->x + lado, f->y);
	glEnd();

	// Barra horizontal
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(f->x + lado / 4, f->y + lado / 2);
	glVertex2f(f->x + 3 * lado / 4, f->y + lado / 2);
	glEnd();	
	
	// Barra vertical
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(f->x + lado / 2, f->y + lado / 4);
	glVertex2f(f->x + lado / 2, f->y + 3*lado / 4);
	glEnd();
	
	// Seta cima
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2f(f->x + 2*lado / 5, f->y + 3.5*lado / 5);
	glVertex2f(f->x + lado / 2, f->y + 5.5*lado / 6);
	glVertex2f(f->x + 3*lado / 5, f->y + 3.5*lado / 5);
	glEnd();	
	
	// Seta baixo
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2f(f->x + 2*lado / 5, f->y + 1.5*lado / 5);
	glVertex2f(f->x + lado / 2, f->y + .5*lado / 6);
	glVertex2f(f->x + 3*lado / 5, f->y + 1.5*lado / 5);
	glEnd();

	// Seta esquerda
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2f(f->x + 1.5*lado/5, f->y + 2*lado/5);
	glVertex2f(f->x + .5 * lado / 6, f->y + lado / 2);
	glVertex2f(f->x + 1.5 * lado / 5, f->y + 3 * lado / 5);
	glEnd();

	// Seta direita
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2f(f->x + 3.5*lado/5, f->y + 2*lado/5);
	glVertex2f(f->x + 5.5 * lado / 6, f->y + lado / 2);
	glVertex2f(f->x + 3.5 * lado / 5, f->y + 3 * lado / 5);
	glEnd();
}

/* Alterar tamanho forma */
Forma novo_quadrado_alterar_tamanho(float x, float y, float lado) {
	return criar_forma(ALTERARTAMANHO, x, y, lado, lado);
}

void desenhar_quadrado_alterar_tamanho(Forma f) {
	float lado = f->comprimento;
	glColor3f(.8, .8, .8);
	glBegin(GL_POLYGON);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x, f->y + lado);
	glVertex2f(f->x + lado, f->y + lado);
	glVertex2f(f->x + lado, f->y);
	glEnd();

	// Desenha as duas setas
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(f->x + lado / 4, f->y + lado / 2);
	glVertex2f(f->x + 3 * lado / 4, f->y + lado / 2);
	glEnd();

	// Seta esquerda
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2f(f->x + 1.5 * lado / 5, f->y + 1.75 * lado / 5);
	glVertex2f(f->x + .5 * lado / 6, f->y + lado / 2);
	glVertex2f(f->x + 1.5 * lado / 5, f->y + 3.25 * lado / 5);
	glEnd();

	// Seta direita
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2f(f->x + 3.5 * lado / 5, f->y + 1.75 * lado / 5);
	glVertex2f(f->x + 5.5 * lado / 6, f->y + lado / 2);
	glVertex2f(f->x + 3.5 * lado / 5, f->y + 3.25 * lado / 5);
	glEnd();
}

void desenhar_forma(Forma f) {
	// Desenha a forma idenpendentemente do tipo da forma
	switch (f->tipo)
	{
	case RETANGULO:
		desenhar_retangulo(f); break;
	case QUADRADO:
		desenharQuadrado(f); break;
	case TRINAGULO_ISOSCELES:
		desenhar_triangulo_isosceles(f); break;
	case TRIANGULO_EQUILATERO:
		desenhar_triangulo_equilatero(f); break;
	case LINHA:
		desenhar_linha(f); break;
	case CIRCULO:
		desenhar_circulo(f); break;
	case ELIPSE:
		desenhar_elipse(f); break;
	case HEXAGONO:
		desenhar_hexagono(f); break;	
	case ESTRELA:
		desenhar_estrela(f); break;
	case APAGAR:
		desenhar_quadrado_apagar(f); break;
	case INSERIR:
		desenhar_quadrado_inserir(f); break;
	case MUDARCORFORMA:
		desenhar_quadrado_mudar_cor_forma(f); break;
	case MUDARCONTORNOFORMA:
		desenhar_quadrado_mudar_contorno(f); break;
	case MOVERFORMA:
		desenhar_quadrado_mover_forma(f); break;
	case ALTERARTAMANHO:
		desenhar_quadrado_alterar_tamanho(f); break;
	}
}

void desenhar_contorno(Forma f) {
	switch (f->tipo)
	{
	case RETANGULO:
		desenhar_contorno_retangulo(f); break;
	case QUADRADO:
		desenhar_contorno_quadrado(f); break;
	case TRINAGULO_ISOSCELES:
		desenhar_contorno_triangulo_isosceles(f); break;
	case TRIANGULO_EQUILATERO:
		desenhar_contorno_triangulo_equilatero(f); break;
	case LINHA:
		desenhar_contorno_linha(f); break;
	case CIRCULO:
		desenhar_contorno_circulo(f); break;
	case ELIPSE:
		desenhar_contorno_elipse(f); break;
	case HEXAGONO:
		desenhar_contorno_hexagono(f); break;
	case ESTRELA:
		desenhar_contorno_estrela(f); break;
	case APAGAR:
		desenhar_contorno_quadrado(f); break;
	case INSERIR:
		desenhar_contorno_quadrado(f); break;
	case MUDARCORFORMA:
		desenhar_contorno_quadrado(f); break;
	case MUDARCONTORNOFORMA:
		desenhar_contorno_quadrado(f); break;
	case MOVERFORMA:
		desenhar_contorno_quadrado(f); break;
	case ALTERARTAMANHO:
		desenhar_contorno_quadrado(f); break;
	}
}

void get_cor(Forma f, float* c) {
	c[0] = f->r;
	c[1] = f->g;
	c[2] = f->b;
}

void muda_pontos(Forma f, float x, float y) {
	float largura, altura, lado;

	switch (f->tipo)
	{
		case QUADRADO:
		case TRIANGULO_EQUILATERO:
		case CIRCULO:
		{
			largura = x - f->x;
			altura = y - f->y;
			
			// Determina o lado do quadrado
			if (fabs(largura) > fabs(altura)) lado = fabs(largura);
			else lado = fabs(altura);
			
			// Ajusta largura
			if (largura >= 0) f->comprimento = lado; 
			else f->comprimento = -lado; 
			
			// Ajusta altura
			if (altura >= 0) f->altura = lado; 
			else f->altura = -lado; 
			
			break;
		}

		default:
			f->comprimento = x - f->x;
			f->altura = y - f->y;
			break;
	}

}


int apanha_clique(Forma f, float x, float y) {
	// Verifica se o clique está dentro da figura
	float x_min, x_max, y_min, y_max, temp;

	x_min = f->x;
	x_max = f->x + f->comprimento;
	if (x_min > x_max) { 
		temp = x_min;
		x_min = x_max;
		x_max = temp;
	}

	y_min = f->y;
	y_max = f->y + f->altura;
	if (y_min > y_max) { 
		temp = y_min;
		y_min = y_max;
		y_max = temp;
	}

	return (x >= x_min && x <= x_max && y >= y_min && y <= y_max);
}

void set_tipo(Forma f, int tipo) {
	f->tipo = tipo;
}

int get_tipo(Forma f) {
	return f->tipo;
}

void desloca_forma(Forma f, float x, float y) {
	// Calcula a diferença do centro e o ponto desejado
	float dx = x - (f->x + f->comprimento / 2);  
	float dy = y - (f->y + f->altura / 2);       

	// Atualiza as coordenadas da forma
	f->x += dx;
	f->y += dy;
}

int esta_area_desenho(Forma f, int windowX, int windowY) {
	// Verifica se a forma está dentro dos limites da janela
	float x_min, x_max, y_min, y_max, temp;

	x_min = f->x;
	x_max = f->x + f->comprimento;

	// Caso comprimento seja negativo
	if (x_min > x_max) { 
		temp = x_min;
		x_min = x_max;
		x_max = temp;
	}

	y_min = f->y;
	y_max = f->y + f->altura;
	// Caso altura seja negativa
	if (y_min > y_max) { 
		temp = y_min;
		y_min = y_max;
		y_max = temp;
	}

	return (x_min >= -100 && x_max <= windowX + 400 && y_min >= -100 && y_max <= windowY);
}

void get_coord_quadrado(float Xi, float Yi, float Xf, float Yf, float *coordenadas) {
	// Retorna as novas coordenadas finais, mantendo um quadrado como bounding box
	float largura, lado, altura, novoXf, novoYf;

	largura = fabs(Xf - Xi);
	altura = fabs(Yf - Yi);

	// Determina o lado do quadrado 
	if (largura > altura) lado = largura;
	else lado = altura;

	// Ajusta as coordenadas finais para manter um quadrado
	if (Xf > Xi) novoXf = Xi + lado;
	else novoXf = Xi - lado;

	if (Yf > Yi) novoYf = Yi + lado;
	else novoYf = Yi - lado;

	coordenadas[0] = novoXf;
	coordenadas[1] = novoYf;
}