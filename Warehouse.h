#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <list>
#include <cstdlib>
#include "Container.h"
#include "Size.h"
#include "Temperature.h"
#include "Position.h"
#include "Orientation.h"
#include "Tree.h"

/*
class Warehouse {
private:
    int number;
    Size dimensions;
    Temperature temperature;
    std::list<Container> containers; 

public:
    Warehouse(int number, Size size, Temperature temp);
    //Container* find_container(int number);
    std::list<Container>::iterator find_container(int number);
    void add_container_hand(const Container& container, int container_number, const Position& position);
    void move_container(const Container& container, const Position& new_position);
    void rotate_container(const Container& container, Orientation orientation);
    void remove_container(const Container& container);
    const std::list<Container>& get_report() const;
    bool is_position_free(const Position& position, const Size& container_size, int container_weight) const;
    Position find_suitable_position(const Size& container_size) const;
    Position add_container_automatically(Container& container);
    int get_maximal_containers_size(const Size& size, bool allow_rotation) const;
    std::list<Container>::iterator find_container_by_number(int container_number);
    void set_dimensions(const Size& new_dimensions);
    Container& get_container_by_number(int container_number);
    std::string get_report_string() const {
        std::string report;
        for (const auto& container : containers) {
            report += "Container Number: " + std::to_string(container.get_container_number()) + "\n";
        }
        return report;
    }
    // Переопределение оператора сравнения для класса Warehouse
    bool operator==(const Warehouse& other) const {
        // Сравнение по размерам, температуре и списку контейнеров
        return dimensions == other.dimensions &&
               temperature == other.temperature &&
               containers == other.containers;
    }
    const Size& get_dimensions() const;
    virtual ~Warehouse() = default; // Виртуальный деструктор
    int get_number() const;
    void set_number(int new_number);
};
*/


//Tree


class Warehouse {
private:
    int number;
    Size dimensions;
    Temperature temperature;
    //Tree<3, Container*> containerTree; // K-D tree to store Container objects

public:
    Tree<3, Container*> containerTree; // K-D tree to store Container objects
    
    Tree<3, Container*>::Node* getTreeRoot() const {
        return containerTree.getRoot();
    }
    Warehouse() = default;
    Warehouse(int number, Size size, Temperature temp);
    
    Container* search_container(const Position& position);

    void add_container_hand(const Container& container, const Position& position);
    void move_container(const Position& position, const Position& new_position);
    void rotate_container(const Position& position, Orientation orientation);
    void remove_container(const Position& position);

    /*bool is_position_free(const Position& position, const Size& container_size, int container_weight) const;
    Position find_suitable_position(const Size& container_size) const;*/
    int proc_thread(Container* container,int l, int h, int w0, int w1);
    void add_container_automatically(Container* container);
    void add_container_automatically_mp(Container* container);

    int get_maximal_containers_size(const Size& size) const;

    void set_dimensions(const Size& new_dimensions);
    
    void get_all_containers_report() const;
    
    bool operator==(const Warehouse& other) const {
        // Сравнение по размерам, температуре 
        return dimensions == other.dimensions &&
               temperature == other.temperature;
    }
    
    const Size& get_dimensions() const;
    virtual ~Warehouse() = default;
    int get_number() const;
    void set_number(int new_number);

    
};



#endif
