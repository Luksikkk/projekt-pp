#include "../../include/posty/post.h"

#include <stdio.h>
#include <stdlib.h>

enum status {
    DO_WERYFIKACJI,
    W_TRAKCIE_ANALIZY,
    ZATWIERDZONE,
    USUNIETE
};

struct Post {
    int id;
    char autor[100];
    char tresc[280];
    enum kategoria kategoria_zgloszenia;
    int liczba_zgloszen;
    enum status status_zgloszenia;
};

int getid(Post* post) {
    return post -> id;
}

char* gettresc(Post* post) {
    return post -> tresc;
}

char* getautor(Post* post) {
    return post -> autor;
}

int getliczba_zgloszen(Post* post) {
    return post -> liczba_zgloszen;
}

char *statuszgloszenie_to_string(enum status Status) {
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

enum status getstatuszgloszenie(Post* post) {
    return post->status_zgloszenia;
}


enum kategoria getkategoria_zgloszenia(Post* post) {
    return post -> kategoria_zgloszenia;
}





Post* stworz_post(int id) {
    int wybor;
    Post* post = malloc(sizeof(*post));
    if (!post) return NULL;
    post->id = id;
    printf("Podaj autora posta: \n");
    scanf("%s", post->autor); //trezba zmienic
    printf("Podaj tresc posta: \n");
    scanf("%s", post->tresc); //trzeba zmienic
    printf("Podaj kategorie zgłoszenia:\n");
    printf("0. SPAM\n 1. HEJT\n 2.Wulgaryzmy \n 3. Fejk news \n 4. Nieodpowiednie tresci \n");
    post -> kategoria_zgloszenia = BRAK;
    while (post ->kategoria_zgloszenia == BRAK) {
        scanf("%d", &wybor);
        switch (wybor) {
            case 0:
                post -> kategoria_zgloszenia = SPAM;
                break;
            case 1:
                post -> kategoria_zgloszenia = HEJT;
                break;
            case 2:
                post -> kategoria_zgloszenia = WULGARYZMY;
                break;
            case 3:
                post -> kategoria_zgloszenia = FEJK_NEWS;
                break;
            case 4:
                post -> kategoria_zgloszenia = NIEODPOWIEDNIE;
                break;
            default:
                printf("Wybrano zla opcje. Sprobuj jeszcze raz.\n");
        }
    }
    return post;
}

const char *kategoria_to_string(enum kategoria kat) {
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

void wyswietl_post(Post* post) {
    printf("Autor posta: %s\n", post->autor);
    printf("Kategoria posta: %s\n", kategoria_to_string(post->kategoria_zgloszenia));
    printf("Tresc posta: %s\n", post->tresc);
}

void usun_post(Post** p_post) {
    free (*p_post);
    *p_post = NULL;
}