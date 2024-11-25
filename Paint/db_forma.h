#ifndef DB_FORMA_H
#define DB_FORMA_H

void inicializar_db(int nFormas);

int apagar_forma_db(Forma f);

void desenha_formas_db(int windowX, int windowY);

int inserir_forma_db(Forma f);

Forma escolheDBForma(float x, float y);

#endif