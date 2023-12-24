#include "ContainerType.h"

std::string ContainerTypeUtil::to_string(ContainerType type) {
    switch (type) {
        case ContainerType::STANDARD:
            return "Standard";
        case ContainerType::COOLED:
            return "Cooled";
        case ContainerType::FRAGILE:
            return "Fragile";
        default:
            return "Unknown";
    }
}