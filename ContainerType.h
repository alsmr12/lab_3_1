#ifndef CONTAINERTYPE_H
#define CONTAINERTYPE_H

#include <string>

enum class ContainerType {
    STANDARD,
    COOLED,
    FRAGILE
};

class ContainerTypeUtil {
public:
    static std::string to_string(ContainerType type);
};

#endif