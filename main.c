#include "include/menu/menu.h"

int main(void) {
    Menu *menu = stworz_menu();
    wypisz_menu(menu);
    usun_menu(&menu);
}