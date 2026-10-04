#ifndef GIFTED_DRINK_H
#define GIFTED_DRINK_H

#include "Billable.h"

namespace gifted
{
    class Drink : public Billable
    {
        char m_size;
    public:
        std::ostream &print(std::ostream &ostr = std::cout) const override;
        bool order() override;
        bool ordered() const override;
        std::ifstream &read(std::ifstream &file) override;
        double price() const override;
    };
}

#endif