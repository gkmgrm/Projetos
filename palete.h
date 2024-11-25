#ifndef PALETE_H
#define PALETE_H

// Cores
int criarPalete(int comprimento, int altura);
void desenhar_palete(Forma f);

// Área de ferramentas
void criar_area_ferramentas(int comprimento, int altura);
void desenhar_area_ferramentas();

// Figuras
int criar_figuras_palete(int comprimento, int altura);
void desenhar_figuras_palete(Forma f);

// Modos
int criar_modos_palete(int comprimento, int altura);
void desenhar_modos_palete(Forma);

#endif 

