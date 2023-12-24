#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <string>
#include "Size.h"
#include "Position.h"
#include "Orientation.h"
#include "ContainerType.h"


class Container {
private:
    int container_number;
    std::string client;
    Size dimensions;
    int cost;
    int weight;
    Position position; 
    Orientation orientation;
    ContainerType type;

public:
    Container() : container_number(0), cost(0), weight(0), type(ContainerType::STANDARD) {}
    Container(int number, std::string client, Size size, int cost, int weight, Position position);
    std::string get_information_container() const;
    std::string get_container_type() const;
    const Size& get_dimensions() const;
    int get_container_number() const;
    int get_cost() const;
    int get_weight() const;
    void set_position(const Position& new_position);
    Orientation get_orientation() const;
    void set_orientation(Orientation new_orientation);
    Position get_position() const;
    virtual bool is_fragile() const;
    friend std::ostream& operator<<(std::ostream& os, const Container& container);
    // Операторы сравнения
    // Оператор сравнения для класса Container
    bool operator==(const Container& other) const {
    return container_number == other.container_number;
}
    // Оператор несравнимости
bool operator!=(const Container& other) const {
    return !(*this == other);
}

// Оператор "меньше"
bool operator<(const Container& other) const {
    return container_number < other.container_number;
}

// Оператор "меньше или равно"
bool operator<=(const Container& other) const {
    return container_number <= other.container_number;
}

// Оператор "больше"
bool operator>(const Container& other) const {
    return container_number > other.container_number;
}

// Оператор "больше или равно"
bool operator>=(const Container& other) const {
    return container_number >= other.container_number;
}
    virtual ~Container() = default; // Виртуальный деструктор
    Size getBoundingBox() const {
        return dimensions;
    }
    void set_number(int new_number) {
        container_number = new_number;
    }

    // Метод для получения массива координат контейнера
    const int* get_keys() const {
        static int keys[3];  // Предполагается, что у вас трехмерное пространство

        keys[0] = position.get_x();
        keys[1] = position.get_y();
        keys[2] = position.get_z();

        return keys;
    }

    
};

#endif 