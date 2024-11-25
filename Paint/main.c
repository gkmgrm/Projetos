/*
	Auntores: Gonçalo Pimenta - 24265 e Guilherme Miranda - 24156
	Data: 26/11/2024
*/

#include <stdlib.h>
#include <gl/glut.h>
#include "forma.h"
#include "db_forma.h"
#include "palete.h"
#include <stdio.h>

#define N 50

// Dimensões da janela inicial
int windowX = 900;
int windowY = 600;

// Estados
int tipo = RETANGULO;
int modo = INSERIR;
float rState = 1;
float gState = 1;
float bState = 1;

int inserir = 0;
int arrastar = 0;
int alterar_tamanho = 0;

Forma forma_selecionada = NULL;

// Feedback
Forma cor_atual, modo_atual, figura_atual;

// Palete
Forma* palete, *figuras_palete, * modos_palete;
int nCoresPalete, nFigurasPalete, nModos;

// Funções
void init();
void my_display();
void my_reshape(int w, int h);
void my_mouse(GLint button, GLint state, GLint x, GLint y);
void my_mouse_tools(GLint button, GLint state, GLint x, GLint y);
void mymouse_canvas(GLint button, GLint state, GLint x, GLint y);
void mousePassiveMotion(int x, int y);
void apagarForma(int x, int y);
void my_mouse_canvas_cria_forma(float x, float y, Forma(*criar)(float, float, float, float));
void mudar_cor_forma(int x, int y);
void mudar_contorno_forma(int x, int y);
void my_mouse_mexe_forma(GLint button, GLint state, GLint x, GLint y, int estado);
void my_mouse_motion(int x, int y);
void myKey(unsigned char key, int x, int y);
void atalhos();
void instrucoes();


int main(int argc, char **argv) {
	instrucoes();
	atalhos();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(windowX, windowY);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Paint");

	glutDisplayFunc(my_display);
	glutReshapeFunc(my_reshape);
	glutMouseFunc(my_mouse);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutMotionFunc(my_mouse_motion);
	glutKeyboardFunc(myKey);

	init();

	glutMainLoop();
}

void my_mouse(GLint button, GLint state, GLint x, GLint y) {
	// Implementa as seguintes funções de acordo com o modo selecionado
	y = windowY - y;  

	if (y > windowY - 100) 
		my_mouse_tools(button, state, x, y);
	else {
		switch (get_tipo(modo_atual))
		{
		case INSERIR: mymouse_canvas(button, state, x, y); break;
		case APAGAR: apagarForma(x, y); break;
		case MUDARCORFORMA: mudar_cor_forma(x, y); break;
		case MUDARCONTORNOFORMA: mudar_contorno_forma(x, y); break;
		case MOVERFORMA: my_mouse_mexe_forma(button, state, x, y, &arrastar); break;		
		case ALTERARTAMANHO: my_mouse_mexe_forma(button, state, x, y, &alterar_tamanho); break;
		default: break;
		}
	}
	
}

void my_mouse_mexe_forma(GLint button, GLint state, GLint x, GLint y, int *estado) {
	// Escolhe a forma e ativa o modo
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		Forma f = escolheDBForma(x, y);
		if (f != NULL) {
			forma_selecionada = f;
			*estado = 1;
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		*estado = 0;
		forma_selecionada = NULL;
	}
	
}

void my_mouse_tools(GLint button, GLint state, GLint x, GLint y) {
	// Deteta um clique na área de ferramentas e muda de cor, forma ou modo

	float cor[3];
	int cliqueProcessado = 0; 

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = 0; i < nCoresPalete; i++) 
			if (apanha_clique(palete[i], x, y)) {
				get_cor(palete[i], cor);
				rState = cor[0];
				gState = cor[1];
				bState = cor[2];
				definirCorFundo(cor_atual, rState, gState, bState);
				definir_contorno(cor_atual, rState, gState, bState);
				glutPostRedisplay();
				cliqueProcessado = 1; 
				break;
			}
		

		if (!cliqueProcessado) {

			for (int i = 0; i < nFigurasPalete; i++) 
				if (apanha_clique(figuras_palete[i], x, y)) {
					tipo = get_tipo(figuras_palete[i]);
					set_tipo(figura_atual, tipo);
					glutPostRedisplay();
					cliqueProcessado = 1; 
					break;
				}
			
		
			for (int i = 0; i < nModos; i++)
				if (apanha_clique(modos_palete[i], x, y)) {
					modo = get_tipo(modos_palete[i]);
					set_tipo(modo_atual, modo);
					glutPostRedisplay();
					cliqueProcessado = 1;
					break;
				}
		}
		
	}
}


void my_mouse_canvas_cria_forma(float x, float y, Forma(*criar)(float, float, float, float)) {
	// Cria uma forma com dois cliques
	if (inserir) {  
		muda_pontos(forma_selecionada, x, y);
		inserir = 0;
		forma_selecionada = NULL;
		glutPostRedisplay();
	}
	else {  
		forma_selecionada = criar(x, y, x, y);
		definirCorFundo(forma_selecionada, rState, gState, bState);
		definir_contorno(forma_selecionada, rState, gState, bState);
		if (!inserir_forma_db(forma_selecionada)) {
			printf("MEMORIA CHEIA!!!\n");
			apagar_forma(forma_selecionada);
			forma_selecionada = NULL;
		}
		else {
			inserir = 1;
			glutPostRedisplay();
		}
	}
}

void mymouse_canvas(GLint button, GLint state, GLint x, GLint y) {
	// Cria uma forma de acordo com o tipo selecionado

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		switch (tipo)
		{
		case RETANGULO:
			my_mouse_canvas_cria_forma(x, y, cria_retangulo); break;
		case QUADRADO:
			my_mouse_canvas_cria_forma(x, y, cria_quadrado); break;
		case TRINAGULO_ISOSCELES:
			my_mouse_canvas_cria_forma(x, y, criar_triangulo_isosceles); break;
		case LINHA:
			my_mouse_canvas_cria_forma(x, y, criar_linha); break;
		case HEXAGONO:
			my_mouse_canvas_cria_forma(x, y, criar_hexagono); break;
		case TRIANGULO_EQUILATERO:
			my_mouse_canvas_cria_forma(x, y, criar_triangulo_equilatero); break;
		case CIRCULO:
			my_mouse_canvas_cria_forma(x, y, criar_circulo); break;
		case ELIPSE:
			my_mouse_canvas_cria_forma(x, y, criar_elipse); break;
		case ESTRELA:
			my_mouse_canvas_cria_forma(x, y, criar_estrela); break;

		}
		
	}


}

void mousePassiveMotion(int x, int y) {
	y = windowY - y;

	if (inserir) {  // second click
		muda_pontos(forma_selecionada, x, y);
		glutPostRedisplay();
	}
}

void my_mouse_motion(int x, int y) {
	// Muda tamanho ou posição de acordo com o modo ativo
	y = windowY - y;

	if (arrastar) 
		desloca_forma(forma_selecionada, x, y);
	
	else if (alterar_tamanho)
		muda_pontos(forma_selecionada, x, y);
		
	glutPostRedisplay();
}


void my_reshape(int w, int h)
{
	windowX = w;
	windowY = h;

	glViewport(0, 0, windowX, windowY);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, windowX, 0, windowY);	// cordenadas do mundo
}

void my_display() {
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha ferramentas e paletes
	desenhar_area_ferramentas();
	desenhar_palete(cor_atual);
	desenhar_figuras_palete(figura_atual);
	desenhar_modos_palete(modo_atual);

	// Desenha todas as formas do array
	desenha_formas_db(windowX, windowY);
	
	glFlush();
}

void init() {
	// Inicializa as formas
	srand(time(NULL));

	inicializar_db(N);

	// Inicializa a área de ferramentas cores, figuras, etc
	criar_area_ferramentas(windowX, windowY);
	nCoresPalete = criarPalete(windowX, windowY);
	nFigurasPalete = criar_figuras_palete(windowX, windowY);
	nModos = criar_modos_palete(windowX, windowY);

	// Inicializa as formas que vão dar feedback
	cor_atual = novo_quadrado(1, 1, 2);
	definirCorFundo(cor_atual, rState, gState, bState);
	definir_contorno(cor_atual, rState, gState, bState);
	figura_atual = criar_forma(tipo, 30, windowY - 35, 20, 30);
	modo_atual = criar_forma(modo, 0, 0, 1, 1);

	glClearColor(.9, .9, .9, 1);  // Define a cor de fundo

	glViewport(0, 0, windowX, windowY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, windowX, 0, windowY);	// cordenadas do mundo
}


void apagarForma(int x, int y) {
	// Apaga a froma selecionada da base de dados
	Forma f = escolheDBForma(x, y);
	if (f != NULL) {
		apagar_forma_db(f);  
		glutPostRedisplay();  
	}

}

void mudar_cor_forma(int x, int y) {
	// Muda a cor da forma selecionada
	Forma f = escolheDBForma(x, y);
	if (f != NULL) {
		definirCorFundo(f, rState, gState, bState);
		glutPostRedisplay();  
	}
}

void mudar_contorno_forma(int x, int y) {
	// Muda a cor de contorno
	Forma f = escolheDBForma(x, y);
	if (f != NULL) {
		definir_contorno(f, rState, gState, bState);
		glutPostRedisplay();
	}
}

void myKey(unsigned char key, int x, int y) {
	y = windowY - y;

	switch (key)
	{
		case 'a':
		{
			rState = 0;
			gState = 0;
			bState = 1;
			break;
		}
		case 'A':
		{
			modo = APAGAR;
			break;
		}
		case 'b':
		{
			rState = 1;
			gState = 1;
			bState = 1;
			break;
		}
		case 'c':
		{
			modo = MUDARCONTORNOFORMA;
			break;
		}
		case 'C':
		{
			modo = MUDARCORFORMA;
			break;
		}
		case 'e':
		{
			tipo = ELIPSE;
			break;
		}
		case 'E':
		{
			tipo = ESTRELA;
			break;
		}
		case 'h':
		{
			tipo = HEXAGONO;
			break;
		}
		case 'I':
		{
			modo = INSERIR;
			break;
		}		
		case 'l':
		{
			rState = 1;
			gState = .5;
			bState = 0;
			break;
		}
		case 'L':
		{
			tipo = LINHA;
			break;
		}
		case 'M':
		{
			modo = MOVERFORMA;
			break;
		}
		case 'p':
		{
			rState = 0;
			gState = 0;
			bState = 0;
			break;
		}
		case 's':
			exit(0);
		case 'r':
		{
			rState = 1;
			gState = 0.2;
			bState = 0.8;
			break;
		}
		case 'R':
		{
			tipo = RETANGULO;
			break;
		}
		case 't':
		{
			tipo = TRINAGULO_ISOSCELES;
			break;
		}
		case 'T':
		{
			modo = ALTERARTAMANHO;
			break;
		}

		case 'v':
		{
			rState = 0;
			gState = 1;
			bState = 0;
			break;
		}
		case 'V':
		{
			rState = 1;
			gState = 0;
			bState = 0;
			break;
		}
		case 'q':
		{
			tipo = QUADRADO;
		}
		default:
			break;
	}


	set_tipo(modo_atual, modo);
	set_tipo(figura_atual, tipo);
	definirCorFundo(cor_atual, rState, gState, bState);
	glutPostRedisplay();
}

void atalhos() {
	printf("\n---Atalhos keyboard---\n");
	printf("\n's' - Sair do programa");

	printf("\n\nAlterar modos");
	printf("\n'A' - Modo apagar");
	printf("\n'c' - Modo alterar contorno");
	printf("\n'C' - Modo alterar cor de fundo");
	printf("\n'I' - Modo inserir forma");
	printf("\n'M' - Modo mover forma");
	printf("\n'T' - Modo alterar tamanho");

	printf("\n\nAlterar forma");
	printf("\n'e' - Forma elipse");
	printf("\n'E' - Forma estrela");
	printf("\n'h' - Forma hexagono");
	printf("\n'L' - Forma linha");
	printf("\n'R' - Forma retangulo");
	printf("\n't' - Forma triangulo isosceles");
	printf("\n'q' - Forma quadrado");

	printf("\n\nAlterar cor");
	printf("\n'a' - Cor azul");
	printf("\n'b' - Cor branco");
	printf("\n'l' - Cor laranja");
	printf("\n'p' - Cor preto");
	printf("\n'r' - Cor rosa");
	printf("\n'v' - Cor verde");
	printf("\n'V' - Cor vermelha");
}

void instrucoes() {
	printf("---Instrucoes---");
	printf("\nInserir - Clique uma vez e arraste sem o mouse permido, o segundo clique desenha a figura");
	printf("\nApagar - Clicar em cima da figura");
	printf("\nMudar cor de fundo e contorno - Clique em cima da figura em questao");
	printf("\nMover figura - Clique e arraste com o mouse permido");
	printf("\nAlterar tamanho figura - Clique e arraste com o mouse permido");
	printf("\n----------------\n");
}