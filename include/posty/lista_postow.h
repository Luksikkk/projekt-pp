#ifndef MAIN_C_LISTY_POSTOW_H
#define MAIN_C_LISTY_POSTOW_H

typedef struct ListaPostow ListaPostow;

ListaPostow* stworz_liste(void);
int dodaj_post(ListaPostow* lista, int pytaj);
void usun_liste(ListaPostow** p_post);
void wypisz_posty(const ListaPostow* post);
int usun_post_z_listy(ListaPostow *lista,int id);
int zapisz_do_pliku(ListaPostow *lista, const char* sciezka);
void wczytaj_z_pliku(ListaPostow *lista, const char* sciezka);


#endif //MAIN_C_LISTY_POSTOW_H