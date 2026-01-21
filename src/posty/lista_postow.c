#include "../../include/posty/lista_postow.h"
#include "../../include/posty/post.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct ListaPostow {
    int rozmiar;
    Post** posty;
    enum SortujPo sortowane_po;
    enum Sortowanie sortowanie_kierunek;
};

ListaPostow* stworz_liste(void) {
    ListaPostow* lista = malloc(sizeof(*lista));
    if(!lista) return NULL;
    lista -> rozmiar = 0;
    lista -> posty = NULL;
    return lista;
}

int dodaj_post(ListaPostow* lista, int pytaj) {
    int id = 1;
    for (int i=0; i<lista->rozmiar;i++) {
        if (getid(lista->posty[i]) != id) {
            break;
        }
        id++;
    }
    Post* nowy_post = stworz_post(id);
    if (pytaj) {
        utworz_post(nowy_post);
    }
    if (nowy_post) {
        lista -> rozmiar++;
        lista -> posty = realloc(lista -> posty, lista -> rozmiar * sizeof(*(lista -> posty)));
        if (lista -> posty == NULL) {
            lista -> rozmiar--;
        }
        lista -> posty[lista -> rozmiar - 1] = nowy_post;

        return 1;
    }
    return 0;
}

void usun_liste(ListaPostow** p_post) {
     for (int i=0; i<(*p_post) -> rozmiar; i++) {
        usun_post(&(*p_post) -> posty[i]);
     }
    free((*p_post)->posty);
    free(*p_post);
    *p_post = NULL;
}

void wypisz_posty(const ListaPostow* lista) {
    if (lista->rozmiar == 0) {
        printf("Brak postow w bazie.\n\n\n");
    }
    else {
        for (int i=0; i<lista -> rozmiar; i++) {
            wyswietl_post(lista -> posty[i]);
        }
    }
}

void edytuj_kategorie(Post* post) {
    int wybor,c;
    do {
        printf("Kategoria zgloszenia (0 = anuluj):\n");
        for (int i = 0; i < liczba_kategorii; i++) {
            printf("%d. %s\n", i + 1, kategoria_to_string((enum Kategoria)i));
        }
        printf("Wybierz opcje: \n");
        if (scanf("%d", &wybor) != 1) {
            while ((c = getchar()) != '\n' && c != EOF) {}
            wybor = -1;
        }

        if (wybor < 0 || wybor > liczba_kategorii) {
            printf("Nie ma takiej opcji! Sprobuj ponownie.\n\n");
        }
    } while (wybor < 0 || wybor > liczba_kategorii);

    if (wybor != 0) {
        setkategoria(post, (enum Kategoria)(wybor - 1));
        printf("Zmieniono kategorie.\n");
    }
    else {
        printf("Anulowano zmiane kategorii.\n");
    }
}

void edytuj_status(Post* post) {
    int wybor;
    int c;
    do {
        printf("Status zgloszenia (0 = anuluj):\n");
        for (int i = 0; i < liczba_statusow; i++) {
            printf("%d. %s\n", i + 1, statuszgloszenie_to_string((enum Status)i));
        }
        printf("Twoj wybor: ");

        if (scanf("%d", &wybor) != 1) {
            while ((c = getchar()) != '\n' && c != EOF) {}
            wybor = -1;
        }

        if (wybor < 0 || wybor > liczba_statusow) {
            printf("Nie ma takiej opcji! Sprobuj ponownie.\n\n");
        }
    } while (wybor < 0 || wybor > liczba_statusow);

    if (wybor != 0) {
        setstatuszgloszenia(post, (enum Status)(wybor - 1));
        printf("Zmieniono status.\n");
    } else {
        printf("Anulowano zmiane statusu.\n");
    }
}

void edytuj_autora(Post* post) {
    char autor[maxauthor];
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    printf("Podaj nowego autora (ENTER = bez zmian): ");
    if (fgets(autor, sizeof(autor), stdin)) {
        autor[strcspn(autor, "\n")] = 0;
        if (autor[0] != '\0') {
            setautor(post, autor);
            printf("Zmieniono autora.\n");
        } else {
            printf("Nie wprowadzono zmian.\n");
        }
    }
}

void edytuj_tresc(Post* post) {
    char tresc[maxtresc];
    while (getchar() != '\n') {}
    printf("Podaj nowa tresc (ENTER = bez zmian): ");
    if (fgets(tresc, sizeof(tresc), stdin)) {
        tresc[strcspn(tresc, "\n")] = 0; // usuń enter
        if (tresc[0] != '\0') {
            settresc(post, tresc);
            printf("Zmieniono tresc.\n");
        } else {
            printf("Nie wprowadzono zmian.\n");
        }
    }
}

int edytuj_post(ListaPostow* lista) {
    if (!lista || !lista->posty || lista->rozmiar <= 0) {
        printf("Brak postow do edycji.\n\n");
        return 0;
    }
    int id;
    printf("Podaj ID posta do edycji: ");
    if (scanf("%d", &id) != 1) {
        while (getchar() != '\n') {}
        printf("Niepoprawne ID.\n\n");
        return 0;
    }
    Post* post = NULL;
    for (int i = 0; i < lista->rozmiar; i++) {
        if (getid(lista->posty[i]) == id) {
            post = lista->posty[i];
            break;
        }
    }

    if (!post) {
        printf("Nie znaleziono posta o ID=%d.\n\n", id);
        return 0;
    }

    printf("\nAktualne dane posta:\n");
    wyswietl_post(post);

    printf("Jaka wartosc chcesz zmienic?\n");
    printf("1. Kategorie zgloszenia.\n");
    printf("2. Status zgloszenia.\n");
    printf("3. Autora posta.\n");
    printf("4. Tresc posta.\n");
    printf("0. Wyjscie z edycji.\n");
    int wybor;
    if (scanf("%d", &wybor) != 1) {
        while (getchar() != '\n') {}
        printf("Niepoprawny wybor! Sprobuj jeszcze raz.\n");
        return 0;
    }
    switch (wybor) {
        case 1:
            edytuj_kategorie(post);
            break;
        case 2:
            edytuj_status(post);
            break;
        case 3:
            edytuj_autora(post);
            break;
        case 4:
            edytuj_tresc(post);
            break;
        case 0:
            break;
         default:
            printf("Niepoprawny wybor! Sprobuj jeszcze raz.\n");
            break;
    }
    return 1;
}

int usun_post_z_listy(ListaPostow *lista,enum Usuwanie usuwanie) {
    if (!lista || !lista->posty || lista->rozmiar <= 0) return 0;
    int usuniete = 0;
    int c;
    if (usuwanie == PO_ID) {
        int id;
        int liczba = 0;
        while (!liczba) {
            printf("Podaj ID posta: ");
            if (scanf("%d", &id) != 1) {
                while ((c = getchar()) != '\n' && c != EOF) {}
                printf("Niepoprawny wybor! Sprobuj jeszcze raz.\n");
            }
            else {
                liczba = 1;
            }
        }
        for (int i = 0; i < lista->rozmiar; i++) {
            if (getid(lista->posty[i]) == id) {
                if (getstatuszgloszenie(lista->posty[i]) == DO_WERYFIKACJI) {
                    printf("Nie mozesz usunac posta! Post wymaga weryfikacji!\n");
                    break;
                }
                usun_post(&lista->posty[i]);
                for (int j = i + 1; j < lista->rozmiar; j++)
                    lista->posty[j - 1] = lista->posty[j];
                lista->rozmiar--;
                usuniete++;
                i--;
            }
        }
        if (usuniete == 0) {
            printf("Nie znaleziono posta o ID %d.\n", id);
        }
    }
    else if (usuwanie == PO_KAT_ZGLOSZENIA) {
        int wybor;
        int c;
        int petla = 0;
        do {
            printf("Wybierz kategorie:\n");
            for (int i = 0; i < liczba_kategorii; i++) {
                printf("%d. %s\n", i + 1, kategoria_to_string(i));
            }
            printf("Wybierz opcje: \n");
            if (scanf("%d", &wybor) != 1) {
                printf("Niepoprawny wybor! Sprobuj ponownie.\n");
                while ((c = getchar()) != '\n' && c != EOF) {}
                continue;
            }
            if (wybor<1 || wybor > liczba_kategorii) {
                puts("Niepoprawna opcja. Sprobuj jeszcze raz.\n");
            }
            else {
                petla = 1;
            }
        } while (!petla);

        enum Kategoria kat = (enum Kategoria)(wybor - 1);

        for (int i = 0; i < lista->rozmiar; i++) {
            if (getstatuszgloszenie(lista->posty[i]) == DO_WERYFIKACJI) {
                printf("Pominieto post nr %d\n", getid(lista->posty[i]));
                printf("Powod: post wymaga weryfikacji.\n");
                continue;
            }
            if (getkategoria_zgloszenia(lista->posty[i]) == kat)
            {
                usun_post(&lista->posty[i]);
                for (int j = i + 1; j < lista->rozmiar; j++)
                    lista->posty[j - 1] = lista->posty[j];
                lista->rozmiar--;
                usuniete++;
                i--;
            }
        }
    }
        else if (usuwanie == PO_STATUSIEZGLOSZENIA)
        {
            enum Status st;
            do {
                for (int i = 0; i < liczba_statusow-1; i++) {
                    printf("%d. %s\n", i + 1, statuszgloszenie_to_string(i+1));
                }
                printf("Wybierz status zgloszenia:\n");
                if (scanf("%d", &st) != 1) return 0;
                if (st==0 || st >= liczba_statusow-1) puts("Niepoprawny wybor, sprobuj jeszcze raz.\n");

            } while (st==0 || st >= liczba_statusow-1);
            for (int i = 0; i < lista->rozmiar; i++) {
                if (getstatuszgloszenie(lista->posty[i]) == st) {
                    usun_post(&lista->posty[i]);
                    for (int j = i + 1; j < lista->rozmiar; j++)
                        lista->posty[j - 1] = lista->posty[j];
                    lista->rozmiar--;
                    usuniete++;
                    i--;
                }
            }
        }

        if (lista->rozmiar == 0)
        {
            free(lista->posty);
            lista->posty = NULL;
        }
        else
        {
            Post** nowe = realloc(lista->posty, lista->rozmiar * sizeof(Post*));
            if (nowe) lista->posty = nowe;
            przelicz_id(lista);
        }
        if (usuniete>0) {
            printf("Poprawnie usunieto %d posty!\n", usuniete);
        }
        return usuniete;
}

void usun_posty(ListaPostow* lista) {
    if (lista->rozmiar == 0) {
        printf("Brak postow do usuniecia.\n");
        return;
    }
    int wybor, c;
    printf("\n--- MENU USUWANIA ---\n");
    printf("1. Usun pojedynczego posta. (po ID)\n");
    printf("2. Usun wiele postow. (po Kategorii)\n");
    printf("3. Usun wiele postow. (po Statusie)\n");
    printf("0. Anuluj\n");
    printf("Wybierz opcje: ");

    if (scanf("%d", &wybor) != 1) {
        while ((c = getchar()) != '\n' && c != EOF) {}
        printf("Bledny wybor. Sprobuj jeszcze raz\n");
        return;
    }

    switch (wybor) {
        case 1: {
            usun_post_z_listy(lista, 0);
            break;
        }
        case 2:
            usun_post_z_listy(lista,1);
            break;
        case 3:
            usun_post_z_listy(lista,2);
            break;
        case 0:
            printf("Anulowano.\n");
            break;
        default:
            printf("Niepoprawna opcja.\n");
    }
    while ((c = getchar()) != '\n' && c != EOF);
}


int zapisz_do_pliku(ListaPostow *lista, const char* sciezka) {
    FILE *plik = fopen(sciezka,"w");
    if (plik == NULL) {
        printf("Nie udalo sie zapisac postow do pliku.\n");
        return -1;
    }
    for (int i=0; i<lista->rozmiar;i++) {
        fprintf(plik,"%d\n", getid(lista->posty[i]));
        fprintf(plik,"%s\n", getautor(lista->posty[i]));
        fprintf(plik,"%s\n", gettresc(lista->posty[i]));
        fprintf(plik,"%s\n", kategoria_to_string(getkategoria_zgloszenia(lista->posty[i])));
        fprintf(plik, "%d\n", getliczba_zgloszen(lista->posty[i]));
        fprintf(plik, "%s\n", statuszgloszenie_to_string(getstatuszgloszenie(lista->posty[i])));
    }
    fclose(plik);
    printf("Zapisano do pliku: %s\n", sciezka);
    return 1;
}


void wczytaj_z_pliku(ListaPostow *lista, const char* sciezka) {
    FILE* plik = fopen(sciezka, "r");
    if (plik == NULL) {
        printf("Blad: Nie mozna otworzyc pliku '%s'.\n", sciezka);
        printf("Sprawdz czy plik istnieje i masz uprawnienia do odczytu.\n");
        return;
    }

    int id, liczbazgloszen, c;
    char autor[maxauthor], tresc[maxtresc], kategoria[maxkategoria], statuszgloszenia[maxkategoria];
    int wczytano = 0;
    int bledy = 0;

    while (fscanf(plik, "%d", &id) == 1) {
        while ((c = fgetc(plik)) != '\n' && c != EOF) {}

        if (fgets(autor, maxauthor, plik) == NULL ||
            fgets(tresc, maxtresc, plik) == NULL ||
            fgets(kategoria, maxkategoria, plik) == NULL ||
            fscanf(plik, "%d", &liczbazgloszen) != 1) {
            printf("Ostrzezenie: Niepelne dane dla posta ID=%d.  Pomijam.\n", id);
            bledy++;
            while ((c = fgetc(plik)) != '\n' && c != EOF) {}
            continue;
        }

        while ((c = fgetc(plik)) != '\n' && c != EOF) {}

        if (fgets(statuszgloszenia, maxkategoria, plik) == NULL) {
            printf("Ostrzezenie: Brak statusu dla posta ID=%d. Pomijam.\n", id);
            bledy++;
            continue;
        }

        autor[strcspn(autor, "\n")] = 0;
        tresc[strcspn(tresc, "\n")] = 0;
        kategoria[strcspn(kategoria, "\n")] = 0;
        statuszgloszenia[strcspn(statuszgloszenia, "\n")] = 0;

        enum Kategoria kat = stringtokategoria(kategoria);
        enum Status stat = stringtostatus(statuszgloszenia);

        if (kat == -1 || stat == -1) {
            printf("Ostrzezenie:  Niepoprawna kategoria lub status dla ID=%d. Pomijam.\n", id);
            bledy++;
            continue;
        }

        dodaj_post(lista, 0);
        setautor(lista->posty[lista->rozmiar-1], autor);
        settresc(lista->posty[lista->rozmiar-1], tresc);
        setkategoria(lista->posty[lista->rozmiar-1], kat);
        setliczbazgloszen(lista->posty[lista->rozmiar-1], liczbazgloszen);
        setstatuszgloszenia(lista->posty[lista->rozmiar-1], stat);
        wczytano++;
    }

    fclose(plik);
    printf("Wczytano %d postow z pliku '%s'.\n", wczytano, sciezka);
    if (bledy > 0) {
        printf("Pominietych wpisow z powodu bledow: %d\n", bledy);
    }
    przelicz_id(lista);
}

void przelicz_id(ListaPostow* lista) {
    for (int i = 0; i < lista->rozmiar; i++) {
        setid(lista->posty[i], i + 1);
    }
}

void menu_sortowania(ListaPostow* lista) {
    if (lista->rozmiar == 0) {
        printf("Brak postow do sortowania.\n");
        return;
    }

    int wybor_kryterium, wybor_kierunek, c;
    do {
        printf("\n--- SORTOWANIE ---\n");
        printf("Podaj po czym chcesz sortowac:\n");
        for (int i = 0; i < liczba_sortowaniapo; i++) {
            printf("%d. %s\n", i + 1, sortuj_to_string((enum SortujPo)i));
        }
        printf("Wybierz: ");

        if (scanf("%d", &wybor_kryterium) != 1) {
            while ((c = getchar()) != '\n' && c != EOF) {}
            wybor_kryterium = -1;
        }
        if (wybor_kryterium < 1 || wybor_kryterium > liczba_sortowaniapo) {
            printf("Niepoprawna opcja.\n");
        }
    } while (wybor_kryterium < 1 || wybor_kryterium > liczba_sortowaniapo);

    // 2. Wybór kierunku
    do {
        printf("\nPodaj jak chcesz sortowac:\n");
        for (int i = 0; i < liczba_sortowan; i++) {
            printf("%d. %s\n", i + 1, kieruneksortowania_to_string((enum Sortowanie)i));
        }
        printf("Wybierz: ");

        if (scanf("%d", &wybor_kierunek) != 1) {
            while ((c = getchar()) != '\n' && c != EOF) {}
            wybor_kierunek = -1;
        }
        if (wybor_kierunek < 1 || wybor_kierunek > liczba_sortowan) {
            printf("Niepoprawna opcja.\n");
        }
    } while (wybor_kierunek < 1 || wybor_kierunek > liczba_sortowan);

    sortuj_lista(lista, (enum SortujPo)(wybor_kryterium - 1), (enum Sortowanie)(wybor_kierunek - 1));

    wypisz_posty(lista);
}

int porownaj_posty(const Post* a, const Post* b, const ListaPostow* lista) {
    int wynik = 0;
    switch (lista->sortowane_po) {
        case ID:
            wynik = getid(a) - getid(b);
            break;
        case AUTORZE:
            wynik = strcmp(getautor(a), getautor(b));
            break;
        case KAT_ZGLOSZENIA:
            wynik = getkategoria_zgloszenia(a) - getkategoria_zgloszenia(b);
            break;
        case LICZBIE_ZGLOSZEN:
            wynik = getliczba_zgloszen(a) - getliczba_zgloszen(b);
            break;
        case STATUS_ZGLOSZENIA:
            wynik = getstatuszgloszenie(a) - getstatuszgloszenie(b);
            break;
    }

    if (lista->sortowanie_kierunek == MALEJACO) {
        return -wynik;
    }
    return wynik;
}

void sortuj_lista(ListaPostow* lista, const enum SortujPo po, const enum Sortowanie kierunek) {
    if (lista->rozmiar < 2) {
        printf("Za malo postow do sortowania.\n");
        return;
    }

    lista->sortowane_po = po;
    lista->sortowanie_kierunek = kierunek;

    printf("\nSortowanie: %s - %s...\n", sortuj_to_string(po), kieruneksortowania_to_string(kierunek));

    for (int i = 0; i < lista->rozmiar - 1; i++) {
        for (int j = 0; j < lista->rozmiar - i - 1; j++) {
            if (porownaj_posty(lista->posty[j], lista->posty[j + 1], lista) > 0) {
                Post* tmp = lista->posty[j];
                lista->posty[j] = lista->posty[j + 1];
                lista->posty[j + 1] = tmp;
            }
        }
    }
    przelicz_id(lista);
    printf("Lista zostala posortowana.\n");
}

const char* sortuj_to_string(const enum SortujPo po) {
    switch (po) {
        case ID:
            return "ID";
        case AUTORZE:
            return "Autor";
        case KAT_ZGLOSZENIA:
            return "Kategoria zgloszenia";
        case LICZBIE_ZGLOSZEN:
            return "Liczba zgloszen";
        case STATUS_ZGLOSZENIA:
            return "Status zgloszenia";
         default:
            return "BRAK";
    }
}

const char* kieruneksortowania_to_string(enum Sortowanie kierunek) {
    switch (kierunek) {
        case ROSNACO:
            return "Rosnaco";
        case MALEJACO:
            return "Malejaco";
        default:
            return "Brak";
    }
}

void szukaj_po_id(const ListaPostow* lista) {
    int id, c;
    printf("Podaj ID szukanego posta: ");
    if (scanf("%d", &id) != 1) {
        printf("To nie jest liczba!\n");
        while ((c = getchar()) != '\n' && c != EOF) {}
        return;
    }
    while ((c = getchar()) != '\n' && c != EOF) {}

    int znaleziono = 0;
    for (int i = 0; i < lista->rozmiar; i++) {
        if (getid(lista->posty[i]) == id) {
            printf("\n--- ZNALEZIONO POST ---\n");
            wyswietl_post(lista->posty[i]);
            znaleziono = 1;
            break;
        }
    }

    if (!znaleziono) {
        printf("Nie znaleziono posta o ID: %d\n", id);
    }
}

void szukajpoautorze(const ListaPostow* lista) {
    char fraza[maxauthor];
    int c, tryb;

    while ((c = getchar()) != '\n' && c != EOF) {}

    printf("Podaj nazwe autora: ");
    if (fgets(fraza, sizeof(fraza), stdin)) {
        fraza[strcspn(fraza, "\n")] = 0;
    }

    if (strlen(fraza) == 0) {
        printf("Nie podano frazy.\n");
        return;
    }

    printf("Tryb wyszukiwania:\n");
    printf("1. Pelne dopasowanie\n");
    printf("2. Prefiksowe (zaczyna sie od... )\n");
    printf("Wybierz: \n");

    if (scanf("%d", &tryb) != 1) {
        while ((c = getchar()) != '\n' && c != EOF) {}
        printf("Niepoprawny wybor.\n");
        return;
    }

    int znaleziono = 0;
    printf("\n--- WYNIKI WYSZUKIWANIA ---\n");

    for (int i = 0; i < lista->rozmiar; i++) {
        const char* autor = getautor(lista->posty[i]);
        int pasuje = 0;

        if (tryb == 1) {
            // Pełne dopasowanie
            pasuje = (strcmp(autor, fraza) == 0);
        } else if (tryb == 2) {
            // Prefiksowe
            pasuje = (strncmp(autor, fraza, strlen(fraza)) == 0);
        }

        if (pasuje) {
            wyswietl_post(lista->posty[i]);
            znaleziono++;
        }
    }

    if (znaleziono == 0) {
        printf("Nie znaleziono postow.\n");
    } else {
        printf("Znaleziono %d post(ow).\n", znaleziono);
    }
}

void wyszukaj_post(const ListaPostow* lista) {
    if (!lista || lista->rozmiar == 0) {
        printf("Baza postow jest pusta. Nie ma czego szukac.\n");
        return;
    }

    int wybor, c;
    do {
        printf("\n=== WYSZUKIWANIE POSTA ===\n");
        printf("1. Szukaj po ID\n");
        printf("2. Szukaj po autorze\n");
        printf("0. Wroc do menu glownego\n");
        printf("Wybierz opcje: \n");

        if (scanf("%d", &wybor) != 1) {
            printf("Nieprawidlowy wybor! Sprobuj jeszcze raz.\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
            wybor = -1;
            continue;
        }
        switch (wybor) {
            case 1:
                szukaj_po_id(lista);
                wybor = 0;
                break;
            case 2:
                szukajpoautorze(lista);
                wybor = 0;
                break;
            case 0:
                wybor = 0;
                break;
            default:
                printf("Nieprawidlowy wybor! Sprobuj jeszcze raz.\n");
                break;
        }
    } while (wybor != 0);
}




