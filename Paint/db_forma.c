#include "forma.h"
#include "db_forma.h"
#include <stdlib.h>

Forma* a;
int n;

void inicializar_db(int nFormas) {
	// Inicializa o array de formas 
	n = nFormas;

	a = malloc(sizeof(Forma) * n);
	for (int i = 0; i < n; i++)
		a[i] = NULL;
}

int apagar_forma_db(Forma f) {
	int i, forma_apagada = 0;

	for (i = 0; i < n && a[i] != NULL; i++) {
		if (f == a[i]){
			apagar_forma(a[i]);
			forma_apagada = 1;
			break;
		}
	}

	// Coloca a forma uma posição para trás
	if (forma_apagada) {
		for (i = i + 1; i < n && a[i] != NULL; i++) {
			a[i - 1] = a[i];
		}
		a[i - 1] = NULL;
	}

	return forma_apagada;
}

void desenha_formas_db(int windowX, int windowY) {
	// Desenha todas as formas dentro da área de desenho
	for (int i = 0; i < n; i++)
		if (a[i] != NULL)
		{
			if (esta_area_desenho(a[i], windowX, windowY - 100)) {
				desenhar_forma(a[i]);
				desenhar_contorno(a[i]);
			}
			// Apaga a figura se estiver fora dos limites de toda a janela
			else if (!esta_area_desenho(a[i], windowX, windowY)) 
				apagar_forma_db(a[i]);
		}
}

int inserir_forma_db(Forma f) {
	// Insere a forma se houver espaço e retorna se conseguiu
	for (int i = 0; i < n; i++)
		if (a[i] == NULL) {
			a[i] = f;
			return 1;
		}

	return 0;
}

Forma escolheDBForma(float x, float y) {
	// Retorna a figura selecionada
	for (int i = n - 1; i >= 0; i--)
		if (a[i] != NULL && apanha_clique(a[i], x, y)) {
			return a[i];
		}

	return NULL;
}



