#include <iostream>
#include <stdexcept>
#include "Terminal.h"
#include "Warehouse.h"

// Вспомогательная функция для ввода Size
Size inputSize() {
    Size size;
    std::cout << "Enter size (length width height): ";
    std::cin >> size;
    return size;
}

// Вспомогательная функция для ввода Position
Position inputPosition() {
    Position position;
    std::cout << "Enter position (x y z): ";
    std::cin >> position;
    return position;
}

// Вспомогательная функция для ввода Temperature
Temperature inputTemperature() {
    Temperature temperature;
    std::cout << "Enter temperature: ";
    std::cin >> temperature;
    return temperature;
}

// Вспомогательная функция для ввода Container
Container inputContainer() {
    int containerNumber, containerWeight, cost;
    Size containerSize;
    Position newPosition;
    std::string client;

    std::cout << "Enter container number: ";
    std::cin >> containerNumber;

    containerSize = inputSize();

    newPosition = {0,0,0};

    std::cout << "Enter container weight: ";
    std::cin >> containerWeight;

    std::cout << "Enter container cost: ";
    std::cin >> cost;

    std::cout << "Enter container client: ";
    std::cin >> client;

    return Container(containerNumber, client, containerSize, cost, containerWeight, newPosition);
}
void performWarehouseActions(Warehouse& warehouse) {
    while (true) {
        // Выводим подменю для работы с конкретным складом
        std::cout << "\nWarehouse Menu:\n";
        std::cout << "1. Add a new container\n";
        std::cout << "2. Move a container to a specified position\n";
        std::cout << "3. Rotate a specified container\n";
        std::cout << "4. Remove a specified container\n";
        std::cout << "5. Get a report about all containers on the warehouse\n";
        std::cout << "6. Add a container automatically\n";
        std::cout << "7. Get the maximal number of containers of a specified size\n";
        std::cout << "8. Return to the main menu\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    // Add a new container
                    Container newContainer = inputContainer();
                    Position newPosition = inputPosition();
                    warehouse.add_container_hand(newContainer, newPosition);
                    break;
                }
                case 2: {
                    // Move a container to a specified position
                    /*
                    int containerNumber;
                    Position newPosition;

                    std::cout << "Enter container number: ";
                    std::cin >> containerNumber;

                    std::cout << "Enter new position (x y z): ";
                    std::cin >> newPosition;

                    warehouse.move_container(containerNumber, newPosition);
                     */
                    break;
                }
                case 3: {
                    // Rotate a specified container
                    Position pos;
                    int newOrientation;

                    pos = inputPosition();

                    std::cout << "Enter new orientation (0 - UP, 1 - DOWN, 2 - LEFT, 3 - RIGHT, 4 - FRONT, 5 - BACK): ";
                    std::cin >> newOrientation;

                    Orientation orientation;
                    switch (newOrientation) {
                        case 0:
                            orientation = Orientation::UP;
                            break;
                        case 1:
                            orientation = Orientation::DOWN;
                            break;
                        case 2:
                            orientation = Orientation::LEFT;
                            break;
                        case 3:
                            orientation = Orientation::RIGHT;
                            break;
                        case 4:
                            orientation = Orientation::FRONT;
                            break;
                        case 5:
                            orientation = Orientation::BACK;
                            break;
                        default:
                            std::cerr << "Invalid orientation input!" << std::endl;
                            return;
                    }

                    warehouse.rotate_container(pos, orientation);
                    break;
                }
                case 4: {
                    // Remove a specified container
                    Position newPosition = inputPosition();
                    warehouse.remove_container(newPosition);
                    break;
                }
                case 5: {
                    // Get a report about all containers on the warehouse
                    warehouse.get_all_containers_report();
                    break;
                }
                case 6: {
                    // Add a container automatically
                    Container newContainer = inputContainer();
                    warehouse.add_container_automatically_mp(&newContainer);
                    std::cout << "Added container to position" << "\n";
                    break;
                }
                case 7: {
                    // Get the maximal number of containers of a specified size
                    Size maxSize = inputSize();
                    bool allowRotation;

                    std::cout << "Allow rotation? (0 for No, 1 for Yes): ";
                    std::cin >> allowRotation;

                    int maxCount = warehouse.get_maximal_containers_size(maxSize);
                    std::cout << "Maximal number of containers of specified size: " << maxCount << "\n";
                    break;
                }
                case 8: {
                    // Return to the main menu
                    return;
                }
                default: {
                    std::cout << "Invalid choice. Please enter a valid option.\n";
                    break;
                }
            }
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}


/*
void performWarehouseActions(Warehouse& warehouse) {
    while (true) {
        // Выводим подменю для работы с конкретным складом
        std::cout << "\nWarehouse Menu:\n";
        std::cout << "1. Add a new container\n";
        std::cout << "2. Move a container to a specified position\n";
        std::cout << "3. Rotate a specified container\n";
        std::cout << "4. Remove a specified container\n";
        std::cout << "5. Get a report about all containers on the warehouse\n";
        std::cout << "6. Add a container automatically\n";
        std::cout << "7. Get the maximal number of containers of a specified size\n";
        std::cout << "8. Return to the main menu\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    // Add a new container
                    int containerNumber;
                    Size containerSize;
                    int containerWeight;
                    Position newPosition;
                    int cost;
                    std::string client;

                    std::cout << "Enter container number: ";
                    std::cin >> containerNumber;

                    std::cout << "Enter container size (length width height): ";
                    std::cin >> containerSize;

                    std::cout << "Enter new position (x y z): ";
                    std::cin >> newPosition;

                    std::cout << "Enter container weight: ";
                    std::cin >> containerWeight;

                    std::cout << "Enter container cost: ";
                    std::cin >> cost;

                    std::cout << "Enter container client: ";
                    std::cin >> client;

                    
                    Container newContainer(containerNumber, client, containerSize, cost, containerWeight, newPosition);
                    warehouse.add_container_hand(newContainer, newPosition);
                    

                    break;
                }
                case 2: {
                    // Move a container to a specified position
                    int containerNumber;
                    Position newPosition;

                    std::cout << "Enter container number: ";
                    std::cin >> containerNumber;

                    std::cout << "Enter new position (x y z): ";
                    std::cin >> newPosition;

                    //warehouse.move_container(warehouse.get_container_by_number(containerNumber), newPosition);
                    break;
                }
                case 3: {
                    // Rotate a specified container
                    int containerNumber;
                    int newOrientation;

                    std::cout << "Enter container number: ";
                    std::cin >> containerNumber;
                    std::cout << "Enter new orientation (0 - UP, 1 - DOWN, 2 - LEFT, 3 - RIGHT, 4 - FRONT, 5 - BACK): ";
                    std::cin >> newOrientation;

                    // Convert integer input to Orientation enum
                    Orientation orientation;
                    switch (newOrientation) {
                        case 0:
                            orientation = Orientation::UP;
                            break;
                        case 1:
                            orientation = Orientation::DOWN;
                            break;
                        case 2:
                            orientation = Orientation::LEFT;
                            break;
                        case 3:
                            orientation = Orientation::RIGHT;
                            break;
                        case 4:
                            orientation = Orientation::FRONT;
                            break;
                        case 5:
                            orientation = Orientation::BACK;
                            break;
                        default:
                            std::cerr << "Invalid orientation input!" << std::endl;
                            return;
                        }

                    warehouse.rotate_container(, orientation);
                    break;
                }           

                case 4: {
                    // Remove a specified container
                    
                    int containerNumber;
                    std::cout << "Enter container number: ";
                    std::cin >> containerNumber;
                    
                    Position newPosition;
                    std::cout << "Enter position (x y z): ";
                    std::cin >> newPosition;


                    warehouse.remove_container(newPosition);
                    break;
                }
                case 5: {
                    // Get a report about all containers on the warehouse
                    std::cout << warehouse.get_all_containers_report() << "\n";
                    break;
                }
                case 6: {
                    // Add a container automatically
                    Container newContainer;
                    Position newPosition = warehouse.add_container_automatically(newContainer);
                    std::cout << "Added container to position: " << newPosition << "\n";
                    break;
                }
                case 7: {
                    // Get the maximal number of containers of a specified size
                    Size maxSize;
                    bool allowRotation;

                    std::cout << "Enter maximum size (length width height): ";
                    std::cin >> maxSize;

                    std::cout << "Allow rotation? (0 for No, 1 for Yes): ";
                    std::cin >> allowRotation;

                    int maxCount = warehouse.get_maximal_containers_size(maxSize, allowRotation);
                    std::cout << "Maximal number of containers of specified size: " << maxCount << "\n";
                    break;
                }
                case 8: {
                    // Return to the main menu
                    return;
                }
                default: {
                    std::cout << "Invalid choice. Please enter a valid option.\n";
                    break;
                }
            }
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}
*/

int main() {
    Terminal terminal;
    while (true) {
        // Выводим меню
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Add a new warehouse\n";
        std::cout << "2. Delete an existing warehouse\n";
        std::cout << "3. Change dimensions of an existing warehouse\n";
        std::cout << "4. Show all information about the terminal\n";
        std::cout << "5. Access a warehouse\n";  // Добавили новый пункт
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    // Add a new warehouse
                    Size dimensions;
                    Temperature temperature;
                    int number;

                    std::cout << "Enter warehouse dimensions (length width height): ";
                    std::cin >> dimensions;

                    std::cout << "Enter warehouse temperature: ";
                    std::cin >> temperature;

                    std::cout << "Enter warehouse number: ";
                    std::cin >> number;


                    Warehouse newWarehouse(number, dimensions, temperature);
                    terminal.add_warehouse(newWarehouse, number);
                    break;
                }
                case 2: {
                    // Delete an existing warehouse
                    int warehouseIndex;
                    std::cout << "Enter the index of the warehouse to delete: ";
                    std::cin >> warehouseIndex;

                    terminal.delete_warehouse(warehouseIndex);
                    break;
                }
                case 3: {
                    // Change dimensions of an existing warehouse
                    int warehouseIndex;
                    Size newDimensions;

                    std::cout << "Enter the index of the warehouse to change dimensions: ";
                    std::cin >> warehouseIndex;

                    std::cout << "Enter new dimensions (length width height): ";
                    std::cin >> newDimensions;

                    terminal.change_dimension_warehouse(warehouseIndex, newDimensions);
                    break;
                }
                case 4: {
                    // Show all information about the terminal
                    terminal.show_information();
                    break;
                }
                
                case 5: {
                    // Access a warehouse
                    int warehouseIndex;
                    std::cout << "Enter the NUMBER of the warehouse: ";
                    std::cin >> warehouseIndex;

                    // Проверка наличия индекса
                    if (warehouseIndex >= 0) {
                        Warehouse* selectedWarehouse = terminal.find_warehouse_by_number(warehouseIndex);
                        if (selectedWarehouse != nullptr)
                            performWarehouseActions(*selectedWarehouse);
                        else {
                            std::cout << "Invalid warehouse index. Please enter a valid index.\n";
                        }
                    }
                    break;
                }
                case 6: {
                    // Exit the program
                    std::cout << "Exiting the program...\n";
                    return 0;
                }
                default: {
                    std::cout << "Invalid choice. Please enter a valid option.\n";
                    break;
                }
            }

        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }

    }
    return 0;
}