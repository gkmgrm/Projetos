#include "form.h"
#include "db_form.h"
#include <stdlib.h>
#include<gl/glut.h>
#define N 10

// Array of pointers to form objects (Recall, Form is a pointer!)
Form a[N];
int counter = 0;
int windowX = 600;
int windowY = 600;

//estados
int type = RETANGULO;
int cor = BRANCO;
int criar_forma = 0;

// feedback
Form active_color;

// Guardar última posição do clique
int x_last_click;
int y_last_click;

// cor palete
Form* palete;
int nPalete_colors;

void init();
void insert_form_2click(int x, int y);
void mydisplay();
void myReshape(int w, int h);
void my_mouse_canvas(GLint button, GLint state, GLint x, GLint y);
void my_mouse_tools(GLint button, GLint state, GLint x, GLint y);

void my_mouse(GLint button, GLint state, GLint x, GLint y);

void myKey(unsigned char key, int x, int y);


void main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(windowX, windowY);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Hello world");

	glutDisplayFunc(mydisplay);

	glutMouseFunc(my_mouse);

	glutKeyboardFunc(myKey);
	glutReshapeFunc(myReshape);

	init();
	
	

	glutMainLoop();

}

void my_mouse_tools(GLint button, GLint state, GLint x, GLint y) {

	for (int i = 0; i < nPalete_colors; i++)
	{
		if (pick(palete[i], x, y));
	}
}

void my_mouse_canvas(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		printf("\nButao esquerdo, cordenadas: (%i,%i)", x, y);

		if (type == CIRCULO ) {
			if (criar_forma) {
				Form f = novo_circulo(x_last_click, y_last_click, x, y);

				if (!insert_db_form(f, cor)) {	// se já não houver espaço para uma nova figura apaga-a
					printf("\nMemoria cheia");
					deleteForm(f);
				}
				else
					glutPostRedisplay();

				criar_forma = 0;

			}
			else {
				x_last_click = x;
				y_last_click = y;
				criar_forma = 1;
			}
		}
		else {
			Form f = random_form_type(type, x, y, windowX);	// atribui uma nova forma à variavel f



			if (!insert_db_form(f, cor)) {	// se já não houver espaço para uma nova figura apaga-a
				printf("\nMemoria cheia");
				deleteForm(f);
			}
			else
				glutPostRedisplay();

		}

	}
	// se for o direito apaga uma figura aleatória
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		printf("\nButao direito, cordenadas: (%i,%i)", x, y);


		Form f = pick_DB(x, y);

		// se o valor retornado for uma figura apaga-a
		if (f != NULL) {
			if (delete_form_DB(f))
				glutPostRedisplay();

		}

	}
}

void my_mouse(GLint button, GLint state, GLint x, GLint y) {
	y = windowY - y;	// muda a posição y para a posição inferior esquerdo ser (0,0)

	if (y < 40)
		my_mouse_tools(button, state, x, y);
	else
		my_mouse_canvas(button, state, x, y);
}

void myKey(unsigned char key, int x, int y) {
	y = windowY - y;

	//recebe uma letra do teclado e atribuí-a a um tipo de forma 
	switch (key) {
		case 'r':
		case 'R':
			type = RETANGULO;
			break;
		case 'q':
		case 'Q':
			type = QUADRADO;
			break;
		case 't':
		case 'T':
			type = TRINAGULO_ISOSCELES;
			break;
		case 'e':
		case 'E':
			type = TRIANGULO_EQUILATERO;
			break;
		case 'h':
		case 'H':
			type = HEXAGONO;
			break;
		case 'c':
		case 'C':
			type = CIRCULO;
			break;
		case 'l':
		case 'L':
			type = LINHA;
			break;
		case 'a':
		case 'A':
			cor = AZUL;
			break;
		case 'v':
			cor = VERMELHO;
			break;
		case 'V':
			cor = VERDE;
			break;
		case 'p':
		case 'P':
			cor = PRETO;
			break;
		case 'b':
		case 'B':
			cor = BRANCO;
			break;
		case 'i':
		case 'I': {

			Form f = random_form_type(type, x, y, windowX);	// atribui uma nova forma à variavel f



			if (!insert_db_form(f, cor)) {	// se já não houver espaço para uma nova figura apaga-a
				printf("\nMemoria cheia");
				deleteForm(f);
			}
			else
				glutPostRedisplay();
			break;
		}
		case 's':
		case 'S':
			exit(0);
	}

	set_background_color(active_color, (cor >> 16) & 0xFF, (cor >> 8) & 0xFF, cor & 0xFF);
	set_type(active_color, type);
	glutPostRedisplay();
}

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	draw_db_form();	// desenha as formas salvas no array

	counter++;	// incrementa o contador de chamadas mydisplay
	draw_form(active_color);

	for (int i = 0; i < nPalete_colors; i++)
		draw_form(palete[i]);
	

	glFlush();
}

void init() {

	srand(time(NULL));

	init_dbForm(N);


	active_color = novo_retangulo(10, 10, 20, 10);
	set_background_color(active_color, (cor >> 16) & 0xFF, (cor >> 8) & 0xFF, cor & 0xFF);

	nPalete_colors = 5;
	palete = malloc(sizeof(Form) * nPalete_colors);

	palete[0] = novo_quadrado(40, 10, 20);
	set_background_color(palete[0], (VERMELHO >> 16) & 0xFF, (VERMELHO >> 8) & 0xFF, VERMELHO & 0xFF);

	palete[1] = novo_quadrado(70, 10, 20);
	set_background_color(palete[1], (AZUL >> 16) & 0xFF, (AZUL >> 8) & 0xFF, AZUL & 0xFF);

	palete[2] = novo_quadrado(100, 10, 20);
	set_background_color(palete[2], (VERDE >> 16) & 0xFF, (VERDE >> 8) & 0xFF, VERDE & 0xFF);

	palete[3] = novo_quadrado(130, 10, 20);
	set_background_color(palete[3], (PRETO >> 16) & 0xFF, (PRETO >> 8) & 0xFF, PRETO & 0xFF);

	palete[4] = novo_quadrado(160, 10, 20);
	set_background_color(palete[4], (BRANCO >> 16) & 0xFF, (BRANCO >> 8) & 0xFF, BRANCO & 0xFF);

	glClearColor(.65, .65, .65, .1);  // Define a cor de fundo

	glViewport(0, 0, windowX, windowY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, windowX, 0, windowY);	// cordenadas do mundo

}

void myReshape(int w, int h)
{
	windowX = w;
	windowY = h;

	glViewport(0, 0, windowX, windowY);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, windowX, 0, windowY);	// cordenadas do mundo
}

void insert_form_2click(int x, int y) {

}
