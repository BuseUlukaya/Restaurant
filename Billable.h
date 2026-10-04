#ifndef GIFTED_BILLABLE_H
#define GIFTED_BILLABLE_H

#include <iostream>
#include <fstream>

namespace gifted
{
    class Billable
    {
        char *m_name;
        double m_price;

    protected:
        void name(const char *value);
        void price(double value);

    public:
        Billable() = default;
        Billable(const Billable &other);
        Billable &operator=(const Billable &other);
        virtual ~Billable();
        virtual double price() const;
        virtual std::ostream &print(std::ostream &ostr = std::cout) const = 0;
        virtual bool order() = 0;
        virtual bool ordered() const = 0;
        virtual std::ifstream &read(std::ifstream &file) = 0;
        operator const char *() const;
    };
    double operator+(double money, const Billable &item);
    double &operator+=(double &money, const Billable &item);
}

#endif