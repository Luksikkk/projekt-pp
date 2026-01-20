#include "../../include/posty/lista_postow.h"
#include "../../include/posty/post.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct ListaPostow {
    int rozmiar;
    Post** posty;
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

int usun_post_z_listy(ListaPostow *lista,int id) {
     for (int i=0; i<lista->rozmiar; i++) {
         if (getid(lista->posty[i]) == id) {
             usun_post(&lista->posty[i]);

             for (int j=i+1; j<lista->rozmiar; j++) {
                 lista->posty[j-1] = lista->posty[j];
             }

             lista->rozmiar--;

             lista->posty = realloc(lista->posty,lista->rozmiar);
             if (lista->posty == NULL) {
                 return -1;
             }
             return 1;
         }
     }
    return 0;
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
    return 1;
}


void wczytaj_z_pliku(ListaPostow *lista, const char* sciezka) {
    FILE* plik = fopen(sciezka, "r");
    if (plik == NULL) {
        printf("Nie udalo sie wczytac pliku.\n");
        return;
    }
    int id, liczbazgloszen, c;
    char autor[maxauthor], tresc[maxtresc], kategoria[maxkategoria], statuszgloszenia[maxkategoria];
    while (fscanf(plik,"%d",&id) == 1) {
        while ((c = fgetc(plik)) != '\n' && c != EOF);
        dodaj_post(lista,0);
        setid(lista->posty[lista->rozmiar-1],id);

        fgets(autor,maxauthor, plik);
        autor[strcspn(autor, "\n")] = 0;
        setautor(lista->posty[lista->rozmiar-1],autor);

        fgets(tresc,maxtresc,plik);
        tresc[strcspn(tresc, "\n")] = 0;
        settresc(lista->posty[lista->rozmiar-1],tresc);

        fgets(kategoria,maxkategoria,plik);
        kategoria[strcspn(kategoria, "\n")] = 0;
        setkategoria(lista->posty[lista->rozmiar-1],stringtokategoria(kategoria));

        fscanf(plik, "%d", &liczbazgloszen);
        setliczbazgloszen(lista->posty[lista->rozmiar-1], liczbazgloszen);

        while ((c = fgetc(plik)) != '\n' && c != EOF);

        fgets(statuszgloszenia,maxkategoria, plik);
        statuszgloszenia[strcspn(statuszgloszenia, "\n")] = 0;
        setstatuszgloszenia(lista->posty[lista->rozmiar-1], stringtostatus(statuszgloszenia));
    }
    fclose(plik);
    printf("Poprawnie wczytano plik.\n\n");
}

