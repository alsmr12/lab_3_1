#include "Terminal.h"
#include <algorithm>

/*
void Terminal::add_warehouse(const Warehouse& warehouse) {
    warehouses.push_back(warehouse);
}

void Terminal::delete_warehouse(const Warehouse& warehouse) {
    warehouses.remove(warehouse);
}

void Terminal::change_dimension_warehouse(const Warehouse& warehouse, const Size& new_dimensions) {
    auto it = std::find(warehouses.begin(), warehouses.end(), warehouse);
    if (it != warehouses.end()) {
        it->set_dimensions(new_dimensions);
    }
}

void Terminal::show_information() const {
    std::cout << "Terminal Information:\n";
    for (const auto& warehouse : warehouses) {
        std::cout << "Warehouse Size: " << warehouse.get_dimensions().get_length()
                  << " x " << warehouse.get_dimensions().get_width()
                  << " x " << warehouse.get_dimensions().get_height() << "\n";
    }
}

const std::list<Warehouse>& Terminal::get_warehouses() const {
    return warehouses;
}

std::istream& operator>>(std::istream& in, Temperature& temp) {
    in >> temp.temperature;
    return in;
}


Warehouse& Terminal::get_warehouse_by_index(int index) {
    auto it = std::next(warehouses.begin(), index);
    return *it;
}
*/

Warehouse* Terminal::find_warehouse_by_number(int number) {
    for (auto& warehouse : warehouses) {
        if (warehouse.get_number() == number) {
            return &warehouse;
        }
    }
    return nullptr; // Если склад с указанным номером не найден
}

void Terminal::add_warehouse(const Warehouse& warehouse, int number) {
    if(find_warehouse_by_number(number) == nullptr){
        Warehouse newWarehouse = warehouse; // Create a copy
        newWarehouse.set_number(number); // Assign a unique number
        warehouses.push_back(newWarehouse);
    }else{
        std::cout << "Error";
    }
}
/*
void Terminal::delete_warehouse(int warehouseIndex) {
    if (find_warehouse_by_number(warehouseIndex) != nullptr) {
        auto it = std::next(warehouses.begin(), warehouseIndex);
        warehouses.erase(it);
    }else{
        std::cout << "Error";
    }
}
*/

void Terminal::delete_warehouse(int warehouseNumber) {
    auto it = std::find_if(warehouses.begin(), warehouses.end(),
                           [warehouseNumber](const Warehouse& warehouse) {
                               return warehouse.get_number() == warehouseNumber;
                           });

    if (it != warehouses.end()) {
        warehouses.erase(it);
    } else {
        std::cout << "Error: Warehouse with number " << warehouseNumber << " not found.\n";
    }
}
/*
void Terminal::change_dimension_warehouse(int warehouseIndex, const Size& new_dimensions) {
    if (find_warehouse_by_number(warehouseIndex) != nullptr) {
        auto it = std::next(warehouses.begin(), warehouseIndex);
        it->set_dimensions(new_dimensions);
    }else{
        std::cout << "Error";
    }
}
*/

void Terminal::change_dimension_warehouse(int warehouseNumber, const Size& new_dimensions) {
   auto it = std::find_if(warehouses.begin(), warehouses.end(),
                           [warehouseNumber](const Warehouse& warehouse) {
                               return warehouse.get_number() == warehouseNumber;
                           });
    if(it != warehouses.end()){
        it->set_dimensions(new_dimensions);
    }else{
        std::cout << "Error: Warehouse with number " << warehouseNumber << " not found.\n";
    }
}

void Terminal::show_information() const {
    std::cout << "Terminal Information:\n";
    for (const auto& warehouse : warehouses) {
        std::cout << "Warehouse #" << warehouse.get_number() << " Size: "
                  << warehouse.get_dimensions().get_length() << " x "
                  << warehouse.get_dimensions().get_width() << " x "
                  << warehouse.get_dimensions().get_height() << "\n";
    }
}

const std::list<Warehouse>& Terminal::get_warehouses() const {
    return warehouses;
}

std::string Terminal::show_terminal_information() const {
    std::string info;
    for (const auto& warehouse : warehouses) {
        info += "Warehouse #" + std::to_string(warehouse.get_number()) + " Size: "
                + std::to_string(warehouse.get_dimensions().get_length()) + " x "
                + std::to_string(warehouse.get_dimensions().get_width()) + " x "
                + std::to_string(warehouse.get_dimensions().get_height()) + "\n";
    }
    return info;
}

Warehouse& Terminal::get_warehouse_by_index(int index) {
    auto it = std::next(warehouses.begin(), index);
    return *it;
}

