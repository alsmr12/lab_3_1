#ifndef SIZE_H
#define SIZE_H

#include <iostream>

class Size {
private:
    int length;
    int width;
    int height;

public:
    // Конструктор по умолчанию
    Size() : length(0), width(0), height(0) {}
    Size(int l, int w, int h);
    int get_length() const;
    int get_width() const;
    int get_height() const;
    Size transpose() const;
    bool equals(const Size& other) const;
    bool operator==(const Size& other) const;
    // Оператор ввода
    
    friend std::istream& operator>>(std::istream& in, Size& size);    
};

#endif 
