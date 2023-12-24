#include "Temperature.h"

Temperature::Temperature(int temp) : temperature(temp) {}

int Temperature::get_temperature() const {
    return temperature;
}

std::istream& operator>>(std::istream& in, Temperature& temp) {
    in >> temp.temperature;
    return in;
}