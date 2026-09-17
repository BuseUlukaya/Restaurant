/* Don't forget to use the 'gifted' namespace. */
#include <cctype>
#include <cstring>
#include <iostream>
#include "constants.h"

namespace gifted {
    class Menu;
    class MenuItem {
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
        std::ostream& display(std::ostream& ostr = std::cout) const;
        ~MenuItem();
    };
    class Menu {
        private:
            unsigned int item_tab_number;
            unsigned int item_tab_size;
            unsigned int items_number;
            MenuItem title;
            MenuItem exit_option;
            MenuItem selection_entry_prompt;
            MenuItem* items[MaximumNumberOfMenuItems];
        public:
            Menu();
    };
}