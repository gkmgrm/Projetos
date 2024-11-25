#include "form.h"
#include "db_form.h"
#include <stdlib.h>

Form *a;
int n;



void init_dbForm(int num) {
	// aloca memória para o array e inicializa como null
	n = num;

	a = malloc(sizeof(Form) * num);

	for (int i = 0; i < n; i++)
		a[i] = NULL;
	
}

void draw_db_form() {
	for (int i = 0; i < n; i++)
		if (a[i] != NULL)
		{
			draw_form(a[i]);	// desenha a forma salva nesse index
		}
}

int insert_db_form(Form f, int cor) {
	// verifica se há espaço no array, se houver retorna true, se não retorna false
	for (int i = 0; i < n; i++)
		if (a[i] == NULL)
		{
			a[i] = f;
			set_background_color(a[i], (cor >> 16) & 0xFF, (cor >> 8) & 0xFF, cor & 0xFF);
			return 1;
		}
	
	return 0;
}

int delete_random_db_form() {
	int i = rand() % n;	// cria uma aleatório entre 0-9

	if (a[i] != NULL) {
		deleteForm(a[i]);
		a[i] = NULL;
		return 1;
	}
	
	return 0;
}

Form random_form(int x, int y, int max_size) {
	// atribui uma forma aleatória e retorna-a
	Form f;

	switch (rand() % 7)
	{
		case 0:
			f = novo_retangulo(x, y, rand() % (max_size / 4), rand() % (max_size / 4));
			break;
		case 1:
			f = novo_quadrado(x, y, rand() % (max_size / 4));
			break;
		case 2:
			f = novo_triangulo_isosceles(x, y, rand() % (max_size / 4), rand() % (max_size / 4));
			break;
		case 3:
			f = nova_linha(x, y, rand() % (max_size / 4), rand() % (max_size / 4));
			break;
		case 4:
			f = novo_hexagono(x, y, rand() % (max_size / 4));
			break;
		case 5:
			f = novo_triangulo_equilatero(x, y, rand() % (max_size / 4));
			break;
		case 6:
			f = novo_circulo(x, y, rand() % (max_size / 4));
			break;

		return f;
	}
}

Form random_form_type(int type, int x, int y, int max_size) {
	// atribui uma forma aleatória e retorna-a
	Form f;

	switch (type)
	{
	case RETANGULO:
		f = novo_retangulo_centro(x, y, rand() % (max_size / 4), rand() % (max_size / 4));
		break;
	case QUADRADO:
		f = novo_quadrado_centro(x, y, rand() % (max_size / 4));
		break;
	case TRINAGULO_ISOSCELES:
		f = novo_triangulo_isosceles_centro(x, y, rand() % (max_size / 4), rand() % (max_size / 4));
		break;
	case LINHA:
		f = nova_linha(x, y, rand() % (max_size / 4), rand() % (max_size / 4));
		break;
	case HEXAGONO:
		f = novo_hexagono_centro(x, y, rand() % (max_size / 4));
		break;
	case TRIANGULO_EQUILATERO:
		f = novo_triangulo_equilatero_centro(x, y, rand() % (max_size / 4));
		break;
	case CIRCULO:
		f = novo_circulo(x, y, rand() % (max_size / 4));
		break;

		return f;
	}
}

Form pick_DB(float x, float y) {
	// conta do final para o principio para se houver sobreposicao nao haver problema
	for (int i = n - 1; i >= 0; i--) {
		if (a[i] != NULL && pick(a[i], x, y))
			return a[i];
	}
	return NULL;
}

int delete_form_DB(Form f) {
	for (int i = 0; i < n; i++)
	{
		if (a[i] == f && a[i] != NULL) {
			deleteForm(a[i]);
			a[i] = NULL;
			return 1;
		}
	}
	return 0;
}