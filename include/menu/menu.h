#ifndef PROJEKT_C_MENU_H
#define PROJEKT_C_MENU_H


typedef struct Menu Menu;

Menu* stworz_menu(void);
void usun_menu(Menu** p_menu);

void wypisz_menu(const Menu* menu);

#endif
