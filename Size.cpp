#include "Size.h"

Size::Size(int l, int w, int h) : length(l), width(w), height(h) {}

int Size::get_length() const {
    return length;
}

int Size::get_width() const {
    return width;
}

int Size::get_height() const {
    return height;
}

Size Size::transpose() const {
    return Size(width, length, height);
}

bool Size::equals(const Size& other) const {
    return (length == other.length) && (width == other.width) && (height == other.height);
}

bool Size::operator==(const Size& other) const {
    return equals(other);
}

std::istream& operator>>(std::istream& in, Size& size) {
    int l, w, h;
    std::cout << "Enter length: ";
    in >> l;
    std::cout << "Enter width: ";
    in >> w;
    std::cout << "Enter height: ";
    in >> h;

    // Проверка на корректность ввода
    if (in) {
        size = Size(l, w, h);
    }

    return in;
}