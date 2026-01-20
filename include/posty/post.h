#ifndef MAIN_C_POST_H
#define MAIN_C_POST_H

#define maxtresc 280
#define maxauthor 100
#define maxkategoria 50

enum Status {
    DO_WERYFIKACJI,
    W_TRAKCIE_ANALIZY,
    ZATWIERDZONE,
    USUNIETE,
};

enum Kategoria {
    SPAM,
    HEJT,
    WULGARYZMY,
    FEJK_NEWS,
    NIEODPOWIEDNIE,
    BRAK
};

typedef struct Post Post;

int getid(const Post* post);
Post* stworz_post(int id);
void usun_post(Post** p_post);
const char *kategoria_to_string(enum Kategoria kat);
void wyswietl_post(Post* post);
enum Status getstatuszgloszenie(const Post* post);
enum Kategoria getkategoria_zgloszenia(const Post* post);
char *statuszgloszenie_to_string(enum Status Status);
int getliczba_zgloszen(const Post* post);
const char* getautor(const Post* post);
const char* gettresc(const Post* post);
void setid(Post* post, int id);
void setautor(Post* post, const char* autor);
void settresc(Post* post, const char* tresc);
void setkategoria(Post* post, enum Kategoria kat);
void setliczbazgloszen(Post* post, int liczbazgloszen);
void setstatuszgloszenia(Post* post, enum Status statuszgloszenia);
enum Status stringtostatus(const char* stat);
void utworz_post(Post *post);
enum Kategoria stringtokategoria(const char* tekst);
void podaj_autor(char* autor);
void podaj_tresc(char* tresc);
void podaj_liczbezgloszen(int* liczba);
void podaj_kategoriezgloszenia(enum Kategoria *kategoria);




#endif //MAIN_C_POST_H