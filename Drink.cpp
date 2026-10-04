#include "Drink.h"
#include "Menu.h"
#include "Utils.h"

namespace gifted {
    std::ostream& Drink::print(std::ostream& ostr) const {
        const char* size = ".....";
        if (m_size == 'S') {
            size = "SML..";
        }
        else if (m_size == 'M') {
            size = "MID..";
        }
        else if (m_size == 'L') {
            size = "LRG..";
        }
        else if (m_size == 'X') {
            size = "XLR..";
        }
        ut.printItem(ostr, *this, size, price());
        return ostr;
    }
    bool Drink::order() {
        Menu menu("Drink Size Selection", "Back", 3);
        menu << "Small"
             << "Medium"
             << "Larg"
             << "Extra Large";
        const char sizes[] = { '\0', 'S', 'M', 'L', 'X' };
        m_size = sizes[menu.select()];
        return ordered();
    }
    bool Drink::ordered() const {
        return m_size != '\0';
    }
    std::ifstream& Drink::read(std::ifstream& file) {
        char* text = nullptr;
        double value{};
        if (ut.readItem(file, text, value)) {
            name(text);
            Billable::price(value);
            m_size = '\0';
        }
        delete[] text;
        return file;
    }

    double Drink::price() const {
        double value = Billable::price();
        if (m_size == 'S') {
            value *= 0.5;   
        }
        else if (m_size == 'M') {
            value *= 0.75;  
        }
        else if (m_size == 'X') {
            value *= 1.5;   
        }
        return value;
    }
}