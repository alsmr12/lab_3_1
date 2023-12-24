#include "Container.h"

Container::Container(int number, std::string client, Size size, int cost, int weight, Position position)
    : container_number(number), client(client), dimensions(size), cost(cost), weight(weight), position(position) {}

std::string Container::get_information_container() const {
    return "Container Number: " + std::to_string(container_number) +
           "\nClient: " + client +
           "\nSize: " + std::to_string(dimensions.get_length()) + "x" +
                       std::to_string(dimensions.get_width()) + "x" +
                       std::to_string(dimensions.get_height()) +
           "\nCost: " + std::to_string(cost) +
           "\nWeight: " + std::to_string(weight);
}

std::string Container::get_container_type() const {
    return ContainerTypeUtil::to_string(type);
}

const Size& Container::get_dimensions() const {
    return dimensions;
}

int Container::get_container_number() const {
    return container_number;
}

int Container::get_weight() const {
    return weight;
}

int Container::get_cost() const {
    return cost;
}

void Container::set_position(const Position& new_position) {
    position.set_x(new_position.get_x());
    position.set_y(new_position.get_y());
    position.set_z(new_position.get_z());
}

Orientation Container::get_orientation() const {
    return orientation;
}

void Container::set_orientation(Orientation new_orientation) {
    orientation = new_orientation;
}

Position Container::get_position() const {
    return position;
}

bool Container::is_fragile() const {
    return false;  // Базовый класс не является хрупким
}



std::ostream& operator<<(std::ostream& os, const Container& container) {
    os << "Container Number: " << container.get_container_number() << "\n"
       << "Size: " << container.get_dimensions().get_length() << "x"
       << container.get_dimensions().get_width() << "x"
       << container.get_dimensions().get_height() << "\n"
       << "Cost: " << container.get_cost() << "\n"
       << "Weight: " << container.get_weight() << "\n";

    return os;
}
