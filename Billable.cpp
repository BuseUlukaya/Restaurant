#include "Billable.h"
#include "Utils.h"

namespace gifted {
    void Billable::price(double value) {
        m_price = value;
    }
    void Billable::name(const char* value) {
        ut.alocpy(m_name, value);
    }

    // Copy constructor:
    // Ad için ayrı bellek ayırır; iki nesne aynı belleği paylaşmaz.
    Billable::Billable(const Billable& other)
        : m_name(ut.alocpy(other.m_name)),
          m_price(other.m_price) {
    }

    // Copy assignment operator:
    // Önceden oluşturulmuş nesnenin bilgilerini değiştirir.
    Billable& Billable::operator=(const Billable& other) {
        // Nesnenin kendisine atanmasını kontrol eder.
        if (this != &other) {
            name(other.m_name);
            m_price = other.m_price;
        }

        // Zincirleme atamaya izin verir: a = b = c;
        return *this;
    }

    // Ürün adı için ayrılan dinamik belleği serbest bırakır.
    Billable::~Billable() {
        delete[] m_name;
    }

    // Temel fiyatı döndürür.
    double Billable::price() const {
        return m_price;
    }

    // Ürün adını döndürür.
    // Ad yoksa nullptr yerine boş metin döndürür.
    Billable::operator const char*() const {
        return m_name ? m_name : "";
    }

    // Örnek kullanım: total = total + drink;
    double operator+(double money, const Billable& item) {
        // Sanal price(), ürünün Food/Drink fiyatını çağırır.
        return money + item.price();
    }

    // Örnek kullanım: total += food;
    double& operator+=(double& money, const Billable& item) {
        money += item.price();

        return money;
    }

}