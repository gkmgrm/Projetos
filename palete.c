#include "forma.h"
#include "db_forma.h"
#include <stdio.h>
#include <gl/glut.h>
#include <stdlib.h>

Forma* palete, ferramentas, * figuras_palete, * modos_palete;
int nCoresPalete = 10, nFiguras = 9, modos = 6;

// Array de cores
float rStateArray[10] = {1, 0, 0, 1, 1, 1, 0.6, 0, 1, .5};
float gStateArray[10] = {0, 1, 0, 1, .5, .2, .1, 0, 1, .5};
float bStateArray[10] = {0, 0, 1, 0, 0, .8, 1, 0, 1, .5};

/* Cores */
int criarPalete(int comprimento, int altura) {
	// Cria as cores disponíveis na palete

	int i, j = 0;

	palete = malloc(sizeof(Forma) * nCoresPalete);

	for (i = 0; i < nCoresPalete; i++)
	{
		if (i < 5) {
			palete[i] = novo_quadrado(comprimento - 30 - (i * 30), altura - 30, 20);
			definirCorFundo(palete[i], rStateArray[i], gStateArray[i], bStateArray[i]);
		}
		else {
			palete[i] = novo_quadrado(comprimento - 30 - (j * 30), altura - 60, 20);
			definirCorFundo(palete[i], rStateArray[i], gStateArray[i], bStateArray[i]);
			j++;
		}
	}

	return nCoresPalete;
}

void desenhar_palete(Forma f) {
	// Desenha as cores da palete e o contorno na cor selecionada
	float cor_forma[3];
	float r, g, b;

	get_cor(f, cor_forma);
	r = cor_forma[0];
	g = cor_forma[1];
	b = cor_forma[2];
	
	for (int i = 0; i < nCoresPalete; i++) {
		desenhar_forma(palete[i]);
		if (r == rStateArray[i] && g == gStateArray[i] && b == bStateArray[i] && r == 0 && g == 0 && b == 0)
		{
			definir_contorno(palete[i], 1, 1, 1);
			desenhar_contorno(palete[i]);
		} 
		else if (r == rStateArray[i] && g == gStateArray[i] && b == bStateArray[i])
		{
			definir_contorno(palete[i], 0, 0, 0);
			desenhar_contorno(palete[i]);
		}

	}
}

/* Ferramentas */
void criar_area_ferramentas(int comprimento, int altura) {
	ferramentas = novo_retangulo(0, altura - 100, 1920, (altura / 3));
	definirCorFundo(ferramentas, .8, .8, .8);
}

void desenhar_area_ferramentas() {
	desenhar_forma(ferramentas);
}

/* Figuras palete */
int criar_figuras_palete(int comprimento, int altura) {
	// Cria a palete de figuras

	figuras_palete = malloc(sizeof(Forma) * nFiguras);

	figuras_palete[0] = novo_quadrado(comprimento / 2 - 30, altura - 30, 20);
	figuras_palete[1] = novo_retangulo(comprimento / 2 + 10, altura - 30, 30, 20);
	figuras_palete[2] = novo_triangulo_equilatero(comprimento / 2 + 60, altura - 30, 20);
	figuras_palete[3] = novo_hexagono(comprimento / 2 - 30, altura - 60, 20, 20);
	figuras_palete[4] = criar_linha(comprimento / 2 + 10, altura - 60, comprimento / 2 + 40, altura - 40);
	figuras_palete[5] = novo_triangulo_isosceles(comprimento / 2 + 60, altura - 60, 20, 30);
	figuras_palete[6] = novo_circulo(comprimento / 2 - 70, altura - 30, 20, 20);
	figuras_palete[7] = nova_estrela(comprimento / 2 - 70, altura - 60, 20, 20);
	figuras_palete[8] = nova_elipse(comprimento / 2 - 120, altura - 30, 30, 20);
	
	return nFiguras;
}

void desenhar_figuras_palete(Forma f) {
	// Desenha todas as figuras disponíveis e contorna a figura selecionada
	for (int i = 0; i < nFiguras ; i++) {
		desenhar_forma(figuras_palete[i]);
		if (get_tipo(f) == get_tipo(figuras_palete[i]))
		{
			definir_contorno(figuras_palete[i], 0, 0, 0);
			desenhar_contorno(figuras_palete[i]);
		}
	}
}

/* Modos palete */
int criar_modos_palete(int comprimento, int altura) {
	// Cria os modos disponíveis
	modos_palete = malloc(sizeof(Forma) * modos);

	modos_palete[0] = novo_quadrado_apagar(10, altura - 40, 30);
	modos_palete[1] = novo_quadrado_inserir(50, altura - 40, 30);
	modos_palete[2] = novo_quadrado_mudar_cor_forma(90, altura - 40, 30);
	modos_palete[3] = novo_quadrado_mudar_contorno(10, altura - 80, 30);
	modos_palete[4] = novo_quadrado_mover_forma(50, altura - 80, 30);
	modos_palete[5] = novo_quadrado_alterar_tamanho(90, altura - 80, 30);

	return modos;
}

void desenhar_modos_palete(Forma f) {
	// Desenha todos os modos disponíveis e contorna o modo selecionado
	for (int i = 0; i < modos; i++) {
		desenhar_forma(modos_palete[i]);
		if (get_tipo(f) == get_tipo(modos_palete[i]))
		{
			definir_contorno(modos_palete[i], 0, 0, 0);
			desenhar_contorno(modos_palete[i]);
		}
	}

}