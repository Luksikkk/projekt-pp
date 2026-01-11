#include "../../include/posty/lista_postow.h"
#include <stdlib.h>
#include "../../include/posty/post.h"


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

void dodaj_post(ListaPostow* lista) {
    int id = 1;
    for (int i=0; i<lista->rozmiar;i++) {
        if (getid(lista->posty[i]) != id) {
            break;
        }
        id++;
    }
    Post* nowy_post = stworz_post(id);
    lista -> rozmiar++;
    lista -> posty = realloc(lista -> posty, lista -> rozmiar * sizeof(*(lista -> posty)));
    if (lista -> posty == NULL) {
        lista -> rozmiar--;
        return;
    }
    lista -> posty[lista -> rozmiar - 1] = nowy_post;
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
    for (int i=0; i<lista -> rozmiar; i++) {
        wyswietl_post(lista -> posty[i]);
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

