#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>
#include <list>
#include "Warehouse.h"

class Terminal {
private:
    std::list<Warehouse> warehouses;

public:
    
    void add_warehouse(const Warehouse& warehouse, int number);
    void delete_warehouse(int warehouseNumber);
    void change_dimension_warehouse(int warehouseNumber, const Size& new_dimensions);
    void show_information() const;
    std::string show_terminal_information() const;
    const std::list<Warehouse>& get_warehouses() const;
    Warehouse& get_warehouse_by_index(int index);
    Warehouse* find_warehouse_by_number(int number); 

    
};

#endif

