#include "Food.h"
#include "Menu.h"
#include "Utils.h"

namespace gifted {
    Food::Food(const Food& other): Billable(other), m_ordered(other.m_ordered), m_child(other.m_child),
          m_customize(ut.alocpy(other.m_customize)) {
    }
    Food& Food::operator=(const Food& other) {
        if (this != &other) {
            Billable::operator=(other);
            ut.alocpy(m_customize, other.m_customize);
            m_ordered = other.m_ordered;
            m_child = other.m_child;
        }
        return *this;
    }
    Food::~Food() {
        delete[] m_customize;
    }
    std::ostream& Food::print(std::ostream& ostr) const {
        const char* portion = ".....";
        if (ordered()) {
            portion = m_child ? "Child" : "Adult";
        }
        ut.printItem(ostr, *this, portion, price());
        if (&ostr == &std::cout && m_customize) {
            ostr << " >> ";
            for (int i = 0; i < 30 && m_customize[i]; ++i) {
                ostr << m_customize[i];
            }
        }
        return ostr;
    }
    bool Food::order() {
        Menu menu("Food Size Selection", "Back", 3);
        menu << "Adult" << "Child";
        size_t selection = menu.select();
        delete[] m_customize;
        m_customize = nullptr;
        m_ordered = selection != 0;
        m_child = selection == 2;

        if (m_ordered) {
            std::cout << "Special instructions\n> ";
            m_customize = ut.readLine(std::cin);
            if (m_customize && m_customize[0] == '\0') {
                delete[] m_customize;
                m_customize = nullptr;
            }
        }
        return ordered();
    }
    bool Food::ordered() const {
        return m_ordered;
    }
    std::ifstream& Food::read(std::ifstream& file) {
        char* text = nullptr;
        double value{};
        if (ut.readItem(file, text, value)) {
            name(text);
            Billable::price(value);
            m_ordered = false;
            m_child = false;
            delete[] m_customize;
            m_customize = nullptr;
        }
        delete[] text;
        return file;
    }
    double Food::price() const {
        double value = Billable::price();
        if (ordered() && m_child) {
            value *= 0.5;
        }
        return value;
    }

}