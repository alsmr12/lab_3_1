#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <iostream>

class Temperature {
private:
    int temperature;

public:
    Temperature() : temperature(0) {}

    Temperature(int temp);
    int get_temperature() const;

    bool operator==(const Temperature& other) const {
        return temperature == other.temperature;
    }
     friend std::istream& operator>>(std::istream& in, Temperature& temperature);
};

#endif 
