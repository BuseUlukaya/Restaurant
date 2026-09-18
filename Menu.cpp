/* Don't forget to use the 'gifted' namespace. */
#include <iostream>
#include "Menu.h"
#include "Utils.h"

namespace gifted {
    MenuItem::MenuItem(const char* text, unsigned int tabs, unsigned int size, int item) {
        content = nullptr;
        tab_number = 0;
        tab_size = 0;
        item_number = 0;
        bool onlySpace = true;
        if (text != nullptr) {
            for (int i = 0; text[i] != '\0'; i++) {
                if (!isspace(text[i])) {
                    onlySpace = false;
                }
            }
        }
        if (text == nullptr || text[0] == '\0' || onlySpace || tabs > 4 || size > 4 || item > MaximumNumberOfMenuItems) {
            content = nullptr;
        }
        else {
            content = new char[strlen(text) + 1];
            strcpy(content, text);
            tab_number = tabs;
            tab_size = size;
            item_number = item;
        }
    }
    MenuItem::~MenuItem() {
        delete[] content;
    }

    MenuItem::operator bool() const {
        bool valid = true;
        if (content == nullptr) {
            valid = false;
        }
        return valid;
    }
    std::ostream& MenuItem::display(std::ostream& ostr) const {
        if (content == nullptr) {
            ostr << "??????????";
        }
        else {
            for (unsigned int i = 0; i < tab_number * tab_size; i++) {
                ostr << ' ';
            }
            if (item_number >= 0) {
                ostr.width(2);
                ostr << item_number << "- ";
            }
            int i = 0;
            while (content[i] != '\0' && isspace(content[i])) {
                i++;
            }
            ostr << (content + i);
        }
        return ostr;
    }
    Menu::Menu(const char* title_text, const char* exit_text, unsigned int tabs, unsigned int size) : item_tab_number(tabs),
          item_tab_size(size), item_count(0), title(title_text, tabs, size, -1), exit_option(exit_text, tabs, size, 0),
          selection_entry_prompt("> ", tabs, size, -1) {
        for (unsigned int i = 0; i < MaximumNumberOfMenuItems; i++) {
            items[i] = nullptr;
        }
    }
    Menu& Menu::operator<<(const char* content) {
        if (item_count < MaximumNumberOfMenuItems) {
            items[item_count] = new MenuItem(content, item_tab_number, item_tab_size, item_count + 1);
            item_count++;
        }
        return *this;
    }
    Menu::~Menu() {
        for (unsigned int i = 0; i < MaximumNumberOfMenuItems; i++) {
            if (items[i] != nullptr) {
                delete items[i];
                items[i] = nullptr;
            }
        }
    }
    size_t Menu::select() const {
        if (title) {
            title.display() << std::endl;
        }
        for (unsigned int i = 0; i < item_count; i++) {
            items[i]->display() << std::endl;
        }
        exit_option.display() << std::endl;
        selection_entry_prompt.display();
        int selection = ut.getInt(0, item_count);
        return selection;
    }
    size_t operator<<(std::ostream& ostr, const Menu& m) {
        if (&ostr == &std::cout) {
            return m.select();
        }
        return 0;
    }
}