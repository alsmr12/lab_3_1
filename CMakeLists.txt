# Установка версии CMake
cmake_minimum_required(VERSION 3.16)

# Название проекта (обязательно)
project(lab_3)

# Установка стандарта языка - C++20
set(CMAKE_CXX_STANDARD 20)

# Установка флагов компилятора: CMAKE_CXX_FLAGS += -Wall -Wextra
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")



add_library(Container Container.h Container.cpp)
add_library(ContainerType ContainerType.h ContainerType.cpp)
add_library(Cooled_Container Cooled_Container.h Cooled_Container.cpp)
add_library(Fragile_Container Fragile_Container.h Fragile_Container.cpp)
add_library(Position Position.h Position.cpp)
add_library(Size Size.h Size.cpp)
add_library(Temperature Temperature.h Temperature.cpp)
add_library(Warehouse Warehouse.h Warehouse.cpp)
add_library(Terminal Terminal.h Terminal.cpp)
#add_library(Tree Tree.h)

add_library(catch_amalgamated catch_amalgamated.hpp catch_amalgamated.cpp)

# Создание исполняемого файла и линковка с библиотеками
add_executable(bin main.cpp)

# Линковка библиотек с исполняемым файлом bin
target_link_libraries(bin Container)
target_link_libraries(bin ContainerType)
target_link_libraries(bin Cooled_Container)
target_link_libraries(bin Fragile_Container)
target_link_libraries(bin Position)
target_link_libraries(bin Size)
target_link_libraries(bin Temperature)
target_link_libraries(bin Warehouse)
target_link_libraries(bin Terminal)
#target_link_libraries(bin Tree)

add_executable(t test.cpp)
target_link_libraries(t Container)
target_link_libraries(t ContainerType)
target_link_libraries(t Cooled_Container)
target_link_libraries(t Fragile_Container)
target_link_libraries(t Position)
target_link_libraries(t Size)
target_link_libraries(t Temperature)
target_link_libraries(t Warehouse)
target_link_libraries(t Terminal)
target_link_libraries(t catch_amalgamated)


# Для сборки из консоли:
#
# mkdir build   # Создание директории для файлов сборки
# cd build      # Переход в директорию сборки
# cmake ..      # Генерация файлов сборки на основе CMakeLists.txt
# make          # Сборка проекта
