#include "Cooled_Container.h"

Cooled_Container::Cooled_Container(int number, std::string client, Size size, int cost, int weight, Temperature temp, Position position)
    : Container(number, client, size, cost, weight, position), max_temperature(temp) {}

std::string Cooled_Container::get_information_container() const {
    return Container::get_information_container() +
           "\nMaximum Temperature: " + std::to_string(max_temperature.get_temperature());
}

std::string Cooled_Container::get_container_type() const {
    return ContainerTypeUtil::to_string(ContainerType::COOLED);
}