#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include <vector>

#include "Temperature.h"
#include "Size.h"
#include "Position.h"
#include "Container.h"
#include "Cooled_Container.h"
#include "Fragile_Container.h"
#include "Warehouse.h"
#include "Terminal.h"


TEST_CASE("Temperature: конструктор и геттер") {
    Temperature temp(25);
    REQUIRE(temp.get_temperature() == 25);
}

TEST_CASE("Temperature: отрицательная температура") {
    Temperature temp(-5);
    REQUIRE(temp.get_temperature() == -5);
}

TEST_CASE("Size: конструктор и геттеры") {
    Size size(10, 20, 30);
    REQUIRE(size.get_length() == 10);
    REQUIRE(size.get_width() == 20);
    REQUIRE(size.get_height() == 30);
}

TEST_CASE("Size: transpose") {
    Size size(10, 20, 30);
    Size transposed = size.transpose();
    REQUIRE(transposed.get_length() == 20);
    REQUIRE(transposed.get_width() == 10);
    REQUIRE(transposed.get_height() == 30);
}

TEST_CASE("Size: equals") {
    Size size1(10, 20, 30);
    Size size2(10, 20, 30);
    REQUIRE(size1.equals(size2));

    Size size3(5, 10, 15);
    REQUIRE(!size1.equals(size3));
}

TEST_CASE("Position: конструктор и геттеры") {
    Position pos(3, 4, 5);
    REQUIRE(pos.get_x() == 3);
    REQUIRE(pos.get_y() == 4);
    REQUIRE(pos.get_z() == 5);
}

TEST_CASE("Position: set_x, set_y, set_z") {
    Position pos(1, 2, 3);
    pos.set_x(4);
    pos.set_y(5);
    pos.set_z(6);
    REQUIRE(pos.get_x() == 4);
    REQUIRE(pos.get_y() == 5);
    REQUIRE(pos.get_z() == 6);
}


TEST_CASE("Container: конструктор и геттеры") {
    Size size(10, 20, 30);
    Position position(1, 2, 3);
    Container container(1, "Client", size, 100, 50, position);
    REQUIRE(container.get_container_number() == 1);
    REQUIRE(container.get_information_container() == "Container Number: 1\nClient: Client\nSize: 10x20x30\nCost: 100\nWeight: 50");
    REQUIRE(container.get_weight() == 50);
    REQUIRE(container.get_cost() == 100);
    REQUIRE(!container.is_fragile());
}

TEST_CASE("Cooled_Container: конструктор и геттеры") {
    Size size(10, 20, 30);
    Position position(1, 2, 3);
    Temperature temp(5);
    Cooled_Container cooledContainer(2, "CoolingClient", size, 150, 70, temp, position);

    REQUIRE(cooledContainer.get_container_number() == 2);
    REQUIRE(cooledContainer.get_information_container() == "Container Number: 2\nClient: CoolingClient\nSize: 10x20x30\nCost: 150\nWeight: 70\nMaximum Temperature: 5");
    REQUIRE(cooledContainer.get_weight() == 70);
    REQUIRE(cooledContainer.get_cost() == 150);
    REQUIRE(!cooledContainer.is_fragile());
}

TEST_CASE("Fragile_Container: конструктор и геттеры") {
    Size size(10, 20, 30);
    Position position(1, 2, 3);
    Fragile_Container fragileContainer(3, "FragileClient", size, 200, 90, 500, position);

    REQUIRE(fragileContainer.get_container_number() == 3);
    REQUIRE(fragileContainer.get_information_container() == "Container Number: 3\nClient: FragileClient\nSize: 10x20x30\nCost: 200\nWeight: 90\nMaximum Load: 500");
    REQUIRE(fragileContainer.get_container_type() == "Fragile");
    REQUIRE(fragileContainer.get_weight() == 90);
    REQUIRE(fragileContainer.get_cost() == 200);
    
    REQUIRE(fragileContainer.is_fragile());
}

/*
TEST_CASE("Warehouse operations", "[Warehouse]") {
    SECTION("Add container by hand") {
        Warehouse warehouse(Size(10, 10, 10), 27);
        Container container(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));

        warehouse.add_container_hand(container, Position(1, 1, 1));

        REQUIRE(warehouse.get_report().size() == 1);
    }

    SECTION("Move container") {
        Warehouse warehouse(Size(10, 10, 10), 27);
        Container container(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));

        warehouse.add_container_hand(container, Position(1, 1, 1));
        warehouse.move_container(container, Position(2, 2, 2));

        const auto& report = warehouse.get_report();
        REQUIRE(report.size() == 1);
    }

    SECTION("Rotate container") {
        Warehouse warehouse(Size(10, 10, 10), 27);
        Container container(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));

        warehouse.add_container_hand(container, Position(1, 1, 1));
        warehouse.rotate_container(container, Orientation::LEFT);

        const auto& report = warehouse.get_report();
        REQUIRE(report.size() == 1);
        REQUIRE(report.front().get_orientation() == Orientation::LEFT);
    }

    SECTION("Remove container") {
        Warehouse warehouse(Size(10, 10, 10), 27);
        Container container(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));

        warehouse.add_container_hand(container, Position(1, 1, 1));
        warehouse.remove_container(container);

        REQUIRE(warehouse.get_report().empty());
    }

    SECTION("Get maximal containers size") {
        Warehouse warehouse(Size(10, 10, 10), 27);
        Container container1(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));
        Container container2(2, "Client2", Size(2, 2, 2), 100, 50, Position(0, 0, 0));
        Container container3(3, "Client3", Size(3, 3, 3), 100, 50, Position(0, 0, 0));

        warehouse.add_container_hand(container1, Position(1, 1, 1));
        warehouse.add_container_hand(container2, Position(4, 4, 4));
        warehouse.add_container_hand(container3, Position(7, 7, 7));

        REQUIRE(warehouse.get_maximal_containers_size(Size(2, 2, 2), false) == 2);
        REQUIRE(warehouse.get_maximal_containers_size(Size(2, 2, 2), true) == 2);
    }

    SECTION("Find container by number") {
        Warehouse warehouse(Size(10, 10, 10), 27);
        Container container1(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));
        Container container2(2, "Client2", Size(3, 3, 3), 100, 50, Position(0, 0, 0));

        warehouse.add_container_hand(container1, Position(1, 1, 1));
        warehouse.add_container_hand(container2, Position(4, 4, 4));

        auto found_container1 = warehouse.find_container_by_number(1);
        auto found_container2 = warehouse.find_container_by_number(2);
        auto not_found_container = warehouse.find_container_by_number(3);

        REQUIRE(found_container1 != warehouse.get_report().end());
        REQUIRE(found_container2 != warehouse.get_report().end());
        REQUIRE(not_found_container == warehouse.get_report().end());
    }

    SECTION("Set dimensions") {
        Warehouse warehouse(Size(10, 10, 10), 27);

        warehouse.set_dimensions(Size(15, 15, 15));

        REQUIRE(warehouse.get_dimensions() == Size(15, 15, 15));
    }

}
*/
/*

TEST_CASE("Test add_container_hand", "[Warehouse]") {
    Warehouse warehouse(Size(10, 10, 10), Temperature(25));
    Container container(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));

    SECTION("Adding a container by hand") {
        warehouse.add_container_hand(container, Position(0, 0, 0));
        REQUIRE(warehouse.get_report().size() == 0);
    }
}

TEST_CASE("Test move_container", "[Warehouse]") {
    Warehouse warehouse(Size(10, 10, 10), Temperature(25));
    Container container(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));

    SECTION("Moving an existing container") {
        warehouse.add_container_hand(container, Position(0, 0, 0));
        warehouse.move_container(container, Position(1, 1, 1));
        REQUIRE(warehouse.get_report().front().get_position() == Position(1, 1, 1));
    }

    SECTION("Moving a non-existing container") {
        REQUIRE_THROWS_AS(warehouse.move_container(container, Position(1, 1, 1)), std::runtime_error);
    }
}

// Продолжение файла с тестами...

TEST_CASE("Test rotate_container", "[Warehouse]") {
    Warehouse warehouse(Size(10, 10, 10), Temperature(25));
    Container container(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));

    SECTION("Rotate an existing container") {
        warehouse.add_container_hand(container, Position(0, 0, 0));
        warehouse.rotate_container(container, Orientation::RIGHT);
        REQUIRE(warehouse.get_report().front().get_orientation() == Orientation::RIGHT);
    }

    SECTION("Rotate a non-existing container") {
        REQUIRE_THROWS_AS(warehouse.rotate_container(container, Orientation::RIGHT), std::runtime_error);
    }
}

TEST_CASE("Test remove_container", "[Warehouse]") {
    Warehouse warehouse(Size(10, 10, 10), Temperature(25));
    Container container(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));

    SECTION("Remove an existing container") {
        warehouse.add_container_hand(container, Position(0, 0, 0));
        warehouse.remove_container(container);
        REQUIRE(warehouse.get_report().empty());
    }

    SECTION("Remove a non-existing container") {
        REQUIRE_THROWS_AS(warehouse.remove_container(container), std::runtime_error);
    }
}

TEST_CASE("Test find_suitable_position", "[Warehouse]") {
    Warehouse warehouse(Size(10, 10, 10), Temperature(25));
    Container container(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));

    SECTION("Find a suitable position for a container") {
        Position position = warehouse.find_suitable_position(container.get_dimensions());
        REQUIRE(position.get_x() >= 0);
        REQUIRE(position.get_y() >= 0);
        REQUIRE(position.get_z() >= 0);
    }

    
}

TEST_CASE("Test is_position_free", "[Warehouse]") {
    Warehouse warehouse(Size(10, 10, 10), Temperature(25));
    Container container(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));

    SECTION("Check if position is free for a container") {
        REQUIRE(warehouse.is_position_free(Position(0, 0, 0), container.get_dimensions(), 0));
    }

   
}

TEST_CASE("Test get_maximal_containers_size", "[Warehouse]") {
    Warehouse warehouse(Size(10, 10, 10), Temperature(25));
    Container container1(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));
    Container container2(2, "Client2", Size(2, 2, 2), 100, 50, Position(3, 3, 3));

    SECTION("Get maximal containers size for a specific size") {
        warehouse.add_container_hand(container1, Position(0, 0, 0));
        warehouse.add_container_hand(container2, Position(3, 3, 3));
        REQUIRE(warehouse.get_maximal_containers_size(Size(2, 2, 2), false) == 2);
    }

    // Добавьте еще тестов для get_maximal_containers_size
}

TEST_CASE("Test set_dimensions", "[Warehouse]") {
    Warehouse warehouse(Size(10, 10, 10), Temperature(25));

    SECTION("Set dimensions of the warehouse") {
        Size newDimensions(20, 20, 20);
        warehouse.set_dimensions(newDimensions);
        REQUIRE(warehouse.get_dimensions() == newDimensions);
    }
}
*/
/*
TEST_CASE("Terminal operations", "[Terminal]") {
    SECTION("Add warehouse") {
        Terminal terminal;

        Warehouse warehouse1(Size(10, 10, 10), 27);
        Warehouse warehouse2(Size(8, 8, 8), 3);

        terminal.add_warehouse(warehouse1);
        terminal.add_warehouse(warehouse2);

        REQUIRE(terminal.get_warehouses().size() == 2);
    }

    SECTION("Delete warehouse") {
        Terminal terminal;

        Warehouse warehouse1(Size(10, 10, 10), 27);
        Warehouse warehouse2(Size(8, 8, 8), 3);

        terminal.add_warehouse(warehouse1);
        terminal.add_warehouse(warehouse2);

        terminal.delete_warehouse(warehouse1);

        REQUIRE(terminal.get_warehouses().size() == 1);
    }
}
*/

/*TEST_CASE("K-D Tree Operations with ValueType as char", "[Tree]") {
    Tree<2, char> kdTree;

    SECTION("Insertion and Traversal") {
        Tree<2, char>::Node* root = nullptr;

        // Insert elements into the K-D tree
        root = kdTree.insert(root, new int[2]{5, 10}, new char('A'));
        root = kdTree.insert(root, new int[2]{2, 7}, new char('B'));
        root = kdTree.insert(root, new int[2]{8, 4}, new char('C'));
        root = kdTree.insert(root, new int[2]{9, 6}, new char('D'));
        root = kdTree.insert(root, new int[2]{3, 1}, new char('E'));

        // Verify traversal order
        std::ostringstream oss;
        std::streambuf* coutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        kdTree.traverse(root);

        std::cout.rdbuf(coutBuffer);

        REQUIRE(oss.str() == "Keys: [3 1 ], Info: E\nKeys: [2 7 ], Info: B\nKeys: [5 10 ], Info: A\nKeys: [8 4 ], Info: C\nKeys: [9 6 ], Info: D\n");

       
    }

    SECTION("Search in Range") {
        Tree<2, char>::Node* root = nullptr;

        // Insert elements into the K-D tree
        root = kdTree.insert(root, new int[2]{5, 10}, new char('A'));
        root = kdTree.insert(root, new int[2]{2, 7}, new char('B'));
        root = kdTree.insert(root, new int[2]{8, 4}, new char('C'));
        root = kdTree.insert(root, new int[2]{9, 6}, new char('D'));
        root = kdTree.insert(root, new int[2]{3, 1}, new char('E'));

        // Search for elements in the range [4, 8] along the first axis and [5, 10] along the second axis
        std::ostringstream oss;
        std::streambuf* coutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        kdTree.searchInRange(root, new int[2]{4, 5}, new int[2]{8, 10});

        std::cout.rdbuf(coutBuffer);

        REQUIRE(oss.str() == "Keys: [5 10 ], Info: A\n");


    }

    SECTION("Deletion") {
        Tree<2, char>::Node* root = nullptr;

        // Insert elements into the K-D tree
        root = kdTree.insert(root, new int[2]{5, 10}, new char('A'));
        root = kdTree.insert(root, new int[2]{2, 7}, new char('B'));
        root = kdTree.insert(root, new int[2]{8, 4}, new char('C'));
        root = kdTree.insert(root, new int[2]{9, 6}, new char('D'));
        root = kdTree.insert(root, new int[2]{3, 1}, new char('E'));

        // Delete an element from the K-D tree
        root = kdTree.deleteNode(root, new int[2]{8, 4});

        // Verify the remaining elements after deletion
        std::ostringstream oss;
        std::streambuf* coutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        kdTree.traverse(root);

        std::cout.rdbuf(coutBuffer);

        REQUIRE(oss.str() == "Keys: [3 1 ], Info: E\nKeys: [2 7 ], Info: B\nKeys: [5 10 ], Info: A\nKeys: [9 6 ], Info: D\n");

    }
}*/


/*TEST_CASE("Add container in hand mode", "[add_container_hand]") {
    Warehouse warehouse;

    // Create a sample container
    Size containerSize(10, 5, 3);
    Container container(1, "ClientName", containerSize, 100, 500, Position(0, 0, 0));
    Position position(1, 2, 3);

    // Check that the tree is initially empty
    REQUIRE(warehouse.containerTree.getRoot() != nullptr);

    // Add the container in hand mode
    warehouse.add_container_hand(container, position);

    // Check that the tree is not empty after adding the container
    REQUIRE(warehouse.containerTree.getRoot() != nullptr);

    // Check that the added container exists in the tree
    int keys[3] = {position.get_x(), position.get_y(), position.get_z()};
    auto foundNode = warehouse.containerTree.find(warehouse.containerTree.getRoot(), keys);
    REQUIRE(foundNode != nullptr);
    //REQUIRE(foundNode->i.info != nullptr);

}*/

/*
TEST_CASE("Remove container from Warehouse", "[remove_container]") {
    Warehouse warehouse;

    // Create a sample container
    Size containerSize(10, 5, 3);
    Container container(1, "ClientName", containerSize, 100, 500, Position(1, 2, 3));
    Position position(1, 2, 3);

   
    REQUIRE(warehouse.containerTree.getRoot() != nullptr);

    // Add the container in hand mode
    warehouse.add_container_hand(container, position);

    // Check that the tree is not empty after adding the container
    REQUIRE(warehouse.containerTree.getRoot() != nullptr);


    warehouse.remove_container(position);

    int keys[3] = {position.get_x(), position.get_y(), position.get_z()};
    auto foundNode = warehouse.containerTree.find(warehouse.containerTree.getRoot(), keys);
    REQUIRE(foundNode == nullptr);

}
*/

/*TEST_CASE("Move container", "[move_container]") {
    Warehouse warehouse;

    // Create a sample container
    Size containerSize(10, 5, 3);
    Container container(1, "ClientName", containerSize, 100, 500, Position(0, 0, 0));
    Position position(1, 2, 3);

    // Check that the tree is initially empty
    REQUIRE(warehouse.containerTree.getRoot() != nullptr);

    // Add the container in hand mode
    warehouse.add_container_hand(container, position);

    // Check that the tree is not empty after adding the container
    REQUIRE(warehouse.containerTree.getRoot() != nullptr);

    Position new_position(1, 1, 1);

    //warehouse.move_container(container, position, new_position);

    int k[3] = {new_position.get_x(), new_position.get_y(), new_position.get_z()};
    auto f = warehouse.containerTree.find(warehouse.containerTree.getRoot(), k);
    REQUIRE(f != nullptr);
    REQUIRE(f->info != nullptr);

}*/
/*
TEST_CASE("Rotate container", "[rotate_container]") {
    Warehouse warehouse;

    // Create a sample container
    Size containerSize(10, 5, 3);
    Container container(1, "ClientName", containerSize, 100, 500, Position(0, 0, 0));
    Position position(1, 2, 3);

    // Check that the tree is initially empty
    REQUIRE(warehouse.containerTree.getRoot() != nullptr);

    // Add the container in hand mode
    warehouse.add_container_hand(container, position);

    // Check that the tree is not empty after adding the container
    REQUIRE(warehouse.containerTree.getRoot() != nullptr);

    Orientation o;
    o = Orientation::UP;

    //warehouse.rotate_container(container, position, o);

    int k[3] = {position.get_x(), position.get_y(), position.get_z()};
    auto f = warehouse.containerTree.find(warehouse.containerTree.getRoot(), k);
    REQUIRE(f != nullptr);
    REQUIRE(f->info != nullptr);

}*/


TEST_CASE("Maximal containers size"){
    SECTION("get_maximal_containers_size") {
        Warehouse warehouse(1, Size(10, 10, 10), 27);
        Container container1(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));
        Container container2(2, "Client2", Size(2, 2, 2), 100, 50, Position(0, 0, 0));
        Container container3(3, "Client3", Size(3, 3, 3), 100, 50, Position(0, 0, 0));

        warehouse.add_container_hand(container1, Position(1, 1, 1));
        warehouse.add_container_hand(container2, Position(4, 4, 4));
        warehouse.add_container_hand(container3, Position(7, 7, 7));

        REQUIRE(warehouse.get_maximal_containers_size(Size(2, 2, 2)) == 125);
        
    }
}
/*
TEST_CASE("Warehouse add_container_automatically test", "[add_container_automatically]") {
    SECTION("Adding container to an empty warehouse") {
        Warehouse warehouse(1, Size(10, 10, 10), 27);
        Container container(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));
        Container container2(2, "Client2", Size(2, 2, 2), 100, 50, Position(0, 0, 0));
        Container container3(3, "Client3", Size(3, 3, 3), 100, 50, Position(0, 0, 0));
        
        REQUIRE(warehouse.getTreeRoot() == nullptr);  // Ensure the warehouse is initially empty
        warehouse.add_container_hand(container3, Position(1, 1, 1));
        warehouse.add_container_automatically(&container);
        REQUIRE(warehouse.getTreeRoot() == nullptr);
        
    }

    SECTION("Adding container to a non-empty warehouse") {
        Warehouse warehouse(1, Size(10, 10, 10), 27);
        Container container1(1, "Client1", Size(2, 2, 2), 100, 50, Position(0, 0, 0));
        Container container2(2, "Client2", Size(2, 2, 2), 100, 50, Position(0, 0, 0));
        Container container3(3, "Client3", Size(3, 3, 3), 100, 50, Position(0, 0, 0));

        warehouse.add_container_hand(container3, Position(1, 1, 1));

        warehouse.add_container_automatically(&container1);

        warehouse.add_container_automatically(&container2);

        REQUIRE(warehouse.getTreeRoot() == nullptr);  // Ensure the second container is added
    }
}


TEST_CASE("Terminal find_warehouse_by_number test", "[find_warehouse_by_number]") {
    Terminal terminal;

    SECTION("Finding warehouse by number in an empty terminal") {
        REQUIRE(terminal.find_warehouse_by_number(1) == nullptr);  // Ensure nullptr is returned for an empty terminal
    }

    SECTION("Finding existing warehouse by number") {
        Warehouse warehouse(1, Size(10, 10, 10), 27);
        terminal.add_warehouse(warehouse, 1);

        REQUIRE(terminal.find_warehouse_by_number(1) != nullptr);  // Ensure the existing warehouse is found
    }

    SECTION("Finding non-existing warehouse by number") {
        Warehouse warehouse(1, Size(10, 10, 10), 27);
        terminal.add_warehouse(warehouse, 1);

        REQUIRE(terminal.find_warehouse_by_number(2) == nullptr);  // Ensure nullptr is returned for a non-existing warehouse
    }
}

TEST_CASE("Terminal add_warehouse test", "[add_warehouse]") {
    Terminal terminal;

    SECTION("Adding a new warehouse to an empty terminal") {
        Warehouse warehouse(1, Size(10, 10, 10), 27);
        terminal.add_warehouse(warehouse, 1);

        REQUIRE(terminal.find_warehouse_by_number(1) != nullptr);  // Ensure the warehouse is added to an empty terminal
    }

    SECTION("Adding a new warehouse with a unique number") {
        Warehouse warehouse(1, Size(10, 10, 10), 27);
        terminal.add_warehouse(warehouse, 1);

        REQUIRE(terminal.find_warehouse_by_number(1) != nullptr);  // Ensure the first warehouse is added

        Warehouse warehouse2(2, Size(15, 15, 15), 27);
        terminal.add_warehouse(warehouse2, 2);

        REQUIRE(terminal.find_warehouse_by_number(2) != nullptr);  // Ensure the second warehouse is added
    }

    SECTION("Adding a new warehouse with a non-unique number") {
        Warehouse warehouse(1, Size(10, 10, 10), 27);
        terminal.add_warehouse(warehouse, 1);

        REQUIRE(terminal.find_warehouse_by_number(1) != nullptr);  // Ensure the first warehouse is added

        Warehouse warehouse2(2, Size(15, 15, 15), 27);
        terminal.add_warehouse(warehouse2, 1);

        REQUIRE(terminal.find_warehouse_by_number(1) != nullptr);  // Ensure the second warehouse is not added due to non-unique number
    }
}

TEST_CASE("Terminal change_dimension_warehouse test", "[change_dimension_warehouse]") {
    Terminal terminal;

    SECTION("Changing dimensions of a warehouse that exists") {
        Warehouse warehouse(1, Size(10, 10, 10), 27);
        terminal.add_warehouse(warehouse, 1);

        Size newDimensions(15, 15, 15);
        terminal.change_dimension_warehouse(1, newDimensions);

        REQUIRE(terminal.find_warehouse_by_number(1)->get_dimensions() == newDimensions);
    }

    SECTION("Changing dimensions of a warehouse that does not exist") {
        Size newDimensions(15, 15, 15);
        terminal.change_dimension_warehouse(1, newDimensions);

        REQUIRE(terminal.find_warehouse_by_number(1) == nullptr);
    }

    SECTION("Changing dimensions of multiple warehouses") {
        Warehouse warehouse1(1, Size(10, 10, 10), 27);
        terminal.add_warehouse(warehouse1, 1);

        Warehouse warehouse2(2, Size(20, 20, 20), 27);
        terminal.add_warehouse(warehouse2, 2);

        Size newDimensions1(15, 15, 15);
        Size newDimensions2(25, 25, 25);

        terminal.change_dimension_warehouse(1, newDimensions1);
        terminal.change_dimension_warehouse(2, newDimensions2);

        REQUIRE(terminal.find_warehouse_by_number(1)->get_dimensions() == newDimensions1);
        REQUIRE(terminal.find_warehouse_by_number(2)->get_dimensions() == newDimensions2);
    }
}

TEST_CASE("Terminal delete_warehouse test", "[delete_warehouse]") {
    Terminal terminal;

    SECTION("Deleting an existing warehouse") {
        Warehouse warehouse(1, Size(10, 10, 10),27);
        terminal.add_warehouse(warehouse, 1);

        terminal.delete_warehouse(1);

        REQUIRE(terminal.find_warehouse_by_number(1) == nullptr);
    }

    SECTION("Deleting a non-existing warehouse") {
        terminal.delete_warehouse(1);

        REQUIRE(terminal.find_warehouse_by_number(1) == nullptr);
    }

    SECTION("Deleting multiple warehouses") {
        Warehouse warehouse1(1, Size(10, 10, 10),27);
        terminal.add_warehouse(warehouse1, 1);

        Warehouse warehouse2(2, Size(20, 20, 20), 27);
        terminal.add_warehouse(warehouse2, 2);

        terminal.delete_warehouse(1);

        REQUIRE(terminal.find_warehouse_by_number(1) == nullptr);
        REQUIRE(terminal.find_warehouse_by_number(2) != nullptr);

        terminal.delete_warehouse(2);

        REQUIRE(terminal.find_warehouse_by_number(2) == nullptr);
    }
}*/