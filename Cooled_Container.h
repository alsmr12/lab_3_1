#ifndef COOLED_CONTAINER_H
#define COOLED_CONTAINER_H

#include "Container.h"
#include "Temperature.h"

class Cooled_Container : public Container {
private:
    Temperature max_temperature;

public:
    Cooled_Container(int number, std::string client, Size size, int cost, int weight, Temperature temp, Position position);
    std::string get_information_container() const;
    std::string get_container_type() const;
};

#endif
