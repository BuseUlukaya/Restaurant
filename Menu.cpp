/* Don't forget to use the 'gifted' namespace. */
#include <iostream>
#include "Menu.h"

namespace gifted
{
    MenuItem::MenuItem(const char *text, unsigned int tabs, unsigned int size, int item)
    {
        content = nullptr;
        tab_number = 0;
        tab_size = 0;
        item_number = 0;
        bool onlySpace = true;

        if (text != nullptr)
        {
            for (int i = 0; text[i] != '\0'; i++)
            {
                if (!isspace(text[i]))
                {
                    onlySpace = false;
                }
            }
        }

        if (text == nullptr || text[0] == '\0' || onlySpace || tabs > 4 || size > 4 || item > 20)
        {
            content = nullptr;
        }
        else
        {
            content = new char[strlen(text) + 1];
            strcpy(content, text);
            tab_number = tabs;
            tab_size = size;
            item_number = item;
        }
    }
    MenuItem::~MenuItem()
    {
        delete[] content;
    }
    MenuItem::operator bool() const
    {
        bool valid = true;
        if (content == nullptr)
        {
            valid = false;
        }

        return valid;
    }
    std::ostream &MenuItem::display(std::ostream &ostr) const
    {
        if (content == nullptr)
        {
            ostr << "??????????";
        }
        else
        {
            for (unsigned int i = 0; i < tab_number * tab_size; i++)
            {
                ostr << ' ';
            }

            if (item_number >= 0)
            {
                ostr.width(2);
                ostr << item_number << "- ";
            }

            int i = 0;
            while (content[i] != '\0' && isspace(content[i]))
            {
                i++;
            }

            ostr << (content + i);
        }

        return ostr;
    }
}