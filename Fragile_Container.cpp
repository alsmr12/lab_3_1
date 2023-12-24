#include "Fragile_Container.h"

Fragile_Container::Fragile_Container(int number, std::string client, Size size, int cost, int weight, int load, Position position)
    : Container(number, client, size, cost, weight, position), max_load(load) {}

std::string Fragile_Container::get_information_container() const {
    return Container::get_information_container() +
           "\nMaximum Load: " + std::to_string(max_load);
}

std::string Fragile_Container::get_container_type() const {
    return ContainerTypeUtil::to_string(ContainerType::FRAGILE);
}

bool Fragile_Container::is_fragile() const {
    return true;  // Fragile_Container является хрупким
}