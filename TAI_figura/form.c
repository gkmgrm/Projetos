#include "form.h"
#include <stdlib.h>
#include <stdio.h>
#include<gl/glut.h>
#include <math.h>


// this struct is encapsulated
struct form {
	int type;
	float x, y;             // initial point of the form
	float xSize, ySize;     // sides 
	float cor_r, cor_g, cor_b;

	
};

Form newForm(int type, float x, float y, float xSize, float ySize) {
	Form f = (Form)malloc(sizeof(struct form));

	f->x = x;
	f->y = y;
	f->xSize = xSize;
	f->ySize = ySize;

	f->type = type;

	return f;
}

Form newFormC(int type, float x, float y, float xSize, float ySize) {
	return newForm(type, x - (xSize / 2), y - (ySize / 2), xSize, ySize);
}

/* Retangulos */
Form novo_retangulo(float x, float y, float x_size, float y_size) {
	return newForm(RETANGULO, x, y, x_size, y_size);
}

Form novo_retangulo_centro(float x, float y, float x_size, float y_size) {
	return newFormC(RETANGULO, x, y, x_size, y_size);
}

Form novo_retangulo_2pontos(float Xi,  float Yi, float Xf, float Yf) {
	return newForm(RETANGULO, Xi, Yi, (Xf - Xi), (Yf - Yi));
}

Form novo_quadrado(float x, float y, float lado) {
	return newForm(QUADRADO ,x, y, lado, lado);
}

Form novo_quadrado_centro(float x, float y, float lado) {
	return newFormC(QUADRADO, x, y, lado, lado);
}

Form cria_quadrado(float Xi, float Yi, float Xf, float Yf) {
	if (Xf - Xi > Yf - Yi)
		return newForm(QUADRADO, Xi, Yi, (Xf - Xi), (Xf - Xi));
	else
		return newForm(QUADRADO, Xi, Yi, (Yf - Yi), (Yf - Yi));
}

Form novo_triangulo_isosceles(float x, float y, float x_size, float y_size) {
	return newForm(TRINAGULO_ISOSCELES, x, y, x_size, y_size);
}

Form novo_triangulo_isosceles_centro(float x, float y, float x_size, float y_size) {
	return newFormC(TRINAGULO_ISOSCELES, x, y, x_size, y_size);
}


Form novo_isosceles_2pontos(float Xi, float Yi, float Xf, float Yf) {
	return newForm(TRINAGULO_ISOSCELES, Xi, Yi, (Xf - Xi), (Yf - Yi));
}

Form nova_linha(float Xi, float Yi, float Xf, float Yf) {
	return newForm(LINHA, Xi, Yi, (Xf - Xi), (Yf - Yi));
}

Form novo_hexagono(float x, float y, float lado) {
	return newForm(HEXAGONO, x, y, lado, lado);
}

Form novo_hexagono_centro(float x, float y, float lado) {
	return newFormC(HEXAGONO, x, y, lado, lado);
}


Form novo_triangulo_equilatero(float x, float y, float lado) {
	return newForm(TRIANGULO_EQUILATERO, x, y, lado, lado);
}

Form novo_triangulo_equilatero_centro(float x, float y, float lado) {
	return newFormC(TRIANGULO_EQUILATERO, x, y, lado, lado);
}

Form novo_circulo(float x, float y, float lado) {
	return newForm(CIRCULO, x, y, lado, lado);
}

void set_background_color(Form f, float cor_r, float cor_g, float cor_b) {
	f->cor_r = cor_r;
	f->cor_g = cor_g;
	f->cor_b = cor_b;
}

void set_type(Form f, int type) {
	f->type = type;
}

void draw_form(Form f) {
	// recebe a forma a desenhar e desenha-a
	switch (f->type)
	{
		case RETANGULO:
			draw_retangulo(f); break;
		case QUADRADO:
			draw_quadrado(f); break;
		case TRINAGULO_ISOSCELES:
			draw_triangulo(f); break;
		case LINHA:
			draw_line(f); break;
		case HEXAGONO:
			draw_hexagono(f); break;
		case TRIANGULO_EQUILATERO:
			draw_triangulo_equilatero(f); break;
		case CIRCULO:
			draw_circulo(f); break;
	}
}

void deleteForm(Form f) {
	free(f);
}

void updateForm(Form f, float dx, float dy) {
	f->x += dx;
	f->y += dy;
}


void printfForm(Form f) {
	printf("Graphical Form BBox: (%.2f,%.2f), (%.2f, %.2f), (%.2f, %.2f), (%.2f, %.2f)\t",
		getVertex1_X(f), getVertex1_Y(f),//f->x, f->y,
		getVertex2_X(f), getVertex2_Y(f),//f->x, f->y + f->ySize,
		getVertex3_X(f), getVertex3_Y(f),//f->x + f->xSize, f->y + f->ySize,
		getVertex4_X(f), getVertex4_Y(f));//f->x + f->xSize, f->y);


	printf("Center(%.2f,%.2f) Size{%.2f,%.2f}\n",
		f->x + (f->xSize / 2), f->y + (f->ySize / 2),
		f->xSize, f->ySize);

}

void draw_retangulo(Form f) {
	glColor3f(f->cor_r, f->cor_g, f->cor_b);
	glBegin(GL_POLYGON);
	glVertex2f(getVertex1_X(f), getVertex1_Y(f));
	glVertex2f(getVertex2_X(f), getVertex2_Y(f));
	glVertex2f(getVertex3_X(f), getVertex3_Y(f));
	glVertex2f(getVertex4_X(f), getVertex4_Y(f));
	glEnd();

	glColor3f(f->cor_g, f->cor_b, f->cor_r);
	glLineWidth(2);	 // Define a espessura do contorno
	glBegin(GL_LINE_LOOP);
	glVertex2f(getVertex1_X(f), getVertex1_Y(f));
	glVertex2f(getVertex2_X(f), getVertex2_Y(f));
	glVertex2f(getVertex3_X(f), getVertex3_Y(f));
	glVertex2f(getVertex4_X(f), getVertex4_Y(f));
	glEnd();
	
}

void draw_quadrado(Form f) {
	glColor3f(f->cor_r, f->cor_g, f->cor_b);
	glBegin(GL_POLYGON);
	glVertex2f(getVertex1_X(f), getVertex1_Y(f));
	glVertex2f(getVertex2_X(f), getVertex2_Y(f));
	glVertex2f(f->x + f->ySize, getVertex3_Y(f));
	glVertex2f(f->x + f->ySize, getVertex4_Y(f));
	glEnd();



	glColor3f(f->cor_g, f->cor_b, f->cor_r);
	glLineWidth(2);	 // Define a espessura do contorno
	glBegin(GL_LINE_LOOP);
	glVertex2f(getVertex1_X(f), getVertex1_Y(f));
	glVertex2f(getVertex2_X(f), getVertex2_Y(f));
	glVertex2f(f->x + f->ySize, getVertex3_Y(f));
	glVertex2f(f->x + f->ySize, getVertex4_Y(f));
	glEnd();

	

}


void draw_triangulo(Form f) {
	glColor3f(f->cor_r, f->cor_g, f->cor_b);
	glBegin(GL_TRIANGLES);
	glVertex2f(getVertex1_X(f), getVertex1_Y(f));
	glVertex2f(f->x + f->xSize/2, getVertex2_Y(f));
	glVertex2f(getVertex3_X(f), f->y);
	glEnd();

	glColor3f(f->cor_g, f->cor_b, f->cor_r);
	glLineWidth(2);	 // Define a espessura do contorno
	glBegin(GL_LINE_LOOP);
	glVertex2f(getVertex1_X(f), getVertex1_Y(f));
	glVertex2f(f->x + f->xSize / 2, getVertex2_Y(f));
	glVertex2f(getVertex3_X(f), f->y);
	glEnd();
}

void draw_triangulo_equilatero(Form f) {
	glColor3f(f->cor_r, f->cor_g, f->cor_b);	//Define a cor do triangulo
	//Desenha o triangulo
	glBegin(GL_TRIANGLES);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x + (f->xSize/2), f->y + f->ySize);
	glVertex2f(f->x + f->xSize, f->y);
	glEnd();

	glColor3f(f->cor_g, f->cor_b, f->cor_r);	//Define a cor do contorno 

	glLineWidth(2);	 // Define a espessura do contorno
	//Desenha o contorno
	glBegin(GL_LINE_LOOP);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x + (f->xSize / 2), f->y + f->ySize);
	glVertex2f(f->x + f->xSize, f->y);
	glEnd();

}

Form criar_triangulo_equilatero(float Xi, float Yi, float Xf, float Yf) {
	if (Xf - Xi > Yf - Yi)
		return newForm(TRIANGULO_EQUILATERO, Xi, Yi, (Xf - Xi), (Xf - Xi));
	else
		return newForm(TRIANGULO_EQUILATERO, Xi, Yi, (Yf - Yi), (Yf - Yi));
}

void draw_line(Form f) {
	glColor3f(f->cor_r, f->cor_g, f->cor_b);
	//glLineWidth(2.0f);           // Definir a espessura da linha

	glBegin(GL_LINES);
	glVertex2f(f->x, f->y);
	glVertex2f(f->x + f->xSize, f->y + f->ySize);
	glEnd();
}

void draw_hexagono(Form f) {
	glColor3f(f->cor_r, f->cor_g, f->cor_b);	//Define a cor do hexagono
	//Desenha o hexagono

	int num_lados = 6;
	float raio = (f->x + f->xSize) / 2;
	float angulo_inicial = 3.14159265358979323846 / 6;

	glBegin(GL_POLYGON);
	for (int i = 0; i < num_lados; i++) {
		float theta = angulo_inicial + i * 2.0f * 3.14159265358979323846 / num_lados;
		float x = raio * cos(theta);
		float y = raio * sin(theta);
		glVertex2f(x, y);
	}

	glEnd();


}

void draw_circulo(Form f) {
	glColor3f(f->cor_r, f->cor_g, f->cor_b);	//cores do circulo

	float teta;
	float raio = f->xSize / 2;

	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i += 10)
	{
		teta = i * 3.14159265358979323846 / 180;
		//desenha a posição consoante o angulo - i, em radianos
		float x = f->x + cos(teta) * raio;
		float y = f->y + sin(teta) * raio;
		glVertex2d(x, y);
	}
	glEnd();



	//desenhar contorno

	//define a cor do contorno
	glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);

	glLineWidth(2);	//Espessura
	glBegin(GL_LINE_LOOP);
	for (double i = 0; i <= 360; i += 10)
	{
		//desenha a posição consoante o angulo - i, em radianos
		double x = f->x + cos(i * 3.14159265358979323846 / 180) * raio;
		double y = f->y + sin(i * 3.14159265358979323846 / 180) * raio;
		glVertex2d(x, y);
	}
	glEnd();
	

}


float getVertex1_X(Form f) {
	return f->x;
}

float getVertex1_Y(Form f) {
	return f->y;
}

float getVertex2_X(Form f) {
	return f->x;
}

float getVertex2_Y(Form f) {
	return (f->y + f->ySize);
}

float getVertex3_X(Form f) {
	return (f->x + f->xSize);
}

float getVertex3_Y(Form f) {
	return (f->y + f->ySize);
}


float getVertex4_X(Form f) {
	return (f->x + f->xSize);
}

float getVertex4_Y(Form f) {
	return f->y;
}

int pick(Form f, float x, float y) {
	if (f->x <= x && f->x + f->xSize >= x && f->y <= y && f->y + f->ySize >= y)
		return 1;
	return 0;
}

void get_color(Form f, int cor) {
	f->cor_r = (cor >> 16) & 0xFF;
	f->cor_g = (cor >> 8) & 0xFF;
	f->cor_b = cor & 0xFF;
	
}