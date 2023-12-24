#ifndef FRAGILE_CONTAINER_H
#define FRAGILE_CONTAINER_H

#include <iostream>
#include "Container.h"
#include "Orientation.h"

class Fragile_Container : public Container {
private:
    int max_load;

public:
    Fragile_Container(int number, std::string client, Size size, int cost, int weight, int load, Position position);
    std::string get_information_container() const;
    std::string get_container_type() const;
    bool is_fragile() const override;
};


#endif 
