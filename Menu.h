/* Don't forget to use the 'gifted' namespace. */
#ifndef GIFTED_MENU_H
#define GIFTED_MENU_H

#include <cctype>
#include <cstring>
#include <iostream>
#include "constants.h"

namespace gifted
{
    class Menu;
    class MenuItem
    {
    private:
        friend class Menu;
        char *content;
        unsigned int tab_number;
        unsigned int tab_size;
        int item_number;
        MenuItem(const char *text, unsigned int tabs, unsigned int size, int item);
        MenuItem(const MenuItem &) = delete;
        MenuItem &operator=(const MenuItem &) = delete;
        operator bool() const;
        std::ostream &display(std::ostream &ostr = std::cout) const;
        ~MenuItem();
    };
    class Menu
    {
    private:
        unsigned int item_tab_number;
        unsigned int item_tab_size;
        unsigned int item_count;
        MenuItem title;
        MenuItem exit_option;
        MenuItem selection_entry_prompt;
        MenuItem *items[MaximumNumberOfMenuItems];

    public:
        Menu(const char *title_text, const char *exit_text = "Exit", unsigned int tabs = 0, unsigned int size = 3);
        Menu &operator<<(const char *content);
        Menu(const Menu &) = delete;
        Menu &operator=(const Menu &) = delete;
        size_t select() const;
        ~Menu();
    };
    size_t operator<<(std::ostream &ostr, const Menu &m);
}
#endif