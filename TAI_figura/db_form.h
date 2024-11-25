#ifndef DB_FORM_H
#define DB_FORM_H

void init_dbForm(int num);

void draw_db_form();

int insert_db_form(Form f, int cor);
int delete_random_db_form();
int delete_form_DB(Form f);

Form random_form(int x, int y, int max_size);
Form random_form_type(int type, int x, int y, int max_size);

Form pick_DB(float x, float y);




#endif
