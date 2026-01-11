#include <stdio.h>

#include "include/menu/menu.h"
#include "include/posty/lista_postow.h"
#include "include/posty/post.h"


int main(void) {
    Menu *menu = stworz_menu();
    ListaPostow *lista = stworz_liste();
    while (1) {
        int wybor;
        int id_posta;
        wypisz_menu(menu);
        printf("Wybierz opcje: \n");
        scanf("%d",&wybor);
        switch (wybor) {
            case 1:
                wypisz_posty(lista);
                break;
            case 2:
                dodaj_post(lista);
                break;
            case 3:
                printf("Podaj ID posta:\n");
                scanf("%d",&id_posta);
                usun_post_z_listy(lista, id_posta);
                break;
            case 4:
                //zapisz_do_pliku(lista);
                printf("Funkcjonalnosc w trakcie implementacji.\n");
                break;
            case 5:
                //wczytaj_z_pliku(lista);
                printf("Funkcjonalnosc w trakcie implementacji.\n");
                break;
            default:
                printf("Koniec programu.\n");
                return 0;
        }

    }
    usun_menu(&menu);
    usun_liste(&lista);

}
