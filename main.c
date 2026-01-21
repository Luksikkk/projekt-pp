#include <stdio.h>
#include <string.h>

#include "include/menu/menu.h"
#include "include/posty/lista_postow.h"


int main(int argc, char* argv[]) {
    char sciezka_pliku[256] = "dane.txt";
    if (argc >= 2) {
        strncpy(sciezka_pliku, argv[1], sizeof(sciezka_pliku) - 1);
        sciezka_pliku[sizeof(sciezka_pliku) - 1] = '\0';
        printf("Uzywam pliku: %s\n", sciezka_pliku);
    } else {
        printf("Uzycie: %s <sciezka_do_pliku>\n", argv[0]);
        printf("Uzywam domyslnej sciezki:  %s\n", sciezka_pliku);
    }
    Menu *menu = stworz_menu();
    ListaPostow *lista = stworz_liste();
    int petla = 1;
    int wybor;
    while (petla == 1) {
        printf("======== Moderacyjna Baza Postow Social-Media ========\n");
        wypisz_menu(menu);
        printf("Wybierz opcje: \n");
        if (scanf("%d",&wybor) != 1) {
            while (getchar() != '\n') {}
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
                edytuj_post(lista);
                break;
            case 4:
                usun_posty(lista);
                break;
            case 5:
                menu_sortowania(lista);
                break;
            case 6:
                wyszukaj_post(lista);
                break;
            case 7:
                zapisz_do_pliku(lista, sciezka_pliku);
                break;
            case 8:
                wczytaj_z_pliku(lista,sciezka_pliku);
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
    return 0;
}