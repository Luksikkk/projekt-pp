#include <stdio.h>

#include "include/menu/menu.h"
#include "include/posty/lista_postow.h"


int main(int argc, char* argv[]) {
    Menu *menu = stworz_menu();
    ListaPostow *lista = stworz_liste();
    int petla = 1;
    int wybor;
    int id_posta;
    while (petla == 1) {
        printf("======== Moderacyjna Baza Postow Social-Media ========\n");
        wypisz_menu(menu);
        printf("Wybierz opcje: \n");
        if (scanf("%d",&wybor) != 1) {
            while (getchar() != '\n');
            printf("Niepoprawny wybor. Sprobuj jeszcze raz.\n\n");
            continue;
        }
        switch (wybor) {
            case 1:
                wypisz_posty(lista);
                break;
            case 2:
                dodaj_post(lista,1);
                break;
            case 3:
                printf("Podaj ID posta:\n");
                scanf("%d",&id_posta);
                usun_post_z_listy(lista, id_posta);
                break;
            case 4:
                char nazwa[100];
                printf("Podaj nazwe pliku:\n");
                scanf("%s", nazwa);
                zapisz_do_pliku(lista, nazwa);
                break;
            case 5:
                char sciezka[100];
                printf("Podaj sciezke pliku\n");
                scanf("%s", sciezka);
                wczytaj_z_pliku(lista,sciezka);
                break;
            case 0:
                printf("Koncze dzialanie programu...\n");
                petla = 0;
                break;
            default:
                printf("Nieprawidlowy wybor! Sprobuj jeszcze raz.\n\n");
                break;
        }
    }
    usun_menu(&menu);
    usun_liste(&lista);
}