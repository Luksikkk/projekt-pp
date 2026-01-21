#ifndef MAIN_C_LISTY_POSTOW_H
#define MAIN_C_LISTY_POSTOW_H
#include "post.h"

static const int liczba_sortowaniapo = 5;
enum SortujPo {
    ID,
    AUTORZE,
    KAT_ZGLOSZENIA,
    LICZBIE_ZGLOSZEN,
    STATUS_ZGLOSZENIA
};


static const int liczba_sortowan = 2;
enum Sortowanie {
    ROSNACO,
    MALEJACO
};

static const int liczba_usuniec = 3;
enum Usuwanie {
    PO_ID,
    PO_KAT_ZGLOSZENIA,
    PO_STATUSIEZGLOSZENIA
};

typedef struct ListaPostow ListaPostow;

ListaPostow* stworz_liste(void);
int dodaj_post(ListaPostow* lista, int pytaj);
void usun_liste(ListaPostow** p_post);
void wypisz_posty(const ListaPostow* lista);
int edytuj_post(ListaPostow* lista);

void edytuj_kategorie(Post* post);
void edytuj_status(Post* post);
void edytuj_autora(Post* post);
void edytuj_tresc(Post* post);

void usun_posty(ListaPostow* lista);
int usun_posta_z_listy(ListaPostow *lista, enum Usuwanie usuwanie);

int zapisz_do_pliku(ListaPostow *lista, const char* sciezka);
void wczytaj_z_pliku(ListaPostow *lista, const char* sciezka);

void przelicz_id(ListaPostow* lista);

void menu_sortowania(ListaPostow* lista);
int porownaj_posty(const Post* a, const Post* b, const ListaPostow* lista);
void sortuj_lista(ListaPostow* lista, enum SortujPo po, enum Sortowanie kierunek);
const char* sortuj_to_string(const enum SortujPo po);
const char* kieruneksortowania_to_string(enum Sortowanie kierunek);

void wyszukaj_post(const ListaPostow* lista);
void szukajpoautorze(const ListaPostow* lista);
void szukaj_po_id(const ListaPostow* lista);
#endif //MAIN_C_LISTY_POSTOW_H