#include <algorithm>
#include <iostream>
#include <thread>
#include <mutex>

#include "Warehouse.h"
//list
/*
Warehouse::Warehouse(int number, Size size, Temperature temp)
    : number(number), dimensions(size), temperature(temp) {
    containers = std::list<Container>(100);
}



std::list<Container>::iterator Warehouse::find_container_by_number(int container_number) {
    // Используем алгоритм std::find_if для поиска контейнера с указанным номером
    return std::find_if(containers.begin(), containers.end(),
                        [container_number](const Container& c) {
                            std::cout << "find\n";
                            return c.get_container_number() == container_number;
                        });
}

void Warehouse::add_container_hand(const Container& container, int container_number, const Position& position) {
    // Поиск контейнера по его номеру
    std::cout <<"1\n";

    auto it = find_container(container_number);

    if (it == containers.end()) {
        // Контейнера с таким номером нет, добавляем его на склад
        std::cout <<"3\n";
        Container newContainer = container;

        containers.push_back(newContainer);

        // Устанавливаем позицию контейнера
        containers.back().set_position(position);

        // Выводим сообщение о успешном добавлении
        std::cout << "Контейнер успешно добавлен на склад.\n";
    } else {
        // Контейнер с таким номером уже существует
        std::cout << "Ошибка: Контейнер с номером " << container.get_container_number() << " уже существует на складе.\n";
    }
}

void Warehouse::move_container(const Container& container, const Position& new_position) {
    // Поиск контейнера по его номеру
    auto it = find_container_by_number(container.get_container_number());

    if (it != containers.end()) {
        // Контейнер с таким номером найден, перемещаем его на новую позицию
        //преверить место 
        it->set_position(new_position);

        // Выводим сообщение о успешном перемещении
        std::cout << "Контейнер успешно перемещен на новую позицию.\n";
    } else {
        // Контейнер с таким номером не найден
        std::cout << "Ошибка: Контейнер с номером " << container.get_container_number() << " не найден на складе.\n";
    }
}

void Warehouse::rotate_container(const Container& container, Orientation new_orientation) {
    // Поиск контейнера по его номеру
    auto it = find_container_by_number(container.get_container_number());

    if (it != containers.end()) {
        // Контейнер с таким номером найден, поворачиваем его
        //TODO: понять можно ли повернуть
        it->set_orientation(new_orientation);

        // Выводим сообщение о успешном повороте
        std::cout << "Контейнер успешно повернут.\n";
    } else {
        // Контейнер с таким номером не найден
        std::cout << "Ошибка: Контейнер с номером " << container.get_container_number() << " не найден на складе.\n";
    }
}

void Warehouse::remove_container(const Container& container) {
    // Поиск контейнера по его номеру
    auto it = find_container_by_number(container.get_container_number());

    if (it != containers.end()) {
        // Контейнер с таким номером найден, удаляем его
        containers.erase(it);

        // Выводим сообщение о успешном удалении
        std::cout << "Контейнер успешно удален со склада.\n";
    } else {
        // Контейнер с таким номером не найден
        std::cout << "Ошибка: Контейнер с номером " << container.get_container_number() << " не найден на складе.\n";
    }
}

const std::list<Container>& Warehouse::get_report() const {
    return containers;
}

int Warehouse::get_maximal_containers_size(const Size& size, bool allow_rotation) const {
    // Подсчет максимального количества контейнеров указанного размера на складе
    int max_count = 0;

    for (const auto& container : containers) {
        const Size& container_size = container.get_dimensions();

        if ((container_size.equals(size)) || (allow_rotation && (container_size.transpose().equals(size)))) {
            // Размеры контейнера совпадают с заданными или с их транспонированными размерами (если разрешено вращение)
            max_count++;
        }
    }

    return max_count;
}

void Warehouse::set_dimensions(const Size& new_dimensions) {
    dimensions = new_dimensions;
}

const Size& Warehouse::get_dimensions() const {
    return dimensions;
}


bool Warehouse::is_position_free(const Position& position, const Size& container_size, int container_weight) const {
    // Проверяем, свободно ли место для контейнера
    for (const auto& existing_container : containers) {
        const Position& existing_position = existing_container.get_position();
        const Size& existing_size = existing_container.get_dimensions();
        int existing_weight = existing_container.get_weight();

        // Проверяем, перекрываются ли контейнеры
        if (position.get_x() < existing_position.get_x() + existing_size.get_length() &&
            position.get_x() + container_size.get_length() > existing_position.get_x() &&
            position.get_y() < existing_position.get_y() + existing_size.get_width() &&
            position.get_y() + container_size.get_width() > existing_position.get_y() &&
            position.get_z() < existing_position.get_z() + existing_size.get_height() &&
            position.get_z() + container_size.get_height() > existing_position.get_z()) {

            // Контейнеры перекрываются, это место занято

            // Дополнительно проверяем, что масса нового контейнера не превышает массу хрупкого контейнера
            if (existing_container.is_fragile() && container_weight > existing_weight) {
                // Масса нового контейнера больше массы хрупкого контейнера, это место нельзя использовать
                return false;
            }

            // Контейнеры перекрываются, но масса не превышает, продолжаем поиск
            continue;
        }
    }

    // Место свободно
    return true;
}


Position Warehouse::find_suitable_position(const Size& container_size) const {
    // Простая логика поиска свободного места
    for (int x = 0; x <= dimensions.get_length() - container_size.get_length(); ++x) {
        for (int y = 0; y <= dimensions.get_width() - container_size.get_width(); ++y) {
            for (int z = 0; z <= dimensions.get_height() - container_size.get_height(); ++z) {
                Position position(x, y, z);

                // Проверяем, свободно ли это место
                if (is_position_free(position, container_size, 0)) {
                    return position;
                }
            }
        }
    }

    // Если не найдено подходящего места, возвращаем некорректную позицию
    return Position(-1, -1, -1);
}

Position Warehouse::add_container_automatically(Container& container) {
    // Получаем размеры контейнера
    const Size& container_size = container.get_dimensions();

    // Находим подходящее место для контейнера
    Position position = find_suitable_position(container_size);

    // Устанавливаем позицию контейнера
    container.set_position(position);

    // Добавляем контейнер на склад
    containers.push_back(container);

    // Возвращаем позицию, на которую был добавлен контейнер
    return position;
}


Container& Warehouse::get_container_by_number(int container_number) {
    auto it = find_container_by_number(container_number);

    if (it != containers.end()) {
        return *it;
    } else {
        throw std::out_of_range("Container not found with number: " + std::to_string(container_number));
    }
}

int Warehouse::get_number() const {
    return number;
}

void Warehouse::set_number(int new_number) {
    number = new_number;
}
*/

Warehouse::Warehouse(int number, Size size, Temperature temp)
    : number(number), dimensions(size), temperature(temp), containerTree() {}


// Метод для добавления контейнера в рукопашном режиме
void Warehouse::add_container_hand(const Container& container, const Position& position) {
    int keys[3] = {position.get_x(), position.get_y(), position.get_z()};
    auto ptr = containerTree.find(containerTree.getRoot(), keys);
    if (ptr == nullptr) {
        Container* containerPtr = new Container(container);  // Предполагается, что у Container есть копирующий конструктор
        containerTree.root = containerTree.insert(containerTree.getRoot(), keys, &containerPtr);
    }
}

/*void Warehouse::add_container_automatically(Container* container) {
    Position position = container->get_position();
    int keys[3] = {position.get_x(), position.get_y(), position.get_z()};
    //Container* containerPtr = new Container(container);
    containerTree.automatically_insert(keys, &container);
}*/

Container* Warehouse::search_container(const Position& position) {
    int keys[3] = {position.get_x(), position.get_y(), position.get_z()};
    Container** foundContainerPtr = containerTree.search(containerTree.getRoot(), keys);

    if (foundContainerPtr != nullptr) {
        return *foundContainerPtr;  // Возвращаем разыменованный указатель на контейнер
    }

    return nullptr;
}

/*
// Метод для перемещения контейнера
void Warehouse::move_container(const Container& container, const Position& position, const Position& new_position) {
    int keys[3] = {position.get_x(), position.get_y(), position.get_z()};
    Container* containerPtr = new Container(container);  // Предполагается, что у Container есть копирующий конструктор
    if (containerTree.find(containerTree.getRoot(), keys) != nullptr) {
        containerTree.deleteNode(containerTree.getRoot(), keys);  // Удаляем контейнер по старой позиции
        int new_keys[3] = {new_position.get_x(), new_position.get_y(), new_position.get_z()};
        containerTree.insert(containerTree.getRoot(), new_keys, &containerPtr);  // Вставляем контейнер по новой позиции
    }
}

void Warehouse::rotate_container(const Container& container, const Position& position, Orientation orientation) {
    int keys[3] = {position.get_x(), position.get_y(), position.get_z()};
    Container* containerPtr = new Container(container);
    containerPtr->set_orientation(orientation);
    if (containerTree.find(containerTree.getRoot(), keys) != nullptr) {
        containerTree.deleteNode(containerTree.getRoot(), keys);  // Удаляем контейнер по старой позиции
        containerTree.insert(containerTree.getRoot(),keys, &containerPtr);  // Вставляем контейнер по новой позиции
    }
    
} 
*/

void Warehouse::move_container(const Position& position, const Position& new_position) {
    int old_keys[3] = {position.get_x(), position.get_y(), position.get_z()};
    int new_keys[3] = {new_position.get_x(), new_position.get_y(), new_position.get_z()};

    Container** foundContainerPtr = containerTree.search(containerTree.getRoot(), old_keys);

    if (foundContainerPtr != nullptr) {
        Container* containerToMove = *foundContainerPtr;
        containerTree.deleteNode(containerTree.getRoot(), old_keys);
        containerTree.insert(containerTree.getRoot(), new_keys, &containerToMove);
    }
}


void Warehouse::rotate_container(const Position& position, Orientation orientation) {
    int keys[3] = {position.get_x(), position.get_y(), position.get_z()};

    Container** foundContainerPtr = containerTree.search(containerTree.getRoot(), keys);

    if (foundContainerPtr != nullptr) {
        Container* containerToRotate = *foundContainerPtr;
        containerToRotate->set_orientation(orientation);
    }
}



// Метод для удаления контейнера
void Warehouse::remove_container(const Position& position) {
    int keys[3] = {position.get_x(), position.get_y(), position.get_z()};
    containerTree.deleteNode(containerTree.getRoot(), keys);
}


void Warehouse::set_dimensions(const Size& new_dimensions) {
    dimensions = new_dimensions;
}

int Warehouse::get_number() const {
    return number;
}

void Warehouse::set_number(int new_number) {
    number = new_number;
}

const Size& Warehouse::get_dimensions() const {
    return dimensions;
}

int Warehouse::get_maximal_containers_size(const Size& size) const{
    // Подсчет максимального количества контейнеров указанного размера на складе
    int max_count = 0;
    int volume_container = size.get_height() * size.get_length() * size.get_width();
    int volume_warehouse = dimensions.get_height() * dimensions.get_length() * dimensions.get_width();
    max_count = volume_warehouse / volume_container;

    return max_count;
}

void Warehouse::get_all_containers_report() const {
    // Вызываем метод traverse на корне дерева
    containerTree.traverse(containerTree.getRoot());
}




void Warehouse::add_container_automatically(Container* container) {

    auto ptr = containerTree.getRoot();
    for (int h = 0; h < dimensions.get_height() - container->get_dimensions().get_height(); h++) {
        for (int i = 0; i < dimensions.get_length() - container->get_dimensions().get_length(); i++) {
            for (int j = 0; j < dimensions.get_width() - container->get_dimensions().get_width(); j++) {
                int keys[3] = {i, j, h};
                ptr = containerTree.find(containerTree.getRoot(), keys);
                if (ptr == nullptr) {
                    containerTree.root = containerTree.insert(containerTree.getRoot(), keys, &container);
                    return;
                }
            }
        }
    }
}

int Warehouse::proc_thread(Container* container,int l, int h, int w0, int w1)
{
    auto ptr = containerTree.getRoot();
            for (int j = w0; j < w1; j++) {
                int keys[3] = {l, j, h};
                    ptr = containerTree.find(containerTree.getRoot(), keys);
                    if (ptr == nullptr) {
                        return j;
                    }
            }
    return -1;
}

void Warehouse::add_container_automatically_mp(Container* container) {
    auto threadNum = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(threadNum);
    int w = (int)(dimensions.get_length() - container->get_dimensions().get_length()) / (int)threadNum + 1;

    for (int h = 0; h < dimensions.get_height() - container->get_dimensions().get_height(); h++) {
        for (int l = 0; l < dimensions.get_length() - container->get_dimensions().get_length(); l++) {
            int *res = new int;
            *res = -1;
            for (int i = 0; i < (int) threadNum; i++) {
                int w0 = (int) (i * w);
                int w1 = w0 + w;
                threads[i] = std::thread(
                        [=]() {
                            if (*res == -1) {
                                *res = proc_thread(container, l, h, w0, w1);
                            }
                        });
            }
            for (auto &th: threads) {
                th.join();
            }
            if (*res != -1) {
                int keys[3] = {l, h, *res};
                containerTree.root = containerTree.insert(containerTree.getRoot(), keys, &container);
                return;
            }
        }
    }

}