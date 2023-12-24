#ifndef POSITION_H
#define POSITION_H

#include <iostream>

class Position {
private:
    int x;
    int y;
    int z;

public:
    // Конструктор по умолчанию
    Position() : x(0), y(0), z(0) {}
    Position(int x, int y, int z);
    int get_x() const;
    int get_y() const;
    int get_z() const;
    
    void set_x(int new_x);
    void set_y(int new_y);
    void set_z(int new_z);
    friend bool operator==(const Position& lhs, const Position& rhs);
    friend bool operator!=(const Position& lhs, const Position& rhs);
    friend std::istream& operator>>(std::istream& in, Position& position);
    friend std::ostream& operator<<(std::ostream& out, const Position& position);  
 
};

#endif 
