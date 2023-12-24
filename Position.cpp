#include "Position.h"

Position::Position(int x, int y, int z) : x(x), y(y), z(z) {}

int Position::get_x() const {
    return x;
}

int Position::get_y() const {
    return y;
}

int Position::get_z() const {
    return z;
}

void Position::set_x(int new_x) {
    x = new_x;
}

void Position::set_y(int new_y) {
    y = new_y;
}

void Position::set_z(int new_z) {
    z = new_z;
}

bool operator==(const Position& lhs, const Position& rhs) {
    return lhs.get_x() == rhs.get_x() && lhs.get_y() == rhs.get_y() && lhs.get_z() == rhs.get_z();
}

bool operator!=(const Position& lhs, const Position& rhs) {
    return !(lhs == rhs);
}

// Оператор ввода
std::istream& operator>>(std::istream& in, Position& position) {
    // Вводим значения координат из потока
    in >> position.x >> position.y >> position.z;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Position& position) {
    out << "(" << position.get_x() << ", " << position.get_y() << ", " << position.get_z() << ")";
    return out;
}
