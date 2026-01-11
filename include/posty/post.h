#ifndef MAIN_C_POST_H
#define MAIN_C_POST_H

enum kategoria {
    SPAM,
    HEJT,
    WULGARYZMY,
    FEJK_NEWS,
    NIEODPOWIEDNIE,
    BRAK
};

typedef struct Post Post;

int getid(Post* post);
Post* stworz_post(int id);
void usun_post(Post** p_post);
const char *kategoria_to_string(enum kategoria kat);
void wyswietl_post(Post* post);
enum status getstatuszgloszenie(Post* post);
enum kategoria getkategoria_zgloszenia(Post* post);
char *statuszgloszenie_to_string(enum status Status);
int getliczba_zgloszen(Post* post);
char* getautor(Post* post);
char* gettresc(Post* post);



#endif //MAIN_C_POST_H