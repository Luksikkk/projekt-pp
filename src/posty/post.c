#include "../../include/posty/post.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Post {
    int id;
    char autor[maxauthor];
    char tresc[maxtresc];
    enum Kategoria kategoria_zgloszenia;
    int liczba_zgloszen;
    enum Status status_zgloszenia;
};

Post* stworz_post(int id) {
    Post* post = malloc(sizeof(*post));
    if (!post) return NULL;
    post->id = id;
    return post;
}

void utworz_post(Post *post) {
    podaj_autor(post->autor);
    podaj_tresc(post->tresc);
    podaj_kategoriezgloszenia(&post->kategoria_zgloszenia);
    post -> status_zgloszenia = DO_WERYFIKACJI;
    podaj_liczbezgloszen(&post->liczba_zgloszen);
    printf("Poprawnie dodano post!\n\n");
}

void usun_post(Post** p_post) {
    free (*p_post);
    *p_post = NULL;
}


void wyswietl_post(Post* post) {
    printf("ID Posta: %d\n", post->id);
    printf("Kategoria zgloszenia: %s\n", kategoria_to_string(post->kategoria_zgloszenia));
    printf("Status zgloszenia: %s\n", statuszgloszenie_to_string(post->status_zgloszenia));
    printf("Liczba zgloszen: %d\n", post->liczba_zgloszen);
    printf("Autor posta: %s\n", post->autor);
    printf("Tresc posta: %s\n", post->tresc);
    printf("=====================\n\n");
}


const char *kategoria_to_string(const enum Kategoria kat) {
    switch (kat) {
        case SPAM:
            return "SPAM";
        case HEJT:
            return "HEJT";
        case WULGARYZMY:
            return "WULGARYZMY";
        case FEJK_NEWS:
            return "FEJK_NEWS";
        case NIEODPOWIEDNIE:
            return "NIEODPOWIEDNIE";
        default:
            return "BRAK";
    }
}

char *statuszgloszenie_to_string(const enum Status Status) {
    switch (Status) {
        case DO_WERYFIKACJI:
            return "DO_WERYFIKACJI";
        case W_TRAKCIE_ANALIZY:
            return "W_TRAKCIE_ANALIZY";
        case ZATWIERDZONE:
            return "ZATWIERDZONE";
        case USUNIETE:
            return "USUNIETE";
        default:
            return "BRAK";
    }
}

enum Kategoria stringtokategoria(const char* tekst) {
    if (strcmp(tekst, "SPAM") == 0) {
        return SPAM;
    }
    if (strcmp(tekst, "HEJT") == 0) {
        return HEJT;
    }
    if (strcmp(tekst,"WULGARYZMY") == 0) {
        return WULGARYZMY;
    }
    if (strcmp(tekst, "FEJK_NEWS") == 0) {
        return FEJK_NEWS;
    }
    if (strcmp(tekst, "NIEODPOWIEDNIE") == 0) {
        return NIEODPOWIEDNIE;
    }
    if (strcmp(tekst, "BRAK") == 0 || !tekst) {
        return BRAK;
    }
    return -1;
}

enum Status stringtostatus(const char* stat) {
    if (strcmp(stat, "DO_WERYFIKACJI") == 0) {
        return DO_WERYFIKACJI;
    }
    if (strcmp(stat, "W_TRAKCIE_ANALIZY") == 0) {
        return W_TRAKCIE_ANALIZY;
    }
    if (strcmp(stat, "ZATWIERDZONE") == 0) {
        return ZATWIERDZONE;
    }
    if (strcmp(stat, "USUNIETE") == 0) {
        return USUNIETE;
    }
    return -1;
}

int getid(const Post* post) {
    if (post) return post ->id;
    return -1;
}

const char* getautor(const Post* post) {
    if (post) return post -> autor;
    return NULL;
}

const char* gettresc(const Post* post) {
    if (post) return post -> tresc;
    return NULL;
}

enum Kategoria getkategoria_zgloszenia(const Post* post) {
    if (post) return post -> kategoria_zgloszenia;
    return BRAK;
}

enum Status getstatuszgloszenie(const Post* post) {
    if (post) return post -> status_zgloszenia;
    return DO_WERYFIKACJI;
}

int getliczba_zgloszen(const Post* post) {
    if (post) return post -> liczba_zgloszen;
    return -1;
}

void setid(Post* post, int id) {
    post-> id = id;
}

void setautor(Post* post, const char* autor) {
    strncpy(post -> autor, autor,sizeof(post->autor));
    post -> autor[sizeof(post -> autor) - 1] = '\0';
}
void settresc(Post* post, const char* tresc) {
    strncpy(post -> tresc, tresc,sizeof(post->tresc));
    post -> tresc[sizeof(post -> tresc) - 1] = '\0';
}
void setkategoria(Post* post, const enum Kategoria kat) {
    post -> kategoria_zgloszenia = kat;
}
void setliczbazgloszen(Post* post, int liczbazgloszen) {
    post -> liczba_zgloszen = liczbazgloszen;
}
void setstatuszgloszenia(Post* post, const enum Status statuszgloszenia) {
    post -> status_zgloszenia = statuszgloszenia;
}

void podaj_autor(char* autor) {
    int c;
    int poprawny = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
    while (poprawny == 0) {
        printf("Podaj nazwe autora:\n");
        if (fgets(autor,maxauthor,stdin) == NULL) break;
        size_t dlugosc = strlen(autor);
        if (dlugosc == maxauthor - 1 && autor[dlugosc-1] != '\n') {
            printf("Nazwa jest za dluga! Sprobuj jeszcze raz\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }
        if (dlugosc > 0 && autor[dlugosc-1] == '\n') {
            autor[dlugosc-1] = '\0';
            dlugosc--;
        }
        if (dlugosc == 0) {
            continue;
        }
        int znak=0;
        for (int i=0;i<dlugosc; i++) {
            if (!isalpha(autor[i]) && autor[i] != ' ') {
                printf("Nazwa autora moze sklada sie tylko z liter. Sprobuj jeszcze raz.\n");
                znak=1;
                break;
            }
        }
        if (znak) continue;
        poprawny=1;
    }

}

void podaj_tresc(char* tresc) {
    int c;
    int poprawny = 0;
    while (poprawny == 0) {
        printf("Podaj tresc posta:\n");
        if (fgets(tresc,maxtresc,stdin) == NULL) break;
        size_t dlugosc = strlen(tresc);
        if (dlugosc == maxtresc - 1 && tresc[dlugosc-1] != '\n') {
            printf("Tresc jest za dluga! Sprobuj jeszcze raz\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }
        if (dlugosc > 0 && tresc[dlugosc-1] == '\n') {
            tresc[dlugosc-1] = '\0';
            dlugosc--;
        }
        if (dlugosc == 0) {
            printf("Tresc nie moze byc pusta! Sprobuj jeszcze raz\n");
            continue;
        }
        poprawny=1;
    }
}


void podaj_kategoriezgloszenia(enum Kategoria *kategoria) {
    *kategoria = BRAK;
    int wybor, c;
    while (*kategoria == BRAK) {
        printf("Podaj kategorie zgloszenia:\n");
        printf("0. SPAM\n1. HEJT\n2. Wulgaryzmy \n3. Fejk news \n4. Nieodpowiednie tresci\n");
        if (scanf("%d", &wybor) != 1) {
            printf("Niepoprawny wybor. Sprobuj jeszcze raz.\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }
        switch (wybor) {
            case 0:
                *kategoria = SPAM;
                break;
            case 1:
                *kategoria = HEJT;
                break;
            case 2:
                *kategoria = WULGARYZMY;
                break;
            case 3:
                *kategoria = FEJK_NEWS;
                break;
            case 4:
                *kategoria = NIEODPOWIEDNIE;
                break;
            default:
                printf("Wybrano zla opcje. Sprobuj jeszcze raz.\n");
        }
    }
}

void podaj_liczbezgloszen(int* liczba) {
    int wartosc;
    int c;
    int poprawnie = 0;
    while (poprawnie == 0) {
        printf("Podaj liczbe zgloszen: \n");
        if (scanf("%d", &wartosc) != 1) {
            printf("Niepoprawna wartosc! Sprobuj jeszcze raz.\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }
        if (wartosc<0) {
            printf("Liczba zgloszen nie moze byc ujemna! Sprobuj jeszcze raz.\n");
            continue;
        }
        if (wartosc>=2147483647) {
            printf("Podana liczba jest za duza! Sprobuj jeszcze raz\n");
            continue;
        }
        *liczba = wartosc;
        poprawnie = 1;
    }
}

